/*
 * DOS compatibility header. Takes care of some legacy code issues.
 *
 *  Written by Ryan C. Gordon (icculus@lokigames.com)
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

// need these for something where we abstracted with SDL...
typedef unsigned long Uint32;
typedef unsigned short Uint16;
typedef unsigned char Uint8;

#include <io.h>
#include <conio.h>
#include <i86.h>
#include <dos.h>
#include <process.h>

#pragma intrinsic(min);
#pragma intrinsic(max);

#endif

// end of doscmpat.h ...


