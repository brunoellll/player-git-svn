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
 * robot_params.cc 
 *
 * ActivMedia robot parameters, automatically generated by saphconv.tcl from 
 * Saphira parameter files:
 *    /home/gerkey/holding/robot_params/amigo.p
 *    /home/gerkey/holding/robot_params/p2at.p
 *    /home/gerkey/holding/robot_params/p2at8+.p
 *    /home/gerkey/holding/robot_params/p2at8.p
 *    /home/gerkey/holding/robot_params/p2ce.p
 *    /home/gerkey/holding/robot_params/p2d8+.p
 *    /home/gerkey/holding/robot_params/p2d8.p
 *    /home/gerkey/holding/robot_params/p2de.p
 *    /home/gerkey/holding/robot_params/p2df.p
 *    /home/gerkey/holding/robot_params/p2dx.p
 *    /home/gerkey/holding/robot_params/p2it.p
 *    /home/gerkey/holding/robot_params/p2pb.p
 *    /home/gerkey/holding/robot_params/p2pp.p
 *    /home/gerkey/holding/robot_params/p3at.p
 *    /home/gerkey/holding/robot_params/p3dx.p
 *    /home/gerkey/holding/robot_params/perfpb+.p
 *    /home/gerkey/holding/robot_params/perfpb.p
 *    /home/gerkey/holding/robot_params/pion1m.p
 *    /home/gerkey/holding/robot_params/pion1x.p
 *    /home/gerkey/holding/robot_params/pionat.p
 *    /home/gerkey/holding/robot_params/powerbot.p
 *    /home/gerkey/holding/robot_params/psos1m.p
 *    /home/gerkey/holding/robot_params/psos1x.p
*/
#include <robot_params.h>


RobotParams_t amigo_params = 
{
  0.001534,
  "Pioneer",
  0.011000,
  0.508300,
  0,
  0,
  1,
  1,
  0,
  "COM3",
  0,
  1,
  0,
  0,
  300.000000,
  1000.000000,
  0,
  0,
  0,
  1.000000,
  0,
  0,
  0,
  120.000000,
  0,
  180.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  8,
  "amigo",
  0,
  0,
  0,
  0,
  0,
  20.000000,
  0.615400,
  {
    { 73, 105, 90 },
    { 130, 78, 41 },
    { 154, 30, 15 },
    { 154, -30, -15 },
    { 130, -78, -41 },
    { 73, -105, -90 },
    { -146, -60, -145 },
    { -146, 60, 145 },
  }
};

RobotParams_t p2at_params = 
{
  0.001534,
  "Pioneer",
  0.003400,
  1.320000,
  0,
  0,
  1,
  1.000000,
  0,
  "COM3",
  0,
  1,
  160,
  7,
  300.000000,
  1200.000000,
  0,
  5,
  5,
  0.268000,
  0,
  0,
  0,
  120.000000,
  0,
  500.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  16,
  "p2at",
  0,
  0,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 145, 130, 90 },
    { 185, 115, 50 },
    { 220, 80, 30 },
    { 240, 25, 10 },
    { 240, -25, -10 },
    { 220, -80, -30 },
    { 185, -115, -50 },
    { 145, -130, -90 },
    { -145, -130, -90 },
    { -185, -115, -130 },
    { -220, -80, -150 },
    { -240, -25, -170 },
    { -240, 25, 170 },
    { -220, 80, 150 },
    { -185, 115, 130 },
    { -145, 130, 90 },
  }
};

RobotParams_t p2at8plus_params = 
{
  0.001534,
  "Pioneer",
  0.003400,
  0.465000,
  0,
  0,
  1,
  1.000000,
  0,
  "COM3",
  0,
  1,
  160,
  7,
  300.000000,
  1200.000000,
  0,
  5,
  5,
  1.000000,
  0,
  0,
  0,
  120.000000,
  0,
  500.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  16,
  "p2at8+",
  0,
  0,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 145, 130, 90 },
    { 185, 115, 50 },
    { 220, 80, 30 },
    { 240, 25, 10 },
    { 240, -25, -10 },
    { 220, -80, -30 },
    { 185, -115, -50 },
    { 145, -130, -90 },
    { -145, -130, -90 },
    { -185, -115, -130 },
    { -220, -80, -150 },
    { -240, -25, -170 },
    { -240, 25, 170 },
    { -220, 80, 150 },
    { -185, 115, 130 },
    { -145, 130, 90 },
  }
};

