/*
 * "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
 * Ken Silverman's official web site: "http://www.advsys.net/ken"
 * See the included license file "BUILDLIC.TXT" for license info.
 * This file has been modified from Ken Silverman's original release
 */

#ifndef __PRAGMAS_H__
#define __PRAGMAS_H__

#if (defined __WATCOMC__)

static long dmval = 0;

long is_vmware_running(void);
#pragma aux is_vmware_running modify exact [eax ebx ecx edx];

unsigned long getkensmessagecrc(long param);
#pragma aux getkensmessagecrc =\
    "xor eax, eax",\
    "mov ecx, 32",\
    "beg: mov edx, dword ptr [ebx+ecx*4-4]",\
    "ror edx, cl",\
    "adc eax, edx",\
    "bswap eax",\
    "loop short beg",\
    parm [ebx]\
    modify exact [eax ebx ecx edx]\

long msqrtasm(int param);
#pragma aux msqrtasm =\
    "mov eax, 0x40000000",\
    "mov ebx, 0x20000000",\
    "begit: cmp ecx, eax",\
    "jl skip",\
    "sub ecx, eax",\
    "lea eax, [eax+ebx*4]",\
    "skip: sub eax, ebx",\
    "shr eax, 1",\
    "shr ebx, 2",\
    "jnz begit",\
    "cmp ecx, eax",\
    "sbb eax, -1",\
    "shr eax, 1",\
    parm nomemory [ecx]\
    modify exact [eax ebx ecx]\

int sqr(int i1);
#pragma aux sqr =\
        "imul eax, eax",\
        parm nomemory [eax]\
        modify exact [eax]\
        value [eax]

long scale(long i1, long i2, long i3);
#pragma aux scale =\
        "imul edx",\
        "idiv ecx",\
        parm nomemory [eax][edx][ecx]\
        modify exact [eax edx]\

long mulscale(long i1, long i2, long i3);
#pragma aux mulscale =\
        "imul edx",\
        "shrd eax, edx, cl",\
        parm nomemory [eax][edx][ecx]\
        modify exact [eax edx]\

long mulscale1(long i1, long i2);
#pragma aux mulscale1 =\
        "imul edx",\
        "shrd eax, edx, 1",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale2(long i1, long i2);
#pragma aux mulscale2 =\
        "imul edx",\
        "shrd eax, edx, 2",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale3(long i1, long i2);
#pragma aux mulscale3 =\
        "imul edx",\
        "shrd eax, edx, 3",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale4(long i1, long i2);
#pragma aux mulscale4 =\
        "imul edx",\
        "shrd eax, edx, 4",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale5(long i1, long i2);
#pragma aux mulscale5 =\
        "imul edx",\
        "shrd eax, edx, 5",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale6(long i1, long i2);
#pragma aux mulscale6 =\
        "imul edx",\
        "shrd eax, edx, 6",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale7(long i1, long i2);
#pragma aux mulscale7 =\
        "imul edx",\
        "shrd eax, edx, 7",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale8(long i1, long i2);
#pragma aux mulscale8 =\
        "imul edx",\
        "shrd eax, edx, 8",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale9(long i1, long i2);
#pragma aux mulscale9 =\
        "imul edx",\
        "shrd eax, edx, 9",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale10(long i1, long i2);
#pragma aux mulscale10 =\
        "imul edx",\
        "shrd eax, edx, 10",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale11(long i1, long i2);
#pragma aux mulscale11 =\
        "imul edx",\
        "shrd eax, edx, 11",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale12(long i1, long i2);
#pragma aux mulscale12 =\
        "imul edx",\
        "shrd eax, edx, 12",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale13(long i1, long i2);
#pragma aux mulscale13 =\
        "imul edx",\
        "shrd eax, edx, 13",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale14(long i1, long i2);
#pragma aux mulscale14 =\
        "imul edx",\
        "shrd eax, edx, 14",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale15(long i1, long i2);
#pragma aux mulscale15 =\
        "imul edx",\
        "shrd eax, edx, 15",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale16(long i1, long i2);
