// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.
// This file has been modified from Ken Silverman's original release

/* DDOI - This file is an attempt to reimplement a_nasm.asm in C */

#include "platform.h"
#include "build.h"

#define shrd(a,b,c) (((b)<<(32-(c))) | ((a)>>(c)))
#define shld(a,b,c) (((b)>>(32-(c))) | ((a)<<(c)))

extern long asm1;
extern long asm2;
extern long asm3;
extern long asm4;

long is_vmware_running(void)
{
    return 0;
} /* is_vmware_running */

/* #pragma aux mmxoverlay modify [eax ebx ecx edx] */
long mmxoverlay(void)
{
    return 0;
} /* mmxoverlay */

/* #pragma aux sethlinesizes parm [eax][ebx][ecx] */
static unsigned char machxbits_al;
static unsigned char machxbits_bl;
static long machxbits_ecx;
static unsigned long machxbits_edx;
void sethlinesizes(long i1, long i2, long i3)
{
    machxbits_al = i1;
    machxbits_bl = i2;
    machxbits_ecx = i3;
    machxbits_edx = -1;
    machxbits_edx >>= (256-machxbits_al-machxbits_bl);
} /* sethlinesizes */

/* #pragma aux setpalookupaddress parm [eax] */
static unsigned char* pal_eax;
void setpalookupaddress(char *i1)
{
    pal_eax = i1;
} /* setpalookupaddress */

/* #pragma aux setuphlineasm4 parm [eax][ebx] */
static long hmach4_eax;
static long hmach4_ebx;
void setuphlineasm4(long i1, long i2)
{
    hmach4_eax = ((i1<<machxbits_al)|(((unsigned)i1)>>(32-machxbits_al)));
    hmach4_ebx = ((i2&0xffffff00)|(hmach4_eax&0xff));
} /* setuphlineasm4 */

/* #pragma aux hlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
void hlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    unsigned char *source = (unsigned char *)i5;
    unsigned char *dest = (unsigned char *)i6;

    i1 += 1;
    if (i1 == 0) return;
    while (i1) {
	    unsigned char *source2 = source;
	    ((unsigned)source2)>>=(256-machxbits_al);
	    ((unsigned)source2) =
		    shld(((unsigned)source2),(unsigned)i4,machxbits_bl);
	    i3 = (i3&0xffffff00) | (source2[machxbits_ecx]&0xff);
	    *dest = pal_eax[i3];
	    dest--;
	    source -= asm1;
	    i4 -= asm2;
	    i1--;
    }
} /* hlineasm4 */

/* #pragma aux setuprhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
static long rmach_eax;
static long rmach_ebx;
static long rmach_ecx;
static long rmach_edx;
static long rmach_esi;
void setuprhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    rmach_eax = i1;
    rmach_ebx = i2;
    rmach_ecx = i3;
    rmach_edx = i4;
    rmach_esi = i5;
} /* setuprhlineasm4 */

void rhlineasm4(long i1, long i2, long i3, unsigned long i4, unsigned long i5, long i6)
{
    unsigned long ebp = i6 - i1;
    unsigned long rmach6b = ebp-1;

    if (i1 <= 0) return;

    i6 = i1;
    do {
	    i3 = ((i3&0xffffff00)|(*((unsigned char *)i2)));
	    i4 -= rmach_eax;
	    ebp = (((i4+rmach_eax) < i4) ? -1 : 0);
	    i5 -= rmach_ebx;
	    if ((i5 + rmach_ebx) < i5) i2 -= (rmach_ecx+1);
	    else i2 -= rmach_ecx;
	    ebp &= rmach_esi;
	    i1 = ((i1&0xffffff00)|(((unsigned char *)i3)[rmach_edx]));
	    ((unsigned char *)rmach6b)[i6] = (i1&0xff);
	    i2 -= ebp;
	    i6--;
    } while (i6);
} /* rhlineasm4 */

static long rmmach_eax;
static long rmmach_ebx;
static long rmmach_ecx;
static long rmmach_edx;
static long rmmach_esi;
void setuprmhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    rmmach_eax = i1;
    rmmach_ebx = i2;
    rmmach_ecx = i3;
    rmmach_edx = i4;
    rmmach_esi = i5;
} /* setuprmhlineasm4 */

/* #pragma aux rmhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
void rmhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    unsigned long ebp = i6 - i1;
    unsigned long rmach6b = ebp-1;

    if (i1 <= 0) return;

    i6 = i1;
    do {
	    i3 = ((i3&0xffffff00)|(*((unsigned char *)i2)));
	    i4 -= rmmach_eax;
	    ebp = (((i4+rmmach_eax) < i4) ? -1 : 0);
	    i5 -= rmmach_ebx;
	    if ((i5 + rmmach_ebx) < i5) i2 -= (rmmach_ecx+1);
	    else i2 -= rmmach_ecx;
	    ebp &= rmmach_esi;
	    if ((i3&0xff) != 255) {
		    i1 = ((i1&0xffffff00)|(((unsigned char *)i3)[rmmach_edx]));
		    ((unsigned char *)rmach6b)[i6] = (i1&0xff);
	    }
	    i2 -= ebp;
	    i6--;
    } while (i6);
} /* rmhlineasm4 */


/* #pragma aux setupqrhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
static long qrmach_ebx;
static unsigned long qrmach_ebx2;
static long qrmach_ecx;
static long qrmach_ecx2;
static long qrmach_edx;
static long qrmach_edi;
void setupqrhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    qrmach_ebx = i2;
    qrmach_ecx = i3;
    qrmach_edx = i6;
    qrmach_edi = -qrmach_ecx;
    qrmach_ebx2 = qrmach_ebx + qrmach_ebx;
    if (qrmach_ebx2 < qrmach_ebx) qrmach_ecx2 = qrmach_ecx + qrmach_ecx + 1;
    else qrmach_ecx2 = qrmach_ecx + qrmach_ecx;
} /* setupqrhlineasm4 */


/* #pragma aux qrhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
void qrhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
	/*
    __asm__ __volatile__ (
        "call _asm_qrhlineasm4   \n\t"
        : : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
	*/
/*
_asm_qrhlineasm4:
	push ebp

	cmp eax, 0
	jle NEAR endqrhline

	mov ebp, eax
	test ebp, 3
	jz short skipqrhline1
	jmp short startqrhline1

ALIGN 16
startqrhline1:
	mov cl, byte [ebx]                      ;bufplc
	dec edi
qrmach2e: sub esi, 88888888h                   ;ylo
	dec ebp
qrmach3e: sbb ebx, 88888888h                   ;xhi*tilesizy + yhi+ycarry
qrmach4e: mov al, byte [ecx+88888888h]     ;palookup
	mov byte [edi], al                      ;vidcntoffs
	test ebp, 3
	jnz short startqrhline1
	test ebp, ebp
	jz short endqrhline

skipqrhline1:
	mov cl, byte [ebx]                      ;bufplc
	jmp short begqrhline
ALIGN 16
begqrhline:
qrmach7a: mov dl, byte [ebx+88888888h]     ;bufplc
qrmach2a: sub esi, 88888888h                   ;ylo
qrmach3a: sbb ebx, 88888888h                   ;xhi*tilesizy + yhi+ycarry
qrmach4a: mov ah, byte [ecx+88888888h]     ;palookup
qrmach4b: mov al, byte [edx+88888888h]     ;palookup
	sub edi, 4
	shl eax, 16
	mov cl, byte [ebx]                      ;bufplc
qrmach7b: mov dl, byte [ebx+88888888h]     ;bufplc
qrmach2b: sub esi, 88888888h                   ;ylo
qrmach3b: sbb ebx, 88888888h                   ;xhi*tilesizy + yhi+ycarry
qrmach4c: mov ah, byte [ecx+88888888h]     ;palookup
qrmach4d: mov al, byte [edx+88888888h]     ;palookup
	mov cl, byte [ebx]                      ;bufplc
	mov dword [edi], eax
	sub ebp, 4
	jnz short begqrhline

endqrhline:
	pop ebp
	ret
*/
} /* qrhlineasm4 */

