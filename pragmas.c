/*
 * Inline assembly.
 *
 * Initial PLATFORM_UNIX work done by Andrew Henderson. The DOS stuff is
 *  Ken's original code, and was in pragmas.h
 *
 * Please do NOT harrass Ken Silverman about any code modifications
 *  (including this file) to BUILD.
 */

/*
 * "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
 * Ken Silverman's official web site: "http://www.advsys.net/ken"
 * See the included license file "BUILDLIC.TXT" for license info.
 * This file has been modified from Ken Silverman's original release
 */

#include <stdio.h>
#include "platform.h"

static long dmval;

#define low32(a) ((a&0xffffffff))

unsigned long getkensmessagecrc(long param) {
    return(0x56c764d4);
}

long msqrtasm(int i1)
{
    int retval = 0x40000000;
    int temp = 0x20000000;

    while (temp != 0)
    {
	    if (i1 >= retval)
	    {
		    i1 -= retval;
		    retval += temp*4;
	    }
	    retval -= temp;
	    retval >>= 1;
	    temp >>= 2;
    }

    if (i1 >= retval) retval--;
    retval >>= 1;
    return(retval);
}

int sqr (int i1) {
    return (i1*i1);
}

int scale (int i1, int i2, int i3) {
  return (int)((__int64)i1 * (__int64)i2 / (__int64) i3);
}

int mulscale (int i1, int i2, short i3) {
  unsigned int retval;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>i3));
  return(retval);
}

int mulscale1 (int i1, int i2) {
  unsigned int retval;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>1));
  return(retval);
}

int mulscale2 (int i1, int i2) {
  unsigned int retval;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>2));
  return(retval);
}

int mulscale3 (int i1, int i2) {
  unsigned int retval;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>3));
  return(retval);
}

int mulscale4 (int i1, int i2) {
  unsigned int retval;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>4));
  return(retval);
}

int mulscale5 (int i1, int i2) {
  unsigned int retval;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>5));
  return(retval);
}

int mulscale6 (int i1, int i2) {
  unsigned int retval;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>6));
  return(retval);
}

int mulscale7 (int i1, int i2) {
  unsigned int retval;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>7));
  return(retval);
}

int mulscale8 (int i1, int i2) {
  unsigned int retval;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>8));
  return(retval);
}

int mulscale9 (int i1, int i2) {
  unsigned int retval;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>9));
  return(retval);
}

int mulscale10 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>10));
  return(retval);
}

int mulscale11 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>11));
  return(retval);
}

int mulscale12 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>12));
  return(retval);
}

int mulscale13 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>13));
  return(retval);
}

int mulscale14 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>14));
  return(retval);
}

int mulscale15 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>15));
  return(retval);
}

int mulscale16 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>16));
  return(retval);
}

int mulscale17 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>17));
  return(retval);
}

int mulscale18 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>18));
  return(retval);
}

int mulscale19 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>19));
  return(retval);
}

int mulscale20 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>20));
  return(retval);
}

int mulscale21 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>21));
  return(retval);
}

int mulscale22 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>22));
  return(retval);
}

int mulscale23 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>23));
  return(retval);
}

int mulscale24 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>24));
  return(retval);
}

int mulscale25 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>25));
  return(retval);
}

int mulscale26 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>26));
  return(retval);
}

int mulscale27 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>27));
  return(retval);
}

int mulscale28 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>28));
  return(retval);
}

int mulscale29 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>29));
  return(retval);
}

int mulscale30 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>30));
  return(retval);
}

int mulscale31 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>31));
  return(retval);
}

int mulscale32 (int i1, int i2) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  retval = low32 ((scratch1>>32));
  return(retval);
}

int divmod (int i1, int i2) {
  int retval;
  dmval = i1%i2;
  retval = i1/i2;
  return(retval);
}

int dmulscale(int i1, int i2, int i3, int i4, int i5) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>i5));
  return(retval);
}

int dmulscale1(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>1));
  return(retval);
}

int dmulscale2(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>2));
  return(retval);
}

int dmulscale3(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>3));
  return(retval);
}

int dmulscale4(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>4));
  return(retval);
}

int dmulscale5(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>5));
  return(retval);
}

int dmulscale6(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>6));
  return(retval);
}

int dmulscale7(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>7));
  return(retval);
}