#pragma aux mulscale16 =\
        "imul edx",\
        "shrd eax, edx, 16",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale17(long i1, long i2);
#pragma aux mulscale17 =\
        "imul edx",\
        "shrd eax, edx, 17",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale18(long i1, long i2);
#pragma aux mulscale18 =\
        "imul edx",\
        "shrd eax, edx, 18",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale19(long i1, long i2);
#pragma aux mulscale19 =\
        "imul edx",\
        "shrd eax, edx, 19",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale20(long i1, long i2);
#pragma aux mulscale20 =\
        "imul edx",\
        "shrd eax, edx, 20",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale21(long i1, long i2);
#pragma aux mulscale21 =\
        "imul edx",\
        "shrd eax, edx, 21",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale22(long i1, long i2);
#pragma aux mulscale22 =\
        "imul edx",\
        "shrd eax, edx, 22",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale23(long i1, long i2);
#pragma aux mulscale23 =\
        "imul edx",\
        "shrd eax, edx, 23",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale24(long i1, long i2);
#pragma aux mulscale24 =\
        "imul edx",\
        "shrd eax, edx, 24",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale25(long i1, long i2);
#pragma aux mulscale25 =\
        "imul edx",\
        "shrd eax, edx, 25",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale26(long i1, long i2);
#pragma aux mulscale26 =\
        "imul edx",\
        "shrd eax, edx, 26",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale27(long i1, long i2);
#pragma aux mulscale27 =\
        "imul edx",\
        "shrd eax, edx, 27",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale28(long i1, long i2);
#pragma aux mulscale28 =\
        "imul edx",\
        "shrd eax, edx, 28",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale29(long i1, long i2);
#pragma aux mulscale29 =\
        "imul edx",\
        "shrd eax, edx, 29",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale30(long i1, long i2);
#pragma aux mulscale30 =\
        "imul edx",\
        "shrd eax, edx, 30",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale31(long i1, long i2);
#pragma aux mulscale31 =\
        "imul edx",\
        "shrd eax, edx, 31",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\

long mulscale32(long i1, long i2);
#pragma aux mulscale32 =\
        "imul edx",\
        parm nomemory [eax][edx]\
        modify exact [eax edx]\
        value [edx]\

long dmulscale(long i1, long i2, long i3, long i4, long i5);
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

long dmulscale1(long i1, long i2, long i3, long i4);
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

long dmulscale2(long i1, long i2, long i3, long i4);
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

long dmulscale3(long i1, long i2, long i3, long i4);
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

long dmulscale4(long i1, long i2, long i3, long i4);
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

long dmulscale5(long i1, long i2, long i3, long i4);
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

long dmulscale6(long i1, long i2, long i3, long i4);
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

long dmulscale7(long i1, long i2, long i3, long i4);
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

long dmulscale8(long i1, long i2, long i3, long i4);
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

long dmulscale9(long i1, long i2, long i3, long i4);
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

long dmulscale10(long i1, long i2, long i3, long i4);
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

long dmulscale11(long i1, long i2, long i3, long i4);
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

long dmulscale12(long i1, long i2, long i3, long i4);
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

long dmulscale13(long i1, long i2, long i3, long i4);
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

long dmulscale14(long i1, long i2, long i3, long i4);
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

long dmulscale15(long i1, long i2, long i3, long i4);
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

long dmulscale16(long i1, long i2, long i3, long i4);
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

long dmulscale17(long i1, long i2, long i3, long i4);
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

long dmulscale18(long i1, long i2, long i3, long i4);
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

long dmulscale19(long i1, long i2, long i3, long i4);
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

long dmulscale20(long i1, long i2, long i3, long i4);
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

long dmulscale21(long i1, long i2, long i3, long i4);
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

long dmulscale22(long i1, long i2, long i3, long i4);
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

long dmulscale23(long i1, long i2, long i3, long i4);
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

long dmulscale24(long i1, long i2, long i3, long i4);
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

long dmulscale25(long i1, long i2, long i3, long i4);
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

long dmulscale26(long i1, long i2, long i3, long i4);
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