/* #pragma aux setvlinebpl parm [eax] */
static long fixchain;
void setvlinebpl(long i1)
{
    fixchain = i1;
} /* setvlinebpl */

/* #pragma aux fixtransluscence parm [eax] */
static long tmach;
void fixtransluscence(long i1)
{
    tmach = i1;
    /*
    __asm__ __volatile__ (
        "call _asm_fixtransluscence   \n\t"
        : : "a" (i1)
        : "cc", "memory");
	*/
/*
_asm_fixtransluscence:
	mov dword [transmach4+2], eax
	mov dword [tmach1+2], eax
	mov dword [tmach2+2], eax
	mov dword [tmach3+2], eax
	mov dword [tmach4+2], eax
	mov dword [tran2traa+2], eax
	mov dword [tran2trab+2], eax
	mov dword [tran2trac+2], eax
	mov dword [tran2trad+2], eax
    ret
*/ 
} /* fixtransluscence */

long vlineasm1(long i1, long i2, long i3, long i4, long i5, long i6);

/* #pragma aux prevlineasm1 parm [eax][ebx][ecx][edx][esi][edi] */
static unsigned char mach3_al;
long prevlineasm1(long i1, long i2, long i3, long i4, long i5, long i6)
{
    unsigned char *source = (unsigned char *)i5;
    unsigned char *dest = (unsigned char *)i6;
    if (i3 == 0)
    {
	    i1 += i4;
	    ((unsigned long)i4) >>= mach3_al;
	    i4 = (i4&0xffffff00) | (source[i4]&0xff);
	    *dest = ((unsigned char*)i2)[i4];
	    return i1;
    } else {
	    return vlineasm1(i1,i2,i3,i4,i5,i6);
    }
} /* prevlineasm1 */

/* #pragma aux vlineasm1 parm [eax][ebx][ecx][edx][esi][edi] */
long vlineasm1(long i1, long i2, long i3, long i4, long i5, long i6)
{
    unsigned char *source = (unsigned char *)i5;
    unsigned char *dest = (unsigned char *)i6;

    i3++;
    dest -= fixchain;
    while (i3)
    {
	    unsigned long temp = i4;
	    temp >>= mach3_al;
	    dest += fixchain;
	    temp = (temp&0xffffff00) | (source[temp]&0xff);
	    *dest = ((unsigned char*)i2)[temp];
	    i4 += i1;
	    i3--;
    }
    return i4;
} /* vlineasm1 */


/* #pragma aux setuptvlineasm parm [eax] */
static unsigned char transmach3_al;
void setuptvlineasm(long i1)
{
    transmach3_al = i1;
    /*
    __asm__ __volatile__ (
        "call _asm_setuptvlineasm   \n\t"
        : : "a" (i1)
        : "cc", "memory");
	*/
/*
_asm_setuptvlineasm:
	mov byte [transmach3a+2], al
	ret
*/
} /* setuptvlineasm */


/* #pragma aux tvlineasm1 parm [eax][ebx][ecx][edx][esi][edi] */
long tvlineasm1(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval = 0;
    /*
    __asm__ __volatile__ (
        "call _asm_tvlineasm1   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
*/
    return(retval);
/*
_asm_tvlineasm1:
	push ebp
	mov ebp, eax
	xor eax, eax
	inc ecx
	mov dword [transmach3c+2], ebx
	jmp short begintvline

ALIGN 16
begintvline:
	mov ebx, edx
transmach3a: shr ebx, 32
	mov bl, byte [esi+ebx]
	cmp bl, 255
	je short skiptrans1
transrev0:
transmach3c: mov al, [ebx+88888888h]
transrev1:
	mov ah, byte [edi]
transmach4: mov al, byte [eax+88888888h]   ;transluc[eax]
	mov byte [edi], al
skiptrans1:
	add edx, ebp
fixchain1t: add edi, 320
	dec ecx
	jnz short begintvline

	pop ebp
	mov eax, edx
	ret
*/
} /* tvlineasm1 */

/* #pragma aux setuptvlineasm2 parm [eax][ebx][ecx] */
long setuptvlineasm2(long i1, long i2, long i3)
{
    long retval = 0;
    /*
    __asm__ __volatile__ (
        "call _asm_setuptvlineasm2   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3)
        : "cc", "memory");
	*/
    return(retval);
/*
_asm_setuptvlineasm2:
	mov byte [tran2shra+2], al
	mov byte [tran2shrb+2], al
	mov dword [tran2pala+2], ebx
	mov dword [tran2palb+2], ecx
	mov dword [tran2palc+2], ebx
	mov dword [tran2pald+2], ecx
	ret
*/
} /* */

/* #pragma aux tvlineasm2 parm [eax][ebx][ecx][edx][esi][edi] */
long tvlineasm2(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval = 0;
    /*
    __asm__ __volatile__ (
        "call _asm_tvlineasm2   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
	*/
    return(retval);
/*
_asm_tvlineasm2:
	push ebp

	mov ebp, eax

	mov dword [tran2inca+2], ebx
	mov eax, [asm1]
	mov dword [tran2incb+2], eax

	mov dword [tran2bufa+2], ecx         ;bufplc1
	mov dword [tran2bufb+2], edx         ;bufplc2

	mov eax, [asm2]
	sub edi, eax
	mov dword [tran2edia+3], eax
	mov dword [tran2edic+2], eax
	inc eax
	mov dword [tran2edie+2], eax
fixchaint2a: sub eax, 320
	mov dword [tran2edif+2], eax
	dec eax
	mov dword [tran2edib+3], eax
	mov dword [tran2edid+2], eax

	xor ecx, ecx
	xor edx, edx
	jmp short begintvline2

		;eax 0000000000  temp  temp
		;ebx 0000000000 odat2 odat1
		;ecx 0000000000000000 ndat1
		;edx 0000000000000000 ndat2
		;esi          vplc1
		;edi videoplc--------------
		;ebp          vplc2

ALIGN 16
		;LEFT ONLY
skipdraw2:
transrev10:
tran2edic: mov ah, byte [edi+88888888h]      ;getpixel
transrev11:
tran2palc: mov al, byte [ecx+88888888h]      ;palookup1
fixchaint2d: add edi, 320
tran2trac: mov bl, byte [eax+88888888h]      ;transluc
tran2edid: mov byte [edi+88888888h-320], bl  ;drawpixel
	jnc short begintvline2
	jmp endtvline2

skipdraw1:
	cmp dl, 255
	jne short skipdraw3
fixchaint2b: add edi, 320
	jc short endtvline2

begintvline2:
	mov eax, esi
tran2shra: shr eax, 88h                      ;globalshift
	mov ebx, ebp
tran2shrb: shr ebx, 88h                      ;globalshift
tran2inca: add esi, 88888888h                ;vinc1
tran2incb: add ebp, 88888888h                ;vinc2
tran2bufa: mov cl, byte [eax+88888888h]  ;bufplc1
	cmp cl, 255
tran2bufb: mov dl, byte [ebx+88888888h]  ;bufplc2
	je short skipdraw1
	cmp dl, 255
	je short skipdraw2

	;mov ax        The transluscent reverse of both!
	;mov bl, ah
	;mov ah
	;mov bh

		;BOTH
transrev12:
tran2edia: mov bx, word [edi+88888888h]      ;getpixels
transrev13:
	mov ah, bl
transrev14:
tran2pala: mov al, byte [ecx+88888888h]      ;palookup1
transrev15:
tran2palb: mov bl, byte [edx+88888888h]      ;palookup2
fixchaint2c: add edi, 320
tran2traa: mov al, byte [eax+88888888h]      ;transluc
tran2trab: mov ah, byte [ebx+88888888h]      ;transluc
tran2edib: mov word [edi+88888888h-320], ax  ;drawpixels
	jnc short begintvline2
	jmp short endtvline2

	;RIGHT ONLY
skipdraw3:
transrev16:
tran2edie: mov ah, byte [edi+88888889h]      ;getpixel
transrev17:
tran2pald: mov al, byte [edx+88888888h]      ;palookup2
fixchaint2e: add edi, 320
tran2trad: mov bl, byte [eax+88888888h]      ;transluc
tran2edif: mov byte [edi+88888889h-320], bl  ;drawpixel
	jnc short begintvline2

endtvline2:
	mov [asm1], esi
	mov [asm2], ebp

	pop ebp
	ret
*/
} /* tvlineasm2 */


