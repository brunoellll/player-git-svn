/*
 *  Player - One Hell of a Robot Server
 *  Copyright (C) 2000  Brian Gerkey   &  Kasper Stoy
 *                      gerkey@usc.edu    kaspers@robotics.usc.edu
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
///////////////////////////////////////////////////////////////////////////
//
// Desc: Gazebo (simulator) position driver
// Author: Andrew Howard
// Date: 6 Apr 2003
// CVS: $Id$
//
///////////////////////////////////////////////////////////////////////////

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>       // for atoi(3)
#include <sys/types.h>
#include <netinet/in.h>

#include "player.h"
#include "error.h"
#include "driver.h"
#include "drivertable.h"

#include "gazebo.h"
#include "gz_client.h"


// Incremental navigation driver
class GzPosition : public Driver
{
  // Constructor
  public: GzPosition(ConfigFile* cf, int section);

  // Destructor
  public: virtual ~GzPosition();

  // Setup/shutdown routines.
  public: virtual int Setup();
  public: virtual int Shutdown();

  // Check for new data
  public: virtual void Update();

  // Commands
  public: virtual void PutCommand(player_device_id_t id,
                                  void* src, size_t len,
                                  struct timeval* timestamp);

  // Request/reply
  public: virtual int PutConfig(player_device_id_t id, void *client, 
                                void* src, size_t len,
                                struct timeval* timestamp);

  // Handle geometry requests
  private: void HandleGetGeom(void *client, void *req, int reqlen);

  // Handle motor configuration
  private: void HandleMotorPower(void *client, void *req, int reqlen);

  // Gazebo id
  private: char *gz_id;

  // Gazebo client object
  private: gz_client_t *client;
  
  // Gazebo Interface
  private: gz_position_t *iface;

  // Timestamp on last data update
  private: double datatime;
};


// Initialization function
Driver* GzPosition_Init(ConfigFile* cf, int section)
{
  if (GzClient::client == NULL)
  {
    PLAYER_ERROR("unable to instantiate Gazebo driver; did you forget the -g option?");
    return (NULL);
  }
  return ((Driver*) (new GzPosition(cf, section)));
}


// a driver registration function
void GzPosition_Register(DriverTable* table)
{
  table->AddDriver("gz_position", GzPosition_Init);
  return;
}


////////////////////////////////////////////////////////////////////////////////
// Constructor
GzPosition::GzPosition(ConfigFile* cf, int section)
    : Driver(cf, section, PLAYER_POSITION_CODE, PLAYER_ALL_MODE,
             sizeof(player_position_data_t), sizeof(player_position_cmd_t), 10, 10)
{
    // Get the globally defined Gazebo client (one per instance of Player)
  this->client = GzClient::client;

  // Get the id of the device in Gazebo.
  // TODO: fix potential buffer overflow
  this->gz_id = (char*) calloc(1024, sizeof(char));
  strcat(this->gz_id, GzClient::prefix_id);
  strcat(this->gz_id, cf->ReadString(section, "gz_id", ""));
  
  // Create an interface
  this->iface = gz_position_alloc();

  this->datatime = -1;

  return;
}


////////////////////////////////////////////////////////////////////////////////
// Destructor
GzPosition::~GzPosition()
{
  gz_position_free(this->iface); 
  return;
}


////////////////////////////////////////////////////////////////////////////////
// Set up the device (called by server thread).
int GzPosition::Setup()
{
  // Open the interface
  if (gz_position_open(this->iface, this->client, this->gz_id) != 0)
    return -1;

  // Add ourselves to the update list
  GzClient::AddDriver(this);

  return 0;
}


////////////////////////////////////////////////////////////////////////////////
// Shutdown the device (called by server thread).
int GzPosition::Shutdown()
{
  // Remove ourselves to the update list
  GzClient::DelDriver(this);

  gz_position_close(this->iface);
  
  return 0;
}


////////////////////////////////////////////////////////////////////////////////
// Check for new data
void GzPosition::Update()
{
  player_position_data_t data;
  struct timeval ts;

  gz_position_lock(this->iface, 1);

  if (this->iface->data->time > this->datatime)
  {
    this->datatime = this->iface->data->time;
    
    ts.tv_sec = (int) (this->iface->data->time);
    ts.tv_usec = (int) (fmod(this->iface->data->time, 1) * 1e6);
  
    data.xpos = htonl((int) (this->iface->data->pos[0] * 1000));
    data.ypos = htonl((int) (this->iface->data->pos[1] * 1000));
    data.yaw = htonl((int) (this->iface->data->rot[2] * 180 / M_PI));

    data.xspeed = htonl((int) (this->iface->data->vel_pos[0] * 1000));
    data.yspeed = htonl((int) (this->iface->data->vel_pos[1] * 1000));
    data.yawspeed = htonl((int) (this->iface->data->vel_rot[2] * 180 / M_PI));

    data.stall = (uint8_t) this->iface->data->stall;

    this->PutData(&data, sizeof(data), &ts);
  }

  gz_position_unlock(this->iface);

  return;
}


////////////////////////////////////////////////////////////////////////////////
// Commands
void GzPosition::PutCommand(player_device_id_t id,
                            void* src, size_t len,
                            struct timeval* timestamp)
{
  player_position_cmd_t *cmd;
    
  assert(len >= sizeof(player_position_cmd_t));
  cmd = (player_position_cmd_t*) src;

  gz_position_lock(this->iface, 1);
  this->iface->data->cmd_vel_pos[0] = ((int) ntohl(cmd->xspeed)) / 1000.0;
  this->iface->data->cmd_vel_pos[1] = ((int) ntohl(cmd->yspeed)) / 1000.0;
  this->iface->data->cmd_vel_rot[2] = ((int) ntohl(cmd->yawspeed)) * M_PI / 180;
  gz_position_unlock(this->iface);
    
  return;
}


////////////////////////////////////////////////////////////////////////////////
// Handle requests
int GzPosition::PutConfig(player_device_id_t id, void *client, 
                          void* src, size_t len,
                          struct timeval* timestamp)
{
  switch (((char*) src)[0])
  {
    case PLAYER_POSITION_GET_GEOM_REQ:
      HandleGetGeom(client, src, len);
      break;

    case PLAYER_POSITION_MOTOR_POWER_REQ:
      HandleMotorPower(client, src, len);
      break;

    default:
      if (PutReply(client, PLAYER_MSGTYPE_RESP_NACK,NULL) != 0)
        PLAYER_ERROR("PutReply() failed");
      break;
  }
  return 0;
}


////////////////////////////////////////////////////////////////////////////////
// Handle geometry requests.
void GzPosition::HandleGetGeom(void *client, void *req, int reqlen)
{
  player_position_geom_t geom;

  // TODO: get correct dimensions; there are for the P2AT
  
  geom.subtype = PLAYER_POSITION_GET_GEOM_REQ;
  geom.pose[0] = htons((int) (0));
  geom.pose[1] = htons((int) (0));
  geom.pose[2] = htons((int) (0));
  geom.size[0] = htons((int) (0.53 * 1000));
  geom.size[1] = htons((int) (0.38 * 1000));

  if (PutReply(client, PLAYER_MSGTYPE_RESP_ACK, &geom, sizeof(geom),NULL) != 0)
    PLAYER_ERROR("PutReply() failed");
  
  return;
}


////////////////////////////////////////////////////////////////////////////////
// Handle motor power 
void GzPosition::HandleMotorPower(void *client, void *req, int reqlen)
{
  player_position_power_config_t *power;
  
  assert((size_t) reqlen >= sizeof(player_position_power_config_t));
  power = (player_position_power_config_t*) req;

  gz_position_lock(this->iface, 1);
  this->iface->data->cmd_enable_motors = power->value;
  gz_position_unlock(this->iface);

  if (PutReply(client, PLAYER_MSGTYPE_RESP_ACK, NULL) != 0)
    PLAYER_ERROR("PutReply() failed");
  
  return;
}
