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


#if (defined __WATCOMC__)
  #if ((defined PLATFORM_DOS) || (defined PLATFORM_WIN32))
    #error Do not compile this. Just include pragmas.h instead.
  #endif
#endif

#ifdef USE_I386_ASM

static long dmval;

// rcg02132001 Cygwin support.
#if (defined C_IDENTIFIERS_UNDERSCORED)
#define SYM_dmval   "_dmval"
#else
#define SYM_dmval   "dmval"
#endif

static inline void _touch_dmval_stop_compiler_whining(void)
{
    dmval = 0;
}


int sqr (int i1) {
  int retval;
  __asm__ __volatile__ ("
    imull 	%%eax, %%eax
  " : "=a" (retval) : "a" (i1) : "cc");
  return(retval);
}

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

int mulscale1 (int i1, int i2) {
  int retval;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $1, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale2 (int i1, int i2) {
  int retval;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $2, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale3 (int i1, int i2) {
  int retval;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $3, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale4 (int i1, int i2) {
  int retval;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $4, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale5 (int i1, int i2) {
  int retval;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $5, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale6 (int i1, int i2) {
  int retval;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $6, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale7 (int i1, int i2) {
  int retval;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $7, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale8 (int i1, int i2) {
  int retval;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $8, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale9 (int i1, int i2) {
  int retval;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $9, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale10 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $10, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale11 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $11, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale12 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $12, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale13 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $13, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale14 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $14, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale15 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $15, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale16 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $16, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale17 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $17, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale18 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $18, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale19 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $19, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale20 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $20, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale21 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $21, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale22 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $22, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale23 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $23, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale24 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $24, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale25 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $25, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale26 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $26, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale27 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $27, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale28 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $28, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale29 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $29, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale30 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $30, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale31 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
    shrdl $31, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int mulscale32 (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    imull %%edx
  " : "=d" (retval) : "a" (i1), "d" (i2) : "cc");
  return(retval);
}

int divmod (int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
    xorl %%edx, %%edx
    divl %%ebx
    movl %%edx, " SYM_dmval "
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "memory", "cc");
  return(retval);
}

int dmulscale(int i1, int i2, int i3, int i4, int i5) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl %%cl, %%edx, %%eax     
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4), "c" (i5)
    : "ebx", "cc");
  return(retval);
}

int dmulscale1(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $1, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale2(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $2, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale3(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $3, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale4(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $4, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale5(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $5, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale6(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $6, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale7(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $7, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale8(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $8, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale9(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $9, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale10(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $10, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale11(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $11, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale12(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $12, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale13(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $13, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale14(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $14, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale15(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $15, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale16(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $16, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale17(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $17, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale18(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $18, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale19(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $19, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale20(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $20, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale21(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $21, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale22(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $22, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale23(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $23, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale24(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $24, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale25(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $25, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale26(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $26, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale27(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $27, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale28(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $28, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale29(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $29, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}


int dmulscale30(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $30, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale31(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
	shrdl $31, %%edx, %%eax
  " : "=a" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int dmulscale32(int i1, int i2, int i3, int i4) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	movl %%eax, %%ebx
	movl %%esi, %%eax
	movl %%edx, %%esi
	imull %%edi
	addl %%ebx, %%eax
	adcl %%esi, %%edx
  " : "=d" (retval) : "a" (i1), "d" (i2), "S" (i3), "D" (i4)
    : "ebx", "cc");
  return(retval);
}

int tmulscale1(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $1, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale2(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $2, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale3(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $3, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale4(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $4, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale5(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $5, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale6(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $6, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale7(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $7, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale8(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $8, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale9(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $9, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale10(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $10, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale11(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $11, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale12(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $12, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale13(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $13, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale14(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $14, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale15(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $15, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale16(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $16, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale17(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $17, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale18(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $18, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale19(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $19, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale20(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $20, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale21(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $21, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale22(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $22, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale23(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $23, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale24(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $24, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale25(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $25, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale26(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $26, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale27(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $27, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale28(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $28, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale29(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $29, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale30(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $30, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale31(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
	shrdl $31, %%edx, %%eax
  " : "=a" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
  return(retval);
}

int tmulscale32(int i1, int i2, int i3, int i4, int i5, int i6) {
  int retval = 0;
  __asm__ __volatile__ ("
	imull %%edx
	xchgl %%ebx, %%eax
	xchgl %%ecx, %%edx
	imull %%edx
	addl %%eax, %%ebx
	adcl %%edx, %%ecx
	movl %%esi, %%eax
	imull %%edi
	addl %%ebx, %%eax
	adcl %%ecx, %%edx
  " : "=d" (retval)
    : "a" (i1), "d" (i2), "b" (i3), "c" (i4), "S" (i5), "D" (i6)
    : "cc");
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

int divscale1(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	addl %%eax, %%eax
	sbbl %%edx, %%edx
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}


int divscale2(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $30, %%edx
	leal (, %%eax, 4), %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale3(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $29, %%edx
	leal (, %%eax, 8), %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale4(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $28, %%edx
	shll $4, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale5(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $27, %%edx
	shll $5, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale6(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $26, %%edx
	shll $6, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale7(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $25, %%edx
	shll $7, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale8(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $24, %%edx
	shll $8, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale9(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $23, %%edx
	shll $9, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale10(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $22, %%edx
	shll $10, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale11(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $21, %%edx
	shll $11, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale12(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $20, %%edx
	shll $12, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale13(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $19, %%edx
	shll $13, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale14(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $18, %%edx
	shll $14, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale15(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $17, %%edx
	shll $15, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale16(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $16, %%edx
	shll $16, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale17(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $15, %%edx
	shll $17, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale18(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $14, %%edx
	shll $18, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale19(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $13, %%edx
	shll $19, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale20(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $12, %%edx
	shll $20, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale21(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $11, %%edx
	shll $21, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale22(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $10, %%edx
	shll $22, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale23(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $9, %%edx
	shll $23, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale24(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $8, %%edx
	shll $24, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale25(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $7, %%edx
	shll $25, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale26(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $6, %%edx
	shll $26, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale27(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $5, %%edx
	shll $27, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale28(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $4, %%edx
	shll $28, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale29(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $3, %%edx
	shll $29, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale30(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $2, %%edx
	shll $30, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale31(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	movl %%eax, %%edx
	sarl $1, %%edx
	shll $31, %%eax
	idivl %%ebx
  " : "=a" (retval) : "a" (i1), "b" (i2) : "edx", "cc");
  return(retval);
}

int divscale32(int i1, int i2) {
  int retval = 0;
  __asm__ __volatile__ ("
	xorl %%eax, %%eax
	idivl %%ebx
  " : "=a" (retval) : "d" (i1), "b" (i2): "cc");
  return(retval);
}

int mul3 (int i1) {
  int output;
  __asm__ __volatile__ ("
    leal (%1, %1, 2), %1
  " : "=r" (output) : "r" (i1) : "cc");
  return (output);
}

int mul5 (int i1) {
  int output;
  __asm__ __volatile__ ("
    leal (%1, %1, 4), %1
  " : "=r" (output) : "r" (i1) : "cc");
  return (output);
}

int mul9 (int i1) {
  int output;
  __asm__ __volatile__ ("
    leal (%1, %1, 8), %1
  " : "=r" (output) : "r" (i1) : "cc");
  return (output);
}

void clearbuf(void *buffer, int size, long fill_value) {
  __asm__ __volatile__ ("
	rep
    stosl
  " : : "D" (buffer), "c" (size), "a" (fill_value) : "cc");
}

void clearbufbyte(void *buffer, int size, long fill_value) {
  __asm__ __volatile__ ("
	cmpl $4, %%ecx
	jae longcopya
	testb $1, %%cl
	jz preskipa
	stosb
	preskipa: shrl $1, %%ecx
	rep
    stosw
	jmp endita
	longcopya: testl $1, %%edi
	jz skip1a
	stosb
	decl %%ecx
	skip1a: testl $2, %%edi
	jz skip2a
	stosw
	subl $2, %%ecx
	skip2a: movl %%ecx, %%ebx
	shrl $2, %%ecx
    rep
    stosl
	testb $2, %%bl
	jz skip3a
	stosw
	skip3a: testb $1, %%bl
	jz endita
	stosb
	endita:
  " : : "D" (buffer), "c" (size), "a" (fill_value) : "ebx", "cc");
}

void copybuf(void *source, void *dest, int size) {
  __asm__ __volatile__ ("
	rep
    movsl
  " : : "S" (source), "D" (dest), "c" (size) : "cc");
}

void copybufbyte(void *source, void *dest, int size) {
  __asm__ __volatile__ ("
	cmpl $4, %%ecx
	jae longcopyb
	testb $1, %%cl
	jz preskipb
	movsb
	preskipb: shrl $1, %%ecx
	rep
    movsw
	jmp enditb
	longcopyb: testl $1, %%edi
	jz skip1b
	movsb
	decl %%ecx
	skip1b: testl $2, %%edi
	jz skip2b
	movsw
	sub $2, %%ecx
	skip2b: mov %%ecx, %%ebx
	shr $2, %%ecx
	rep
    movsl
	testb $2, %%bl
	jz skip3b
	movsw
	skip3b: testb $1, %%bl
	jz enditb
	movsb
	enditb:
  " : : "S" (source), "D" (dest), "c" (size) : "ebx", "cc");
}

void copybufreverse(void *source, void *dest, int size) {
  __asm__ __volatile__ ("
	shrl $1, %%ecx
	jnc skipit1
	movb (%%esi), %%al
	decl %%esi
	movb %%al, (%%edi)
	incl %%edi
	skipit1: shrl $1, %%ecx
	jnc skipit2
	movw -1(%%esi), %%ax
	subl $2, %%esi
	rorw $8, %%ax
	movw %%ax, (%%edi)
	addl $2, %%edi
	skipit2: testl %%ecx, %%ecx
	jz endloop
	begloop: movl -3(%%esi), %%eax
	subl $4, %%esi
	bswapl %%eax
	movl %%eax, (%%edi)
	addl $4, %%edi
	decl %%ecx
	jnz begloop
	endloop:
  " : : "S" (source), "D" (dest), "c" (size) : "cc");
}

void qinterpolatedown16 (long *source, int size, int linum, int linum_inc) {
  __asm__ __volatile__ ("
	movl %%ecx, %%ebx
	shrl $1, %%ecx
	jz skipbegcalc
	begqcalc: leal (%%esi, %%edx), %%edi
	sarl $16, %%edx
	movl %%edx, (%%eax)
	leal (%%edi, %%esi), %%edx
	sarl $16, %%edi
	movl %%edi, 4(%%eax)
	addl $8, %%eax
	decl %%ecx
	jnz begqcalc
	testl $1, %%ebx
	jz skipbegqcalc2
	skipbegcalc: sarl $16, %%edx
	movl %%edx, (%%eax)
	skipbegqcalc2:
  ": :"a" (source), "c" (size), "d" (linum), "S" (linum_inc) : "ebx", "edi", "cc", "memory" );
}

void qinterpolatedown16short (long *source, int size, int linum, int linum_inc)
{
  __asm__ __volatile__ ("
	testl %%ecx, %%ecx
	jz endit
	testb $2, %%al
	jz skipalignit
	movl %%edx, %%ebx
	sarl $16, %%ebx
	movw %%bx, (%%eax)
	addl %%esi, %%edx
	addl $2, %%eax
	decl %%ecx
	jz endit
	skipalignit: subl $2, %%ecx
	jc finishit
	bbegqcalc: movl %%edx, %%ebx
	addl %%esi, %%edx
	sarl $16, %%ebx
	movl %%edx, %%edi
	andl $0xffff0000, %%edi
	addl %%esi, %%edx
	addl %%edi, %%ebx
	movl %%ebx, (%%eax)
	addl $4, %%eax
	subl $2, %%ecx
	jnc bbegqcalc
	testb $1, %%cl
	jz endit
	finishit: movl %%edx, %%ebx
	sarl $16, %%ebx
	movw %%bx, (%%eax)
	endit:
  ": :"a" (source), "c" (size), "d" (linum), "S" (linum_inc) : "ebx", "edi", "cc", "memory");
}

void vlin16first (long i1, long i2) {
  __asm__ __volatile__ ("
  	movb 	(%%edi), %%al
	movl 	%%ecx, %%eax
	shrl 	$2, %%ecx
	
	begvlin16firsta:
		movb	%%al, (%%edi)
		movb 	%%al, 80(%%edi)
		movb 	%%al, 160(%%edi)
		movb 	%%al, 240(%%edi)
		addl 	$320, %%edi
		decl 	%%ecx
	jnz 	begvlin16firsta
	
	movl 	%%eax, %%ecx
	andl 	$3, %%ecx
	jz 	skipfirst
	begvlin16firstb:
		movb	%%al, (%%edi)
		addl 	$80, %%edi
		decl 	%%ecx
	jnz begvlin16firstb
	skipfirst:
  "
  : : "D" (i1), "c" (i2) : "cc", "memory");
}

void vlin16 (long i1, long i2) {
  __asm__ __volatile__ ("
  	movl 	%%edi, %%esi
	begvlin16:
		movsb
		addl 	$79, %%edi
		addl 	$79, %%esi
		decl 	%%ecx
	jnz 	begvlin16
  "
  : : "D" (i1), "c" (i2) : "cc", "memory");

}

int klabs (int i1) {
  int retval = 0;
  __asm__ __volatile__ ("
	testl %%eax, %%eax
	jns skipnegate
	negl %%eax
	skipnegate:
  " : "=a" (retval) : "a" (i1) : "cc");
  return(retval);
}

int ksgn(int i1) {
  int retval = 0;
  __asm__ __volatile__ ("
	addl %%ebx, %%ebx
	sbbl %%eax, %%eax
	cmpl %%ebx, %%eax
	adcb $0, %%al
  " : "=a" (retval) : "b" (i1) : "cc");
  return(retval);
}

void swapchar(int i1, int i2) {
  __asm__ __volatile__ ("
	movb (%%eax), %%cl
	movb (%%ebx), %%ch
	movb %%cl, (%%ebx)
	movb %%ch, (%%eax)
  " : : "a" (i1), "b" (i2) : "ecx", "cc", "memory");
}

void swapshort(int i1, int i2) {
  __asm__ __volatile__ ("
	movw (%%eax), %%cx
	movw (%%ebx), %%dx
	movw %%cx, (%%ebx)
	movw %%dx, (%%eax)
  " : : "a" (i1), "b" (i2) : "ecx", "edx", "cc", "memory");
}


void swaplong(int i1, int i2) {
  __asm__ __volatile__ ("
	movl (%%eax), %%ecx
	movl (%%ebx), %%edx
	movl %%ecx, (%%ebx)
	movl %%edx, (%%eax)
  " : : "a" (i1), "b" (i2) : "ecx", "edx", "cc", "memory");
}


/*
#pragma aux swapbuf4 =\
	"begswap:",\
	"mov esi, (%%eax)",\
	"mov edi, (%%ebx)",\
	"mov (%%ebx), esi",\
	"mov (%%eax), edi",\
	"add eax, 4",\
	"add ebx, 4",\
	"dec ecx",\
	"jnz short begswap",\
	parm (%%eax)(%%ebx)[ecx]\
	modify exact [eax ebx ecx esi edi]\

#pragma aux swap64bit =\
	"mov ecx, (%%eax)",\
	"mov edx, (%%ebx)",\
	"mov (%%ebx), ecx",\
	"mov ecx, [eax+4]",\
	"mov (%%eax), edx",\
	"mov edx, [ebx+4]",\
	"mov [ebx+4], ecx",\
	"mov [eax+4], edx",\
	parm (%%eax)(%%ebx)\
	modify exact [ecx edx]\
*/


	//swapchar2(ptr1,ptr2,xsiz); is the same as:
	//swapchar(ptr1,ptr2); swapchar(ptr1+1,ptr2+xsiz);
int swapchar2(int i1, int i2, int i3) {
  int retval = 0;
  __asm__ __volatile__ ("
	addl %%ebx, %%esi
	movw (%%eax), %%cx
	movb (%%ebx), %%dl
	movb %%cl, (%%ebx)
	movb (%%esi), %%dh
	movb %%ch, (%%esi)
	movw %%dx, (%%eax)
  " : "=a" (retval) : "a" (i1), "b" (i2), "S" (i3) : "ecx", "edx", "cc", "memory");
    return(retval);
}

/*

	//returns eax%ebx, dmval = eax/edx;
#pragma aux moddiv =\
	"xor edx, edx",\
	"div ebx",\
	"mov dmval, eax",\
	parm [eax][ebx]\
	modify exact [eax edx]\
	value [edx]


	//eax = (unsigned min)umin(eax,ebx)
#pragma aux umin =\
	"sub eax, ebx",\
	"sbb ecx, ecx",\
	"and eax, ecx",\
	"add eax, ebx",\
	parm nomemory [eax][ebx]\
	modify exact [eax ecx]\

	//eax = (unsigned max)umax(eax,ebx)
#pragma aux umax =\
	"sub eax, ebx",\
	"sbb ecx, ecx",\
	"xor ecx, 0xffffffff",\
	"and eax, ecx",\
	"add eax, ebx",\
	parm nomemory [eax][ebx]\
	modify exact [eax ecx]\

#pragma aux kmin =\
	"cmp eax, ebx",\
	"jl skipit",\
	"mov eax, ebx",\
	"skipit:",\
	parm nomemory [eax][ebx]\
	modify exact [eax]\

#pragma aux kmax =\
	"cmp eax, ebx",\
	"jg skipit",\
	"mov eax, ebx",\
	"skipit:",\
	parm nomemory [eax][ebx]\
	modify exact [eax]\

#pragma aux readtimer =\
	"mov al, 0xd2",\
	"out 0x43, al",\
	"in al, 0x40",\
	"shl eax, 24",\
	"in al, 0x40",\
	"rol eax, 8",\
	modify [eax]\

#pragma aux redblueblit = \
	"xor ecx, ecx",\
	"begblit: mov eax, dword ptr [edx+ecx]",\
	"shl eax, 4",\
	"add eax, dword ptr [ebx+ecx]",\
	"mov dword ptr [ecx+0xa0000], eax",\
	"add ecx, 4",\
	"cmp ecx, esi",\
	"jb begblit",\
	parm [ebx][edx][esi]\
	modify exact [eax ecx]\

#pragma aux chainblit =\
	"shr ecx, 1",\
	"jnc prebeg",\
	"mov al, byte ptr [esi+8]",\
	"mov ah, byte ptr [esi+12]",\
	"shl eax, 16",\
	"mov al, byte ptr [esi]",\
	"mov ah, byte ptr [esi+4]",\
	"mov dword ptr [edi], eax",\
	"add esi, 16",\
	"add edi, 4",\
	"test ecx, ecx",\
	"prebeg: jz endit",\
	"beg: mov al, byte ptr [esi+8]",\
	"mov bl, byte ptr [esi+24]",\
	"mov ah, byte ptr [esi+12]",\
	"mov bh, byte ptr [esi+28]",\
	"shl eax, 16",\
	"add edi, 8",\
	"shl ebx, 16",\
	"mov al, byte ptr [esi]",\
	"mov bl, byte ptr [esi+16]",\
	"mov ah, byte ptr [esi+4]",\
	"mov bh, byte ptr [esi+20]",\
	"add esi, 32",\
	"mov dword ptr [edi-8], eax",\
	"dec ecx",\
	"mov dword ptr [edi-4], ebx",\
	"jnz beg",\
	"endit:",\
	parm [esi][edi][ecx]\
	modify exact [eax ebx ecx esi edi]\

static long timeroffs1mhz;
	//accutimeroffs = -8-(t1-t0);
#pragma aux inittimer1mhz =\
	"xor ebx, ebx",\
	"xor ecx, ecx",\
	"in al, 0x61",\
	"or al, 1",\
	"out 0x61, al",\
	"mov al, 0x34",\
	"out 0x43, al",\
	"xor al, al",\
	"out 0x40, al",\
	"mov al, 0xb4",\
	"out 0x43, al",\
	"mov al, 240",\
	"out 0x42, al",\
	"xor al, al",\
	"cli",\
	"out 0x40, al",\
	"dec al",\
	"out 0x42, al",\
	"mov al, 0x04",\
	"out 0x43, al",\
	"in al, 0x40",\
	"mov bl, al",\
	"in al, 0x40",\
	"mov bh, al",\
	"mov al, 0x84",\
	"out 0x43, al",\
	"in al, 0x42",\
	"mov cl, al",\
	"in al, 0x42",\
	"sti",\
	"mov ch, al",\
	"sub ebx, ecx",\
	"sub ebx, 8",\
	"mov timeroffs1mhz, ebx",\
	modify exact [eax ebx ecx]\

#pragma aux uninittimer1mhz =\
	"in al, 0x61",\
	"and al, 252",\
	"out 0x61, al",\
	modify exact [eax]\

	//t = ((ecx-ebx+timeroffs1mhz)&0xfff0)*4095 + ecx;
#pragma aux gettime1mhz =\
	"mov ebx, timeroffs1mhz",\
	"xor ecx, ecx",\
	"mov al, 0x04",\
	"cli",\
	"out 0x43, al",\
	"in al, 0x40",\
	"sub bl, al",\
	"in al, 0x40",\
	"sbb bh, al",\
	"mov al, 0x84",\
	"out 0x43, al",\
	"in al, 0x42",\
	"mov cl, al",\
	"in al, 0x42",\
	"sti",\
	"mov ch, al",\
	"add ebx, ecx",\
	"and ebx, 0x0000fff0",\
	"sub ecx, ebx",\
	"shl ebx, 12",\
	"add ebx, ecx",\
	modify exact [eax ebx ecx]\
	value [ebx]\

	//eax = eax-ebx; if (eax < 0) eax += (1<<28) - (1<<16);
#pragma aux deltatime1mhz =\
	"sub eax, ebx",\
	"jnc skipit",\
	"add eax, 0x0fff0000",\
	"skipit:",\
	parm [ebx][eax]\

*/

#else

void swapchar(unsigned char *p1, unsigned char *p2)
{
    unsigned char tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
} // swapchar

void swapshort(short *p1, short *p2)
{
    short tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
} // swapshort

void swaplong(long *p1, long *p2)
{
    long tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
} // swaplong

void swapchar2(unsigned char *p1, unsigned char *p2, int xsiz)
{
    swapchar(p1, p2);
    swapchar(p1 + 1, p2 + xsiz);
} // swapchar2


void qinterpolatedown16short (long *source, int size, int linum, int linum_inc)
{
//	Attempt at a convert to C :/ - DDOI
    int tmp;

	if (size == 0)
        return;

        // casting sucks ass.  --ryan.
	if ( (((unsigned long) source) & 0xFF) != 2)
    {
		*((short *) source) = (short) ( (linum >> 16) & 0xFFFF ) ;
        source = (long *) ( ((short *) source) + 2 );
		linum += linum_inc;
		size--;
	} // if

	size -= 2;
	if (size < 0)
        *((short *) source) = (short) ((linum << 16) & 0xFFFF);
    else
    {
        while ( size >= 0)
        {
            tmp = linum;
            linum += linum_inc;
            *source = ((tmp >> 16) + (linum & 0xffff0000));
            linum += linum_inc;
            size -= 2;
            source++;
        } // while

        if (size != 1)
            *((short *) source) = (short) ((linum << 16) & 0xFFFF);
    } // else
} // qinterpolatedown16short

#endif

