//==========================================================================
//
//  Project:        libfg - Frame Grabber interface for Linux
//
//  Module:         Frame implementation
//
//  Description:    Each frame captured by the FRAMEGRABBER returns a FRAME
//                  (defined here).  It contains the raw frame data, as well
//                  as information about the frame's size and format.
//
//  Author:         Gavin Baker <gavinb@antonym.org>
//
//  Homepage:       http://www.antonym.org/libfg
//
//--------------------------------------------------------------------------
//
//  libfg - Frame Grabber interface for Linux
//  Copyright (c) 2002 Gavin Baker
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
//  or obtain a copy from the GNU website at http://www.gnu.org/
//
//==========================================================================

#include "v4lframe.h"

#include <stdio.h>
#include <stdlib.h>

#include <linux/videodev.h>

//--------------------------------------------------------------------------

FRAME* frame_new( int width, int height, int format )
{
    FRAME* fr = malloc( sizeof( FRAME ) );

    fr->width = width;
    fr->height = height;
    fr->format = format;

    fr->size = frame_get_size( fr );
    fr->data = malloc( fr->size );

    return fr;
}

//--------------------------------------------------------------------------

void frame_release( FRAME* fr )
{
    free( fr->data );
    free( fr );
}

//--------------------------------------------------------------------------

int frame_get_size( FRAME* fr )
{
  int pixels = fr->width * fr->height;
  int size = 0;

  switch ( fr->format )
  {
    case VIDEO_PALETTE_GREY:
      // 1 bytes per pixel
      size = pixels * 1;
      break;

    case VIDEO_PALETTE_RGB24:
      // 3 bytes per pixel
      size = pixels * 3;
      break;
            
    case VIDEO_PALETTE_RGB32:
      // 4 bytes (1 int) per pixel
      size = pixels * 4;
      break;

    case VIDEO_PALETTE_RGB565:
      // 2 bytes (16 bits) per pixel
      size = pixels * 2;
      break;

    case VIDEO_PALETTE_RGB555:
      // 2 bytes (15 bits) per pixel
      size = pixels * 2;
      break;

    case VIDEO_PALETTE_YUV422:
      // 1 byte (8 bits) per pixel
      size = pixels;
      break;

    case VIDEO_PALETTE_YUV420P:
      // Y : 1 byte per pixel
      // U, V : 1 byte per 4 pixels
      size = pixels + pixels / 2;
      break;

    default:
      // Unsupported!
      fprintf( stderr, "frame_get_size(): Unsupported type!\n" );
      size = -1;
  }

  return size;
}

//--------------------------------------------------------------------------

int frame_save( FRAME* fr, const char* filename )
{
  int i = 0;
  int val = 0;
  unsigned char grey;
  FRAME_RGB rgb;
  FILE* fp = fopen( filename, "w" );

  if ( fp == NULL )
  {
    perror( "frame_save(): opening file for writing" );
    return -1;
  }

  // Write PNM header
  fprintf( fp, "P6\n" );
  fprintf( fp, "# Generated by a herd of rabid fleas\n" );
  fprintf( fp, "%d %d\n", fr->width, fr->height );

  switch ( fr->format )
  {
    case VIDEO_PALETTE_GREY:

      // Max val
      fprintf( fp, "255\n" );

      // Write image data
      for ( i = 0; i < ( fr->width * fr->height ); i++ )
      {
        // 1 bytes per pixel
        grey = ((unsigned char*)(fr->data))[i];

        fprintf( fp, "%c%c%c", grey, grey, grey);
      }
      break;

    case VIDEO_PALETTE_RGB24:

      // Max val
      fprintf( fp, "255\n" );

      // Write image data
      for ( i = 0; i < ( fr->width * fr->height ); i++ )
      {
        // 3 bytes per pixel
        rgb = ((FRAME_RGB*)(fr->data))[i];

        fprintf( fp, "%c%c%c",
                 rgb.blue,
                 rgb.green,
                 rgb.red );
      }
      break;

    case VIDEO_PALETTE_RGB32:

      // Max val
      fprintf( fp, "255\n" );

      // Write image data
      for ( i = 0; i < ( fr->width * fr->height ); i++ )
      {
        // Retrieve lower 24 bits of ARGB
        val = ((int*)(fr->data))[i] & 0x00ffffff;

        fprintf( fp, "%c%c%c",
                 ( val & 0x00ff0000 ) >> 16, // Blue
                 ( val & 0x0000ff00 ) >>  8, // Green
                 ( val & 0x000000ff )        // Red
                 );
      }
      break;

    case VIDEO_PALETTE_RGB565:
    case VIDEO_PALETTE_RGB555:

      // Max val
      fprintf( fp, "65535\n" );

      // Write image data
      for ( i = 0; i < ( fr->width * fr->height ); i++ )
      {
        // Retrieve 16-bit words
        val = ((short*)(fr->data))[i];

        fprintf( fp, "%c%c",
                 ( val & 0xff00 ) >> 8, // High
                 ( val & 0x00ff )       // Low
                 );
      }

      break;

    case VIDEO_PALETTE_YUV422:

      // Max val
      fprintf( fp, "255\n" );

      // Dump raw image data
      fwrite( fr->data,
              1, // YUV422 has 1 byte per pixel
              fr->width * fr->height,
              fp );
      break;

    case VIDEO_PALETTE_YUV420P:

      // Max val
      fprintf( fp, "255\n" );

      // Write image data (Y component only, so greyscale image)
      for ( i = 0; i < ( fr->width * fr->height ); i++ )
      {
        fprintf( fp, "%c", ((unsigned char*) fr->data)[i]);
        fprintf( fp, "%c", ((unsigned char*) fr->data)[i]);
        fprintf( fp, "%c", ((unsigned char*) fr->data)[i]);
      }
      break;

    default:
      // Unsupported!
      fprintf( stderr, "frame_save(): Unsupported type!\n" );
      return -1;
  }

  fclose( fp );

  return 0;
}

//==========================================================================
