/*
 * Cache1d declarations.
 *
 *  Written by Ryan C. Gordon. (icculus@lokigames.com)
 *
 * Please do NOT harrass Ken Silverman about any code modifications
 *  (including this file) to BUILD.
 */

// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.
// This file has been modified from Ken Silverman's original release

#ifndef _INCLUDE_CACHE1D_H_
#define _INCLUDE_CACHE1D_H_

void initcache(long dacachestart, long dacachesize);
void allocache (long *newhandle, long newbytes, unsigned char *newlockptr);
void suckcache (long *suckptr);
void agecache(void);
void reportandexit(char *errormessage);
long initgroupfile(char *filename);
void uninitgroupfile(void);
long kopen4load(unsigned char *filename, char searchfirst);
long kread(long handle, void *buffer, long leng);
long klseek(long handle, long offset, long whence);
long kfilelength(long handle);
void kclose(long handle);
void kdfread(void *buffer, size_t dasizeof, size_t count, long fil);
void dfread(void *buffer, size_t dasizeof, size_t count, FILE *fil);
void dfwrite(void *buffer, size_t dasizeof, size_t count, FILE *fil);
long compress(char *lzwinbuf, long uncompleng, char *lzwoutbuf);
long uncompress(char *lzwinbuf, long compleng, char *lzwoutbuf);

#endif