int dmulscale8(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>8));
  return(retval);
}

int dmulscale9(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>9));
  return(retval);
}

int dmulscale10(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>10));
  return(retval);
}

int dmulscale11(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>11));
  return(retval);
}

int dmulscale12(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>12));
  return(retval);
}

int dmulscale13(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>13));
  return(retval);
}

int dmulscale14(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>14));
  return(retval);
}

int dmulscale15(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>15));
  return(retval);
}

int dmulscale16(int i1, int i2, int i3, int i4) {
  unsigned int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>16));
  return(retval);
}

int dmulscale17(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>17));
  return(retval);
}

int dmulscale18(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>18));
  return(retval);
}

int dmulscale19(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>19));
  return(retval);
}

int dmulscale20(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>20));
  return(retval);
}

int dmulscale21(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>21));
  return(retval);
}

int dmulscale22(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>22));
  return(retval);
}

int dmulscale23(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>23));
  return(retval);
}

int dmulscale24(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>24));
  return(retval);
}

int dmulscale25(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>25));
  return(retval);
}

int dmulscale26(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>26));
  return(retval);
}

int dmulscale27(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>27));
  return(retval);
}

int dmulscale28(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>28));
  return(retval);
}

int dmulscale29(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>29));
  return(retval);
}


int dmulscale30(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>30));
  return(retval);
}

int dmulscale31(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>31));
  return(retval);
}

int dmulscale32(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  scratch1 = scratch1 + scratch2;
  retval = low32 ((scratch1>>32));
  return(retval);
}

int tmulscale1(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>1));
  return(retval);
}

int tmulscale2(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>2));
  return(retval);
}

int tmulscale3(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>3));
  return(retval);
}

int tmulscale4(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>4));
  return(retval);
}

int tmulscale5(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>5));
  return(retval);
}

int tmulscale6(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>6));
  return(retval);
}

int tmulscale7(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>7));
  return(retval);
}

int tmulscale8(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>8));
  return(retval);
}

int tmulscale9(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>9));
  return(retval);
}

int tmulscale10(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>10));
  return(retval);
}

int tmulscale11(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>11));
  return(retval);
}

int tmulscale12(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>12));
  return(retval);
}

int tmulscale13(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>13));
  return(retval);
}

int tmulscale14(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>14));
  return(retval);
}

int tmulscale15(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>15));
  return(retval);
}

int tmulscale16(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>16));
  return(retval);
}

int tmulscale17(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>17));
  return(retval);
}

int tmulscale18(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>18));
  return(retval);
}

int tmulscale19(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>19));
  return(retval);
}

int tmulscale20(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>20));
  return(retval);
}

int tmulscale21(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>21));
  return(retval);
}

int tmulscale22(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>22));
  return(retval);
}

int tmulscale23(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>23));
  return(retval);
}

int tmulscale24(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>24));
  return(retval);
}

int tmulscale25(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>25));
  return(retval);
}

int tmulscale26(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>26));
  return(retval);
}

int tmulscale27(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>27));
  return(retval);
}

int tmulscale28(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>28));
  return(retval);
}

int tmulscale29(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>29));
  return(retval);
}

int tmulscale30(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>30));
  return(retval);
}

int tmulscale31(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>31));
  return(retval);
}

int tmulscale32(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __int64 scratch1 = (__int64) i1 * (__int64) i2;
  __int64 scratch2 = (__int64) i3 * (__int64) i4;
  __int64 scratch3 = (__int64) i5 * (__int64) i6;
  scratch1 = scratch1 + scratch2 + scratch3;
  retval = low32 ((scratch1>>32));
  return(retval);
}

int boundmulscale(int i1, int i2, int i3) {
  return 0;
}

int divscale(int i1, int i2, int i3) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-i3)))<<32)|(((__int64)(i1<<i3))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale1(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-1)))<<32)|(((__int64)(i1<<1))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}


