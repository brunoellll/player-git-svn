/*
 *  Player - One Hell of a Robot Server
 *  Copyright (C) 2006
 *     Kathy Fung, Toby Collett
 *
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 */

/*#include <stdlib.h>
#include <time.h>
#include "nav200.h"

#define LAYER 0
#define R_RADIUS 100
int main(int argc,char ** argv)
{
  //Standby mode
  //PositionXY reflector;
  Nav200 testing;
  testing.Initialise();
  if (!testing.EnterStandby())
  {
      fprintf(stderr,"unable to enter standby mode\n");
      return EXIT_FAILURE;
  }

  PositionXY reflectordata[256];
  int max = 0;
  if(testing.EnterMapping())
  {
    printf("Entered mapping, scanning please wait...");

    max = testing.StartMapping(LAYER, 0, 0, 0, R_RADIUS);

    printf("Number of reflectors scanned = %d\n",max);

    for(int i=0; i<max; i++)
    {
        if(testing.MappingPosition(LAYER,i,reflectordata[i]))
          printf("position of Reflector %d: position X=%d, Y=%d\n",i, reflectordata[i].x,reflectordata[i].y);
    }

  }
  else
  {
    fprintf(stderr,"unable to enter mapping mode\n");
    return EXIT_FAILURE;
  }

  // upload mode
//   if (!testing.EnterStandby())
//   {
//       fprintf(stderr,"unable to enter standby mode\n");
//       EXIT_FAILURE;
//   }
//   ReflectorData reflectors[numOfReflector];
//   ReflectorData temp;
// 
//   printf("Number of reflectors scanned = %d\n",numOfReflector);
//   if(testing.EnterUpload())
//   {
//       printf("\n\n\nEntered upload mode\n\n\n");
// //       int i=0;
// //       while(1)
//       for(int i=0; i<numOfReflector; i++)
//       {
//         if(testing.GetUploadTrans(0,temp))
//           printf("Uploaded reflector is: X = %d, Y = %d, layer = %d, number = %d\n",temp.pos.x,temp.pos.y,temp.layer,temp.number);
//         if(temp.number==255)
//           break;
//         reflectors[i].pos.x = temp.pos.x;
//         reflectors[i].pos.y = temp.pos.y;
//         reflectors[i].layer = temp.layer;
//         reflectors[i].number = temp.number;
// //         i++;
//       }
//   }
//   else
//   {
//     fprintf(stderr,"unable to enter upload mode\n");
//     EXIT_FAILURE;
//   }

  // download mode
  if (!testing.EnterStandby())
  {
      fprintf(stderr,"unable to enter standby mode\n");
      return EXIT_FAILURE;
  }
  if(testing.EnterDownload())
  {
      printf("\n\n\nEntered download mode\n\n\n");
      for(int i=0; i<max; i++)
      {
        testing.DownloadReflector(LAYER,i,reflectordata[i].x,reflectordata[i].y);
      }
      testing.DownloadReflector(LAYER,255,0,0);
  }
  else
  {
    fprintf(stderr,"unable to enter download mode\n");
    return EXIT_FAILURE;
  }

  for(int i=0; i<max; i++)
  {
    printf("downloaded reflectors %d: X=%d, Y=%d\n",i,reflectordata[i].x,reflectordata[i].y);
  }

  return 0;
}

*/

int main()
{}
