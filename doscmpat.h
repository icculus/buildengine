/*
 * DOS compatibility header. Takes care of some legacy code issues.
 *
 *  Written by Ryan C. Gordon (icculus@clutteredmind.org)
 *
 * Please do NOT harrass Ken Silverman about any code modifications
 *  (including this file) to BUILD.
 */

// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.

#ifndef _INCLUDE_DOS_COMPAT_H_
#define _INCLUDE_DOS_COMPAT_H_

#if (!defined PLATFORM_DOS)
#error PLATFORM_DOS is not defined.
#endif

#if (defined PLATFORM_SUPPORTS_SDL)
#warning You have PLATFORM_SUPPORTS_SDL defined.
#warning This is almost certainly wrong.
#endif

#define PLATFORM_TIMER_HZ 280

#if ((!defined __WATCOMC__) && (!defined __int64))
#define __int64 long long
#endif

// need these for something where we abstracted with SDL...
typedef unsigned long Uint32;
typedef unsigned short Uint16;
typedef unsigned char Uint8;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <conio.h>
#include <i86.h>
#include <dos.h>
#include <process.h>
#include <direct.h>

#pragma intrinsic(min);
#pragma intrinsic(max);

void printext16(long xpos, long ypos, short col, short backcol, char name[82], char fontsize);

void *kkmalloc(size_t size);
void *kmalloc(size_t i1);
void kkfree(void *i1);
void kfree(void *i1);

void setstereo(long dastereomode);
void printscreeninterrupt(void);

void setvmode(int i1);
#pragma aux setvmode =\
        "int 0x10",\
        parm [eax]\

#endif

// end of doscmpat.h ...