/* #pragma aux mvlineasm1 parm [eax][ebx][ecx][edx][esi][edi] */
static unsigned char machmv;
long mvlineasm1(long i1, long i2, long i3, long i4, long i5, long i6)
{
    unsigned char *source = (unsigned char *)i5;
    unsigned char *dest = (unsigned char *)i6;

    dest -= fixchain;
    while (i3)
    {
	    unsigned long temp = i4;
	    temp >>= machmv;
	    dest += fixchain;
	    temp = source[temp];
	    if (temp != 255)
		    *dest = ((unsigned char*)i2)[temp];
	    i4 += i1;
	    i3--;
    }
    return i4;
} /* mvlineasm1 */

/* #pragma aux setupvlineasm parm [eax] */
static unsigned char mach3_ah;
static unsigned int mach3_eax;
void setupvlineasm(long i1)
{
    mach3_al = i1;
    mach3_ah = mach3_al - 16;
    mach3_eax = (1<<(256-mach3_al)) - 1;
} /* setupvlineasm */

extern long vplce[4], vince[4], palookupoffse[4], bufplce[4];
/* #pragma aux vlineasm4 parm [ecx][edi] modify [eax ebx ecx edx esi edi] */
void vlineasm4(long i1, long i2)
{
    unsigned long index = (i2 + ylookup[i1])/4;
    long machvbuf1 = bufplce[2];
    long machvbuf2 = bufplce[3];
    long machvbuf3 = bufplce[0];
    long machvbuf4 = bufplce[1];
    long machvpal1 = palookupoffse[2];
    long machvpal2 = palookupoffse[3];
    long machvpal3 = palookupoffse[0];
    long machvpal4 = palookupoffse[1];
    long machvinc1, machvinc2, machvinc5;
    unsigned short machvinc34;
    unsigned long eax, ebx, edx, esi, ebp;
    unsigned long out = 0;
    unsigned long *dest = (unsigned long *)(-ylookup[i1]);

    ebp = vince[0]&0xfffffe00;
    ebx = vince[1];
    esi = vince[2]&0xfffffe00;
    eax = vince[3];

    eax = ((eax<<(256-mach3_al))|(((unsigned)eax)>>(32-(256-mach3_al))));
    ebx = ((ebx<<(256-mach3_al))|(((unsigned)ebx)>>(32-(256-mach3_al))));
    edx = (eax&0xffff0000) + (((unsigned)ebx)>>16);
    esi += (eax&0x1ff);
    ebp += (ebx&0x1ff);

    machvinc1 = (edx&0xffff0000);
    machvinc2 = esi;
    machvinc34= (edx&0xffff);
    machvinc5 = ebp;

    ebp = vplce[0]&0xfffffe00;
    ebx = vplce[1];
    esi = vplce[2]&0xfffffe00;
    eax = vplce[3];

    eax = ((eax<<(256-mach3_al))|(((unsigned)eax)>>(32-(256-mach3_al))));
    ebx = ((ebx<<(256-mach3_al))|(((unsigned)ebx)>>(32-(256-mach3_al))));
    edx = (eax&0xffff0000) + (((unsigned)ebx)>>16);
    esi += (eax&0x1ff);
    ebp += (ebx&0x1ff);

dumbbegin1:
    // XX______
    eax = esi >> mach3_al;
    eax = ((eax&0xffffff00)|((unsigned char*)machvbuf1)[eax]);
    out = ((out&0xffffff00)|((unsigned char*)machvpal1)[eax]);

    // __XX____
    ebx = esi & mach3_eax;
    ebx = ((ebx&0xffffff00)|((unsigned char*)machvbuf2)[ebx]);
    out = ((out&0xffff00ff)|((((unsigned char*)machvpal2)[ebx])<<8));

    if ((edx + machvinc1) < edx) esi++;
    edx += machvinc1;
    esi += machvinc2;

    out <<= 16;

    // ____XX__
    eax = ebp >> mach3_al;
    eax = ((eax&0xffffff00)|((unsigned char*)machvbuf3)[eax]);
    out = ((out&0xffffff00)|((unsigned char*)machvpal3)[eax]);

    // ______XX
    ebx = ebp & mach3_eax;
    ebx = ((ebx&0xffffff00)|((unsigned char*)machvbuf4)[ebx]);
    out = ((out&0xffff00ff)|((((unsigned char*)machvpal4)[ebx])<<8));

    edx += machvinc34;
    if (((edx&0xffff) - machvinc34) > (edx&0xffff)) ebp++;
    ebp += machvinc5;

    dest[index] = out;
    dest += (fixchain/4);
    if (((unsigned)dest - fixchain) < ((unsigned)dest)) goto dumbbegin1;

    vplce[2]=esi;
    vplce[0]=ebp;

    esi <<= mach3_al;
    esi += (edx >> (256-mach3_al));
    vplce[3] = esi;

    ebp <<= mach3_al;
    ebp += (edx&0xffff) << mach3_ah;
    vplce[1] = ebp;
} /* vlineasm4 */

/* #pragma aux setupmvlineasm parm [eax] */
void setupmvlineasm(long i1)
{
    machmv = i1;
} /* setupmvlineasm */

