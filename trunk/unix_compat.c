/*
 * Unix compatibility code. Takes care of some legacy code issues.
 *
 *  Written by Ryan C. Gordon (icculus@clutteredmind.org)
 *
 * Please do NOT harrass Ken Silverman about any code modifications
 *  (including this file) to BUILD.
 */

/*
 * "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
 * Ken Silverman's official web site: "http://www.advsys.net/ken"
 * See the included license file "BUILDLIC.TXT" for license info.
 * This file IS NOT A PART OF Ken Silverman's original release
 */

#ifndef PLATFORM_UNIX
#error Please define PLATFORM_UNIX to use this code.
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include "unix_compat.h"

/*
  256 byte table to assist in performing an
  algebraic shift right. These values represent
  all possible contributions of the sign bit 
  when shifted by different values.
 */
const int hbits[64] = 
{
    0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,
    0x00000000,0x00000000,0x00000000,0x00000000,
    0x80000000,0xC0000000,0xE0000000,0xF0000000, 
    0xF8000000,0xFC000000,0xFE000000,0xFF000000,
    0xFF800000,0xFFC00000,0xFFE00000,0xFFF00000,
    0xFFF80000,0xFFFC0000,0xFFFE0000,0xFFFF0000,
    0xFFFF8000,0xFFFFC000,0xFFFFE000,0xFFFFF000,
    0xFFFFF800,0xFFFFFC00,0xFFFFFE00,0xFFFFFF00,
    0xFFFFFF80,0xFFFFFFC0,0xFFFFFFE0,0xFFFFFFF0,
    0xFFFFFFF8,0xFFFFFFFC,0xFFFFFFFE,0xFFFFFFFF
};


#ifndef DC
int stricmp(const char *x, const char *y)
{
    int ux, uy;

    do
    {
        ux = toupper((int) *x);
        uy = toupper((int) *y);
        if (ux > uy)
            return(1);
        else if (ux < uy)
            return(-1);
        x++;
        y++;
    } while ((ux) && (uy));

    return(0);
} /* stricmp */
#endif /* DC */

long filelength(int fhandle)
{
    long retval = -1;
    struct stat stat_buf;
    if (fstat(fhandle, &stat_buf) == 0)
        retval = (long) stat_buf.st_size;
    return(retval);
} /* filelength */


/* !!! remove me later! */
int _inp_handler(int port, char *source_file, int source_line)
{
    fprintf(stderr, "inp(0x%X) call in %s, line %d.\n", port, source_file, source_line);
    return(0);
} /* _inp_handler */


/* !!! remove me later! */
int _kinp_handler(int port, char *source_file, int source_line)
{
    fprintf(stderr, "kinp(0x%X) call in %s, line %d.\n", port, source_file, source_line);
    return(0);
} /* _kinp_handler */

/* end of unix_compat.c ... */

