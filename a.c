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
void setupqrhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    setuprhlineasm4(i1,i2,i3,i4,i5,i6);
} /* setupqrhlineasm4 */


/* #pragma aux qrhlineasm4 parm [eax][ebx][ecx][edx][esi][edi] */
void qrhlineasm4(long i1, long i2, long i3, long i4, long i5, long i6)
{
    rhlineasm4(i1,i2,i3,i4,i5,i6);
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
    while (i3)
    {
	    unsigned long temp = i4;
	    temp >>= mach3_al;
	    temp = (temp&0xffffff00) | (source[temp]&0xff);
	    *dest = ((unsigned char*)i2)[temp];
	    i4 += i1;
	    dest += fixchain;
	    i3--;
    }
    return i4;
} /* vlineasm1 */


/* #pragma aux setuptvlineasm parm [eax] */
static unsigned char transmach3_al = 32;
void setuptvlineasm(long i1)
{
    transmach3_al = i1;
} /* setuptvlineasm */

/* #pragma aux tvlineasm1 parm [eax][ebx][ecx][edx][esi][edi] */
static int transrev = 0;
long tvlineasm1(long i1, long i2, long i3, long i4, long i5, long i6)
{
	unsigned char *source = (unsigned char *)i5;
	unsigned char *dest = (unsigned char *)i6;

	i3++;
	while (i3)
	{
		unsigned long temp = i4;
		temp >>= transmach3_al;
		temp = source[temp];
		if (temp != 255)
		{
			unsigned short val;
			val = ((unsigned char *)i2)[temp];
			val |= ((*dest)<<8);
			if (transrev) val = ((val>>8)|(val<<8));
			*dest = ((unsigned char *)tmach)[val];
		}
		i4 += i1;
		dest += fixchain;
		i3--;
	}
	return i4;
} /* tvlineasm1 */

/* #pragma aux setuptvlineasm2 parm [eax][ebx][ecx] */
static unsigned char tran2shr;
static unsigned long tran2pal_ebx;
static unsigned long tran2pal_ecx;
void setuptvlineasm2(long i1, long i2, long i3)
{
	tran2shr = (i1&0xff);
	tran2pal_ebx = i2;
	tran2pal_ecx = i3;
} /* */