/* #pragma aux mvlineasm4 parm [ecx][edi] modify [eax ebx ecx edx esi edi] */
void mvlineasm4(long i1, long i2)
{
    long machmv1 = bufplce[0];
    long machmv4 = bufplce[1];
    long machmv7 = bufplce[2];
    long machmv10 = bufplce[3];
    long machmv2 = palookupoffse[0];
    long machmv5 = palookupoffse[1];
    long machmv8 = palookupoffse[2];
    long machmv11 = palookupoffse[3];
    long machmv3 = vince[0]&0xffffff00;
    long machmv6 = vince[1]&0xffffff00;
    long machmv9 = vince[2];
    long machmv12 = vince[3];
    unsigned long eax,ebx,ecx,edi,edx,esi,ebp;

    ebx = i1;
    edi = i2;
    ecx = vplce[0];
    edx = vplce[1];
    esi = vplce[2];
    ebp = vplce[3];
    ecx = ((ecx&0xffffff00)|(ebx&0xff));
    ecx = ((ecx&0xffffff00)|((ecx+1)&0xff));
    ebx = ((ebx&0xffff00ff)|((ebx+0x100)&0xff00));
    asm3 = ((ebx&0xff00)>>8);
    edi -= fixchain;

beginmvlineasm4:
    ecx = ((ecx&0xffffff00)|((ecx-1)&0xff));
    if ((ecx&0xff)==0) goto endmvlineasm4;
beginmvlineasm42:
    eax = ebp;
    ebx = esi;
    eax >>= machmv;
    ebx >>= machmv;
    ebp += machmv12;
    esi += machmv9;
    eax = ((eax&0xffffff00)|((unsigned char*)machmv10)[eax]);
    ebx = ((ebx&0xffffff00)|((unsigned char*)machmv7)[ebx]);

    edx = ((edx&0xffffff00)|((edx<<1)&0xff));
    if ((eax&0xff)<255) edx = ((edx&0xffffff00)|((edx+1)&0xff));

    edx = ((edx&0xffffff00)|((edx<<1)&0xff));
    if ((ebx&0xff)<255) edx = ((edx&0xffffff00)|((edx+1)&0xff));

    ebx = ((ebx&0xffffff00)|((unsigned char*)machmv8)[ebx]);
    ebx = ((ebx&0xffff00ff)|(((unsigned char*)machmv11)[eax])<<8);

    eax = edx;
    eax >>= machmv;
    ebx <<= 16;
    eax = ((eax&0xffffff00)|((unsigned char*)machmv4)[eax]);

    edx = ((edx&0xffffff00)|((edx<<1)&0xff));
    if ((eax&0xff)<255) edx = ((edx&0xffffff00)|((edx+1)&0xff));

    edx += machmv6;
    ebx = ((ebx&0xffff00ff)|(((unsigned char*)machmv5)[eax])<<8);

    eax = ecx;
    eax >>= machmv;
    ecx += machmv3;
    eax = ((eax&0xffffff00)|((unsigned char*)machmv1)[eax]);

    edx = ((edx&0xffffff00)|((edx<<1)&0xff));
    if ((eax&0xff)<255) edx = ((edx&0xffffff00)|((edx+1)&0xff));

    ebx = ((ebx&0xffffff00)|((unsigned char*)machmv2)[eax]);

    eax = 0;
    eax = ((eax&0xffffff00)|(edx&0xff));
    edx = ((edx&0xffffff00)|((edx<<4)&0xff));
    edi += fixchain;
    
    switch (eax)
    {
	    case 0:
		    break;
	    case 1:
		    *((unsigned char*)edi) = (ebx&0xff);
		    break;
	    case 2:
		    *(((unsigned char*)edi)+1) = ((ebx&0xff00)>>8);
		    break;
	    case 3:
		    *((unsigned short*)edi) = (ebx&0xffff);
		    break;
	    case 4:
		    ebx >>= 16;
		    *(((unsigned char*)edi)+2) = (ebx&0xff);
		    break;
	    case 5:
		    *((unsigned char*)edi) = (ebx&0xff);
		    ebx >>= 16;
		    *(((unsigned char*)edi)+2) = (ebx&0xff);
		    break;
	    case 6:
		    ebx >>= 8;
		    *((unsigned short*)(edi+1)) = (ebx&0xffff);
		    break;
	    case 7:
		    *((unsigned short*)edi) = (ebx&0xffff);
		    ebx >>= 16;
		    *(((unsigned char*)edi)+2) = (ebx&0xff);
		    break;
	    case 8:
		    ebx >>= 16;
		    *(((unsigned char*)edi)+3) = ((ebx&0xff00)>>8);
		    break;
	    case 9:
		    *((unsigned char*)edi) = (ebx&0xff);
		    ebx >>= 16;
		    *(((unsigned char*)edi)+3) = ((ebx&0xff00)>>8);
		    break;
	    case 10:
		    *(((unsigned char*)edi)+1) = ((ebx&0xff00)>>8);
		    ebx >>= 16;
		    *(((unsigned char*)edi)+3) = ((ebx&0xff00)>>8);
		    break;
	    case 11:
		    *((unsigned short*)edi) = (ebx&0xffff);
		    ebx >>= 16;
		    *(((unsigned char*)edi)+3) = ((ebx&0xff00)>>8);
		    break;
	    case 12:
		    ebx >>= 16;
		    *((unsigned short*)(edi+2)) = (ebx&0xffff);
		    break;
	    case 13:
		    *((unsigned char*)edi) = (ebx&0xff);
		    ebx >>= 16;
		    *((unsigned short*)(edi+2)) = (ebx&0xffff);
		    break;
	    case 14:
		    *(((unsigned char*)edi)+1) = ((ebx&0xff00)>>8);
		    ebx >>= 16;
		    *((unsigned short*)(edi+2)) = (ebx&0xffff);
		    break;
	    case 15:
		    *((unsigned int*)edi) = ebx;
		    break;
    }
    goto beginmvlineasm4;
endmvlineasm4:
    asm3--;
    if (asm3 != 0) goto beginmvlineasm42;

    vplce[0] = ecx;
    vplce[1] = edx;
    vplce[2] = esi;
    vplce[3] = ebp;
} /* mvlineasm4 */

/* #pragma aux setupspritevline parm [eax][ebx][ecx][edx][esi][edi] */
static long spal_eax;
static long smach_eax;
static long smach2_eax;
static long smach5_eax;
static long smach_ecx;
void setupspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    spal_eax = i1;
    smach_eax = (i5<<16);
    smach2_eax = (i5>>16)+i2;
    smach5_eax = smach2_eax + i4;
    smach_ecx = i3;
} /* setupspritevline */

/* #pragma aux spritevline parm [eax][ebx][ecx][edx][esi][edi] */
void spritevline(long i1, unsigned long i2, long i3, unsigned long i4, long i5, long i6)
{
    unsigned char *source = (unsigned char *)i5;
    unsigned char *dest = (unsigned char *)i6;

dumblabel1:
    i2 += smach_eax;
    i1 = (i1&0xffffff00) | (*source&0xff);
    if ((i2 - smach_eax) > i2) source += smach2_eax + 1;
    else source += smach2_eax;
dumblabel2:
    i1 = (i1&0xffffff00) | (((unsigned char *)spal_eax)[i1]&0xff);
    *dest = i1;
    dest += fixchain;

    i4 += smach_ecx;
    i4--;
    if (!((i4 - smach_ecx) > i4) && i4 != 0)
	    goto dumblabel1;
    if (i4 == 0) return;
    i2 += smach_eax;
    i1 = (i1&0xffffff00) | (*source&0xff);
    if ((i2 - smach_eax) > i2) source += smach5_eax + 1;
    else source += smach5_eax;
    goto dumblabel2;
} /* spritevline */

/* #pragma aux msetupspritevline parm [eax][ebx][ecx][edx][esi][edi] */
static long mspal_eax;
static long msmach_eax;
static long msmach2_eax;
static long msmach5_eax;
static long msmach_ecx;
void msetupspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    mspal_eax = i1;
    msmach_eax = (i5<<16);
    msmach2_eax = (i5>>16)+i2;
    msmach5_eax = smach2_eax + i4;
    msmach_ecx = i3;
} /* msetupspritevline */

