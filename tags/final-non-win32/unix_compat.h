/*
 * Unix compatibility header. Takes care of some legacy code issues.
 *
 *  Written by Ryan C. Gordon (icculus@lokigames.com)
 *
 * Please do NOT harrass Ken Silverman about any code modifications
 *  (including this file) to BUILD.
 */

// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.

#ifndef _INCLUDE_UNIX_COMPAT_H_
#define _INCLUDE_UNIX_COMPAT_H_

#if (!defined PLATFORM_UNIX)
#error PLATFORM_UNIX is not defined.
#endif

extern const int hbits[];

/*
  Do some bitwise magic to approximate an algebraic (sign preserving)
  right shift.
 */
#define shift_algebraic_right(value,distance) \
(((value) >> (distance))| \
 (hbits[(distance) + (((value) & 0x80000000) >> 26)]))

// !!! remove me later!
// !!! remove me later!
// !!! remove me later!
#define outpw(x, y)   printf("outpw(0x%X, 0x%X) call in %s, line %d.\n", \
                              (x), (y), __FILE__, __LINE__)

#define koutpw(x, y)  printf("koutpw(0x%X, 0x%X) call in %s, line %d.\n", \
                              (x), (y), __FILE__, __LINE__)

#define outb(x, y)    printf("outb(0x%X, 0x%X) call in %s, line %d.\n", \
                              (x), (y), __FILE__, __LINE__)

#define koutb(x, y)   printf("koutb(0x%X, 0x%X) call in %s, line %d.\n", \
                              (x), (y), __FILE__, __LINE__)

#define outp(x, y)    printf("outp(0x%X, 0x%X) call in %s, line %d.\n", \
                              (x), (y), __FILE__, __LINE__)

#define koutp(x, y)

 //printf("koutp(0x%X, 0x%X) call in %s, line %d.\n",
                      //        (x), (y), __FILE__, __LINE__)

#define kinp(x)       _kinp_handler((x), __FILE__, __LINE__)
#define inp(x)        _inp_handler((x), __FILE__, __LINE__)

int _inp_handler(int port, char *source_file, int source_line);
int _kinp_handler(int port, char *source_file, int source_line);
// !!! remove me later!
// !!! remove me later!
// !!! remove me later!




#define __far
#define __interrupt
#define interrupt
#define far
#define kmalloc(x) malloc(x)
#define kkmalloc(x) malloc(x)
#define kfree(x) free(x)
#define kkfree(x) free(x)
#define FP_OFF(x) ((long) (x))

#ifndef O_BINARY
#define O_BINARY 0
#endif

#ifndef stricmp
#define stricmp(a,b) strcasecmp(a,b)
#endif

#ifndef max
#define max(x, y)  (((x) > (y)) ? (x) : (y))
#endif

#ifndef min
#define min(x, y)  (((x) < (y)) ? (x) : (y))
#endif

// !!! This might be temporary.
#define printext16 printext256
#define printext16_noupdate printext256_noupdate

#define ENDLINE_CHAR '\n'

// VESA replacement code: The Unix (not-actually-VESA) version of this is
//  originally using SDL (Simple Directmedia Layer: http://www.libsdl.org/),
//  and is stored in sdl_driver.c, but there's no reason another driver
//  couldn't be dropped in, so long as it implements these functions. Please
//  reference sdl_driver.c and ves2.h (the original code) for all the nuances
//  and global variables that need to get set up correctly.

#include "SDL.h"   // need this for Uint?? typedefs.

    // move to display.h? !!!
void getvalidvesamodes(void);
int VBE_getPalette(long start, long num, char *dapal);
int VBE_setPalette(long start, long num, char *palettebuffer);
int setvesa(long x, long y);
void uninitvesa(void);
void setvmode(int mode);
unsigned char readpixel(long offset);
void drawpixel(long offset, Uint8 pixel);
void drawpixels(long offset, Uint16 pixels);
void drawpixelses(long offset, Uint32 pixelses);
void drawpixel16(long offset);
void fillscreen16 (long input1, long input2, long input3);
void limitrate(void);
//void printext16(long xpos, long ypos, short col, short backcol, char name[82], char fontsize);
void setactivepage(long dapagenum);
//void clear2dscreen(void);

// mouse/keystuff stuff. Also implemented in sdl_driver.c ...
int setupmouse(void);
void readmousexy(short *x, short *y);
void readmousebstatus(short *bstatus);
void keyhandler(void);
unsigned char _readlastkeyhit(void);

// timer krap.
void timerhandler(void);

// resolution inits. sdl_driver.c ...
int setgamemode(char davidoption, long daxdim, long daydim);
int _setgamemode(char davidoption, long daxdim, long daydim);
void qsetmode640350(void);
void qsetmode640480(void);


unsigned long getticks();


// Other DOSisms. See unix_compat.c for implementation.
long filelength(int fhandle);

// !!! need an implementation of findfirst()/findnext()!
//     Look for references to _dos_findfirst() in build.c!

#ifndef getch
#define getch() getchar()
#endif

#endif

// end of unix_compat.h ...