RobotParams_t p2at8_params = 
{
  0.001534,
  "Pioneer",
  0.003400,
  1.320000,
  0,
  0,
  1,
  1.000000,
  0,
  "COM3",
  0,
  1,
  160,
  7,
  300.000000,
  1200.000000,
  0,
  5,
  5,
  1.000000,
  0,
  0,
  0,
  120.000000,
  0,
  500.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  16,
  "p2at8",
  0,
  0,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 145, 130, 90 },
    { 185, 115, 50 },
    { 220, 80, 30 },
    { 240, 25, 10 },
    { 240, -25, -10 },
    { 220, -80, -30 },
    { 185, -115, -50 },
    { 145, -130, -90 },
    { -145, -130, -90 },
    { -185, -115, -130 },
    { -220, -80, -150 },
    { -240, -25, -170 },
    { -240, 25, 170 },
    { -220, 80, 150 },
    { -185, 115, 130 },
    { -145, 130, 90 },
  }
};

RobotParams_t p2ce_params = 
{
  0.001534,
  "Pioneer",
  0.005700,
  0.826000,
  0,
  0,
  1,
  1.000000,
  0,
  "COM3",
  0,
  1,
  0,
  0,
  500.000000,
  2200.000000,
  0,
  0,
  0,
  0.268000,
  0,
  0,
  0,
  120.000000,
  0,
  250.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  16,
  "p2ce",
  0,
  0,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 115, 130, 90 },
    { 155, 115, 50 },
    { 190, 80, 30 },
    { 210, 25, 10 },
    { 210, -25, -10 },
    { 190, -80, -30 },
    { 155, -115, -50 },
    { 115, -130, -90 },
    { -115, -130, -90 },
    { -155, -115, -130 },
    { -190, -80, -150 },
    { -210, -25, -170 },
    { -210, 25, 170 },
    { -190, 80, 150 },
    { -155, 115, 130 },
    { -115, 130, 90 },
  }
};

RobotParams_t p2d8plus_params = 
{
  0.001534,
  "Pioneer",
  0.005600,
  0.485000,
  0,
  0,
  1,
  1.000000,
  0,
  "COM3",
  0,
  1,
  18,
  0,
  500.000000,
  2200.000000,
  0,
  5,
  5,
  1.000000,
  0,
  0,
  0,
  120.000000,
  0,
  250.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  16,
  "p2d8+",
  0,
  0,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 115, 130, 90 },
    { 155, 115, 50 },
    { 190, 80, 30 },
    { 210, 25, 10 },
    { 210, -25, -10 },
    { 190, -80, -30 },
    { 155, -115, -50 },
    { 115, -130, -90 },
    { -115, -130, -90 },
    { -155, -115, -130 },
    { -190, -80, -150 },
    { -210, -25, -170 },
    { -210, 25, 170 },
    { -190, 80, 150 },
    { -155, 115, 130 },
    { -115, 130, 90 },
  }
};

RobotParams_t p2d8_params = 
{
  0.001534,
  "Pioneer",
  0.005600,
  0.485000,
  0,
  0,
  1,
  1.000000,
  0,
  "COM3",
  0,
  1,
  18,
  0,
  500.000000,
  2200.000000,
  0,
  5,
  5,
  1.000000,
  0,
  0,
  0,
  120.000000,
  0,
  250.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  16,
  "p2d8",
  0,
  0,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 115, 130, 90 },
    { 155, 115, 50 },
    { 190, 80, 30 },
    { 210, 25, 10 },
    { 210, -25, -10 },
    { 190, -80, -30 },
    { 155, -115, -50 },
    { 115, -130, -90 },
    { -115, -130, -90 },
    { -155, -115, -130 },
    { -190, -80, -150 },
    { -210, -25, -170 },
    { -210, 25, 170 },
    { -190, 80, 150 },
    { -155, 115, 130 },
    { -115, 130, 90 },
  }
};

RobotParams_t p2de_params = 
{
  0.001534,
  "Pioneer",
  0.005600,
  0.969000,
  0,
  0,
  1,
  1.000000,
  0,
  "COM3",
  0,
  1,
  17,
  8,
  500.000000,
  2200.000000,
  0,
  5,
  5,
  0.268000,
  0,
  0,
  0,
  120.000000,
  0,
  250.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  16,
  "p2de",
  0,
  0,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 115, 130, 90 },
    { 155, 115, 50 },
    { 190, 80, 30 },
    { 210, 25, 10 },
    { 210, -25, -10 },
    { 190, -80, -30 },
    { 155, -115, -50 },
    { 115, -130, -90 },
    { -115, -130, -90 },
    { -155, -115, -130 },
    { -190, -80, -150 },
    { -210, -25, -170 },
    { -210, 25, 170 },
    { -190, 80, 150 },
    { -155, 115, 130 },
    { -115, 130, 90 },
  }
};