/* #pragma aux tvlineasm2 parm [eax][ebx][ecx][edx][esi][edi] */
void tvlineasm2(unsigned long i1, unsigned long i2, unsigned long i3, unsigned long i4, unsigned long i5, unsigned long i6)
{
	unsigned long ebp = i1;
	unsigned long tran2inca = i2;
	unsigned long tran2incb = asm1;
	unsigned long tran2bufa = i3;
	unsigned long tran2bufb = i4;
	unsigned long tran2edi = asm2;
	unsigned long tran2edi1 = asm2 + 1;

	i6 -= asm2;

	do {
		i1 = i5 >> tran2shr;
		i2 = ebp >> tran2shr;
		i5 += tran2inca;
		ebp += tran2incb;
		i3 = ((unsigned char *)tran2bufa)[i1];
		i4 = ((unsigned char *)tran2bufb)[i2];
		if (i3 == 255) { // skipdraw1
			if (i4 != 255) { // skipdraw3
				unsigned short val;
				val = ((unsigned char *)tran2pal_ecx)[i4];
				val |= (((unsigned char *)i6)[tran2edi1]<<8);
				if (transrev) val = ((val>>8)|(val<<8));
				((unsigned char *)i6)[tran2edi1] =
					((unsigned char *)tmach)[val];
			}
		} else if (i4 == 255) { // skipdraw2
			unsigned short val;
			val = ((unsigned char *)tran2pal_ebx)[i3];
			val |= (((unsigned char *)i6)[tran2edi]<<8);
			if (transrev) val = ((val>>8)|(val<<8));
			((unsigned char *)i6)[tran2edi] =
				((unsigned char *)tmach)[val];
		} else {
			unsigned short l = ((unsigned char *)i6)[tran2edi]<<8;
			unsigned short r = ((unsigned char *)i6)[tran2edi1]<<8;
			l |= ((unsigned char *)tran2pal_ebx)[i3];
			r |= ((unsigned char *)tran2pal_ecx)[i4];
			if (transrev) {
				l = ((l>>8)|(l<<8));
				r = ((r>>8)|(r<<8));
			}
			((unsigned char *)i6)[tran2edi] =
				((unsigned char *)tmach)[l];
			((unsigned char *)i6)[tran2edi1] =
				((unsigned char *)tmach)[r];
		}
		i6 += fixchain;
	} while (i6 > i6 - fixchain);
	asm1 = i5;
	asm2 = ebp;
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
    unsigned long machvbuf1 = bufplce[2];
    unsigned long machvbuf2 = bufplce[3];
    unsigned long machvbuf3 = bufplce[0];
    unsigned long machvbuf4 = bufplce[1];
    unsigned long machvpal1 = palookupoffse[2];
    unsigned long machvpal2 = palookupoffse[3];
    unsigned long machvpal3 = palookupoffse[0];
    unsigned long machvpal4 = palookupoffse[1];
    unsigned long machvinc1, machvinc2, machvinc5;
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
unsigned long tspal;
unsigned long tsmach_eax1;
unsigned long tsmach_eax2;
unsigned long tsmach_eax3;
unsigned long tsmach_ecx;
void tsetupspritevline(long i1, long i2, long i3, long i4, long i5, long i6)
{
	tspal = i1;
	tsmach_eax1 = i5 << 16;
	tsmach_eax2 = (i5 >> 16) + i2;
	tsmach_eax3 = tsmach_eax2 + i4;
	tsmach_ecx = i3;
} /* tsetupspritevline */

/* #pragma aux tspritevline parm [eax][ebx][ecx][edx][esi][edi] */
void tspritevline(long i1, long i2, long i3, unsigned long i4, long i5, long i6)
{
	while (i3)
	{
		i3--;
		if (i3 != 0)
		{
			unsigned long adder = tsmach_eax2;
			i4 += tsmach_ecx;
			if (i4 < (i4 - tsmach_ecx)) adder = tsmach_eax3;
			i1 = *((unsigned char *)i5);
			i2 += tsmach_eax1;
			if (i2 < (i2 - tsmach_eax1)) i5++;
			i5 += adder;
			// tstartsvline
			if (i1 != 0xff)
			{
				unsigned short val;
				val = ((unsigned char*)tspal)[i1];
				val |= ((*((unsigned char *)i6))<<8);
				if (transrev) val = ((val>>8)|(val<<8));
				i1 = ((unsigned char *)tmach)[val];
				*((unsigned char *)i6) = (i1&0xff);
			}
			i6 += fixchain;
		}
	}
} /* tspritevline */

/* #pragma aux mhline parm [eax][ebx][ecx][edx][esi][edi] */
static long mmach_eax;
static long mmach_asm3;
static long mmach_asm1;
static long mmach_asm2;
void mhlineskipmodify(long i1, unsigned long i2, unsigned long i3, long i4, long i5, long i6);
void mhline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    mmach_eax = i1;
    mmach_asm3 = asm3;
    mmach_asm1 = asm1;
    mmach_asm2 = asm2;
    mhlineskipmodify(asm2,i2,i3,i4,i5,i6);
} /* mhline */

/* #pragma aux mhlineskipmodify parm [eax][ebx][ecx][edx][esi][edi] */
static unsigned char mshift_al = 26;
static unsigned char mshift_bl = 6;
void mhlineskipmodify(long i1, unsigned long i2, unsigned long i3, long i4, long i5, long i6)
{
    unsigned long ebx;
    int counter = (i3>>16);
    while (counter >= 0)
    {
	    ebx = i2 >> mshift_al;
	    ebx = shld (ebx, (unsigned)i5, mshift_bl);
	    i1 = ((unsigned char *)mmach_eax)[ebx];
	    if ((i1&0xff) != 0xff)
		    *((unsigned char *)i6) = (((unsigned char*)mmach_asm3)[i1]);

	    i2 += mmach_asm1;
	    i5 += mmach_asm2;
	    i6++;
	    counter--;
    }
} /* mhlineskipmodify */

/* #pragma aux msethlineshift parm [eax][ebx] */
void msethlineshift(long i1, long i2)
{
    i1 = 256-i1;
    mshift_al = (i1&0xff);
    mshift_bl = (i2&0xff);
} /* msethlineshift */

