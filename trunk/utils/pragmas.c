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

#error Do not compile with pragmas.c on DOS! 

#endif

#ifdef USE_I386_ASM

int scale (int i1, int i2, int i3) {
  int retval;
  __asm__ __volatile__ ("
    imull 	%%edx
    idivl 	%%ecx	
  " : "=a" (retval) : "a" (i1), "d" (i2), "c" (i3) : "cc");
  return(retval);
}

int mulscale (int i1, int i2, short i3) {
  int retval;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl %%cl, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "c" (i3) : "cc");
  return(retval);
}

int boundmulscale(int i1, int i2, int i3) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%ebx
	movl %%edx, %%ebx
	shrdl %%cl, %%edx, %%eax
	sarl %%cl, %%edx
	xorl %%eax, %%edx
	js checkit
	xorl %%eax, %%edx
	jz skipboundit
	cmpl $0xffffffff, %%edx
	je skipboundit
	checkit:
	movl %%ebx, %%eax
	sarl $31, %%eax
	xorl $0x7fffffff, %%eax
	skipboundit:
  " : "=a" (retval) : "a" (i1), "b" (i2), "c" (i3) : "edx", "cc");
  return(retval);
}

int divscale(int i1, int i2, int i3) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	shll %%cl, %%eax
	negb  %%cl
	sarl %%cl, %%edx
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2), "c" (i3) : "edx", "cc");
  return(retval);
}

void clearbuf(void *buffer, int size, long fill_value) {
  __asm__ __volatile__ ("
	rep
    stosl
  " : : "D" (buffer), "c" (size), "a" (fill_value) : "cc");
}

#else

#error Sorry, there are no C equivilents for the ASM functions yet

#endif

