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

#if (!defined __GNUC__) && (!defined __ICC)
#error This file is filled with GNU C-specific inline asm.
#endif



long is_vmware_running(void)
{
    int retval;
    __asm__ __volatile__ (
        "call _asm_isvmwarerunning   \n\t"
       : "=a" (retval)
        :
        :  "cc", "ebx", "ecx", "edx", "memory");
    return(retval);
} /* is_vmware_running */


/* #pragma aux mmxoverlay modify [eax ebx ecx edx] */
long mmxoverlay(void)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_mmxoverlay   \n\t"
       : "=a" (retval)
        :
        :  "cc", "ebx", "ecx", "edx", "memory");
    return(retval);
} /* mmxoverlay */

/* #pragma aux sethlinesizes parm [eax][ebx][ecx] */
long sethlinesizes(long i1, long i2, long i3)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_sethlinesizes   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3)
        : "cc", "memory");
    return(retval);
} /* sethlinesizes */

/* #pragma aux setpalookupaddress parm [eax] */
long setpalookupaddress(char *i1)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_setpalookupaddress   \n\t"
       : "=a" (retval)
        : "a" (i1)
        : "cc", "memory");
    return(retval);
} /* setpalookupaddress */

/* #pragma aux setuphlineasm4 parm [eax][ebx] */
long setuphlineasm4(long i1, long i2)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_setuphlineasm4   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2)
        : "cc", "memory");
    return(retval);
} /* setuphlineasm4 */

/* #pragma aux hlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
long hlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_hlineasm4   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* hlineasm4 */

/* #pragma aux setuprhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
long setuprhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_setuprhlineasm4   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* setuprhlineasm4 */



/* #pragma aux rhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
long rhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_rhlineasm4   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* rhlineasm4 */


/* #pragma aux setuprmhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
long setuprmhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_setuprmhlineasm4   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* setuprmhlineasm4 */

/* #pragma aux rmhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
long rmhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_rmhlineasm4   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* rmhlineasm4 */


/* #pragma aux setupqrhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
long setupqrhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_setupqrhlineasm4   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* setupqrhlineasm4 */


/* #pragma aux qrhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
long qrhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_qrhlineasm4   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* qrhlineasm4 */

/* #pragma aux setvlinebpl parm [eax] */
long setvlinebpl(long i1)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_setvlinebpl   \n\t"
       : "=a" (retval)
        : "a" (i1)
        : "cc", "memory");
    return(retval);
} /* setvlinebpl */

/* #pragma aux fixtransluscence parm [eax] */
long fixtransluscence(long i1)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_fixtransluscence   \n\t"
       : "=a" (retval)
        : "a" (i1)
        : "cc", "memory");
    return(retval);
} /* fixtransluscence */

/* #pragma aux prevlineasm1 parm [eax][ebx][ecx][edx][esi][edi] */
long prevlineasm1(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_prevlineasm1   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* prevlineasm1 */

/* #pragma aux vlineasm1 parm [eax][ebx][ecx][edx][esi][edi] */
long vlineasm1(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_vlineasm1   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* vlineasm1 */


/* #pragma aux setuptvlineasm parm [eax] */
long setuptvlineasm(long i1)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_setuptvlineasm   \n\t"
       : "=a" (retval)
        : "a" (i1)
        : "cc", "memory");
    return(retval);
} /* setuptvlineasm */


/* #pragma aux tvlineasm1 parm [eax][ebx][ecx][edx][esi][edi] */
long tvlineasm1(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_tvlineasm1   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* tvlineasm1 */

/* #pragma aux setuptvlineasm2 parm [eax][ebx][ecx] */
long setuptvlineasm2(long i1, long i2, long i3)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_setuptvlineasm2   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3)
        : "cc", "memory");
    return(retval);
} /* */

/* #pragma aux tvlineasm2 parm [eax][ebx][ecx][edx][esi][edi] */
long tvlineasm2(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_tvlineasm2   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* tvlineasm2 */


/* #pragma aux mvlineasm1 parm [eax][ebx][ecx][edx][esi][edi] */
long mvlineasm1(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_mvlineasm1   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* mvlineasm1 */

/* #pragma aux setupvlineasm parm [eax] */
long setupvlineasm(long i1)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_setupvlineasm   \n\t"
       : "=a" (retval)
        : "a" (i1)
        : "cc", "memory");
    return(retval);
} /* setupvlineasm */

/* #pragma aux vlineasm4 parm [ecx][edi] modify [eax ebx ecx edx esi edi] */
long vlineasm4(long i1, long i2)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_vlineasm4   \n\t"
       : "=a" (retval)
        : "c" (i1), "D" (i2)
        : "cc", "ebx", "edx", "esi", "memory");
    return(retval);
} /* vlineasm4 */