RobotParams_t p2df_params = 
{
  0.001534,
  "Pioneer",
  0.006000,
  0.485000,
  0,
  0,
  1,
  1.000000,
  0,
  "COM3",
  0,
  1,
  17,
  8,
  500.000000,
  2200.000000,
  0,
  5,
  5,
  0.268000,
  0,
  0,
  0,
  120.000000,
  0,
  250.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  16,
  "p2df",
  0,
  0,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 115, 130, 90 },
    { 155, 115, 50 },
    { 190, 80, 30 },
    { 210, 25, 10 },
    { 210, -25, -10 },
    { 190, -80, -30 },
    { 155, -115, -50 },
    { 115, -130, -90 },
    { -115, -130, -90 },
    { -155, -115, -130 },
    { -190, -80, -150 },
    { -210, -25, -170 },
    { -210, 25, 170 },
    { -190, 80, 150 },
    { -155, 115, 130 },
    { -115, 130, 90 },
  }
};

RobotParams_t p2dx_params = 
{
  0.001534,
  "Pioneer",
  0.005600,
  0.840000,
  0,
  0,
  1,
  1.000000,
  0,
  "COM3",
  0,
  1,
  17,
  8,
  500.000000,
  2200.000000,
  0,
  5,
  5,
  0.268000,
  0,
  0,
  0,
  120.000000,
  0,
  250.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  16,
  "p2dx",
  0,
  0,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 115, 130, 90 },
    { 155, 115, 50 },
    { 190, 80, 30 },
    { 210, 25, 10 },
    { 210, -25, -10 },
    { 190, -80, -30 },
    { 155, -115, -50 },
    { 115, -130, -90 },
    { -115, -130, -90 },
    { -155, -115, -130 },
    { -190, -80, -150 },
    { -210, -25, -170 },
    { -210, 25, 170 },
    { -190, 80, 150 },
    { -155, 115, 130 },
    { -115, 130, 90 },
  }
};

RobotParams_t p2it_params = 
{
  0.001534,
  "Pioneer",
  0.003200,
  1.136000,
  0,
  0,
  1,
  1.000000,
  0,
  "COM3",
  0,
  1,
  160,
  7,
  300.000000,
  1200.000000,
  0,
  5,
  5,
  0.268000,
  0,
  0,
  0,
  120.000000,
  0,
  500.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  16,
  "p2it",
  0,
  0,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 145, 130, 90 },
    { 185, 115, 50 },
    { 220, 80, 30 },
    { 240, 25, 10 },
    { 240, -25, -10 },
    { 220, -80, -30 },
    { 185, -115, -50 },
    { 145, -130, -90 },
    { -145, -130, -90 },
    { -185, -115, -130 },
    { -220, -80, -150 },
    { -240, -25, -170 },
    { -240, 25, 170 },
    { -220, 80, 150 },
    { -185, 115, 130 },
    { -145, 130, 90 },
  }
};

RobotParams_t p2pb_params = 
{
  0.001534,
  "Pioneer",
  0.005600,
  0.424000,
  1,
  0,
  1,
  1.000000,
  0,
  "COM3",
  0,
  1,
  17,
  8,
  500.000000,
  2200.000000,
  0,
  5,
  5,
  0.268000,
  1,
  0,
  0,
  120.000000,
  0,
  300.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  24,
  "p2pb",
  0,
  0,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 115, 130, 90 },
    { 155, 115, 50 },
    { 190, 80, 30 },
    { 210, 25, 10 },
    { 210, -25, -10 },
    { 190, -80, -30 },
    { 155, -115, -50 },
    { 115, -130, -90 },
    { 50, 130, 90 },
    { 90, 115, 50 },
    { 125, 80, 30 },
    { 145, 25, 10 },
    { 145, -25, -10 },
    { 125, -80, -30 },
    { 90, -115, -50 },
    { 50, -130, -90 },
    { -115, -130, -90 },
    { -155, -115, -130 },
    { -190, -80, -150 },
    { -210, -25, -170 },
    { -210, 25, 170 },
    { -190, 80, 150 },
    { -155, 115, 130 },
    { -115, 130, 90 },
  }
};

