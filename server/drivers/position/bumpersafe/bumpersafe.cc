#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <math.h>

#include "player.h"
#include "device.h"
#include "devicetable.h"
#include "drivertable.h"

class BumperSafe : public CDevice 
{
  public:
    // Constructor
    BumperSafe(char* interface, ConfigFile* cf, int section);

    // Destructor
    virtual ~BumperSafe();

    // Setup/shutdown routines.
    virtual int Setup();
    virtual int Shutdown();

    // Underlying devices
    int SetupPosition();
    int ShutdownPosition();
	int GetPosition();
	
    int SetupBumper();
    int ShutdownBumper();
	int GetBumper();


    // Main function for device thread.
    virtual void Main();


  private:
    // Process requests.  Returns 1 if the configuration has changed.
    int HandleRequests();

    // Write the pose data (the data going back to the client).
    void PutPose();

    // Send commands to underlying position device
    void PutCommand();

    // Check for new commands from server
    void GetCommand();
    
    // state info
    bool Blocked;
    player_bumper_data_t CurrentState;
    player_bumper_data_t SafeState;

    // Position device info
    CDevice *position;
    int position_index;
	int speed,turnrate;
	player_position_cmd_t cmd;
	player_position_data_t data;
	double position_time;
    
    // Bumper device info
    CDevice *bumper;
    int bumper_index;
	double bumper_time;
	player_bumper_geom_t bumper_geom;
		
};

// Initialization function
CDevice* BumperSafe_Init(char* interface, ConfigFile* cf, int section) 
{
  if (strcmp(interface, PLAYER_POSITION_STRING) != 0) { 
    PLAYER_ERROR1("driver \"bumper_safe\" does not support interface \"%s\"\n", interface);
    return (NULL);
  }
  return ((CDevice*) (new BumperSafe(interface, cf, section)));
} 

// a driver registration function
void BumperSafe_Register(DriverTable* table)
{ 
  table->AddDriver("bumper_safe", PLAYER_ALL_MODE, BumperSafe_Init);
  return;
} 