/* #pragma aux setupmvlineasm parm [eax] */
long setupmvlineasm(long i1)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_setupmvlineasm   \n\t"
       : "=a" (retval)
        : "a" (i1)
        : "cc", "memory");
    return(retval);
} /* setupmvlineasm */

/* #pragma aux mvlineasm4 parm [ecx][edi] modify [eax ebx ecx edx esi edi] */
long mvlineasm4(long i1, long i2)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_mvlineasm4   \n\t"
       : "=a" (retval)
        : "c" (i1), "D" (i2)
        : "cc", "ebx", "edx", "esi", "memory");
    return(retval);
} /* mvlineasm4 */

/* #pragma aux setupspritevline parm [eax][ebx][ecx][edx][esi][edi] */
void setupspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    __asm__ __volatile__ (
        "call _asm_setupspritevline   \n\t"
       :
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
} /* setupspritevline */

/* #pragma aux spritevline parm [eax][ebx][ecx][edx][esi][edi] */
void spritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    __asm__ __volatile__ (
        "call _asm_spritevline   \n\t"
       :
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
} /* spritevline */

/* #pragma aux msetupspritevline parm [eax][ebx][ecx][edx][esi][edi] */
void msetupspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    __asm__ __volatile__ (
        "call _asm_msetupspritevline   \n\t"
       :
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
} /* msetupspritevline */

/* #pragma aux mspritevline parm [eax][ebx][ecx][edx][esi][edi] */
void mspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    __asm__ __volatile__ (
        "call _asm_mspritevline   \n\t"
       :
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
} /* mspritevline */

/* #pragma aux tsetupspritevline parm [eax][ebx][ecx][edx][esi][edi] */
void tsetupspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    __asm__ __volatile__ (
        "call _asm_tsetupspritevline   \n\t"
       :
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
} /* tsetupspritevline */

/* #pragma aux tspritevline parm [eax][ebx][ecx][edx][esi][edi] */
void tspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    __asm__ __volatile__ (
        "call _asm_tspritevline   \n\t"
       :
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
} /* tspritevline */

/* #pragma aux mhline parm [eax][ebx][ecx][edx][esi][edi] */
long mhline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_mhline   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* mhline */

/* #pragma aux mhlineskipmodify parm [eax][ebx][ecx][edx][esi][edi] */
long mhlineskipmodify(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_mhlineskipmodify   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* mhlineskipmodify */

/* #pragma aux msethlineshift parm [eax][ebx] */
long msethlineshift(long i1, long i2)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_msethlineshift   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2)
        : "cc", "memory");
    return(retval);
} /* msethlineshift */

/* #pragma aux thline parm [eax][ebx][ecx][edx][esi][edi] */
long thline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_thline   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* thline */

/* #pragma aux thlineskipmodify parm [eax][ebx][ecx][edx][esi][edi] */
long thlineskipmodify(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_thlineskipmodify   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* thlineskipmodify */

/* #pragma aux tsethlineshift parm [eax][ebx] */
long tsethlineshift(long i1, long i2)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_tsethlineshift   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2)
        : "cc", "memory");
    return(retval);
} /* tsethlineshift */

/* #pragma aux setupslopevlin parm [eax][ebx][ecx] modify [edx] */
long setupslopevlin(long i1, long i2, long i3)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_setupslopevlin   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3)
        : "cc", "edx", "memory");
    return(retval);
} /* setupslopevlin */

/* #pragma aux slopevlin parm [eax][ebx][ecx][edx][esi][edi] */
long slopevlin(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_slopevlin   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* slopevlin */

/* #pragma aux settransnormal parm */
long settransnormal(void)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_settransnormal   \n\t"
       : "=a" (retval)
        :
        : "cc", "memory");
    return(retval);
} /* settransnormal */

/* #pragma aux settransreverse parm */
long settransreverse(void)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_settransreverse   \n\t"
       : "=a" (retval)
        :
        : "cc", "memory");
    return(retval);
} /* settransreverse */

/* #pragma aux setupdrawslab parm [eax][ebx] */
long setupdrawslab(long i1, long i2)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_setupdrawslab   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2)
        : "cc", "memory");
    return(retval);
} /* setupdrawslab */

/* #pragma aux drawslab parm [eax][ebx][ecx][edx][esi][edi] */
long drawslab(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_drawslab   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* drawslab */

/* #pragma aux stretchhline parm [eax][ebx][ecx][edx][esi][edi] */
long stretchhline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval;
    __asm__ __volatile__ (
        "call _asm_stretchhline   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return(retval);
} /* drawslab */

/* end of a_gnu.c ... */

