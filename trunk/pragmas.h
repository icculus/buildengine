// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.
// This file has been modified from Ken Silverman's original release

#ifndef __PRAGMAS_H__
#define __PRAGMAS_H__

#if (defined __WATCOMC__)

static long dmval = 0;

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
int sqr(int i1);
#endif
#pragma aux sqr =\
        "imul eax, eax",\
        parm nomemory [eax]\
        modify exact [eax]\
        value [eax]

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long scale(long i1, long i2, long i3);
#endif
#pragma aux scale =\
        "imul edx",\
        "idiv ecx",\
        parm nomemory [eax][edx][ecx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale(long i1, long i2, long i3);
#endif
#pragma aux mulscale =\
        "imul edx",\
        "shrd eax, edx, cl",\
        parm nomemory [eax][edx][ecx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale1(long i1, long i2);
#endif
#pragma aux mulscale1 =\
        "imul edx",\
        "shrd eax, edx, 1",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale2(long i1, long i2);
#endif
#pragma aux mulscale2 =\
        "imul edx",\
        "shrd eax, edx, 2",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale3(long i1, long i2);
#endif
#pragma aux mulscale3 =\
        "imul edx",\
        "shrd eax, edx, 3",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale4(long i1, long i2);
#endif
#pragma aux mulscale4 =\
        "imul edx",\
        "shrd eax, edx, 4",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale5(long i1, long i2);
#endif
#pragma aux mulscale5 =\
        "imul edx",\
        "shrd eax, edx, 5",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale6(long i1, long i2);
#endif
#pragma aux mulscale6 =\
        "imul edx",\
        "shrd eax, edx, 6",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale7(long i1, long i2);
#endif
#pragma aux mulscale7 =\
        "imul edx",\
        "shrd eax, edx, 7",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale8(long i1, long i2);
#endif
#pragma aux mulscale8 =\
        "imul edx",\
        "shrd eax, edx, 8",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale9(long i1, long i2);
#endif
#pragma aux mulscale9 =\
        "imul edx",\
        "shrd eax, edx, 9",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale10(long i1, long i2);
#endif
#pragma aux mulscale10 =\
        "imul edx",\
        "shrd eax, edx, 10",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale11(long i1, long i2);
#endif
#pragma aux mulscale11 =\
        "imul edx",\
        "shrd eax, edx, 11",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale12(long i1, long i2);
#endif
#pragma aux mulscale12 =\
        "imul edx",\
        "shrd eax, edx, 12",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale13(long i1, long i2);
#endif
#pragma aux mulscale13 =\
        "imul edx",\
        "shrd eax, edx, 13",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale14(long i1, long i2);
#endif
#pragma aux mulscale14 =\
        "imul edx",\
        "shrd eax, edx, 14",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale15(long i1, long i2);
#endif
#pragma aux mulscale15 =\
        "imul edx",\
        "shrd eax, edx, 15",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale16(long i1, long i2);
#endif
#pragma aux mulscale16 =\
        "imul edx",\
        "shrd eax, edx, 16",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale17(long i1, long i2);
#endif
#pragma aux mulscale17 =\
        "imul edx",\
        "shrd eax, edx, 17",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale18(long i1, long i2);
#endif
#pragma aux mulscale18 =\
        "imul edx",\
        "shrd eax, edx, 18",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale19(long i1, long i2);
#endif
#pragma aux mulscale19 =\
        "imul edx",\
        "shrd eax, edx, 19",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale20(long i1, long i2);
#endif
#pragma aux mulscale20 =\
        "imul edx",\
        "shrd eax, edx, 20",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale21(long i1, long i2);
#endif
#pragma aux mulscale21 =\
        "imul edx",\
        "shrd eax, edx, 21",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale22(long i1, long i2);
#endif
#pragma aux mulscale22 =\
        "imul edx",\
        "shrd eax, edx, 22",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale23(long i1, long i2);
#endif
#pragma aux mulscale23 =\
        "imul edx",\
        "shrd eax, edx, 23",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale24(long i1, long i2);
#endif
#pragma aux mulscale24 =\
        "imul edx",\
        "shrd eax, edx, 24",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale25(long i1, long i2);
#endif
#pragma aux mulscale25 =\
        "imul edx",\
        "shrd eax, edx, 25",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale26(long i1, long i2);
#endif
#pragma aux mulscale26 =\
        "imul edx",\
        "shrd eax, edx, 26",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale27(long i1, long i2);
#endif
#pragma aux mulscale27 =\
        "imul edx",\
        "shrd eax, edx, 27",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale28(long i1, long i2);
#endif
#pragma aux mulscale28 =\
        "imul edx",\
        "shrd eax, edx, 28",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale29(long i1, long i2);
#endif
#pragma aux mulscale29 =\
        "imul edx",\
        "shrd eax, edx, 29",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale30(long i1, long i2);
#endif
#pragma aux mulscale30 =\
        "imul edx",\
        "shrd eax, edx, 30",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale31(long i1, long i2);
#endif
#pragma aux mulscale31 =\
        "imul edx",\
        "shrd eax, edx, 31",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mulscale32(long i1, long i2);
#endif
#pragma aux mulscale32 =\
        "imul edx",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\
        value [edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale(long i1, long i2, long i3, long i4, long i5);
#endif
#pragma aux dmulscale =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, cl",\
        parm nomemory [eax][edx][esi][edi][ecx]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale1(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale1 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 1",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale2(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale2 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 2",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale3(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale3 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 3",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale4(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale4 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 4",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale5(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale5 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 5",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale6(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale6 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 6",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale7(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale7 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 7",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale8(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale8 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 8",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale9(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale9 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 9",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale10(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale10 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 10",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale11(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale11 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 11",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale12(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale12 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 12",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale13(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale13 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 13",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale14(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale14 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 14",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale15(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale15 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 15",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale16(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale16 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 16",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale17(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale17 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 17",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale18(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale18 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 18",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale19(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale19 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 19",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale20(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale20 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 20",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale21(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale21 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 21",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale22(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale22 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 22",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale23(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale23 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 23",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale24(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale24 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 24",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale25(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale25 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 25",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale26(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale26 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 26",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale27(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale27 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 27",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale28(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale28 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 28",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale29(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale29 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 29",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale30(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale30 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 30",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale31(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale31 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        "shrd eax, edx, 31",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long dmulscale32(long i1, long i2, long i3, long i4);
#endif
#pragma aux dmulscale32 =\
        "imul edx",\
        "mov ebx, eax",\
        "mov eax, esi",\
        "mov esi, edx",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, esi",\
        parm nomemory [eax][edx][esi][edi]\
        modify exact [eax ebx edx esi]\
        value [edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale1(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale1 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 1",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale2(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale2 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 2",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale3(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale3 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 3",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale4(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale4 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 4",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale5(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale5 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 5",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale6(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale6 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 6",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale7(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale7 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 7",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale8(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale8 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 8",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale9(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale9 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 9",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale10(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale10 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 10",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale11(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale11 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 11",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale12(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale12 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 12",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale13(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale13 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 13",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale14(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale14 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 14",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale15(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale15 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 15",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale16(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale16 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 16",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale17(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale17 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 17",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale18(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale18 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 18",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale19(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale19 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 19",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale20(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale20 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 20",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale21(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale21 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 21",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale22(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale22 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 22",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale23(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale23 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 23",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale24(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale24 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 24",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale25(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale25 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 25",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale26(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale26 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 26",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale27(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale27 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 27",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale28(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale28 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 28",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale29(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale29 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 29",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale30(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale30 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 30",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale31(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale31 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        "shrd eax, edx, 31",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long tmulscale32(long i1, long i2, long i3, long i4, long i5, long i6);
#endif
#pragma aux tmulscale32 =\
        "imul edx",\
        "xchg eax, ebx",\
        "xchg edx, ecx",\
        "imul edx",\
        "add ebx, eax",\
        "adc ecx, edx",\
        "mov eax, esi",\
        "imul edi",\
        "add eax, ebx",\
        "adc edx, ecx",\
        parm nomemory [eax][edx][ebx][ecx][esi][edi]\
        modify exact [eax ebx ecx edx]\
        value [edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long boundmulscale(long i1, long i2, long i3);
#endif
#pragma aux boundmulscale =\
        "imul ebx",\
        "mov ebx, edx",\
        "shrd eax, edx, cl",\
        "sar edx, cl",\
        "xor edx, eax",\
        "js checkit",\
        "xor edx, eax",\
        "jz skipboundit",\
        "cmp edx, 0xffffffff",\
        "je skipboundit",\
        "checkit:",\
        "mov eax, ebx",\
        "sar eax, 31",\
        "xor eax, 0x7fffffff",\
        "skipboundit:",\
        parm nomemory [eax][ebx][ecx]\
        modify exact [eax ebx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale(long i1, long i2, long i3);
#endif
#pragma aux divscale =\
        "mov edx, eax",\
        "shl eax, cl",\
        "neg cl",\
        "sar edx, cl",\
        "idiv ebx",\
        parm nomemory [eax][ebx][ecx]\
        modify exact [eax ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale1(long i1, long i2);
#endif
#pragma aux divscale1 =\
        "add eax, eax",\
        "sbb edx, edx",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale2(long i1, long i2);
#endif
#pragma aux divscale2 =\
        "mov edx, eax",\
        "sar edx, 30",\
        "lea eax, [eax*4]",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale3(long i1, long i2);
#endif
#pragma aux divscale3 =\
        "mov edx, eax",\
        "sar edx, 29",\
        "lea eax, [eax*8]",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale4(long i1, long i2);
#endif
#pragma aux divscale4 =\
        "mov edx, eax",\
        "sar edx, 28",\
        "shl eax, 4",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale5(long i1, long i2);
#endif
#pragma aux divscale5 =\
        "mov edx, eax",\
        "sar edx, 27",\
        "shl eax, 5",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale6(long i1, long i2);
#endif
#pragma aux divscale6 =\
        "mov edx, eax",\
        "sar edx, 26",\
        "shl eax, 6",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale7(long i1, long i2);
#endif
#pragma aux divscale7 =\
        "mov edx, eax",\
        "sar edx, 25",\
        "shl eax, 7",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale8(long i1, long i2);
#endif
#pragma aux divscale8 =\
        "mov edx, eax",\
        "sar edx, 24",\
        "shl eax, 8",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale9(long i1, long i2);
#endif
#pragma aux divscale9 =\
        "mov edx, eax",\
        "sar edx, 23",\
        "shl eax, 9",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale10(long i1, long i2);
#endif
#pragma aux divscale10 =\
        "mov edx, eax",\
        "sar edx, 22",\
        "shl eax, 10",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale11(long i1, long i2);
#endif
#pragma aux divscale11 =\
        "mov edx, eax",\
        "sar edx, 21",\
        "shl eax, 11",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale12(long i1, long i2);
#endif
#pragma aux divscale12 =\
        "mov edx, eax",\
        "sar edx, 20",\
        "shl eax, 12",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale13(long i1, long i2);
#endif
#pragma aux divscale13 =\
        "mov edx, eax",\
        "sar edx, 19",\
        "shl eax, 13",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale14(long i1, long i2);
#endif
#pragma aux divscale14 =\
        "mov edx, eax",\
        "sar edx, 18",\
        "shl eax, 14",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale15(long i1, long i2);
#endif
#pragma aux divscale15 =\
        "mov edx, eax",\
        "sar edx, 17",\
        "shl eax, 15",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale16(long i1, long i2);
#endif
#pragma aux divscale16 =\
        "mov edx, eax",\
        "sar edx, 16",\
        "shl eax, 16",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale17(long i1, long i2);
#endif
#pragma aux divscale17 =\
        "mov edx, eax",\
        "sar edx, 15",\
        "shl eax, 17",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale18(long i1, long i2);
#endif
#pragma aux divscale18 =\
        "mov edx, eax",\
        "sar edx, 14",\
        "shl eax, 18",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale19(long i1, long i2);
#endif
#pragma aux divscale19 =\
        "mov edx, eax",\
        "sar edx, 13",\
        "shl eax, 19",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale20(long i1, long i2);
#endif
#pragma aux divscale20 =\
        "mov edx, eax",\
        "sar edx, 12",\
        "shl eax, 20",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale21(long i1, long i2);
#endif
#pragma aux divscale21 =\
        "mov edx, eax",\
        "sar edx, 11",\
        "shl eax, 21",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale22(long i1, long i2);
#endif
#pragma aux divscale22 =\
        "mov edx, eax",\
        "sar edx, 10",\
        "shl eax, 22",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale23(long i1, long i2);
#endif
#pragma aux divscale23 =\
        "mov edx, eax",\
        "sar edx, 9",\
        "shl eax, 23",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale24(long i1, long i2);
#endif
#pragma aux divscale24 =\
        "mov edx, eax",\
        "sar edx, 8",\
        "shl eax, 24",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale25(long i1, long i2);
#endif
#pragma aux divscale25 =\
        "mov edx, eax",\
        "sar edx, 7",\
        "shl eax, 25",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale26(long i1, long i2);
#endif
#pragma aux divscale26 =\
        "mov edx, eax",\
        "sar edx, 6",\
        "shl eax, 26",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale27(long i1, long i2);
#endif
#pragma aux divscale27 =\
        "mov edx, eax",\
        "sar edx, 5",\
        "shl eax, 27",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale28(long i1, long i2);
#endif
#pragma aux divscale28 =\
        "mov edx, eax",\
        "sar edx, 4",\
        "shl eax, 28",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale29(long i1, long i2);
#endif
#pragma aux divscale29 =\
        "mov edx, eax",\
        "sar edx, 3",\
        "shl eax, 29",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale30(long i1, long i2);
#endif
#pragma aux divscale30 =\
        "mov edx, eax",\
        "sar edx, 2",\
        "shl eax, 30",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale31(long i1, long i2);
#endif
#pragma aux divscale31 =\
        "mov edx, eax",\
        "sar edx, 1",\
        "shl eax, 31",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale32(long i1, long i2);
#endif
#pragma aux divscale32 =\
        "xor eax, eax",\
        "idiv ebx",\
        parm nomemory [edx][ebx]\
        modify exact [eax edx]\

// !!! move these into dos_driver.c?  --ryan.
#ifdef PLATFORM_DOS

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void int5(void);
#endif
#pragma aux int5 =\
        "int 0x5",\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void setvmode(int i1);
#endif
#pragma aux setvmode =\
        "int 0x10",\
        parm [eax]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
int setupmouse(void);
#endif
#pragma aux setupmouse =\
        "mov ax, 0",\
        "int 33h",\
        "and eax, 0x0000ffff",\
        modify exact [eax]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void readmousexy(short *x, short *y);
#endif
#pragma aux readmousexy =\
        "mov ax, 11d",\
        "int 33h",\
        "mov [esi], cx",\
        "mov [edi], dx",\
        parm [esi][edi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void readmousebstatus(short *buttons);
#endif
#pragma aux readmousebstatus =\
        "mov ax, 5d",\
        "int 33h",\
        "mov [esi], ax",\
        parm [esi]\
        modify exact [eax ebx ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
unsigned char readpixel(long offset);
#endif
#pragma aux readpixel =\
        "mov al, byte ptr [edi]",\
        parm nomemory [edi]\
        modify exact [eax]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void drawpixel(long offset, unsigned char p);
#endif
#pragma aux drawpixel =\
        "mov byte ptr [edi], al",\
        parm [edi][eax]\
        modify exact \

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void drawpixels(long offset, unsigned short p);
#endif
#pragma aux drawpixels =\
        "mov word ptr [edi], ax",\
        parm [edi][eax]\
        modify exact \

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void drawpixelses(long offset, unsigned long p);
#endif
#pragma aux drawpixelses =\
        "mov dword ptr [edi], eax",\
        parm [edi][eax]\
        modify exact \

#endif


#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void clearbuf(void *buf, long i2, long i3);
#endif
#pragma aux clearbuf =\
        "rep stosd",\
        parm [edi][ecx][eax]\
        modify exact [edi ecx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void clearbufbyte(void *buf, long i2, long i3);
#endif
#pragma aux clearbufbyte =\
        "cmp ecx, 4",\
        "jae longcopy",\
        "test cl, 1",\
        "jz preskip",\
        "stosb",\
        "preskip: shr ecx, 1",\
        "rep stosw",\
        "jmp endit",\
        "longcopy: test edi, 1",\
        "jz skip1",\
        "stosb",\
        "dec ecx",\
        "skip1: test edi, 2",\
        "jz skip2",\
        "stosw",\
        "sub ecx, 2",\
        "skip2: mov ebx, ecx",\
        "shr ecx, 2",\
        "rep stosd",\
        "test bl, 2",\
        "jz skip3",\
        "stosw",\
        "skip3: test bl, 1",\
        "jz endit",\
        "stosb",\
        "endit:",\
        parm [edi][ecx][eax]\
        modify [ebx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void copybuf(void *src, void *dst, long len);
#endif
#pragma aux copybuf =\
        "rep movsd",\
        parm [esi][edi][ecx]\
        modify exact [ecx esi edi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void copybufbyte(void *src, void *dst, long len);
#endif
#pragma aux copybufbyte =\
        "cmp ecx, 4",\
        "jae longcopy",\
        "test cl, 1",\
        "jz preskip",\
        "movsb",\
        "preskip: shr ecx, 1",\
        "rep movsw",\
        "jmp endit",\
        "longcopy: test edi, 1",\
        "jz skip1",\
        "movsb",\
        "dec ecx",\
        "skip1: test edi, 2",\
        "jz skip2",\
        "movsw",\
        "sub ecx, 2",\
        "skip2: mov ebx, ecx",\
        "shr ecx, 2",\
        "rep movsd",\
        "test bl, 2",\
        "jz skip3",\
        "movsw",\
        "skip3: test bl, 1",\
        "jz endit",\
        "movsb",\
        "endit:",\
        parm [esi][edi][ecx]\
        modify [ebx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void copybufreverse(void *src, void *dst, long len);
#endif
#pragma aux copybufreverse =\
        "shr ecx, 1",\
        "jnc skipit1",\
        "mov al, byte ptr [esi]",\
        "dec esi",\
        "mov byte ptr [edi], al",\
        "inc edi",\
        "skipit1: shr ecx, 1",\
        "jnc skipit2",\
        "mov ax, word ptr [esi-1]",\
        "sub esi, 2",\
        "ror ax, 8",\
        "mov word ptr [edi], ax",\
        "add edi, 2",\
        "skipit2: test ecx, ecx",\
        "jz endloop",\
        "begloop: mov eax, dword ptr [esi-3]",\
        "sub esi, 4",\
        "bswap eax",\
        "mov dword ptr [edi], eax",\
        "add edi, 4",\
        "dec ecx",\
        "jnz begloop",\
        "endloop:",\
        parm [esi][edi][ecx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void qinterpolatedown16(long *i1, long i2, long i3, long i4);
#endif
#pragma aux qinterpolatedown16 =\
        "mov ebx, ecx",\
        "shr ecx, 1",\
        "jz skipbegcalc",\
        "begqcalc: lea edi, [edx+esi]",\
        "sar edx, 16",\
        "mov dword ptr [eax], edx",\
        "lea edx, [edi+esi]",\
        "sar edi, 16",\
        "mov dword ptr [eax+4], edi",\
        "add eax, 8",\
        "dec ecx",\
        "jnz begqcalc",\
        "test ebx, 1",\
        "jz skipbegqcalc2",\
        "skipbegcalc: sar edx, 16",\
        "mov dword ptr [eax], edx",\
        "skipbegqcalc2:",\
        parm [eax][ecx][edx][esi]\
        modify exact [eax ebx ecx edx edi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void qinterpolatedown16short(long *i1, long i2, long i3, long i4);
#endif
#pragma aux qinterpolatedown16short =\
        "test ecx, ecx",\
        "jz endit",\
        "test al, 2",\
        "jz skipalignit",\
        "mov ebx, edx",\
        "sar ebx, 16",\
        "mov word ptr [eax], bx",\
        "add edx, esi",\
        "add eax, 2",\
        "dec ecx",\
        "jz endit",\
        "skipalignit: sub ecx, 2",\
        "jc finishit",\
        "begqcalc: mov ebx, edx",\
        "add edx, esi",\
        "sar ebx, 16",\
        "mov edi, edx",\
        "and edi, 0ffff0000h",\
        "add edx, esi",\
        "add ebx, edi",\
        "mov dword ptr [eax], ebx",\
        "add eax, 4",\
        "sub ecx, 2",\
        "jnc begqcalc",\
        "test cl, 1",\
        "jz endit",\
        "finishit: mov ebx, edx",\
        "sar ebx, 16",\
        "mov word ptr [eax], bx",\
        "endit:",\
        parm [eax][ecx][edx][esi]\
        modify exact [eax ebx ecx edx edi]\


#if (defined PLATFORM_DOS)   // !!! move this to dos_driver.c?

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void setcolor16(int i1);
#endif
#pragma aux setcolor16 =\
        "mov dx, 0x3ce",\
        "shl ax, 8",\
        "out dx, ax",\
        parm [eax]\
        modify exact [eax edx]\

#endif  // PLATFORM_DOS


#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void vlin16first(long i1, long i2);
#endif
#pragma aux vlin16first =\
        "mov al, byte ptr [edi]",\
        "mov eax, ecx",\
        "shr ecx, 2",\
        "begvlin16firsta: mov byte ptr [edi], al",\
        "mov byte ptr [edi+80], al",\
        "mov byte ptr [edi+160], al",\
        "mov byte ptr [edi+240], al",\
        "add edi, 320",\
        "dec ecx",\
        "jnz begvlin16firsta",\
        "mov ecx, eax",\
        "and ecx, 3",\
        "jz skipfirst",\
        "begvlin16firstb: mov byte ptr [edi], al",\
        "add edi, 80",\
        "dec ecx",\
        "jnz begvlin16firstb",\
        "skipfirst:",\
        parm [edi][ecx]\
        modify exact [eax ecx edi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void vlin16(long i1, long i2);
#endif
#pragma aux vlin16 =\
        "mov esi, edi",\
        "begvlin16: movsb",\
        "add edi, 79",\
        "add esi, 79",\
        "dec ecx",\
        "jnz begvlin16",\
        parm [edi][ecx]\
        modify exact [ecx esi edi]\

#if (defined PLATFORM_DOS)   // !!! move this to dos_driver.c?

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void drawpixel16(long offset);
#endif
#pragma aux drawpixel16 =\
        "mov ecx, edi",\
        "mov eax, 0x00008008",\
        "mov dx, 0x3ce",\
        "ror ah, cl",\
        "shr edi, 3",\
        "out dx, ax",\
        "mov cl, byte ptr [edi+0xa0000]",\
        "mov byte ptr [edi+0xa0000], al",\
        parm [edi]\
        modify exact [eax ecx edx edi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void fillscreen16(long i1, long i2, long i3);
#endif
#pragma aux fillscreen16 =\
        "mov dx, 0x3ce",\
        "shl ax, 8",\
        "out dx, ax",\
        "mov ax, 0xff08",\
        "out dx, ax",\
        "shr ecx, 5",\
        "add edi, 0xa0000",\
        "rep stosd",\
        parm [edi][eax][ecx]\
        modify exact [eax ecx edx edi]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void koutp(long i1, long i);
#endif
#pragma aux koutp =\
        "out dx, al",\
        parm [edx][eax]\
        modify exact \

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void koutpw(long i1, long i);
#endif
#pragma aux koutpw =\
        "out dx, ax",\
        parm [edx][eax]\
        modify exact \

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
int kinp(long i);
#endif
#pragma aux kinp =\
        "in al, dx",\
        parm nomemory [edx]\
        modify exact [eax]\

#endif  // PLATFORM_DOS


#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mul3(long i1);
#endif
#pragma aux mul3 =\
        "lea eax, [eax+eax*2]",\
        parm nomemory [eax]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mul5(long i1);
#endif
#pragma aux mul5 =\
        "lea eax, [eax+eax*4]",\
        parm nomemory [eax]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long mul9(long i1);
#endif
#pragma aux mul9 =\
        "lea eax, [eax+eax*8]",\
        parm nomemory [eax]\

        //returns eax/ebx, dmval = eax%edx;
#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divmod(long i1, long i2);
#endif
#pragma aux divmod =\
        "xor edx, edx",\
        "div ebx",\
        "mov dmval, edx",\
        parm [eax][ebx]\
        modify exact [eax edx]\
        value [eax]

        //returns eax%ebx, dmval = eax/edx;
#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long moddiv(long i1, long i2);
#endif
#pragma aux moddiv =\
        "xor edx, edx",\
        "div ebx",\
        "mov dmval, eax",\
        parm [eax][ebx]\
        modify exact [eax edx]\
        value [edx]

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long klabs(long i1);
#endif
#pragma aux klabs =\
        "test eax, eax",\
        "jns skipnegate",\
        "neg eax",\
        "skipnegate:",\
        parm nomemory [eax]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long ksgn(long i1);
#endif
#pragma aux ksgn =\
        "add ebx, ebx",\
        "sbb eax, eax",\
        "cmp eax, ebx",\
        "adc al, 0",\
        parm nomemory [ebx]\
        modify exact [eax ebx]\

        //eax = (unsigned min)umin(eax,ebx)
#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long umin(long i1, long i2);
#endif
#pragma aux umin =\
        "sub eax, ebx",\
        "sbb ecx, ecx",\
        "and eax, ecx",\
        "add eax, ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax ecx]\

        //eax = (unsigned max)umax(eax,ebx)
#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long umax(long i1, long i2);
#endif
#pragma aux umax =\
        "sub eax, ebx",\
        "sbb ecx, ecx",\
        "xor ecx, 0xffffffff",\
        "and eax, ecx",\
        "add eax, ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax ecx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long kmin(long i1, long i2);
#endif
#pragma aux kmin =\
        "cmp eax, ebx",\
        "jl skipit",\
        "mov eax, ebx",\
        "skipit:",\
        parm nomemory [eax][ebx]\
        modify exact [eax]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long kmax(long i1, long i2);
#endif
#pragma aux kmax =\
        "cmp eax, ebx",\
        "jg skipit",\
        "mov eax, ebx",\
        "skipit:",\
        parm nomemory [eax][ebx]\
        modify exact [eax]\

#if (defined PLATFORM_DOS)  // !!! move to dos_driver.c?
#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void limitrate(void);
#endif
#pragma aux limitrate =\
        "mov dx, 0x3da",\
        "wait1: in al, dx",\
        "test al, 8",\
        "jnz wait1",\
        "wait2: in al, dx",\
        "test al, 8",\
        "jz wait2",\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long readtimer(void);
#endif
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

#endif


#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void swapchar(char *i1, char *i2);
#endif
#pragma aux swapchar =\
        "mov cl, [eax]",\
        "mov ch, [ebx]",\
        "mov [ebx], cl",\
        "mov [eax], ch",\
        parm [eax][ebx]\
        modify exact [ecx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void swapshort(short *i1, short *i2);
#endif
#pragma aux swapshort =\
        "mov cx, [eax]",\
        "mov dx, [ebx]",\
        "mov [ebx], cx",\
        "mov [eax], dx",\
        parm [eax][ebx]\
        modify exact [ecx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void swaplong(long *i1, long *i2);
#endif
#pragma aux swaplong =\
        "mov ecx, [eax]",\
        "mov edx, [ebx]",\
        "mov [ebx], ecx",\
        "mov [eax], edx",\
        parm [eax][ebx]\
        modify exact [ecx edx]\

#pragma aux swapbuf4 =\
        "begswap:",\
        "mov esi, [eax]",\
        "mov edi, [ebx]",\
        "mov [ebx], esi",\
        "mov [eax], edi",\
        "add eax, 4",\
        "add ebx, 4",\
        "dec ecx",\
        "jnz short begswap",\
        parm [eax][ebx][ecx]\
        modify exact [eax ebx ecx esi edi]\

#pragma aux swap64bit =\
        "mov ecx, [eax]",\
        "mov edx, [ebx]",\
        "mov [ebx], ecx",\
        "mov ecx, [eax+4]",\
        "mov [eax], edx",\
        "mov edx, [ebx+4]",\
        "mov [ebx+4], ecx",\
        "mov [eax+4], edx",\
        parm [eax][ebx]\
        modify exact [ecx edx]\


        //swapchar2(ptr1,ptr2,xsiz); is the same as:
        //swapchar(ptr1,ptr2); swapchar(ptr1+1,ptr2+xsiz);
#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
void swapchar2(char *ptr1, char *ptr2, long xsiz);
#endif
#pragma aux swapchar2 =\
        "add esi, ebx",\
        "mov cx, [eax]",\
        "mov dl, [ebx]",\
        "mov [ebx], cl",\
        "mov dh, [esi]",\
        "mov [esi], ch",\
        "mov [eax], dx",\
        parm [eax][ebx][esi]\
        modify exact [ecx edx esi]\

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
        parm [ebx][eax]

#pragma aux boundmulscale =\
        "imul ebx",\
        "mov ebx, edx",\
        "shrd eax, edx, cl",\
        "sar edx, cl",\
        "xor edx, eax",\
        "js checkit",\
        "xor edx, eax",\
        "jz skipboundit",\
        "cmp edx, 0xffffffff",\
        "je skipboundit",\
        "checkit:",\
        "mov eax, ebx",\
        "sar eax, 31",\
        "xor eax, 0x7fffffff",\
        "skipboundit:",\
        parm nomemory [eax][ebx][ecx]\
        modify exact [eax ebx edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale(long i1, long i2, long i3);
#endif
#pragma aux divscale =\
        "mov edx, eax",\
        "shl eax, cl",\
        "neg cl",\
        "sar edx, cl",\
        "idiv ebx",\
        parm nomemory [eax][ebx][ecx]\
        modify exact [eax ecx edx]
        
#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale1(long i1, long i2);
#endif
#pragma aux divscale1 =\
        "add eax, eax",\
        "sbb edx, edx",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]
        
#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale2(long i1, long i2);
#endif
#pragma aux divscale2 =\
        "mov edx, eax",\
        "sar edx, 30",\
        "lea eax, [eax*4]",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale3(long i1, long i2);
#endif
#pragma aux divscale3 =\
        "mov edx, eax",\
        "sar edx, 29",\
        "lea eax, [eax*8]",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale4(long i1, long i2);
#endif
#pragma aux divscale4 =\
        "mov edx, eax",\
        "sar edx, 28",\
        "shl eax, 4",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale5(long i1, long i2);
#endif
#pragma aux divscale5 =\
        "mov edx, eax",\
        "sar edx, 27",\
        "shl eax, 5",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale6(long i1, long i2);
#endif
#pragma aux divscale6 =\
        "mov edx, eax",\
        "sar edx, 26",\
        "shl eax, 6",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale7(long i1, long i2);
#endif
#pragma aux divscale7 =\
        "mov edx, eax",\
        "sar edx, 25",\
        "shl eax, 7",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale8(long i1, long i2);
#endif
#pragma aux divscale8 =\
        "mov edx, eax",\
        "sar edx, 24",\
        "shl eax, 8",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale9(long i1, long i2);
#endif
#pragma aux divscale9 =\
        "mov edx, eax",\
        "sar edx, 23",\
        "shl eax, 9",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale10(long i1, long i2);
#endif
#pragma aux divscale10 =\
        "mov edx, eax",\
        "sar edx, 22",\
        "shl eax, 10",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale11(long i1, long i2);
#endif
#pragma aux divscale11 =\
        "mov edx, eax",\
        "sar edx, 21",\
        "shl eax, 11",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale12(long i1, long i2);
#endif
#pragma aux divscale12 =\
        "mov edx, eax",\
        "sar edx, 20",\
        "shl eax, 12",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale13(long i1, long i2);
#endif
#pragma aux divscale13 =\
        "mov edx, eax",\
        "sar edx, 19",\
        "shl eax, 13",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale14(long i1, long i2);
#endif
#pragma aux divscale14 =\
        "mov edx, eax",\
        "sar edx, 18",\
        "shl eax, 14",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale15(long i1, long i2);
#endif
#pragma aux divscale15 =\
        "mov edx, eax",\
        "sar edx, 17",\
        "shl eax, 15",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale16(long i1, long i2);
#endif
#pragma aux divscale16 =\
        "mov edx, eax",\
        "sar edx, 16",\
        "shl eax, 16",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale17(long i1, long i2);
#endif
#pragma aux divscale17 =\
        "mov edx, eax",\
        "sar edx, 15",\
        "shl eax, 17",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale18(long i1, long i2);
#endif
#pragma aux divscale18 =\
        "mov edx, eax",\
        "sar edx, 14",\
        "shl eax, 18",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale19(long i1, long i2);
#endif
#pragma aux divscale19 =\
        "mov edx, eax",\
        "sar edx, 13",\
        "shl eax, 19",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale20(long i1, long i2);
#endif
#pragma aux divscale20 =\
        "mov edx, eax",\
        "sar edx, 12",\
        "shl eax, 20",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale21(long i1, long i2);
#endif
#pragma aux divscale21 =\
        "mov edx, eax",\
        "sar edx, 11",\
        "shl eax, 21",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale22(long i1, long i2);
#endif
#pragma aux divscale22 =\
        "mov edx, eax",\
        "sar edx, 10",\
        "shl eax, 22",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale23(long i1, long i2);
#endif
#pragma aux divscale23 =\
        "mov edx, eax",\
        "sar edx, 9",\
        "shl eax, 23",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale24(long i1, long i2);
#endif
#pragma aux divscale24 =\
        "mov edx, eax",\
        "sar edx, 8",\
        "shl eax, 24",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale25(long i1, long i2);
#endif
#pragma aux divscale25 =\
        "mov edx, eax",\
        "sar edx, 7",\
        "shl eax, 25",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale26(long i1, long i2);
#endif
#pragma aux divscale26 =\
        "mov edx, eax",\
        "sar edx, 6",\
        "shl eax, 26",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale27(long i1, long i2);
#endif
#pragma aux divscale27 =\
        "mov edx, eax",\
        "sar edx, 5",\
        "shl eax, 27",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale28(long i1, long i2);
#endif
#pragma aux divscale28 =\
        "mov edx, eax",\
        "sar edx, 4",\
        "shl eax, 28",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale29(long i1, long i2);
#endif
#pragma aux divscale29 =\
        "mov edx, eax",\
        "sar edx, 3",\
        "shl eax, 29",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale30(long i1, long i2);
#endif
#pragma aux divscale30 =\
        "mov edx, eax",\
        "sar edx, 2",\
        "shl eax, 30",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale31(long i1, long i2);
#endif
#pragma aux divscale31 =\
        "mov edx, eax",\
        "sar edx, 1",\
        "shl eax, 31",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

#if (__WATCOMC__ < 1100)   // apparently, you need declares for pragmas.
long divscale32(long i1, long i2);
#endif
#pragma aux divscale32 =\
        "xor eax, eax",\
        "idiv ebx",\
        parm nomemory [edx][ebx]\
        modify exact [eax edx]

#else  // non-Watcom platforms:


// These are not defines, so they land in pragma.c for ASM and non-ASM.
void swapchar(unsigned char *p1, unsigned char *p2);
void swapshort(short *p1, short *p2);
void swaplong(long *p1, long *p2);
void swapchar2(unsigned char *p1, unsigned char *p2, int xsiz);


#ifdef USE_I386_ASM
int sqr (int input1);
int scale (int input1, int input2, int input3);
int mulscale (int input1, int input2, short input3);
int mulscale1 (int input1, int input2);
int mulscale2 (int input1, int input2);
int mulscale3 (int input1, int input2);
int mulscale4 (int input1, int input2);
int mulscale5 (int input1, int input2);
int mulscale6 (int input1, int input2);
int mulscale7 (int input1, int input2);
int mulscale8 (int input1, int input2);
int mulscale9 (int input1, int input2);
int mulscale10 (int input1, int input2);
int mulscale11 (int input1, int input2);
int mulscale12 (int input1, int input2);
int mulscale13 (int input1, int input2);
int mulscale14 (int input1, int input2);
int mulscale15 (int input1, int input2);
int mulscale16 (int input1, int input2);
int mulscale17 (int input1, int input2);
int mulscale18 (int input1, int input2);
int mulscale19 (int input1, int input2);
int mulscale20 (int input1, int input2);
int mulscale21 (int input1, int input2);
int mulscale22 (int input1, int input2);
int mulscale23 (int input1, int input2);
int mulscale24 (int input1, int input2);
int mulscale25 (int input1, int input2);
int mulscale26 (int input1, int input2);
int mulscale27 (int input1, int input2);
int mulscale28 (int input1, int input2);
int mulscale29 (int input1, int input2);
int mulscale30 (int input1, int input2);
int mulscale31 (int input1, int input2);
int mulscale32 (int input1, int input2);
int dmulscale  (int input1, int input2, int input3);
int dmulscale1 (int input1, int input2, int input3, int input4);
int dmulscale2 (int input1, int input2, int input3, int input4);
int dmulscale3 (int input1, int input2, int input3, int input4);
int dmulscale4 (int input1, int input2, int input3, int input4);
int dmulscale5 (int input1, int input2, int input3, int input4);
int dmulscale6 (int input1, int input2, int input3, int input4);
int dmulscale7 (int input1, int input2, int input3, int input4);
int dmulscale8 (int input1, int input2, int input3, int input4);
int dmulscale9 (int input1, int input2, int input3, int input4);
int dmulscale10 (int input1, int input2, int input3, int input4);
int dmulscale11 (int input1, int input2, int input3, int input4);
int dmulscale12 (int input1, int input2, int input3, int input4);
int dmulscale13 (int input1, int input2, int input3, int input4);
int dmulscale14 (int input1, int input2, int input3, int input4);
int dmulscale15 (int input1, int input2, int input3, int input4);
int dmulscale16 (int input1, int input2, int input3, int input4);
int dmulscale17 (int input1, int input2, int input3, int input4);
int dmulscale18 (int input1, int input2, int input3, int input4);
int dmulscale19 (int input1, int input2, int input3, int input4);
int dmulscale20 (int input1, int input2, int input3, int input4);
int dmulscale21 (int input1, int input2, int input3, int input4);
int dmulscale22 (int input1, int input2, int input3, int input4);
int dmulscale23 (int input1, int input2, int input3, int input4);
int dmulscale24 (int input1, int input2, int input3, int input4);
int dmulscale25 (int input1, int input2, int input3, int input4);
int dmulscale26 (int input1, int input2, int input3, int input4);
int dmulscale27 (int input1, int input2, int input3, int input4);
int dmulscale28 (int input1, int input2, int input3, int input4);
int dmulscale29 (int input1, int input2, int input3, int input4);
int dmulscale30 (int input1, int input2, int input3, int input4);
int dmulscale31 (int input1, int input2, int input3, int input4);
int dmulscale32 (int input1, int input2, int input3, int input4);

int divscale(int i1, int i2, int i3);
int divscale1 (int input1, int input2);
int divscale2 (int input1, int input2);
int divscale3 (int input1, int input2);
int divscale4 (int input1, int input2);
int divscale5 (int input1, int input2);
int divscale6 (int input1, int input2);
int divscale7 (int input1, int input2);
int divscale8 (int input1, int input2);
int divscale9 (int input1, int input2);
int divscale10 (int input1, int input2);
int divscale11 (int input1, int input2);
int divscale12 (int input1, int input2);
int divscale13 (int input1, int input2);
int divscale14 (int input1, int input2);
int divscale15 (int input1, int input2);
int divscale16 (int input1, int input2);
int divscale17 (int input1, int input2);
int divscale18 (int input1, int input2);
int divscale19 (int input1, int input2);
int divscale20 (int input1, int input2);
int divscale21 (int input1, int input2);
int divscale22 (int input1, int input2);
int divscale23 (int input1, int input2);
int divscale24 (int input1, int input2);
int divscale25 (int input1, int input2);
int divscale26 (int input1, int input2);
int divscale27 (int input1, int input2);
int divscale28 (int input1, int input2);
int divscale29 (int input1, int input2);
int divscale30 (int input1, int input2);
int divscale31 (int input1, int input2);
int divscale32 (int input1, int input2);

void copybufreverse(void *source, void *dest, int size);
void copybuf(void *source, void *dest, int size);
void clearbuf(void *buffer, int size, long fill_value);
void clearbufbyte(void *buffer, int size, long fill_value);
void copybufbyte(void *source, void *dest, int size);
int ksgn(int i1);
int klabs (int i1);
int mul3 (int i1);
int mul5 (int i1);
int mul9 (int i1);

void qinterpolatedown16 (long *source, int size, int linum, int linum_inc);
void qinterpolatedown16short (long *source, int size, int linum, int linum_inc);

#else   // USE_I386_ASM

#define sqr(a) (a*a)
#define scale(a,b,c) ((a*b)/c)
#define mulscale(a,b,c) (((long long)a * (long long) b) >> c)
#define mulscale1(a,b) (((long long)a * (long long) b) >> 1)
#define mulscale2(a,b) (((long long)a * (long long) b) >> 2)
#define mulscale3(a,b) (((long long)a * (long long) b) >> 3)
#define mulscale4(a,b) (((long long)a * (long long) b) >> 4)
#define mulscale5(a,b) (((long long)a * (long long) b) >> 5)
#define mulscale6(a,b) (((long long)a * (long long) b) >> 6)
#define mulscale7(a,b) (((long long)a * (long long) b) >> 7)
#define mulscale8(a,b) (((long long)a * (long long) b) >> 8)
#define mulscale9(a,b) (((long long)a * (long long) b) >> 9)
#define mulscale10(a,b) (((long long)a * (long long) b) >> 10)
#define mulscale11(a,b) (((long long)a * (long long) b) >> 11)
#define mulscale12(a,b) (((long long)a * (long long) b) >> 12)
#define mulscale13(a,b) (((long long)a * (long long) b) >> 13)
#define mulscale14(a,b) (((long long)a * (long long) b) >> 14)
#define mulscale15(a,b) (((long long)a * (long long) b) >> 15)
#define mulscale16(a,b) (((long long)a * (long long) b) >> 16)
#define mulscale17(a,b) (((long long)a * (long long) b) >> 17)
#define mulscale18(a,b) (((long long)a * (long long) b) >> 18)
#define mulscale19(a,b) (((long long)a * (long long) b) >> 19)
#define mulscale20(a,b) (((long long)a * (long long) b) >> 20)
#define mulscale21(a,b) (((long long)a * (long long) b) >> 21)
#define mulscale22(a,b) (((long long)a * (long long) b) >> 22)
#define mulscale23(a,b) (((long long)a * (long long) b) >> 23)
#define mulscale24(a,b) (((long long)a * (long long) b) >> 24)
#define mulscale25(a,b) (((long long)a * (long long) b) >> 25)
#define mulscale26(a,b) (((long long)a * (long long) b) >> 26)
#define mulscale27(a,b) (((long long)a * (long long) b) >> 27)
#define mulscale28(a,b) (((long long)a * (long long) b) >> 28)
#define mulscale29(a,b) (((long long)a * (long long) b) >> 29)
#define mulscale30(a,b) (((long long)a * (long long) b) >> 30)
#define mulscale31(a,b) (((long long)a * (long long) b) >> 31)
#define mulscale32(a,b) ((long long) a * (long long) b)
#define dmulscale(a,b,c,d,e) (((long long)a*(long long)b + (long long)c*(long long)d) >> e)
#define dmulscale1(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 1)
#define dmulscale2(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 2)
#define dmulscale3(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 3)
#define dmulscale4(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 4)
#define dmulscale5(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 5)
#define dmulscale6(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 6)
#define dmulscale7(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 7)
#define dmulscale8(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 8)
#define dmulscale9(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 9)
#define dmulscale10(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 10)
#define dmulscale11(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 11)
#define dmulscale12(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 12)
#define dmulscale13(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 13)
#define dmulscale14(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 14)
#define dmulscale15(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 15)
#define dmulscale16(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 16)
#define dmulscale17(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 17)
#define dmulscale18(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 18)
#define dmulscale19(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 19)
#define dmulscale20(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 20)
#define dmulscale21(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 21)
#define dmulscale22(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 22)
#define dmulscale23(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 23)
#define dmulscale24(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 24)
#define dmulscale25(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 25)
#define dmulscale26(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 26)
#define dmulscale27(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 27)
#define dmulscale28(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 28)
#define dmulscale29(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 29)
#define dmulscale30(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 30)
#define dmulscale31(a,b,c,d) (((long long)a*(long long)b + (long long)c*(long long)d) >> 31)
#define dmulscale32(a,b,c,d) ((a*b + c*d))
#define tmulscale1(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 1)
#define tmulscale2(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 2)
#define tmulscale3(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 3)
#define tmulscale4(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 4)
#define tmulscale5(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 5)
#define tmulscale6(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 6)
#define tmulscale7(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 7)
#define tmulscale8(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 8)
#define tmulscale9(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 9)
#define tmulscale10(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 10)
#define tmulscale11(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 11)
#define tmulscale12(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 12)
#define tmulscale13(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 13)
#define tmulscale14(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 14)
#define tmulscale15(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 15)
#define tmulscale16(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 16)
#define tmulscale17(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 17)
#define tmulscale18(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 18)
#define tmulscale19(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 19)
#define tmulscale20(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 20)
#define tmulscale21(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 21)
#define tmulscale22(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 22)
#define tmulscale23(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 23)
#define tmulscale24(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 24)
#define tmulscale25(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 25)
#define tmulscale26(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 26)
#define tmulscale27(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 27)
#define tmulscale28(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 28)
#define tmulscale29(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 29)
#define tmulscale30(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 30)
#define tmulscale31(a,b,c,d,e,f) ((a*b + c*d + e*f) >> 31)
#define tmulscale32(a,b,c,d,e,f) ((a*b + c*d + e*f))
#define mul3(a) (a*3)
#define mul5(a) (a*5)
#define mul9(a) (a*9)

        //returns eax/ebx, dmval = eax%edx;
#define divmod(a,b) (a/b; dmval=a%b) 

        //returns eax%ebx, dmval = eax/edx;
#define moddiv(a,b) (a%b; dmval = a/b) 

#define clearbufbyte(buf, size, fillval) memset((char *) (buf), size, fillval)
#define clearbuf(buf, size, fillval)     memset((char *) (buf), size, fillval)
#define copybufbyte(src, dst, size)      memcpy((char *) (src), (char *) (dst), size)
#define copybuf(src, dst, size)          memcpy((char *) (src), (char *) (dst), size)
#define klabs(x) ( ((double) (x) < 0.0) ? (-(x)) : (x) )

#endif // USE_I386_ASM
#endif // __WATCOMC__

#endif // _INCLUDE_PRAGMAS_H_