/* #pragma aux mspritevline parm [eax][ebx][ecx][edx][esi][edi] */
void mspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    unsigned char *source = (unsigned char *)i5;
    unsigned char *dest = (unsigned char *)i6;

msdumblabel1:
    i2 += smach_eax;
    i1 = (i1&0xffffff00) | (*source&0xff);
    if ((i2 - smach_eax) > i2) source += smach2_eax + 1;
    else source += smach2_eax;
msdumblabel2:
    if ((i1&0xff) != 255)
    {
	    i1 = (i1&0xffffff00) | (((unsigned char *)spal_eax)[i1]&0xff);
	    *dest = i1;
    }
    dest += fixchain;

    i4 += smach_ecx;
    i4--;
    if (!((i4 - smach_ecx) > i4) && i4 != 0)
	    goto msdumblabel1;
    if (i4 == 0) return;
    i2 += smach_eax;
    i1 = (i1&0xffffff00) | (*source&0xff);
    if ((i2 - smach_eax) > i2) source += smach5_eax + 1;
    else source += smach5_eax;
    goto msdumblabel2;
} /* mspritevline */

/* #pragma aux tsetupspritevline parm [eax][ebx][ecx][edx][esi][edi] */
void tsetupspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
	/*
    __asm__ __volatile__ (
        "call _asm_tsetupspritevline   \n\t"
       :
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
	*/
/*
_asm_tsetupspritevline:
	mov dword [tspal+2], eax

	mov eax, esi                      ;xinc's
	shl eax, 16
	mov dword [tsmach1+2], eax
	mov dword [tsmach4+2], eax
	mov eax, esi
	sar eax, 16
	add eax, ebx                      ;watch out with ebx - it's passed
	mov dword [tsmach2+2], eax
	add eax, edx
	mov dword [tsmach5+2], eax

	mov dword [tsmach3+2], ecx  ;yinc's
	ret
*/
} /* tsetupspritevline */

/* #pragma aux tspritevline parm [eax][ebx][ecx][edx][esi][edi] */
void tspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
	/*
    __asm__ __volatile__ (
        "call _asm_tspritevline   \n\t"
       :
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
	*/
/*
_asm_tspritevline:
	;eax = 0, ebx = x, ecx = cnt, edx = y, esi = yplc, edi = p
	push ebp
	mov ebp, ebx
	xor ebx, ebx
	jmp tenterspritevline
ALIGN 16
tprestartsvline:
tsmach1: add ebp, 88888888h              ;xincshl16
	mov al, byte [esi]
tsmach2: adc esi, 88888888h              ;xincshr16+yalwaysinc

tstartsvline:
	cmp al, 255
	je short tskipsvline
transrev2:
	mov bh, byte [edi]
transrev3:
tspal: mov bl, [eax+88888888h]               ;palookup
tmach4: mov al, byte [ebx+88888888h]     ;transluc
	mov byte [edi], al
tskipsvline:
tfixchain1s: add edi, 320

tenterspritevline:
tsmach3: add edx, 88888888h              ;dayinc
	dec ecx
	ja short tprestartsvline     ;jump if (no carry (add)) and (not zero (dec))!
	jz short tendsvline
tsmach4: add ebp, 88888888h              ;xincshl16
	mov al, byte [esi]
tsmach5: adc esi, 88888888h              ;xincshr16+yalwaysinc+daydime
	jmp short tstartsvline
tendsvline:
	pop ebp
	ret
*/
} /* tspritevline */

/* #pragma aux mhline parm [eax][ebx][ecx][edx][esi][edi] */
long mhline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval = 0;
    /*
    __asm__ __volatile__ (
        "call _asm_mhline   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
	*/
    return(retval);
/*
_asm_mhline:
	;asm1 = bxinc
	;asm2 = byinc
	;asm3 = shadeoffs
	;eax = picoffs
	;ebx = bx
	;ecx = cnt
	;edx = ?
	;esi = by
	;edi = p

	mov dword [mmach1d+2], eax
	mov dword [mmach5d+2], eax
	mov dword [mmach9d+2], eax
	mov eax, [asm3]
	mov dword [mmach2d+2], eax
	mov dword [mmach2da+2], eax
	mov dword [mmach2db+2], eax
	mov dword [mmach6d+2], eax
	mov dword [mmach10d+2], eax
	mov eax, [asm1]
	mov dword [mmach3d+2], eax
	mov dword [mmach7d+2], eax
	mov eax, [asm2]
	mov dword [mmach4d+2], eax
	mov dword [mmach8d+2], eax
	jmp short _asm_mhlineskipmodify
*/
} /* mhline */

/* #pragma aux mhlineskipmodify parm [eax][ebx][ecx][edx][esi][edi] */
long mhlineskipmodify(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval = 0;
    /*
    __asm__ __volatile__ (
        "call _asm_mhlineskipmodify   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
	*/
    return(retval);
/*
_asm_mhlineskipmodify:

	push ebp

	xor eax, eax
	mov ebp, ebx

	test ecx, 00010000h
	jnz short mbeghline

msh1d: shr ebx, 26
msh2d: shld ebx, esi, 6
	add ebp, [asm1]
mmach9d: mov al, byte [ebx+88888888h]    ;picoffs
	add esi, [asm2]
	cmp al, 255
	je mskip5

	mmach10d: mov cl, byte [eax+88888888h]    ;shadeoffs
	mov byte [edi], cl
mskip5:
	inc edi
	sub ecx, 65536
	jc NEAR mendhline
	jmp short mbeghline

ALIGN 16
mpreprebeghline:                                            ;1st only
	mov al, cl
mmach2d: mov al, byte [eax+88888888h]    ;shadeoffs
	mov byte [edi], al

mprebeghline:
	add edi, 2
	sub ecx, 131072
	jc NEAR mendhline
mbeghline:
mmach3d: lea ebx, [ebp+88888888h]            ;bxinc
msh3d: shr ebp, 26
msh4d: shld ebp, esi, 6
mmach4d: add esi, 88888888h                  ;byinc
mmach1d: mov cl, byte [ebp+88888888h]    ;picoffs
mmach7d: lea ebp, [ebx+88888888h]            ;bxinc

msh5d: shr ebx, 26
msh6d: shld ebx, esi, 6
mmach8d: add esi, 88888888h                  ;byinc
mmach5d: mov ch, byte [ebx+88888888h]    ;picoffs

	cmp cl, 255
	je short mskip1
	cmp ch, 255
	je short mpreprebeghline

	mov al, cl                                                  ;BOTH
mmach2da: mov bl, byte [eax+88888888h]    ;shadeoffs
	mov al, ch
mmach2db: mov bh, byte [eax+88888888h]    ;shadeoffs
	mov word [edi], bx
	add edi, 2
	sub ecx, 131072
	jnc short mbeghline
	jmp mendhline
mskip1:                                                     ;2nd only
	cmp ch, 255
	je short mprebeghline

	mov al, ch
mmach6d: mov al, byte [eax+88888888h]    ;shadeoffs
	mov byte [edi+1], al
	add edi, 2
	sub ecx, 131072
	jnc short mbeghline
mendhline:

	pop ebp
	ret
*/
} /* mhlineskipmodify */

