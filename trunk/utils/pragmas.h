/*
 * Inline assembly.
 *
 * Initial PLATFORM_UNIX work done by Andrew Henderson. The DOS stuff is
 *  Ken's original code, and was in pragmas.h
 *
 * Please do NOT harrass Ken Silverman about any code modifications
 *  (including this file) to BUILD.
 */

// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.
// This file has been modified from Ken Silverman's original release

#ifdef PLATFORM_DOS

#warning I think you included the wrong pragmas.h file!

#endif

#ifdef USE_I386_ASM

int scale (int i1, int i2, int i3);
int mulscale (int i1, int i2, short i3);
int boundmulscale(int i1, int i2, int i3);
int divscale(int i1, int i2, int i3);
void clearbuf(void *buffer, int size, long fill_value); 

#else

#error Sorry, there are no C equivilents for the ASM functions yet

#endif