long dmulscale27(long i1, long i2, long i3, long i4);
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

long dmulscale28(long i1, long i2, long i3, long i4);
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

long dmulscale29(long i1, long i2, long i3, long i4);
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

long dmulscale30(long i1, long i2, long i3, long i4);
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

long dmulscale31(long i1, long i2, long i3, long i4);
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

long dmulscale32(long i1, long i2, long i3, long i4);
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

long tmulscale1(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale2(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale3(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale4(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale5(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale6(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale7(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale8(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale9(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale10(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale11(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale12(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale13(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale14(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale15(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale16(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale17(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale18(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale19(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale20(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale21(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale22(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale23(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale24(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale25(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale26(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale27(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale28(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale29(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale30(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale31(long i1, long i2, long i3, long i4, long i5, long i6);
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

long tmulscale32(long i1, long i2, long i3, long i4, long i5, long i6);
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

long boundmulscale(long i1, long i2, long i3);
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

long divscale(long i1, long i2, long i3);
#pragma aux divscale =\
        "mov edx, eax",\
        "shl eax, cl",\
        "neg cl",\
        "sar edx, cl",\
        "idiv ebx",\
        parm nomemory [eax][ebx][ecx]\
        modify exact [eax ecx edx]\

long divscale1(long i1, long i2);
#pragma aux divscale1 =\
        "add eax, eax",\
        "sbb edx, edx",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale2(long i1, long i2);
#pragma aux divscale2 =\
        "mov edx, eax",\
        "sar edx, 30",\
        "lea eax, [eax*4]",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale3(long i1, long i2);
#pragma aux divscale3 =\
        "mov edx, eax",\
        "sar edx, 29",\
        "lea eax, [eax*8]",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale4(long i1, long i2);
#pragma aux divscale4 =\
        "mov edx, eax",\
        "sar edx, 28",\
        "shl eax, 4",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale5(long i1, long i2);
#pragma aux divscale5 =\
        "mov edx, eax",\
        "sar edx, 27",\
        "shl eax, 5",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale6(long i1, long i2);
#pragma aux divscale6 =\
        "mov edx, eax",\
        "sar edx, 26",\
        "shl eax, 6",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale7(long i1, long i2);
#pragma aux divscale7 =\
        "mov edx, eax",\
        "sar edx, 25",\
        "shl eax, 7",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale8(long i1, long i2);
#pragma aux divscale8 =\
        "mov edx, eax",\
        "sar edx, 24",\
        "shl eax, 8",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale9(long i1, long i2);
#pragma aux divscale9 =\
        "mov edx, eax",\
        "sar edx, 23",\
        "shl eax, 9",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale10(long i1, long i2);
#pragma aux divscale10 =\
        "mov edx, eax",\
        "sar edx, 22",\
        "shl eax, 10",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale11(long i1, long i2);
#pragma aux divscale11 =\
        "mov edx, eax",\
        "sar edx, 21",\
        "shl eax, 11",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale12(long i1, long i2);
#pragma aux divscale12 =\
        "mov edx, eax",\
        "sar edx, 20",\
        "shl eax, 12",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale13(long i1, long i2);
#pragma aux divscale13 =\
        "mov edx, eax",\
        "sar edx, 19",\
        "shl eax, 13",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale14(long i1, long i2);
#pragma aux divscale14 =\
        "mov edx, eax",\
        "sar edx, 18",\
        "shl eax, 14",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale15(long i1, long i2);
#pragma aux divscale15 =\
        "mov edx, eax",\
        "sar edx, 17",\
        "shl eax, 15",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale16(long i1, long i2);
#pragma aux divscale16 =\
        "mov edx, eax",\
        "sar edx, 16",\
        "shl eax, 16",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale17(long i1, long i2);
#pragma aux divscale17 =\
        "mov edx, eax",\
        "sar edx, 15",\
        "shl eax, 17",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale18(long i1, long i2);
#pragma aux divscale18 =\
        "mov edx, eax",\
        "sar edx, 14",\
        "shl eax, 18",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale19(long i1, long i2);
#pragma aux divscale19 =\
        "mov edx, eax",\
        "sar edx, 13",\
        "shl eax, 19",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale20(long i1, long i2);
#pragma aux divscale20 =\
        "mov edx, eax",\
        "sar edx, 12",\
        "shl eax, 20",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale21(long i1, long i2);
#pragma aux divscale21 =\
        "mov edx, eax",\
        "sar edx, 11",\
        "shl eax, 21",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale22(long i1, long i2);
#pragma aux divscale22 =\
        "mov edx, eax",\
        "sar edx, 10",\
        "shl eax, 22",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale23(long i1, long i2);
#pragma aux divscale23 =\
        "mov edx, eax",\
        "sar edx, 9",\
        "shl eax, 23",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale24(long i1, long i2);
#pragma aux divscale24 =\
        "mov edx, eax",\
        "sar edx, 8",\
        "shl eax, 24",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale25(long i1, long i2);
#pragma aux divscale25 =\
        "mov edx, eax",\
        "sar edx, 7",\
        "shl eax, 25",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale26(long i1, long i2);
#pragma aux divscale26 =\
        "mov edx, eax",\
        "sar edx, 6",\
        "shl eax, 26",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale27(long i1, long i2);
#pragma aux divscale27 =\
        "mov edx, eax",\
        "sar edx, 5",\
        "shl eax, 27",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale28(long i1, long i2);
#pragma aux divscale28 =\
        "mov edx, eax",\
        "sar edx, 4",\
        "shl eax, 28",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale29(long i1, long i2);
#pragma aux divscale29 =\
        "mov edx, eax",\
        "sar edx, 3",\
        "shl eax, 29",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale30(long i1, long i2);
#pragma aux divscale30 =\
        "mov edx, eax",\
        "sar edx, 2",\
        "shl eax, 30",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale31(long i1, long i2);
#pragma aux divscale31 =\
        "mov edx, eax",\
        "sar edx, 1",\
        "shl eax, 31",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale32(long i1, long i2);
#pragma aux divscale32 =\
        "xor eax, eax",\
        "idiv ebx",\
        parm nomemory [edx][ebx]\
        modify exact [eax edx]\

/* !!! move these into ves.h?  --ryan. */
#ifdef PLATFORM_DOS

void int5(void);
#pragma aux int5 =\
        "int 0x5",\

int setupmouse(void);
#pragma aux setupmouse =\
        "mov ax, 0",\
        "int 33h",\
        "and eax, 0x0000ffff",\
        modify exact [eax]\

void readmousexy(short *x, short *y);
#pragma aux readmousexy =\
        "mov ax, 11d",\
        "int 33h",\
        "mov [esi], cx",\
        "mov [edi], dx",\
        parm [esi][edi]\
        modify exact [eax ebx ecx edx]\

void readmousebstatus(short *buttons);
#pragma aux readmousebstatus =\
        "mov ax, 5d",\
        "int 33h",\
        "mov [esi], ax",\
        parm [esi]\
        modify exact [eax ebx ecx edx]\

unsigned char readpixel(long offset);
#pragma aux readpixel =\
        "mov al, byte ptr [edi]",\
        parm nomemory [edi]\
        modify exact [eax]\

void drawpixel(long offset, unsigned char p);
#pragma aux drawpixel =\
        "mov byte ptr [edi], al",\
        parm [edi][eax]\
        modify exact \

void drawpixels(long offset, unsigned short p);
#pragma aux drawpixels =\
        "mov word ptr [edi], ax",\
        parm [edi][eax]\
        modify exact \

void drawpixelses(long offset, unsigned long p);
#pragma aux drawpixelses =\
        "mov dword ptr [edi], eax",\
        parm [edi][eax]\
        modify exact \

#endif


void clearbuf(void *buf, long i2, long i3);
#pragma aux clearbuf =\
        "rep stosd",\
        parm [edi][ecx][eax]\
        modify exact [edi ecx]\

void clearbufbyte(void *buf, long i2, long i3);
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

void copybuf(void *src, void *dst, long len);
#pragma aux copybuf =\
        "rep movsd",\
        parm [esi][edi][ecx]\
        modify exact [ecx esi edi]\

void copybufbyte(void *src, void *dst, long len);
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

void copybufreverse(void *src, void *dst, long len);
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

void qinterpolatedown16(long *i1, long i2, long i3, long i4);
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

void qinterpolatedown16short(long *i1, long i2, long i3, long i4);
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


#if (defined PLATFORM_DOS)   /* !!! move this to dos_driver.c? */

void setcolor16(int i1);
#pragma aux setcolor16 =\
        "mov dx, 0x3ce",\
        "shl ax, 8",\
        "out dx, ax",\
        parm [eax]\
        modify exact [eax edx]\

#endif  /* defined PLATFORM_DOS */


void vlin16first(long i1, long i2);
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

void vlin16(long i1, long i2);
#pragma aux vlin16 =\
        "mov esi, edi",\
        "begvlin16: movsb",\
        "add edi, 79",\
        "add esi, 79",\
        "dec ecx",\
        "jnz begvlin16",\
        parm [edi][ecx]\
        modify exact [ecx esi edi]\

#if (defined PLATFORM_DOS)   /* !!! move this to dos_driver.c? */

void drawpixel16(long offset);
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

void fillscreen16(long i1, long i2, long i3);
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

void koutp(long i1, long i);
#pragma aux koutp =\
        "out dx, al",\
        parm [edx][eax]\
        modify exact \

void koutpw(long i1, long i);
#pragma aux koutpw =\
        "out dx, ax",\
        parm [edx][eax]\
        modify exact \

int kinp(long i);
#pragma aux kinp =\
        "in al, dx",\
        parm nomemory [edx]\
        modify exact [eax]\

#endif  /* defined PLATFORM_DOS */


long mul3(long i1);
#pragma aux mul3 =\
        "lea eax, [eax+eax*2]",\
        parm nomemory [eax]\

long mul5(long i1);
#pragma aux mul5 =\
        "lea eax, [eax+eax*4]",\
        parm nomemory [eax]\

long mul9(long i1);
#pragma aux mul9 =\
        "lea eax, [eax+eax*8]",\
        parm nomemory [eax]\

        /* returns eax/ebx, dmval = eax%edx; */
long divmod(long i1, long i2);
#pragma aux divmod =\
        "xor edx, edx",\
        "div ebx",\
        "mov dmval, edx",\
        parm [eax][ebx]\
        modify exact [eax edx]\
        value [eax]

        /* returns eax%ebx, dmval = eax/edx; */
long moddiv(long i1, long i2);
#pragma aux moddiv =\
        "xor edx, edx",\
        "div ebx",\
        "mov dmval, eax",\
        parm [eax][ebx]\
        modify exact [eax edx]\
        value [edx]

long klabs(long i1);
#pragma aux klabs =\
        "test eax, eax",\
        "jns skipnegate",\
        "neg eax",\
        "skipnegate:",\
        parm nomemory [eax]\

long ksgn(long i1);
#pragma aux ksgn =\
        "add ebx, ebx",\
        "sbb eax, eax",\
        "cmp eax, ebx",\
        "adc al, 0",\
        parm nomemory [ebx]\
        modify exact [eax ebx]\

        /* eax = (unsigned min)umin(eax,ebx) */
long umin(long i1, long i2);
#pragma aux umin =\
        "sub eax, ebx",\
        "sbb ecx, ecx",\
        "and eax, ecx",\
        "add eax, ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax ecx]\

        /* eax = (unsigned max)umax(eax,ebx) */
long umax(long i1, long i2);
#pragma aux umax =\
        "sub eax, ebx",\
        "sbb ecx, ecx",\
        "xor ecx, 0xffffffff",\
        "and eax, ecx",\
        "add eax, ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax ecx]\

long kmin(long i1, long i2);
#pragma aux kmin =\
        "cmp eax, ebx",\
        "jl skipit",\
        "mov eax, ebx",\
        "skipit:",\
        parm nomemory [eax][ebx]\
        modify exact [eax]\

long kmax(long i1, long i2);
#pragma aux kmax =\
        "cmp eax, ebx",\
        "jg skipit",\
        "mov eax, ebx",\
        "skipit:",\
        parm nomemory [eax][ebx]\
        modify exact [eax]\

#if (defined PLATFORM_DOS)  /* !!! move to dos_driver.c? */
void limitrate(void);
#pragma aux limitrate =\
        "mov dx, 0x3da",\
        "wait1: in al, dx",\
        "test al, 8",\
        "jnz wait1",\
        "wait2: in al, dx",\
        "test al, 8",\
        "jz wait2",\
        modify exact [eax edx]\

long readtimer(void);
#pragma aux readtimer =\
        "mov al, 0xd2",\
        "out 0x43, al",\
        "in al, 0x40",\
        "shl eax, 24",\
        "in al, 0x40",\
        "rol eax, 8",\
        modify [eax]\

void redblueblit(void *i1, void *i2, long i3);
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


void swapchar(char *i1, char *i2);
#pragma aux swapchar =\
        "mov cl, [eax]",\
        "mov ch, [ebx]",\
        "mov [ebx], cl",\
        "mov [eax], ch",\
        parm [eax][ebx]\
        modify exact [ecx]\

void swapshort(short *i1, short *i2);
#pragma aux swapshort =\
        "mov cx, [eax]",\
        "mov dx, [ebx]",\
        "mov [ebx], cx",\
        "mov [eax], dx",\
        parm [eax][ebx]\
        modify exact [ecx edx]\

void swaplong(long *i1, long *i2);
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


        /*
         * swapchar2(ptr1,ptr2,xsiz); is the same as:
         * swapchar(ptr1,ptr2); swapchar(ptr1+1,ptr2+xsiz);
		 */ 
void swapchar2(char *ptr1, char *ptr2, long xsiz);
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
        /* accutimeroffs = -8-(t1-t0); */
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

        /* t = ((ecx-ebx+timeroffs1mhz)&0xfff0)*4095 + ecx; */
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

        /* eax = eax-ebx; if (eax < 0) eax += (1<<28) - (1<<16); */
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


/* FIXME: Why are all these divscale functions in here a second time? */
long divscale(long i1, long i2, long i3);
#pragma aux divscale =\
        "mov edx, eax",\
        "shl eax, cl",\
        "neg cl",\
        "sar edx, cl",\
        "idiv ebx",\
        parm nomemory [eax][ebx][ecx]\
        modify exact [eax ecx edx]
        
long divscale1(long i1, long i2);
#pragma aux divscale1 =\
        "add eax, eax",\
        "sbb edx, edx",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]
        
long divscale2(long i1, long i2);
#pragma aux divscale2 =\
        "mov edx, eax",\
        "sar edx, 30",\
        "lea eax, [eax*4]",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale3(long i1, long i2);
#pragma aux divscale3 =\
        "mov edx, eax",\
        "sar edx, 29",\
        "lea eax, [eax*8]",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale4(long i1, long i2);
#pragma aux divscale4 =\
        "mov edx, eax",\
        "sar edx, 28",\
        "shl eax, 4",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale5(long i1, long i2);
#pragma aux divscale5 =\
        "mov edx, eax",\
        "sar edx, 27",\
        "shl eax, 5",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale6(long i1, long i2);
#pragma aux divscale6 =\
        "mov edx, eax",\
        "sar edx, 26",\
        "shl eax, 6",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale7(long i1, long i2);
#pragma aux divscale7 =\
        "mov edx, eax",\
        "sar edx, 25",\
        "shl eax, 7",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale8(long i1, long i2);
#pragma aux divscale8 =\
        "mov edx, eax",\
        "sar edx, 24",\
        "shl eax, 8",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale9(long i1, long i2);
#pragma aux divscale9 =\
        "mov edx, eax",\
        "sar edx, 23",\
        "shl eax, 9",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale10(long i1, long i2);
#pragma aux divscale10 =\
        "mov edx, eax",\
        "sar edx, 22",\
        "shl eax, 10",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale11(long i1, long i2);
#pragma aux divscale11 =\
        "mov edx, eax",\
        "sar edx, 21",\
        "shl eax, 11",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale12(long i1, long i2);
#pragma aux divscale12 =\
        "mov edx, eax",\
        "sar edx, 20",\
        "shl eax, 12",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale13(long i1, long i2);
#pragma aux divscale13 =\
        "mov edx, eax",\
        "sar edx, 19",\
        "shl eax, 13",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale14(long i1, long i2);
#pragma aux divscale14 =\
        "mov edx, eax",\
        "sar edx, 18",\
        "shl eax, 14",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale15(long i1, long i2);
#pragma aux divscale15 =\
        "mov edx, eax",\
        "sar edx, 17",\
        "shl eax, 15",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale16(long i1, long i2);
#pragma aux divscale16 =\
        "mov edx, eax",\
        "sar edx, 16",\
        "shl eax, 16",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale17(long i1, long i2);
#pragma aux divscale17 =\
        "mov edx, eax",\
        "sar edx, 15",\
        "shl eax, 17",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale18(long i1, long i2);
#pragma aux divscale18 =\
        "mov edx, eax",\
        "sar edx, 14",\
        "shl eax, 18",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale19(long i1, long i2);
#pragma aux divscale19 =\
        "mov edx, eax",\
        "sar edx, 13",\
        "shl eax, 19",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale20(long i1, long i2);
#pragma aux divscale20 =\
        "mov edx, eax",\
        "sar edx, 12",\
        "shl eax, 20",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale21(long i1, long i2);
#pragma aux divscale21 =\
        "mov edx, eax",\
        "sar edx, 11",\
        "shl eax, 21",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale22(long i1, long i2);
#pragma aux divscale22 =\
        "mov edx, eax",\
        "sar edx, 10",\
        "shl eax, 22",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale23(long i1, long i2);
#pragma aux divscale23 =\
        "mov edx, eax",\
        "sar edx, 9",\
        "shl eax, 23",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale24(long i1, long i2);
#pragma aux divscale24 =\
        "mov edx, eax",\
        "sar edx, 8",\
        "shl eax, 24",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale25(long i1, long i2);
#pragma aux divscale25 =\
        "mov edx, eax",\
        "sar edx, 7",\
        "shl eax, 25",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale26(long i1, long i2);
#pragma aux divscale26 =\
        "mov edx, eax",\
        "sar edx, 6",\
        "shl eax, 26",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale27(long i1, long i2);
#pragma aux divscale27 =\
        "mov edx, eax",\
        "sar edx, 5",\
        "shl eax, 27",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale28(long i1, long i2);
#pragma aux divscale28 =\
        "mov edx, eax",\
        "sar edx, 4",\
        "shl eax, 28",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale29(long i1, long i2);
#pragma aux divscale29 =\
        "mov edx, eax",\
        "sar edx, 3",\
        "shl eax, 29",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale30(long i1, long i2);
#pragma aux divscale30 =\
        "mov edx, eax",\
        "sar edx, 2",\
        "shl eax, 30",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale31(long i1, long i2);
#pragma aux divscale31 =\
        "mov edx, eax",\
        "sar edx, 1",\
        "shl eax, 31",\
        "idiv ebx",\
        parm nomemory [eax][ebx]\
        modify exact [eax edx]\

long divscale32(long i1, long i2);
#pragma aux divscale32 =\
        "xor eax, eax",\
        "idiv ebx",\
        parm nomemory [edx][ebx]\
        modify exact [eax edx]

#else  /* non-Watcom platforms land here: */

#include "platform.h" //for __int64

static __inline void swapchar(unsigned char *p1, unsigned char *p2)
{ unsigned char tmp = *p1; *p1 = *p2; *p2 = tmp; }
static __inline void swapshort(short *p1, short *p2)
{ short tmp = *p1; *p1 = *p2; *p2 = tmp; }
static __inline void swaplong(long *p1, long *p2)
{ long tmp = *p1; *p1 = *p2; *p2 = tmp; }
static __inline void swapchar2(unsigned char *p1, unsigned char *p2, int xsiz)
{
    swapchar(p1, p2);
    swapchar(p1 + 1, p2 + xsiz);
}


unsigned long getkensmessagecrc(long param);
long msqrtasm(int i1);

void vlin16first (long i1, long i2);

static __inline int sqr (int input1) { return input1*input1; }

/* internal use:32x32 = 64bit */
static __inline __int64 mul32_64(int i1,int i2)
{
	return (__int64)i1*i2;
}
static __inline int scale (int input1, int input2, int input3)
{
	return mul32_64(input1,input2)/input3;
}
static __inline int mulscale (int input1, int input2, int input3)
{
	return mul32_64(input1,input2)>>input3;
}
static __inline int dmulscale  (int input1, int input2, int input3,int input4,int input5)
{
	return (mul32_64(input1,input2) + mul32_64(input3,input4))>>input5;
}
static __inline int tmulscale(int i1, int i2, int i3, int i4, int i5, int i6,int shift)
{
	return (mul32_64(i1,i2) + mul32_64(i3,i4) + mul32_64(i5,i6))>>shift;
}
static __inline int divscale(int i1, int i2, int i3)
{
	return ((__int64)i1<<i3)/i2;
}

#define DEFFUNCS \
DEFFUN(1)\
DEFFUN(2)\
DEFFUN(3)\
DEFFUN(4)\
DEFFUN(5)\
DEFFUN(6)\
DEFFUN(7)\
DEFFUN(8)\
DEFFUN(9)\
DEFFUN(10)\
DEFFUN(11)\
DEFFUN(12)\
DEFFUN(13)\
DEFFUN(14)\
DEFFUN(15)\
DEFFUN(16)\
DEFFUN(17)\
DEFFUN(18)\
DEFFUN(19)\
DEFFUN(20)\
DEFFUN(21)\
DEFFUN(22)\
DEFFUN(23)\
DEFFUN(24)\
DEFFUN(25)\
DEFFUN(26)\
DEFFUN(27)\
DEFFUN(28)\
DEFFUN(29)\
DEFFUN(30)\
DEFFUN(31)\
DEFFUN(32)

#define DEFFUN(N) \
static __inline int mulscale##N(int input1, int input2) \
{ return mulscale(input1,input2,N); }
DEFFUNCS
#undef DEFFUN

#define DEFFUN(N) \
static __inline int dmulscale##N(int input1, int input2,int input3,int input4) \
{ return dmulscale(input1,input2,input3,input4,N); }
DEFFUNCS
#undef DEFFUN

#define DEFFUN(N) \
static __inline int tmulscale##N(int i1, int i2,int i3,int i4,int i5,int i6) \
{ return tmulscale(i1,i2,i3,i4,i5,i6,N); }
DEFFUNCS
#undef DEFFUN

#define DEFFUN(N) \
static __inline int divscale##N(int input1, int input2) \
{ return divscale(input1,input2,N); }
DEFFUNCS
#undef DEFFUN

static __inline int ksgn(int i1)
{
  if (i1 < 0) return -1;
  else if (i1 > 0) return 1;
  else return 0;
}

static __inline int sgn(int i1) { return ksgn(i1); }
static __inline int klabs (int i1)
{
  if (i1 < 0) i1 = -i1;
  return i1;
}
static __inline int mul3 (int i1) { return i1*3; }
static __inline int mul5 (int i1) { return i1*5; }
static __inline int mul9 (int i1) { return i1*9; }

void copybufreverse(void *source, void *dest, int size);
void copybuf(void *source, void *dest, int size);
void clearbuf(void *buffer, int size, long fill_value);
void clearbufbyte(void *buffer, int size, long fill_value);
void copybufbyte(void *source, void *dest, int size);

void qinterpolatedown16 (long *source, int size, int linum, int linum_inc);
void qinterpolatedown16short (long *source, int size, int linum, int linum_inc);

#endif /* defined __WATCOMC__ */

#endif /* !defined _INCLUDE_PRAGMAS_H_ */

/* end of pragmas.h ... */