RobotParams_t p2pp_params = 
{
  0.001534,
  "Pioneer",
  0.006000,
  0.485000,
  1,
  0,
  1,
  1.000000,
  0,
  "COM3",
  0,
  1,
  16,
  1,
  500.000000,
  2200.000000,
  0,
  5,
  5,
  0.268000,
  1,
  0,
  0,
  120.000000,
  0,
  300.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  24,
  "p2pp",
  0,
  1,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 115, 130, 90 },
    { 155, 115, 50 },
    { 190, 80, 30 },
    { 210, 25, 10 },
    { 210, -25, -10 },
    { 190, -80, -30 },
    { 155, -115, -50 },
    { 115, -130, -90 },
    { 50, 130, 90 },
    { 90, 115, 50 },
    { 125, 80, 30 },
    { 145, 25, 10 },
    { 145, -25, -10 },
    { 125, -80, -30 },
    { 90, -115, -50 },
    { 50, -130, -90 },
    { -115, -130, -90 },
    { -155, -115, -130 },
    { -190, -80, -150 },
    { -210, -25, -170 },
    { -210, 25, 170 },
    { -190, 80, 150 },
    { -155, 115, 130 },
    { -115, 130, 90 },
  }
};

RobotParams_t p3at_params = 
{
  0.001534,
  "Pioneer",
  0.0034,
  0.465,
  0,
  1.626,
  1,
  1,
  0,
  "COM3",
  0,
  1,
  160,
  7,
  300,
  1200,
  0,
  5,
  5,
  1,
  0,
  0,
  0,
  120,
  500,
  500,
  400,
  0,
  0,
  0,
  1,
  1,
  16,
  "p3at",
  38400,
  0,
  0,
  0,
  0,
  20,
  1,
  {
    { 145, 130, 90 },
    { 185, 115, 50 },
    { 220, 80, 30 },
    { 240, 25, 10 },
    { 240, -25, -10 },
    { 220, -80, -30 },
    { 185, -115, -50 },
    { 145, -130, -90 },
    { -145, -130, -90 },
    { -185, -115, -130 },
    { -220, -80, -150 },
    { -240, -25, -170 },
    { -240, 25, 170 },
    { -220, 80, 150 },
    { -185, 115, 130 },
    { -145, 130, 90 },
  }
};

RobotParams_t p3dx_params = 
{
  0.001534,
  "Pioneer",
  0.0056,
  0.485,
  0,
  1.626,
  1,
  1,
  0,
  "COM3",
  0,
  1,
  18,
  0,
  500,
  2200,
  0,
  5,
  5,
  1,
  0,
  0,
  0,
  120,
  500,
  250,
  400,
  0,
  0,
  0,
  1,
  1,
  16,
  "p3dx",
  38400,
  0,
  0,
  0,
  0,
  20,
  1,
  {
    { 115, 130, 90 },
    { 155, 115, 50 },
    { 190, 80, 30 },
    { 210, 25, 10 },
    { 210, -25, -10 },
    { 190, -80, -30 },
    { 155, -115, -50 },
    { 115, -130, -90 },
    { -115, -130, -90 },
    { -155, -115, -130 },
    { -190, -80, -150 },
    { -210, -25, -170 },
    { -210, 25, 170 },
    { -190, 80, 150 },
    { -155, 115, 130 },
    { -115, 130, 90 },
  }
};

RobotParams_t perfpbplus_params = 
{
  0.001534,
  "Pioneer",
  0.006000,
  0.485000,
  1,
  0,
  1,
  1.000000,
  0,
  "COM3",
  0,
  1,
  21,
  0,
  500.000000,
  2200.000000,
  1,
  5,
  5,
  1.000000,
  1,
  0,
  1,
  120.000000,
  0,
  340.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  32,
  "perfpb+",
  0,
  1,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 115, 130, 90 },
    { 155, 115, 50 },
    { 190, 80, 30 },
    { 210, 25, 10 },
    { 210, -25, -10 },
    { 190, -80, -30 },
    { 155, -115, -50 },
    { 115, -130, -90 },
    { 50, 130, 90 },
    { 90, 115, 50 },
    { 125, 80, 30 },
    { 145, 25, 10 },
    { 145, -25, -10 },
    { 125, -80, -30 },
    { 90, -115, -50 },
    { 50, -130, -90 },
    { -115, -130, -90 },
    { -155, -115, -130 },
    { -190, -80, -150 },
    { -210, -25, -170 },
    { -210, 25, 170 },
    { -190, 80, 150 },
    { -155, 115, 130 },
    { -115, 130, 90 },
    { -195, -130, -90 },
    { -235, -115, -130 },
    { -270, -80, -150 },
    { -290, -25, -170 },
    { -290, 25, 170 },
    { -270, 80, 150 },
    { -235, 115, 130 },
    { -195, 130, 90 },
  }
};

