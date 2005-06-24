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

#include <string.h>	// memcpy
#include <stdio.h>
#include "platform.h"
#include "pragmas.h"

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


void clearbuf(void *buffer, int size, long fill_value) {
  int i;
  for (i = 0; i < size; i++) ((long*)buffer)[i] = fill_value;
}

void clearbufbyte(void *vpbuffer, int size, long fill_value) {
  unsigned char *buffer = (unsigned char *) vpbuffer;
  int lsize;
  switch(size){
  case 0: return;
  case 1: *buffer = fill_value; return;
  case 2: *((unsigned short*)buffer) = fill_value; return;
  case 3: { buffer[2]=buffer[1]=buffer[0] = fill_value;} return;
  default:
	if ((int)buffer&1) {
		*buffer = fill_value; size--;
        buffer++;
	}
	if ((int)buffer&2) {
		*((unsigned short*)buffer) = fill_value; size-=2;
        buffer += 2;
	}
	lsize = size>>2;
	while(lsize) {
		*((unsigned int*)buffer) = fill_value;
		lsize--;
        buffer += 4;
	}
	if (size&2) {
		*((unsigned short*)buffer) = fill_value;
        buffer += 2;
	}
	if (size&1) {
		*((unsigned char*)buffer) = fill_value;
        buffer++;
	}
  }
}

void copybuf(void *source, void *dest, int size) {
  int i;
  for (i = 0; i < size; i++) ((long*)dest)[i] = ((long*)source)[i];
}

void copybufbyte(void *source, void *dest, int size) {
  memcpy(dest,source,size);
}

void copybufreverse(void *source, void *dest, int size) {
  unsigned char *s=source,*d=dest;
  do {
    *d++ = *s--;
  } while(--size);
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
        unsigned short *src = (unsigned short *) source;
		*src = ((linum>>16)&0xffff);
        src++;
		linum += linum_inc;
        source = (long *) src;

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
		// DDOI - this fix is from the Amiga port guys
		// http://www.neoscientists.org/~dante/
#ifdef PLATFORM_BIGENDIAN
		int temp = linum & 0xffff0000;
		linum += linum_inc;
		temp |= (linum>>16);
		linum += linum_inc;
#else
		int temp = linum>>16;
		linum += linum_inc;
		temp += (linum&0xffff0000);
		linum += linum_inc;
#endif
		*source = temp;
		source++;
		size -= 2;
	}
	if (size & 1)
		*((unsigned short *)source) = ((linum>>16)&0xffff);
}