////////////////////////////////////////////////////////////////////////////////
// Set up the device (called by server thread).
int BumperSafe::Setup() 
{
  player_position_cmd_t cmd;

  cmd.xpos = cmd.ypos = cmd.yaw = 0;
  cmd.xspeed = cmd.yspeed = cmd.yawspeed = 0;
  CDevice::PutCommand(this,(unsigned char*)&cmd,sizeof(cmd));

  // Initialise the underlying device s.
  if (this->SetupPosition() != 0)
    return -1;
  if (this->SetupBumper() != 0)
    return -1;

  // Start the driver thread.
  this->StartThread();

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Shutdown the device (called by server thread).
int BumperSafe::Shutdown() {
  // Stop the driver thread.
  this->StopThread();

  // Stop the laser
  this->ShutdownPosition();

  // Stop the odom device.
  this->ShutdownBumper();
  
  return 0;
}


////////////////////////////////////////////////////////////////////////////////
// Set up the underlying position device.
int BumperSafe::SetupPosition() 
{
  player_device_id_t id;

// EDIT?
//  id.robot = this->device_id.robot;
  id.port = this->device_id.port;
  id.code = PLAYER_POSITION_CODE;
  id.index = this->position_index;

  this->position = deviceTable->GetDevice(id);
  if (!this->position)
  {
    PLAYER_ERROR("unable to locate suitable position device");
    return -1;
  }

  if (this->position->Subscribe(this) != 0)
  {
    PLAYER_ERROR("unable to subscribe to position device");
    return -1;
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Shutdown the underlying position device.
int BumperSafe::ShutdownPosition() 
{

  // Stop the robot before unsubscribing
  this->speed = 0;
  this->turnrate = 0;
  this->PutCommand();
  
  this->position->Unsubscribe(this);
  return 0;
}


////////////////////////////////////////////////////////////////////////////////
// Set up the bumper
int BumperSafe::SetupBumper() {
  player_device_id_t id;

// EDIT ?
//  id.robot = this->device_id.robot;
  id.port = this->device_id.port;
  id.code = PLAYER_BUMPER_CODE;
  id.index = this->bumper_index;

  this->bumper = deviceTable->GetDevice(id);
  if (!this->bumper)
  {
    PLAYER_ERROR("unable to locate suitable laser device");
    return -1;
  }
  if (this->bumper->Subscribe(this) != 0)
  {
    PLAYER_ERROR("unable to subscribe to laser device");
    return -1;
  }

	// get bumper geometry...
/*	uint8_t req = PLAYER_BUMPER_GET_GEOM_REQ;
	unsigned short reptype;
	struct timeval ts;
	size_t replen = this->bumper->Request(&bumper->device_id, this, &req, sizeof(req), 
										&reptype, &ts, &bumper_geom, sizeof(bumper_geom));
	
*/

  return 0;
}


////////////////////////////////////////////////////////////////////////////////
// Shut down the bumper
int BumperSafe::ShutdownBumper() {
  this->bumper->Unsubscribe(this);
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Check for new bumper data
int BumperSafe::GetBumper() {
  //int i;
  size_t size;
  player_bumper_data_t data;
  uint32_t timesec, timeusec;
  double time;

  // Get the bumper device data.
  size = this->bumper->GetData(this,(unsigned char*) &data, sizeof(data), &timesec, &timeusec);
  if (size == 0)
    return 0;
  time = (double) timesec + ((double) timeusec) * 1e-6;

  // Dont do anything if this is old data.
  if (time - this->bumper_time < 0.001)
    return 0;
  this->bumper_time = time;

  // copy new data to current state
  memcpy(&CurrentState,&data,sizeof(data));
  
  return 1;
}

////////////////////////////////////////////////////////////////////////////////
// Check for new position data
int BumperSafe::GetPosition() 
{
  //int i;
  size_t size;
  uint32_t timesec, timeusec;
  double time;

  // Get the bumper device data.
  size = this->position->GetData(this,(unsigned char*) &data, sizeof(data), &timesec, &timeusec);
  if (size == 0)
    return 0;
  time = (double) timesec + ((double) timeusec) * 1e-6;

  // Dont do anything if this is old data.
  if (time - this->position_time < 0.001)
    return 0;
  this->position_time = time;

  return 1;
}

////////////////////////////////////////////////////////////////////////////////
// Send commands to the underlying position device
void BumperSafe::PutCommand() 
{
	player_position_cmd_t temp_cmd = cmd;

  // in blocked state then stop motors
  if (Blocked)
  {
    temp_cmd.xspeed = 0;
    temp_cmd.yspeed = 0;
    temp_cmd.yawspeed = 0;
  }

  this->position->PutCommand(this, (unsigned char*) &temp_cmd, sizeof(temp_cmd));

  return;
}


////////////////////////////////////////////////////////////////////////////////
// Process requests.  Returns 1 if the configuration has changed.
int BumperSafe::HandleRequests()
{
	int len;
	void *client;
	char request[PLAYER_MAX_REQREP_SIZE], response[PLAYER_MAX_REQREP_SIZE];
	unsigned short reptype;
	struct timeval ts;
	size_t resp_length = PLAYER_MAX_REQREP_SIZE;

	while ((len = GetConfig(&client, &request, sizeof(request))) > 0)
  	{
    	if (request[0] == PLAYER_POSITION_MOTOR_POWER_REQ && Blocked)
		{
			// if motor is switched on then we reset the 'safe state' so robot can move with a bump panel active
	  		if (((player_position_power_config_t *) request)->value == 1)
			{
				SafeState = CurrentState;
				Blocked = false;
    			cmd.xspeed = 0;
    			cmd.yspeed = 0;
    			cmd.yawspeed = 0;
				PutCommand();
			}
		}
		else
		{
			// all other requests pass request onto position device
			this->position->Request(&this->position->device_id, this, request, len, &reptype, &ts, response, resp_length);
    		if (PutReply(client, reptype, &ts, response, resp_length) != 0)
    			PLAYER_ERROR("PutReply() failed");
		}
  	}
  	return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Main function for device thread
void BumperSafe::Main() 
{
  struct timespec sleeptime;
  sleeptime.tv_sec = 0;
  sleeptime.tv_nsec = 1000000L;

  // Wait till we get new odometry data; this may block indefinitely
  this->GetPosition();
  this->GetBumper();

  while (true)
  {
    // Process any pending requests.
    this->HandleRequests();

    // Sleep for 1ms (will actually take longer than this).
    nanosleep(&sleeptime, NULL);

    // Test if we are supposed to cancel this thread.
    pthread_testcancel();

    // Get new odometric data
    if (this->GetPosition() != 0)
	{
	    // Write odometric data (so we emulate the underlying odometric device)
    	this->PutPose();
    }

    // Get new bumper data
    if (this->GetBumper() != 0)
	{
		unsigned char hash = 0;
		for (int i = 0; i < CurrentState.bumper_count; ++i)
			hash |= CurrentState.bumpers[i] & ~SafeState.bumpers[i];
			
		if (hash)
		{
			Blocked = true;
			PutCommand();
		}
		else
		{
			Blocked = false;
			PutCommand();
			SafeState = CurrentState;
		}
    }

    // Read client command
    this->GetCommand();

  }
  return;
}

////////////////////////////////////////////////////////////////////////////////
// Check for new commands from the server
void BumperSafe::GetCommand() 
{
  if(CDevice::GetCommand(&cmd, sizeof(cmd)) != 0) 
  {
  	PutCommand();
  }
}


////////////////////////////////////////////////////////////////////////////////
// Constructor
BumperSafe::BumperSafe(char* interface, ConfigFile* cf, int section)
    : CDevice(sizeof(player_position_data_t), sizeof(player_position_cmd_t), 10, 10)
{
	Blocked = false;

  this->position = NULL;
  this->position_index = cf->ReadInt(section, "position_index", 0);
  this->position_time = 0.0;
  
  this->bumper = NULL;
  this->bumper_index = cf->ReadInt(section, "bumper_index", 0);
  this->bumper_time = 0.0;

  return;
}


BumperSafe::~BumperSafe() {
  return;
}


////////////////////////////////////////////////////////////////////////////////
// Update the device data (the data going back to the client).
void BumperSafe::PutPose()
{
  uint32_t timesec, timeusec;

  // Compute timestamp
  timesec = (uint32_t) this->position_time;
  timeusec = (uint32_t) (fmod(this->position_time, 1.0) * 1e6);

  // Copy data to server.
  PutData((unsigned char*) &data, sizeof(data), timesec, timeusec);

  return;
}

