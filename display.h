// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.

#ifndef _INCLUDE_DISPLAY_H_
#define _INCLUDE_DISPLAY_H_

#ifdef PLATFORM_DOS
#include "ves2.h"
#endif

extern long xres, yres, bytesperline, imageSize, maxpages;
extern char *screen, vesachecked;
extern long buffermode, origbuffermode, linearmode;
extern char permanentupdate, vgacompatible;
extern char moustat;
extern long *horizlookup, *horizlookup2, horizycent;
extern long oxdimen, oviewingrange, oxyaspect;
extern long curbrightness;
extern long qsetmode;
extern long frameplace, pageoffset, ydim16;
extern char textfont[1024], smalltextfont[1024];
extern char pow2char[8];
extern volatile long stereomode, visualpage, activepage, whiteband, blackband;
extern long searchx, searchy;
extern long wx1, wy1, wx2, wy2, ydimen;
extern long xdimen, xdimenrecip, halfxdimen, xdimenscale, xdimscale;

// !!! used to be static. If we ever put the original setgamemode() back, this
// !!! can be made static again.  --ryan.
// !!! (Actually, most of these extern declarations used to be static...rcg.)
extern char permanentlock;



// these are implemented in BUILD:
void setview(long x1, long y1, long x2, long y2);
void clearallviews(long dacol);
void setbrightness(char dabrightness, unsigned char *dapal);


// these need to be implemented by YOUR driver.
void _platform_init(int argc, char **argv, const char *title, const char *icon);
void _idle(void);
void *_getVideoBase(void);
void _initkeys(void);

// !!! move the stuff from unix_compat.h into here. --ryan.


// rcg08012000 this could use a better abstraction...maybe I want a non-SDL
//  driver on UNIX?  GGI?
#ifdef PLATFORM_DOS
#define VIDEOBASE 0xa0000
#else
extern SDL_Surface *surface;
#define VIDEOBASE surface->pixels
#endif

#endif