RobotParams_t perfpb_params = 
{
  0.001534,
  "Pioneer",
  0.006000,
  0.485000,
  1,
  0,
  1,
  1.000000,
  0,
  "COM3",
  0,
  1,
  21,
  0,
  500.000000,
  2200.000000,
  1,
  5,
  5,
  1.000000,
  1,
  0,
  1,
  120.000000,
  0,
  340.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  32,
  "perfpb",
  0,
  1,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 115, 130, 90 },
    { 155, 115, 50 },
    { 190, 80, 30 },
    { 210, 25, 10 },
    { 210, -25, -10 },
    { 190, -80, -30 },
    { 155, -115, -50 },
    { 115, -130, -90 },
    { 50, 130, 90 },
    { 90, 115, 50 },
    { 125, 80, 30 },
    { 145, 25, 10 },
    { 145, -25, -10 },
    { 125, -80, -30 },
    { 90, -115, -50 },
    { 50, -130, -90 },
    { -115, -130, -90 },
    { -155, -115, -130 },
    { -190, -80, -150 },
    { -210, -25, -170 },
    { -210, 25, 170 },
    { -190, 80, 150 },
    { -155, 115, 130 },
    { -115, 130, 90 },
    { -195, -130, -90 },
    { -235, -115, -130 },
    { -270, -80, -150 },
    { -290, -25, -170 },
    { -290, 25, 170 },
    { -270, 80, 150 },
    { -235, 115, 130 },
    { -195, 130, 90 },
  }
};

RobotParams_t pion1m_params = 
{
  0.006136,
  "Pioneer",
  0.003300,
  0.050660,
  0,
  0,
  0,
  1.000000,
  0,
  "COM3",
  0,
  1,
  0,
  0,
  100.000000,
  400.000000,
  0,
  0,
  0,
  0.173400,
  0,
  0,
  0,
  90.000000,
  0,
  220.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  7,
  "pion1m",
  0,
  0,
  0,
  0,
  0,
  4.000000,
  2.533200,
  {
    { 100, 100, 90 },
    { 120, 80, 30 },
    { 130, 40, 15 },
    { 130, 0, 0 },
    { 130, -40, -15 },
    { 120, -80, -30 },
    { 100, -100, -90 },
  }
};

RobotParams_t pion1x_params = 
{
  0.006136,
  "Pioneer",
  0.003333,
  0.050660,
  0,
  0,
  0,
  1.000000,
  0,
  "COM3",
  0,
  1,
  0,
  0,
  100.000000,
  400.000000,
  0,
  0,
  0,
  0.173400,
  0,
  0,
  0,
  90.000000,
  0,
  220.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  7,
  "pion1x",
  0,
  0,
  0,
  0,
  0,
  4.000000,
  0.079790,
  {
    { 100, 100, 90 },
    { 120, 80, 30 },
    { 130, 40, 15 },
    { 130, 0, 0 },
    { 130, -40, -15 },
    { 120, -80, -30 },
    { 100, -100, -90 },
  }
};

RobotParams_t pionat_params = 
{
  0.006136,
  "Pioneer",
  0.003333,
  0.070000,
  0,
  0,
  0,
  1.000000,
  0,
  "COM3",
  0,
  1,
  0,
  0,
  100.000000,
  500.000000,
  0,
  0,
  0,
  0.173400,
  0,
  0,
  0,
  120.000000,
  0,
  330.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  7,
  "pionat",
  0,
  0,
  0,
  0,
  0,
  4.000000,
  2.533200,
  {
    { 100, 100, 90 },
    { 120, 80, 30 },
    { 130, 40, 15 },
    { 130, 0, 0 },
    { 130, -40, -15 },
    { 120, -80, -30 },
    { 100, -100, -90 },
  }
};