/* #pragma aux thline parm [eax][ebx][ecx][edx][esi][edi] */
static long tmach_eax;
static long tmach_asm3;
static long tmach_asm1;
static long tmach_asm2;
void thlineskipmodify(long i1, unsigned long i2, unsigned long i3, long i4, long i5, long i6);
void thline(long i1, long i2, long i3, long i4, long i5, long i6)
{
    tmach_eax = i1;
    tmach_asm3 = asm3;
    tmach_asm1 = asm1;
    tmach_asm2 = asm2;
    thlineskipmodify(asm2,i2,i3,i4,i5,i6);
} /* thline */

/* #pragma aux thlineskipmodify parm [eax][ebx][ecx][edx][esi][edi] */
static unsigned char tshift_al = 26;
static unsigned char tshift_bl = 6;
void thlineskipmodify(long i1, unsigned long i2, unsigned long i3, long i4, long i5, long i6)
{
    unsigned long ebx;
    int counter = (i3>>16);
    while (counter >= 0)
    {
	    ebx = i2 >> tshift_al;
	    ebx = shld (ebx, (unsigned)i5, tshift_bl);
	    i1 = ((unsigned char *)tmach_eax)[ebx];
	    if ((i1&0xff) != 0xff)
	    {
		    unsigned short val = (((unsigned char*)tmach_asm3)[i1]);
		    val |= (*((unsigned char *)i6)<<8);
		    if (transrev) val = ((val>>8)|(val<<8));
		    *((unsigned char *)i6) = (((unsigned char*)tmach)[val]);
	    }

	    i2 += tmach_asm1;
	    i5 += tmach_asm2;
	    i6++;
	    counter--;
    }
} /* thlineskipmodify */

/* #pragma aux tsethlineshift parm [eax][ebx] */
void tsethlineshift(long i1, long i2)
{
    i1 = 256-i1;
    tshift_al = (i1&0xff);
    tshift_bl = (i2&0xff);
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
} /* setupslopevlin */

extern long reciptable[2048];
extern long globalx3, globaly3;
extern long fpuasm;
#define low32(a) ((a&0xffffffff))
#define high32(a) ((int)(((__int64)a&(__int64)0xffffffff00000000)>>32))

/* #pragma aux slopevlin parm [eax][ebx][ecx][edx][esi][edi] */
void slopevlin(long i1, unsigned long i2, long i3, long i4, long i5, long i6)
{
    bitwisef2i c;
    unsigned long ecx,eax,ebx,edx,esi,edi;
    float a = (float) asm3 + asm2_f;
    i1 -= slopemach_ecx;
    esi = i5 + low32((__int64)globalx3 * (__int64)(i2<<3));
    edi = i6 + low32((__int64)globaly3 * (__int64)(i2<<3));
    ebx = i4;
    do {
	    // -------------
	    // All this is calculating a fixed point approx. of 1/a
	    c.f = a;
	    fpuasm = eax = c.i;
	    edx = (((long)eax) < 0) ? 0xffffffff : 0;
	    eax = eax << 1;
	    ecx = (eax>>24);	//  exponent
	    eax = ((eax&0xffe000)>>11);
	    ecx = ((ecx&0xffffff00)|((ecx-2)&0xff));
	    eax = reciptable[eax/4];
	    eax >>= (ecx&0xff);
	    eax ^= edx;
	    // -------------
	    edx = i2;
	    i2 = eax;
	    eax -= edx;
	    ecx = low32((__int64)globalx3 * (__int64)eax);
	    eax = low32((__int64)globaly3 * (__int64)eax);
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
		    i1 += slopemach_ecx;
		    edx = ((edx&0xffffff00)|((((unsigned char *)(ebx+edx))[slopemach_ebx])));
		    ebx = *((unsigned long*)i3); // register trickery
		    i3 -= 4;
		    eax = ((eax&0xffffff00)|(*((unsigned char *)(ebx+edx))));
		    ebx = esi;
		    *((unsigned char *)i1) = (eax&0xff);
		    edx = edi;
		    ecx = ((ecx&0xffffff00)|((ecx-1)&0xff));
	    }
	    ebx = asm4;
	    ebx -= 8;	// BITSOFPRECISIONPOW
    } while ((long)ebx > 0);
} /* slopevlin */

/* #pragma aux settransnormal parm */
void settransnormal(void)
{
	transrev = 0;
} /* settransnormal */

/* #pragma aux settransreverse parm */
void settransreverse(void)
{
	transrev = 1;
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