int divscale2(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-2)))<<32)|(((__int64)(i1<<2))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale3(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-3)))<<32)|(((__int64)(i1<<3))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale4(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-4)))<<32)|(((__int64)(i1<<4))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale5(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-5)))<<32)|(((__int64)(i1<<5))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale6(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-6)))<<32)|(((__int64)(i1<<6))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale7(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-7)))<<32)|(((__int64)(i1<<7))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale8(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-8)))<<32)|(((__int64)(i1<<8))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale9(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-9)))<<32)|(((__int64)(i1<<9))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale10(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-10)))<<32)|(((__int64)(i1<<10))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale11(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-11)))<<32)|(((__int64)(i1<<11))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale12(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-12)))<<32)|(((__int64)(i1<<12))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale13(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-13)))<<32)|(((__int64)(i1<<13))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale14(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-14)))<<32)|(((__int64)(i1<<14))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale15(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-15)))<<32)|(((__int64)(i1<<15))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale16(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-16)))<<32)|(((__int64)(i1<<16))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale17(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-17)))<<32)|(((__int64)(i1<<17))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale18(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-18)))<<32)|(((__int64)(i1<<18))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale19(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-19)))<<32)|(((__int64)(i1<<19))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale20(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-20)))<<32)|(((__int64)(i1<<20))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale21(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-21)))<<32)|(((__int64)(i1<<21))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale22(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-22)))<<32)|(((__int64)(i1<<22))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale23(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-23)))<<32)|(((__int64)(i1<<23))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale24(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-24)))<<32)|(((__int64)(i1<<24))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale25(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-25)))<<32)|(((__int64)(i1<<25))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale26(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-26)))<<32)|(((__int64)(i1<<26))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale27(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-27)))<<32)|(((__int64)(i1<<27))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale28(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-28)))<<32)|(((__int64)(i1<<28))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale29(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-29)))<<32)|(((__int64)(i1<<29))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale30(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-30)))<<32)|(((__int64)(i1<<30))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale31(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1>>(32-31)))<<32)|(((__int64)(i1<<31))&(__int64)0x00000000ffffffff)) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int divscale32(int i1, int i2) {
  int retval = 0;
  __int64 temp = ((((__int64)(i1)))<<32) / (__int64)i2;
  retval = low32(temp);
  return(retval);
}

int mul3 (int i1) {
  return i1*3;
}

int mul5 (int i1) {
  return i1*5;
}

int mul9 (int i1) {
  return i1*9;
}

void clearbuf(void *buffer, int size, long fill_value) {
  int i;
  for (i = 0; i < size; i++) ((long*)buffer)[i] = fill_value;
}

void clearbufbyte(void *buffer, int size, long fill_value) {
  if (size < 4) {
	  if (size&1) {
		  *((unsigned char*)buffer)++ = fill_value;
	  }
	  size = size >> 1;
	  while (size) {
		  *((unsigned short*)buffer)++ = fill_value;
		  size--;
	  }
  } else {
	  int oldsize;
	  if (size&1) {
		  *((unsigned char*)buffer)++ = fill_value;
		  size--;
	  }
	  if (size&2) {
		  *((unsigned short*)buffer)++ = fill_value;
		  size -= 2;
	  }
	  oldsize = size;
	  size = size >> 2;
	  while (size) {
		  *((unsigned int*)buffer)++ = fill_value;
		  size--;
	  }
	  if (oldsize&2) {
		  *((unsigned short*)buffer)++ = fill_value;
	  }
	  if (oldsize&1) {
		  *((unsigned char*)buffer)++ = fill_value;
	  }
  }
}

void copybuf(void *source, void *dest, int size) {
  int i;
  for (i = 0; i < size; i++) ((long*)dest)[i] = ((long*)source)[i];
}

void copybufbyte(void *source, void *dest, int size) {
  if (size < 4) {
	  if (size&1) {
		  *((unsigned char*)dest)++ = *((unsigned char*)source)++;
	  }
	  size = size >> 1;
	  while (size) {
		  *((unsigned short*)dest)++ = *((unsigned short*)source)++;
		  size--;
	  }
  } else {
	  int oldsize;
	  if (size&1) {
		  *((unsigned char*)dest)++ = *((unsigned char*)source)++;
		  size--;
	  }
	  if (size&2) {
		  *((unsigned short*)dest)++ = *((unsigned short*)source)++;
		  size -= 2;
	  }
	  oldsize = size;
	  size = size >> 2;
	  while (size) {
		  *((unsigned int*)dest)++ = *((unsigned int*)source)++;
		  size--;
	  }
	  if (oldsize&2) {
		  *((unsigned short*)dest)++ = *((unsigned short*)source)++;
	  }
	  if (oldsize&1) {
		  *((unsigned char*)dest)++ = *((unsigned char*)source)++;
	  }
  }
}

