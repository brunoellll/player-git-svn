/*
 *  Player - One Hell of a Robot Server
 *  Copyright (C) 2000  
 *     Brian Gerkey, Kasper Stoy, Richard Vaughan, & Andrew Howard
 *                      
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

/*
 * $Id$
 *
 *   the P2OS device.  it's the parent device for all the P2 'sub-devices',
 *   like gripper, position, sonar, etc.  there's a thread here that
 *   actually interacts with P2OS via the serial line.  the other
 *   "devices" communicate with this thread by putting into and getting
 *   data out of shared buffers.
 */
#ifndef _P2OSDEVICE_H
#define _P2OSDEVICE_H

#include <pthread.h>
#include <sys/time.h>

#include <device.h>
#include <packet.h>
#include <playercommon.h>
#include <messages.h>
#include <robot_params.h>
   
#define P2OS_MOTORS_REQUEST_ON 0
#define P2OS_MOTORS_ON 1
#define P2OS_MOTORS_REQUEST_OFF 2
#define P2OS_MOTORS_OFF 3

/* data for the p2-dx robot from p2 operation manual */
#define P2OS_CYCLETIME_USEC 100000
//#define AngleConvFactor 0.001534
//#define DistConvFactor 0.826
//#define VelConvFactor 1.0
//#define RobotRadius 250.0
//#define RobotDiagonal 120.0
//#define Holonomic 1
//#define RangeConvFactor 0.268
//#define RobotAxleLength 320.0

/* p2os constants */
#define SYNC0 0
#define SYNC1 1
#define SYNC2 2

#define PULSE 0
#define OPEN 1
#define CLOSE 2
#define ENABLE 4
#define SETV 6
#define SETO 7
#define VEL 11
#define RVEL 21
#define SONAR 28
#define STOP 29
#define VEL2 32
#define GRIPPER 33
#define GRIPPERVAL 36
#define TTY2 42
#define GETAUX 43

/* gripper stuff */
#define GRIPopen   1
#define GRIPclose  2
#define GRIPstop   3
#define LIFTup     4
#define LIFTdown   5
#define LIFTstop   6
#define GRIPstore  7
#define GRIPdeploy 8
#define GRIPhalt   15
#define GRIPpress  16
#define LIFTcarry  17

#define P2OS_CONFIG_BUFFER_SIZE 256

typedef struct
{
  player_position_data_t position;
  player_sonar_data_t sonar;
  player_gripper_data_t gripper;
  player_misc_data_t misc;
} __attribute__ ((packed)) player_p2os_data_t;

typedef struct
{
  player_position_cmd_t position;
  player_gripper_cmd_t gripper;
} __attribute__ ((packed)) player_p2os_cmd_t;

// this is here because we need the above typedef's before including it.
#include <sip.h>

class CSIP;

class CP2OSDevice:public CDevice 
{
private:
  static pthread_t thread;
  static pthread_mutex_t serial_mutex;
  static CSIP* sippacket;

 public:
  static int param_idx;  // index in the RobotParams table for this robot
  static bool direct_wheel_vel_control;  // false -> separate trans and rot vel
  static char num_loops_since_rvel;  
  static int psos_fd;               // p2os device file descriptor
  static char psos_serial_port[MAX_FILENAME_SIZE]; // device used to communicate with p2os
  static bool radio_modemp; // are we using a radio modem?
  
  static bool arena_initialized_data_buffer;
  static bool arena_initialized_command_buffer;

  //static player_p2os_data_t* data;
  //static player_p2os_cmd_t* command;

  static int last_client_id;

  /*
   * in this order:
   *   char: command (e.g., 'm' for motors enable)
   *   arg: command-specific arg
   */
  static unsigned char* config;
  // set to size by PutConfig and zeroed by GetConfig
  static int config_size;

  static struct timeval timeBegan_tv;

  CP2OSDevice(int argc, char** argv);
  ~CP2OSDevice();

  virtual int Setup();
  virtual int Shutdown();
  virtual void PutData( unsigned char *, size_t maxsize);
  virtual size_t GetConfig( unsigned char *, size_t maxsize);
  virtual void PutConfig( unsigned char *, size_t maxsize);
  int SendReceive(CPacket* pkt); //, bool already_have_lock);
  void ResetRawPositions();
};


#endif