/* #pragma aux msethlineshift parm [eax][ebx] */
long msethlineshift(long i1, long i2)
{
    long retval = 0;
    /*
    __asm__ __volatile__ (
        "call _asm_msethlineshift   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2)
        : "cc", "memory");
	*/
    return(retval);
/*
_asm_msethlineshift:
	neg al
	mov byte [msh1d+2], al
	mov byte [msh2d+3], bl
	mov byte [msh3d+2], al
	mov byte [msh4d+3], bl
	mov byte [msh5d+2], al
	mov byte [msh6d+3], bl
	ret
*/
} /* msethlineshift */

/* #pragma aux thline parm [eax][ebx][ecx][edx][esi][edi] */
long thline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval = 0;
    /*
    __asm__ __volatile__ (
        "call _asm_thline   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
	*/
    return(retval);
/*
_asm_thline:
	;asm1 = bxinc
	;asm2 = byinc
	;asm3 = shadeoffs
	;eax = picoffs
	;ebx = bx
	;ecx = cnt
	;edx = ?
	;esi = by
	;edi = p

	mov dword [tmach1d+2], eax
	mov dword [tmach5d+2], eax
	mov dword [tmach9d+2], eax
	mov eax, [asm3]
	mov dword [tmach2d+2], eax
	mov dword [tmach6d+2], eax
	mov dword [tmach10d+2], eax
	mov eax, [asm1]
	mov dword [tmach3d+2], eax
	mov dword [tmach7d+2], eax
	mov eax, [asm2]
	mov dword [tmach4d+2], eax
	mov dword [tmach8d+2], eax
	jmp _asm_thlineskipmodify
*/
} /* thline */

/* #pragma aux thlineskipmodify parm [eax][ebx][ecx][edx][esi][edi] */
long thlineskipmodify(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval = 0;
    /*
    __asm__ __volatile__ (
        "call _asm_thlineskipmodify   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
	*/
    return(retval);
/*
_asm_thlineskipmodify:

	push ebp

	xor eax, eax
	xor edx, edx
	mov ebp, ebx

	test ecx, 00010000h
	jnz short tbeghline

tsh1d: shr ebx, 26
tsh2d: shld ebx, esi, 6
	add ebp, [asm1]
tmach9d: mov al, byte [ebx+88888888h]    ;picoffs
	add esi, [asm2]
	cmp al, 255
	je tskip5

transrev4:
tmach10d: mov dl, byte [eax+88888888h]   ;shadeoffs
transrev5:
	mov dh, byte [edi]
tmach1: mov al, byte [edx+88888888h]     ;transluc
	mov byte [edi], al
tskip5:
	inc edi
	sub ecx, 65536
	jc NEAR tendhline
	jmp short tbeghline

ALIGN 16
tprebeghline:
	add edi, 2
	sub ecx, 131072
	jc short tendhline
tbeghline:
tmach3d: lea ebx, [ebp+88888888h]            ;bxinc
tsh3d: shr ebp, 26
tsh4d: shld ebp, esi, 6
tmach4d: add esi, 88888888h                  ;byinc
tmach1d: mov cl, byte [ebp+88888888h]    ;picoffs
tmach7d: lea ebp, [ebx+88888888h]            ;bxinc

tsh5d: shr ebx, 26
tsh6d: shld ebx, esi, 6
tmach8d: add esi, 88888888h                  ;byinc
tmach5d: mov ch, byte [ebx+88888888h]    ;picoffs

	cmp cx, 0ffffh
	je short tprebeghline

	mov bx, word [edi]

	cmp cl, 255
	je short tskip1
	mov al, cl
transrev6:
tmach2d: mov dl, byte [eax+88888888h]    ;shadeoffs
transrev7:
	mov dh, bl
tmach2: mov al, byte [edx+88888888h]     ;transluc
	mov byte [edi], al

	cmp ch, 255
	je short tskip2
tskip1:
	mov al, ch
transrev8:
tmach6d: mov dl, byte [eax+88888888h]    ;shadeoffs
transrev9:
	mov dh, bh
tmach3: mov al, byte [edx+88888888h]     ;transluc
	mov byte [edi+1], al
tskip2:

	add edi, 2
	sub ecx, 131072
	jnc tbeghline
tendhline:

	pop ebp
	ret
*/
} /* thlineskipmodify */

/* #pragma aux tsethlineshift parm [eax][ebx] */
long tsethlineshift(long i1, long i2)
{
    long retval = 0;
    /*
    __asm__ __volatile__ (
        "call _asm_tsethlineshift   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2)
        : "cc", "memory");
	*/
    return(retval);
/*
_asm_tsethlineshift:
	neg al
	mov byte [tsh1d+2], al
	mov byte [tsh2d+3], bl
	mov byte [tsh3d+2], al
	mov byte [tsh4d+3], bl
	mov byte [tsh5d+2], al
	mov byte [tsh6d+3], bl
	ret
*/
} /* tsethlineshift */

/* #pragma aux setupslopevlin parm [eax][ebx][ecx] modify [edx] */
static long slopemach_ebx;
static long slopemach_ecx;
static long slopemach_edx;
static unsigned char slopemach_ah1;
static unsigned char slopemach_ah2;
static float asm2_f;
typedef union { unsigned int i; float f; } bitwisef2i;
void setupslopevlin(long i1, long i2, long i3)
{
    bitwisef2i c;
    slopemach_ebx = i2;
    slopemach_ecx = i3;
    slopemach_edx = (1<<(i1&0xff)) - 1;
    slopemach_edx <<= ((i1&0xff00)>>8);
    slopemach_ah1 = 256-((i1&0xff00)>>8);
    slopemach_ah2 = slopemach_ah1 - (i1&0xff);
    c.f = asm2_f = (float)asm1;
    asm2 = c.i;

    /*
    __asm__ __volatile__ (
        "call _asm_setupslopevlin   \n\t"
        : : "a" (i1), "b" (i2), "c" (i3)
        : "cc", "edx", "memory");
	*/
/*
_asm_setupslopevlin:
	mov dword [slopmach3+3], ebx    ;ptr
	mov dword [slopmach5+2], ecx    ;pinc
	neg ecx
	mov dword [slopmach6+2], ecx    ;-pinc

	mov edx, 1
	mov cl, al
	shl edx, cl
	dec edx
	mov cl, ah
	shl edx, cl
	mov dword [slopmach7+2], edx

	neg ah
	mov byte [slopmach2+2], ah

	sub ah, al
	mov byte [slopmach1+2], ah

	fild dword [asm1]
	fstp dword [asm2]
	ret
*/
} /* setupslopevlin */

extern long reciptable[2048];
extern long globalx3, globaly3;
extern long fpuasm;
#define low32(a) ((a&0xffffffff))
#define high32(a) ((int)(((__int64)a&(__int64)0xffffffff00000000)>>32))