void copybufreverse(void *source, void *dest, int size) {
  if (size&1)
  {
	  *((unsigned char*)dest)++ = *((unsigned char*)source)--;
  }
  size = size / 2;
  if (size&1)
  {
	  unsigned short a;
	  ((unsigned char*)source)--;
	  a = *((unsigned short*)source)--;
	  ((unsigned char*)source)++;
	  *((unsigned short*)dest)++ = ((a>>8)|(a<<8));
  }
  size = size / 2;
  while (size)
  {
	  unsigned int a;
	  ((unsigned char*)source) -= 3;
	  a = *((unsigned int*)source)--;
	  ((unsigned char*)source) += 3;
	  *((unsigned int*)dest)++ = ((a<<24)|((a<<8)&0x00FF0000)|((a>>8)&0x0000FF00)|(a>>24));
	  size--;
  }
  return;

  __asm__ __volatile__ (
	"shrl $1, %%ecx   \n\t"
	"jnc skipit1   \n\t"
	"movb (%%esi), %%al   \n\t"
	"decl %%esi   \n\t"
	"movb %%al, (%%edi)   \n\t"
	"incl %%edi   \n\t"
	"skipit1: shrl $1, %%ecx   \n\t"
	"jnc skipit2   \n\t"
	"movw -1(%%esi), %%ax   \n\t"
	"subl $2, %%esi   \n\t"
	"rorw $8, %%ax   \n\t"
	"movw %%ax, (%%edi)   \n\t"
	"addl $2, %%edi   \n\t"
	"skipit2: testl %%ecx, %%ecx   \n\t"
	"jz endloop   \n\t"
	"begloop: movl -3(%%esi), %%eax   \n\t"
	"subl $4, %%esi   \n\t"
	"bswapl %%eax   \n\t"
	"movl %%eax, (%%edi)   \n\t"
	"addl $4, %%edi   \n\t"
	"decl %%ecx   \n\t"
	"jnz begloop   \n\t"
	"endloop:   \n\t"
   : : "S" (source), "D" (dest), "c" (size) : "cc");
}

void qinterpolatedown16 (long *source, int size, int linum, int linum_inc) {
	if (size == 0)
	{
		*source = (linum>>16);
		return;
	}

	while (size)
	{
		*source = (linum>>16);
		source++;
		linum += linum_inc;
		size--;
	}
}

void qinterpolatedown16short (long *source, int size, int linum, int linum_inc)
{
	if (size == 0) return;

	if ((long)source & 0x2)
	{
		*((unsigned short *)source) = ((linum>>16)&0xffff);
		linum += linum_inc;
		((unsigned char*)source) = ((unsigned char*)source) + 2;
		size--;
		if (size == 0) return;
	}
	size -= 2;
	if (size < 0)
	{
		*((unsigned short *)source) = ((linum>>16)&0xffff);
		return;
	}

	while (size >= 0)
	{
		int temp = linum>>16;
		linum += linum_inc;
		temp += (linum&0xffff0000);
		linum += linum_inc;
		*source = temp;
		source++;
		size -= 2;
	}
	if (size & 1)
		*((unsigned short *)source) = ((linum>>16)&0xffff);
}

int klabs (int i1) {
  if (i1 < 0) i1 = -i1;
  return i1;
}

int ksgn(int i1) {
  if (i1 < 0) return -1;
  else if (i1 > 0) return 1;
  else return 0;
}

int sgn(int i1) {
  if (i1 < 0) return -1;
  else if (i1 > 0) return 1;
  else return 0;
}

void swapchar(unsigned char *p1, unsigned char *p2)
{
    unsigned char tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
} /* swapchar */

void swapshort(short *p1, short *p2)
{
    short tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
} /* swapshort */

void swaplong(long *p1, long *p2)
{
    long tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
} /* swaplong */

void swapchar2(unsigned char *p1, unsigned char *p2, int xsiz)
{
    swapchar(p1, p2);
    swapchar(p1 + 1, p2 + xsiz);
} /* swapchar2 */