RobotParams_t powerbot_params = 
{
  0.001534,
  "Pioneer",
  0.003730,
  0.581300,
  1,
  0,
  1,
  1.000000,
  1,
  "COM2",
  1,
  1,
  251,
  0,
  360.000000,
  2000.000000,
  0,
  7,
  5,
  1.000000,
  1,
  0,
  0,
  400.000000,
  0,
  550.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  31,
  "powerbot",
  0,
  0,
  0,
  0,
  0,
  20.000000,
  1.000000,
  {
    { 152, 278, 90 },
    { 200, 267, 65 },
    { 241, 238, 45 },
    { 274, 200, 35 },
    { 300, 153, 25 },
    { 320, 96, 15 },
    { 332, 33, 5 },
    { 0, 0, -180 },
    { 332, -33, -5 },
    { 320, -96, -15 },
    { 300, -153, -25 },
    { 274, -200, -35 },
    { 241, -238, -45 },
    { 200, -267, -65 },
    { 152, -278, -90 },
    { 0, 0, -180 },
    { -298, -278, -90 },
    { -347, -267, -115 },
    { -388, -238, -135 },
    { -420, -200, -145 },
    { -447, -153, -155 },
    { -467, -96, -165 },
    { -478, -33, -175 },
    { 0, 0, -180 },
    { -478, 33, 175 },
    { -467, 96, 165 },
    { -447, 153, 155 },
    { -420, 200, 145 },
    { -388, 238, 135 },
    { -347, 267, 115 },
    { -298, 278, 90 },
  }
};

RobotParams_t psos1m_params = 
{
  0.006136,
  "Pioneer",
  0.003300,
  0.050660,
  0,
  0,
  0,
  1.000000,
  0,
  "COM3",
  0,
  1,
  0,
  0,
  100.000000,
  400.000000,
  0,
  0,
  0,
  0.173400,
  0,
  0,
  0,
  90.000000,
  0,
  220.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  7,
  "psos1m",
  0,
  0,
  0,
  0,
  0,
  4.000000,
  2.533200,
  {
    { 100, 100, 90 },
    { 120, 80, 30 },
    { 130, 40, 15 },
    { 130, 0, 0 },
    { 130, -40, -15 },
    { 120, -80, -30 },
    { 100, -100, -90 },
  }
};

RobotParams_t psos1x_params = 
{
  0.006136,
  "Pioneer",
  0.003333,
  0.050660,
  0,
  0,
  0,
  1.000000,
  0,
  "COM3",
  0,
  1,
  0,
  0,
  100.000000,
  400.000000,
  0,
  0,
  0,
  0.173400,
  0,
  0,
  0,
  90.000000,
  0,
  220.000000,
  0,
  0,
  0,
  0,
  0,
  0,
  7,
  "psos1x",
  0,
  0,
  0,
  0,
  0,
  4.000000,
  0.079790,
  {
    { 100, 100, 90 },
    { 120, 80, 30 },
    { 130, 40, 15 },
    { 130, 0, 0 },
    { 130, -40, -15 },
    { 120, -80, -30 },
    { 100, -100, -90 },
  }
};

RobotParams_t PlayerRobotParams[PLAYER_NUM_ROBOT_TYPES];

void
initialize_robot_params(void)
{
  PlayerRobotParams[0] =  amigo_params;
  PlayerRobotParams[1] =  p2at_params;
  PlayerRobotParams[2] =  p2at8plus_params;
  PlayerRobotParams[3] =  p2at8_params;
  PlayerRobotParams[4] =  p2ce_params;
  PlayerRobotParams[5] =  p2d8plus_params;
  PlayerRobotParams[6] =  p2d8_params;
  PlayerRobotParams[7] =  p2de_params;
  PlayerRobotParams[8] =  p2df_params;
  PlayerRobotParams[9] =  p2dx_params;
  PlayerRobotParams[10] =  p2it_params;
  PlayerRobotParams[11] =  p2pb_params;
  PlayerRobotParams[12] =  p2pp_params;
  PlayerRobotParams[13] =  p3at_params;
  PlayerRobotParams[14] =  p3dx_params;
  PlayerRobotParams[15] =  perfpbplus_params;
  PlayerRobotParams[16] =  perfpb_params;
  PlayerRobotParams[17] =  pion1m_params;
  PlayerRobotParams[18] =  pion1x_params;
  PlayerRobotParams[19] =  pionat_params;
  PlayerRobotParams[20] =  powerbot_params;
  PlayerRobotParams[21] =  psos1m_params;
  PlayerRobotParams[22] =  psos1x_params;
}