/* #pragma aux slopevlin parm [eax][ebx][ecx][edx][esi][edi] */
void slopevlin(long i1, unsigned long i2, long i3, long i4, long i5, long i6)
{
	/*
    __asm__ __volatile__ (
        "call _asm_slopevlin   \n\t"
        : : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
    return;
    */
    {
    bitwisef2i c;
    unsigned long ebp,ecx,eax,ebx,edx,esi,edi,esp;
    float a = (float) asm3 + asm2_f;
    esp = i3;
    ebp = i1 - slopemach_ecx;
    asm1 = i2;
    eax = low32((__int64)globalx3 * (__int64)(i2<<3));	// imull!
    ecx = low32((__int64)globaly3 * (__int64)(i2<<3));	// imull!
    esi = i5 + eax;
    edi = i6 + ecx;
    ebx = i4;
    do {
	    c.f = a;
	    fpuasm = eax = c.i;
	    edx = 0;
	    if ((eax - eax) > eax) edx--;	// edx = sign bit
	    eax += eax;
	    ecx = (eax>>24);	//  exponent
	    eax = ((eax&0xffe000)>>11);
	    ecx = ((ecx&0xffffff00)|((ecx-2)&0xff));
	    eax = reciptable[eax/4];
	    eax >>= (ecx&0xff);
	    eax ^= edx;
	    edx = asm1;
	    ecx = globalx3;
	    asm1 = eax;
	    eax -= edx;
	    edx = globaly3;
	    ecx = low32((__int64)ecx * (__int64)eax);	// warning! imull
	    eax = low32((__int64)eax * (__int64)edx);	// warning! imull
	    a += asm2_f;

	    asm4 = ebx;
	    ecx = ((ecx&0xffffff00)|(ebx&0xff));
	    if (ebx >= 8) ecx = ((ecx&0xffffff00)|8);

	    ebx = esi;
	    edx = edi;
	    while ((ecx&0xff))
	    {
		    ebx >>= slopemach_ah2;
		    esi += ecx;
		    edx >>= slopemach_ah1;
		    ebx &= slopemach_edx;
		    edi += eax;
		    ebp += slopemach_ecx;
		    edx = ((edx&0xffffff00)|((((unsigned char *)(ebx+edx))[slopemach_ebx])));
		    ebx = *((unsigned long*)esp); // register trickery
		    esp -= 4;
		    eax = ((eax&0xffffff00)|(*((unsigned char *)(ebx+edx))));
		    ebx = esi;
		    *((unsigned char *)ebp) = (eax&0xff);
		    edx = edi;
		    ecx = ((ecx&0xffffff00)|((ecx-1)&0xff));
	    }
	    ebx = asm4;
	    ebx -= 8;	// BITSOFPRECISIONPOW
    // jg = jump if overflow or 0
    } while ((long)ebx > 0);
    //if (((ebx + 8) < ebx) || (ebx == 0)) goto bigslopeloop;
    }

/*
_asm_slopevlin:
	mov [ebpbak], ebp		; Added [] AH
	mov [espbak], esp         	; Added [] AH

	sub ecx, esp
	mov dword [slopmach4+3], ecx

	fild dword [asm3]
slopmach6: lea ebp, [eax+88888888h]
	fadd dword [asm2]

	mov [asm1], ebx			; Added [] AH
	shl ebx, 3

	mov eax, [globalx3]
	mov ecx, [globaly3]
	imul eax, ebx
	imul ecx, ebx
	add esi, eax
	add edi, ecx

	mov ebx, edx
	jmp short bigslopeloop
ALIGN 16
bigslopeloop:
	fst dword [fpuasm]

	mov eax, [fpuasm]
	add eax, eax
	sbb edx, edx
	mov ecx, eax
	shr ecx, 24
	and eax, 00ffe000h
	shr eax, 11
	sub cl, 2
	mov eax, dword [reciptable + eax]
	shr eax, cl
	xor eax, edx
	mov edx, [asm1]
	mov ecx, [globalx3]
	mov [asm1], eax			; Added [] AH
	sub eax, edx
	mov edx, [globaly3]
	imul ecx, eax
	imul eax, edx

	fadd dword [asm2]

	cmp ebx, BITSOFPRECISIONPOW
	mov [asm4], ebx			; Added [] AH
	mov cl, bl
	jl short slopeskipmin
	mov cl, BITSOFPRECISIONPOW
slopeskipmin:

;eax: yinc.............
;ebx:   0   0   0   ?
;ecx: xinc......... cnt
;edx:         ?
;esi: xplc.............
;edi: yplc.............
;ebp:     videopos

	mov ebx, esi
	mov edx, edi

beginnerslopeloop:
slopmach1: shr ebx, 20
	add esi, ecx
slopmach2: shr edx, 26
slopmach7: and ebx, 88888888h
	add edi, eax
slopmach5: add ebp, 88888888h                   ;pinc
slopmach3: mov dl, byte [ebx+edx+88888888h] ;ptr
slopmach4: mov ebx, dword [esp+88888888h]
slopmach41: 	sub esp, 4
slopmach42: 	dec cl
slopmach43: 	mov al, byte [ebx+edx] ;tptr
slopmach44: 	mov ebx, esi
slopmach45: 	mov [ebp], al
slopmach46: 	mov edx, edi
slopmach47: 	jnz short beginnerslopeloop

slopmach48: 	mov ebx, [asm4]
slopmach49: 	sub ebx, BITSOFPRECISIONPOW
slopmach4a: 	jg NEAR bigslopeloop

slopmach4b: 	ffree st0

slopmach4c: 	mov esp, [espbak]
slopmach4d: 	mov ebp, [ebpbak]
	ret
*/
} /* slopevlin */

/* #pragma aux settransnormal parm */
long settransnormal(void)
{
    long retval = 0;
    /*
    __asm__ __volatile__ (
        "call _asm_settransnormal   \n\t"
       : "=a" (retval)
        :
        : "cc", "memory");
	*/
    return(retval);
/*
_asm_settransnormal:
	mov byte [transrev0+1], 83h
	mov byte [transrev1+1], 27h
	mov byte [transrev2+1], 3fh
	mov byte [transrev3+1], 98h
	mov byte [transrev4+1], 90h
	mov byte [transrev5+1], 37h
	mov byte [transrev6+1], 90h
	mov word [transrev7+0], 0f38ah
	mov byte [transrev8+1], 90h
	mov word [transrev9+0], 0f78ah
	mov byte [transrev10+1], 0a7h
	mov byte [transrev11+1], 81h
	mov byte [transrev12+2], 9fh
	mov word [transrev13+0], 0dc88h
	mov byte [transrev14+1], 81h
	mov byte [transrev15+1], 9ah
	mov byte [transrev16+1], 0a7h
	mov byte [transrev17+1], 82h
    ret
*/
} /* settransnormal */

/* #pragma aux settransreverse parm */
long settransreverse(void)
{
    long retval = 0;
    /*
    __asm__ __volatile__ (
        "call _asm_settransreverse   \n\t"
       : "=a" (retval)
        :
        : "cc", "memory");
	*/
    return(retval);
/*
_asm_settransreverse:
	mov byte [transrev0+1], 0a3h
	mov byte [transrev1+1], 7h
	mov byte [transrev2+1], 1fh
	mov byte [transrev3+1], 0b8h
	mov byte [transrev4+1], 0b0h
	mov byte [transrev5+1], 17h
	mov byte [transrev6+1], 0b0h
	mov word [transrev7+0], 0d38ah
	mov byte [transrev8+1], 0b0h
	mov word [transrev9+0], 0d78ah
	mov byte [transrev10+1], 87h
	mov byte [transrev11+1], 0a1h
	mov byte [transrev12+2], 87h
	mov word [transrev13+0], 0e388h
	mov byte [transrev14+1], 0a1h
	mov byte [transrev15+1], 0bah
	mov byte [transrev16+1], 87h
	mov byte [transrev17+1], 0a2h
    ret
*/
} /* settransreverse */

