/*
 * "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
 * Ken Silverman's official web site: "http://www.advsys.net/ken"
 * See the included license file "BUILDLIC.TXT" for license info.
 * This file has been modified from Ken Silverman's original release
 * (Actually, all the ASM was from a.asm, but that's obviously commented out.)
 */

#include "a.h"

#if (!defined USE_I386_ASM)
#error Please define USE_I386_ASM if you want to compile this.
#endif

#if (!defined _MSC_VER)
#error This file is filled with Microsoft Visual C-specific inline asm.
#endif

long is_vmware_running(void)
{
    int retval;
    __asm
    {
        call asm_isvmwarerunning
        mov retval, eax
    } /* asm */
    return(retval);
} /* is_vmware_running */


/* #pragma aux mmxoverlay modify [eax ebx ecx edx] */
long mmxoverlay(void)
{
    long retval;
    __asm
    {
        call asm_mmxoverlay
        mov retval, eax
    } /* asm */
    return(retval);
} /* mmxoverlay */

/* #pragma aux sethlinesizes parm [eax][ebx][ecx] */
long sethlinesizes(long i1, long i2, long i3)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        call asm_sethlinesizes
        mov retval, eax
    } /* asm */
    return(retval);
} /* sethlinesizes */

/* #pragma aux setpalookupaddress parm [eax] */
long setpalookupaddress(char *i1)
{
    long retval;
    __asm
    {
        mov eax, i1
        call asm_setpalookupaddress
        mov retval, eax
    } /* asm */
    return(retval);
} /* setpalookupaddress */

/* #pragma aux setuphlineasm4 parm [eax][ebx] */
long setuphlineasm4(long i1, long i2)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        call asm_setuphlineasm4
        mov retval, eax
    } /* asm */
    return(retval);
} /* setuphlineasm4 */

/* #pragma aux hlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
long hlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_hlineasm4
        mov retval, eax
    } /* asm */
    return(retval);
} /* hlineasm4 */

/* #pragma aux setuprhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
long setuprhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_setuprhlineasm4
        mov retval, eax
    } /* asm */
    return(retval);
} /* setuprhlineasm4 */



/* #pragma aux rhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
long rhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_rhlineasm4
        mov retval, eax
    } /* asm */
    return(retval);
} /* rhlineasm4 */


/* #pragma aux setuprmhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
long setuprmhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_setuprmhlineasm4
        mov retval, eax
    } /* asm */
    return(retval);
} /* setuprmhlineasm4 */

/* #pragma aux rmhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
long rmhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_rmhlineasm4
        mov retval, eax
    } /* asm */
    return(retval);
} /* rmhlineasm4 */


/* #pragma aux setupqrhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
long setupqrhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_setupqrhlineasm4
        mov retval, eax
    } /* asm */
    return(retval);
} /* setupqrhlineasm4 */


/* #pragma aux qrhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
long qrhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_qrhlineasm4
        mov retval, eax
    } /* asm */
    return(retval);
} /* qrhlineasm4 */

/* #pragma aux setvlinebpl parm [eax] */
long setvlinebpl(long i1)
{
    long retval;
    __asm
    {
        mov eax, i1
        call asm_setvlinebpl
        mov retval, eax
    } /* asm */
    return(retval);
} /* setvlinebpl */

/* #pragma aux fixtransluscence parm [eax] */
long fixtransluscence(long i1)
{
    long retval;
    __asm
    {
        mov eax, i1
        call asm_fixtransluscence
        mov retval, eax
    } /* asm */
    return(retval);
} /* fixtransluscence */

/* #pragma aux prevlineasm1 parm [eax][ebx][ecx][edx][esi][edi] */
long prevlineasm1(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_prevlineasm1
        mov retval, eax
    } /* asm */
    return(retval);
} /* prevlineasm1 */

/* #pragma aux vlineasm1 parm [eax][ebx][ecx][edx][esi][edi] */
long vlineasm1(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_vlineasm1
        mov retval, eax
    } /* asm */
    return(retval);
} /* vlineasm1 */


/* #pragma aux setuptvlineasm parm [eax] */
long setuptvlineasm(long i1)
{
    long retval;
    __asm
    {
        mov eax, i1
        call asm_setuptvlineasm
        mov retval, eax
    } /* asm */
    return(retval);
} /* setuptvlineasm */


/* #pragma aux tvlineasm1 parm [eax][ebx][ecx][edx][esi][edi] */
long tvlineasm1(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_tvlineasm1
        mov retval, eax
    } /* asm */
    return(retval);
} /* tvlineasm1 */

/* #pragma aux setuptvlineasm2 parm [eax][ebx][ecx] */
long setuptvlineasm2(long i1, long i2, long i3)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        call asm_setuptvlineasm2
        mov retval, eax
    } /* asm */
    return(retval);
} /* */

/* #pragma aux tvlineasm2 parm [eax][ebx][ecx][edx][esi][edi] */
long tvlineasm2(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_tvlineasm2
        mov retval, eax
    } /* asm */
    return(retval);
} /* tvlineasm2 */


/* #pragma aux mvlineasm1 parm [eax][ebx][ecx][edx][esi][edi] */
long mvlineasm1(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_mvlineasm1
        mov retval, eax
    } /* asm */
    return(retval);
} /* mvlineasm1 */

