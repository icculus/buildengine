// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.

#ifndef _SDL_DRIVER_H
#define _SDL_DRIVER_H

#include "SDL.h"

// Defines
#define kinp(x)       _kinp_handler((x), __FILE__, __LINE__)
#define inp(x)        _inp_handler((x), __FILE__, __LINE__)

// Variables
SDL_Surface *surface;

// Function Declarations
void setvmode(int mode);
void drawpixel(long offset, Uint8 pixel);
void limitrate(void);
void setactivepage(long dapagenum);

int setupmouse(void);
void readmousexy(short *x, short *y);
void readmousebstatus(short *bstatus);
void keyhandler(void);
unsigned char _readlastkeyhit(void);

static void timerhandler(void);
int _inp_handler(int port, char *source_file, int source_line);
int _kinp_handler(int port, char *source_file, int source_line);

#endif