/* #pragma aux setupdrawslab parm [eax][ebx] */
long setupdrawslab(long i1, long i2)
{
    long retval = 0;
    /*
    __asm__ __volatile__ (
        "call _asm_setupdrawslab   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2)
        : "cc", "memory");
	*/
    return(retval);
/*
_asm_setupdrawslab:
	mov dword [voxbpl1+2], eax
	mov dword [voxbpl2+2], eax
	mov dword [voxbpl3+2], eax
	mov dword [voxbpl4+2], eax
	mov dword [voxbpl5+2], eax
	mov dword [voxbpl6+2], eax
	mov dword [voxbpl7+2], eax
	mov dword [voxbpl8+2], eax

	mov dword [voxpal1+2], ebx
	mov dword [voxpal2+2], ebx
	mov dword [voxpal3+2], ebx
	mov dword [voxpal4+2], ebx
	mov dword [voxpal5+2], ebx
	mov dword [voxpal6+2], ebx
	mov dword [voxpal7+2], ebx
	mov dword [voxpal8+2], ebx
	ret
*/
} /* setupdrawslab */

/* #pragma aux drawslab parm [eax][ebx][ecx][edx][esi][edi] */
long drawslab(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval = 0;
    /*
    __asm__ __volatile__ (
        "call _asm_drawslab   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
	*/
    return(retval);
/*
_asm_drawslab:
	push ebp
	cmp eax, 2
	je voxbegdraw2
	ja voxskip2
	xor eax, eax
voxbegdraw1:
	mov ebp, ebx
	shr ebp, 16
	add ebx, edx
	dec ecx
	mov al, byte [esi+ebp]
voxpal1: mov al, byte [eax+88888888h]
	mov byte [edi], al
voxbpl1: lea edi, [edi+88888888h]
	jnz voxbegdraw1
	pop ebp
	ret

voxbegdraw2:
	mov ebp, ebx
	shr ebp, 16
	add ebx, edx
	xor eax, eax
	dec ecx
	mov al, byte [esi+ebp]
voxpal2: mov al, byte [eax+88888888h]
	mov ah, al
	mov word [edi], ax
voxbpl2: lea edi, [edi+88888888h]
	jnz voxbegdraw2
	pop ebp
	ret

voxskip2:
	cmp eax, 4
	jne voxskip4
	xor eax, eax
voxbegdraw4:
	mov ebp, ebx
	add ebx, edx
	shr ebp, 16
	xor eax, eax
	mov al, byte [esi+ebp]
voxpal3: mov al, byte [eax+88888888h]
	mov ah, al
	shl eax, 8
	mov al, ah
	shl eax, 8
	mov al, ah
	mov dword [edi], eax
voxbpl3: add edi, 88888888h
	dec ecx
	jnz voxbegdraw4
	pop ebp
	ret

voxskip4:
	add eax, edi

	test edi, 1
	jz voxskipslab1
	cmp edi, eax
	je voxskipslab1

	push eax
	push ebx
	push ecx
	push edi
voxbegslab1:
	mov ebp, ebx
	add ebx, edx
	shr ebp, 16
	xor eax, eax
	mov al, byte [esi+ebp]
voxpal4: mov al, byte [eax+88888888h]
	mov byte [edi], al
voxbpl4: add edi, 88888888h
	dec ecx
	jnz voxbegslab1
	pop edi
	pop ecx
	pop ebx
	pop eax
	inc edi

voxskipslab1:
	push eax
	test edi, 2
	jz voxskipslab2
	dec eax
	cmp edi, eax
	jge voxskipslab2

	push ebx
	push ecx
	push edi
voxbegslab2:
	mov ebp, ebx
	add ebx, edx
	shr ebp, 16
	xor eax, eax
	mov al, byte [esi+ebp]
voxpal5: mov al, byte [eax+88888888h]
	mov ah, al
	mov word [edi], ax
voxbpl5: add edi, 88888888h
	dec ecx
	jnz voxbegslab2
	pop edi
	pop ecx
	pop ebx
	add edi, 2

voxskipslab2:
	mov eax, [esp]

	sub eax, 3
	cmp edi, eax
	jge voxskipslab3

voxprebegslab3:
	push ebx
	push ecx
	push edi
voxbegslab3:
	mov ebp, ebx
	add ebx, edx
	shr ebp, 16
	xor eax, eax
	mov al, byte [esi+ebp]
voxpal6: mov al, byte [eax+88888888h]
	mov ah, al
	shl eax, 8
	mov al, ah
	shl eax, 8
	mov al, ah
	mov dword [edi], eax
voxbpl6: add edi, 88888888h
	dec ecx
	jnz voxbegslab3
	pop edi
	pop ecx
	pop ebx
	add edi, 4

	mov eax, [esp]

	sub eax, 3
	cmp edi, eax
	jl voxprebegslab3

voxskipslab3:
	mov eax, [esp]

	dec eax
	cmp edi, eax
	jge voxskipslab4

	push ebx
	push ecx
	push edi
voxbegslab4:
	mov ebp, ebx
	add ebx, edx
	shr ebp, 16
	xor eax, eax
	mov al, byte [esi+ebp]
voxpal7: mov al, byte [eax+88888888h]
	mov ah, al
	mov word [edi], ax
voxbpl7: add edi, 88888888h
	dec ecx
	jnz voxbegslab4
	pop edi
	pop ecx
	pop ebx
	add edi, 2

voxskipslab4:
	pop eax

	cmp edi, eax
	je voxskipslab5

voxbegslab5:
	mov ebp, ebx
	add ebx, edx
	shr ebp, 16
	xor eax, eax
	mov al, byte [esi+ebp]
voxpal8: mov al, byte [eax+88888888h]
	mov byte [edi], al
voxbpl8: add edi, 88888888h
	dec ecx
	jnz voxbegslab5

voxskipslab5:
	pop ebp
	ret
*/
} /* drawslab */

/* #pragma aux stretchhline parm [eax][ebx][ecx][edx][esi][edi] */
long stretchhline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    long retval = 0;
    /*
    __asm__ __volatile__ (
        "call _asm_stretchhline   \n\t"
       : "=a" (retval)
        : "a" (i1), "b" (i2), "c" (i3), "d" (i4), "S" (i5), "D" (i6)
        : "cc", "memory");
	*/
    return(retval);
/*
_asm_stretchhline:
	push ebp

	mov eax, ebx
	shl ebx, 16
	sar eax, 16
	and ecx, 0000ffffh
	or ecx, ebx

	add esi, eax
	mov eax, edx
	mov edx, esi

	mov ebp, eax
	shl eax, 16
	sar ebp, 16

	add ecx, eax
	adc esi, ebp

	add eax, eax
	adc ebp, ebp
	mov dword [loinc1+2], eax
	mov dword [loinc2+2], eax
	mov dword [loinc3+2], eax
	mov dword [loinc4+2], eax

	inc ch

	jmp begloop

begloop:
	mov al, [edx]
loinc1: sub ebx, 88888888h
	sbb edx, ebp
	mov ah, [esi]
loinc2: sub ecx, 88888888h
	sbb esi, ebp
	sub edi, 4
	shl eax, 16
loinc3: sub ebx, 88888888h
	mov al, [edx]
	sbb edx, ebp
	mov ah, [esi]
loinc4: sub ecx, 88888888h
	sbb esi, ebp
	mov [edi], eax
	dec cl
	jnz begloop
	dec ch
	jnz begloop

	pop ebp
	ret
*/
} /* stretchhline */
