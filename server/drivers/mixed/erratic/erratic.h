// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:1; -*-

/**
	*  Erratic Erratic robot driver for Player
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
**/

#ifndef _P2OSDEVICE_H
#define _P2OSDEVICE_H


#include <pthread.h>
#include <sys/time.h>
#include <queue>

#include <libplayercore/playercore.h>
#include <replace/replace.h>

#include "packet.h"
#include "robot_params.h"

#include <stdint.h>

// Version
#define ERRATIC_VERSION "1.0b"
#define ERRATIC_DATE "2006-05-07"

// Default max speeds
#define MOTOR_DEF_MAX_SPEED 0.5
#define MOTOR_DEF_MAX_TURNSPEED DTOR(100)

// This merely sets a delay policy in the initial connection
#define ROBOT_CYCLETIME 20000

/* Erratic constants */

#define VIDERE_NOMINAL_VOLTAGE 12.0


// Commands for the robot
typedef enum command {
	pulse =                     0,
	open_controller =           1,
	close_controller =          2,
	enable_motors =             4,
	set_max_trans_acc =         5,
	set_max_position_velocity = 6,
	reset_origo =               7,
	trans_vel =                 11,
	configuration =             18,
	rot_vel =                   21,
	set_max_rot_acc =           23,
	stop =                      29,
	wheel_vel =                 32,
	set_analog =                71,
	save_config =               72,
	set_pwm_freq =              73,
	set_pwm_max_on =            74,
	set_pid_trans_p =           80,
	set_pid_trans_v =           81,
	set_pid_trans_i =           82,
	set_pid_rot_p =             83,
	set_pid_rot_v =             84,
	set_pid_rot_i =             85,
	
} command_e;

// Argument types used in robot commands
typedef enum argtype {
	argint =  0x3B,
	argnint = 0x1B,
	argstr =  0x2B
} argtype_e;

// Types of replies from the robot
typedef enum reply {
	debug =   0x15,
	config =  0x20,
	stopped = 0x32,
	moving =  0x33,
	motor =   0x80,
	encoder = 0x90,
	ain =     0x9a
} reply_e;


#define DEFAULT_VIDERE_PORT "/dev/ttyS0"

typedef struct player_erratic_data
{
  player_position2d_data_t position;
  player_power_data_t power;
	player_aio_data_t aio;
} __attribute__ ((packed)) player_erratic_data_t;

// this is here because we need the above typedef's before including it.
#include "sip.h"

extern bool debug_mode;

class erSIP;

class Erratic : public Driver 
{
  private:
    player_erratic_data_t erratic_data;

    player_devaddr_t position_id;
    player_devaddr_t power_id;
    player_devaddr_t aio_id;

    int position_subscriptions;
		int aio_subscriptions;

    //erSIP* sippacket;
		erSIP *motor_packet;
		pthread_mutex_t motor_packet_mutex;
		
		int Connect();
		int Disconnect();
		
		
    int SendReceiveOLD(ErraticPacket* pkt, bool publish_data=true);
    void ResetRawPositions();
    void ToggleMotorPower(unsigned char val);

		void ToggleAIn(unsigned char val);

    int HandleConfig(MessageQueue* resp_queue, player_msghdr * hdr, void* data);
    int HandleCommand(player_msghdr * hdr, void * data);
    void HandlePositionCommand(player_position2d_cmd_vel_t position_cmd);

    void PublishAllData();
		void PublishPosition2D();
		void PublishPower();
		void PublishAIn();
		
		void StartThreads();
		void StopThreads();
		
		void Send(ErraticPacket *packet);
		void SendThread();
		static void *SendThreadDummy(void *driver);
		void ReceiveThread();
		static void *ReceiveThreadDummy(void *driver);

    int direct_wheel_vel_control;    // false -> separate trans and rot vel

    int read_fd, write_fd;
    const char* psos_serial_port;
    struct timeval lastblob_tv;

    player_position2d_cmd_vel_t last_position_cmd;

		std::queue<ErraticPacket *> send_queue;
		pthread_mutex_t send_queue_mutex;
		pthread_cond_t send_queue_cond;

		pthread_t send_thread;
		pthread_t receive_thread;

		// Parameters

		bool print_all_packets;
		bool print_status_summary;
		
		bool save_settings_in_robot;

    int param_idx;  // index in the RobotParams table for this robot
		
    // Max motor speeds (mm/sec,deg/sec)
    int motor_max_speed;
    int motor_max_turnspeed;

		// Customized control settings for the robot
		int16_t pid_trans_p, pid_trans_v, pid_trans_i;
		int16_t pid_rot_p, pid_rot_v, pid_rot_i;

		// This is a fairly low-level setting that is exposed
		uint16_t motor_pwm_frequency, motor_pwm_max_on;

    // Bound the command velocities
    bool use_vel_band; 

    // Max motor accel/decel (mm/sec/sec, deg/sec/sec)
    short motor_max_trans_accel, motor_max_trans_decel;
    short motor_max_rot_accel, motor_max_rot_decel;

  public:

    Erratic(ConfigFile* cf, int section);

    virtual int Subscribe(player_devaddr_t id);
    virtual int Unsubscribe(player_devaddr_t id);

    /* the main thread */
    virtual void Main();

    virtual int Setup();
    virtual int Shutdown();

    // MessageHandler
    virtual int ProcessMessage(MessageQueue * resp_queue, player_msghdr * hdr, void * data);
};


#endif
