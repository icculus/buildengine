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

// Defines
#define outpw(x, y)
#define koutpw(x, y)
#define outb(x, y)
#define koutb(x, y)
#define outp(x, y)
#define koutp(x, y)

#define __far
#define __interrupt
#define interrupt
#define far
#define kmalloc(x) malloc(x)
#define kkmalloc(x) malloc(x)
#define kfree(x) free(x)
#define kkfree(x) free(x)
#define FP_OFF(x) ((long) (x))

#define VIDEOBASE surface->pixels
// Need this for FNM_CASEFOLD
#define _GNU_SOURCE

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

#ifndef getch
#define getch() getchar()
#endif

// Sane writing permissions for Unix systems
#define UC_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#endif