/* #pragma aux setupvlineasm parm [eax] */
long setupvlineasm(long i1)
{
    long retval;
    __asm
    {
        mov eax, i1
        call asm_setupvlineasm
        mov retval, eax
    } /* asm */
    return(retval);
} /* setupvlineasm */

/* #pragma aux vlineasm4 parm [ecx][edi] modify [eax ebx ecx edx esi edi] */
long vlineasm4(long i1, long i2)
{
    long retval;
    __asm
    {
        mov ecx, i1
        mov edi, i2
        call asm_vlineasm4
        mov retval, eax
    } /* asm */
    return(retval);
} /* vlineasm4 */

/* #pragma aux setupmvlineasm parm [eax] */
long setupmvlineasm(long i1)
{
    long retval;
    __asm
    {
        mov eax, i1
        call asm_setupmvlineasm
        mov retval, eax
    } /* asm */
    return(retval);
} /* setupmvlineasm */

/* #pragma aux mvlineasm4 parm [ecx][edi] modify [eax ebx ecx edx esi edi] */
long mvlineasm4(long i1, long i2)
{
    long retval;
    __asm
    {
        mov ecx, i1
        mov edi, i2
        call asm_mvlineasm4
        mov retval, eax
    } /* asm */
    return(retval);
} /* mvlineasm4 */

/* #pragma aux setupspritevline parm [eax][ebx][ecx][edx][esi][edi] */
void setupspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_setupspritevline
    } /* asm */
} /* setupspritevline */

/* #pragma aux spritevline parm [eax][ebx][ecx][edx][esi][edi] */
void spritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_spritevline
    } /* asm */
} /* spritevline */

/* #pragma aux msetupspritevline parm [eax][ebx][ecx][edx][esi][edi] */
void msetupspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_msetupspritevline
    } /* asm */
} /* msetupspritevline */

/* #pragma aux mspritevline parm [eax][ebx][ecx][edx][esi][edi] */
void mspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_mspritevline
    } /* asm */
} /* mspritevline */

/* #pragma aux tsetupspritevline parm [eax][ebx][ecx][edx][esi][edi] */
void tsetupspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_tsetupspritevline
    } /* asm */
} /* tsetupspritevline */

/* #pragma aux tspritevline parm [eax][ebx][ecx][edx][esi][edi] */
void tspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_tspritevline
    } /* asm */
} /* tspritevline */

/* #pragma aux mhline parm [eax][ebx][ecx][edx][esi][edi] */
long mhline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_mhline
        mov retval, eax
    } /* asm */
    return(retval);
} /* mhline */

/* #pragma aux mhlineskipmodify parm [eax][ebx][ecx][edx][esi][edi] */
long mhlineskipmodify(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_mhlineskipmodify
        mov retval, eax
    } /* asm */
    return(retval);
} /* mhlineskipmodify */

/* #pragma aux msethlineshift parm [eax][ebx] */
long msethlineshift(long i1, long i2)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        call asm_msethlineshift
        mov retval, eax
    } /* asm */
    return(retval);
} /* msethlineshift */

/* #pragma aux thline parm [eax][ebx][ecx][edx][esi][edi] */
long thline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_thline
        mov retval, eax
    } /* asm */
    return(retval);
} /* thline */

/* #pragma aux thlineskipmodify parm [eax][ebx][ecx][edx][esi][edi] */
long thlineskipmodify(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_thlineskipmodify
        mov retval, eax
    } /* asm */
    return(retval);
} /* thlineskipmodify */

/* #pragma aux tsethlineshift parm [eax][ebx] */
long tsethlineshift(long i1, long i2)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        call asm_tsethlineshift
        mov retval, eax
    } /* asm */
    return(retval);
} /* tsethlineshift */

/* #pragma aux setupslopevlin parm [eax][ebx][ecx] modify [edx] */
long setupslopevlin(long i1, long i2, long i3)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        call asm_setupslopevlin
        mov retval, eax
    } /* asm */
    return(retval);
} /* setupslopevlin */

/* #pragma aux slopevlin parm [eax][ebx][ecx][edx][esi][edi] */
long slopevlin(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_slopevlin
        mov retval, eax
    } /* asm */
    return(retval);
} /* slopevlin */

/* #pragma aux settransnormal parm */
long settransnormal(void)
{
    long retval;
    __asm
    {
        call asm_settransnormal
        mov retval, eax
    } /* asm */
    return(retval);
} /* settransnormal */

/* #pragma aux settransreverse parm */
long settransreverse(void)
{
    long retval;
    __asm
    {
        call asm_settransreverse
        mov retval, eax
    } /* asm */
    return(retval);
} /* settransreverse */

/* #pragma aux setupdrawslab parm [eax][ebx] */
long setupdrawslab(long i1, long i2)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        call asm_setupdrawslab
        mov retval, eax
    } /* asm */
    return(retval);
} /* setupdrawslab */

/* #pragma aux drawslab parm [eax][ebx][ecx][edx][esi][edi] */
long drawslab(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_drawslab
        mov retval, eax
    } /* asm */
    return(retval);
} /* drawslab */

/* #pragma aux stretchhline parm [eax][ebx][ecx][edx][esi][edi] */
long stretchhline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm
    {
        mov eax, i1
        mov ebx, i2
        mov ecx, i3
        mov edx, i4
        mov esi, i5
        mov edi, i6
        call asm_stretchhline
        mov retval, eax
    } /* asm */
    return(retval);
} /* drawslab */

/* end of a_visualc.c ... */

