// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.

// This file has been modified from Ken Silverman's original release
// (Actually, most of it was moved here from original BUILD source.)

#ifndef PLATFORM_DOS
#error Please do not compile this if PLATFORM_DOS is not defined.
#endif


// !!! check these includes against original engine.c !!!
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "pragmas.h"
#include <io.h>
#include <conio.h>
#include <i86.h>
#include <dos.h>

#include "platform.h"
#include "display.h"
#include "build.h"
#include "cache1d.h"
#include "ves2.h"
#include "engine.h"

static unsigned char tempbuf[MAXWALLS];
extern long transarea;
extern long totalarea;
extern long beforedrawrooms;
extern long stereowidth, stereopixelwidth, ostereopixelwidth;
extern volatile long stereomode, visualpage, activepage, whiteband, blackband;
extern volatile char oa1, o3c2, ortca, ortcb, overtbits, laststereoint;

extern char pow2char[8];
extern long pow2long[32];
extern char kensmessage[128];

static short capturecount = 0;
static char screenalloctype = 255;

static char pcxheader[128] =
{
        0xa,0x5,0x1,0x8,0x0,0x0,0x0,0x0,0x3f,0x1,0xc7,0x0,
        0x40,0x1,0xc8,0x0,0x0,0x0,0x0,0x8,0x8,0x8,0x10,0x10,
        0x10,0x18,0x18,0x18,0x20,0x20,0x20,0x28,0x28,0x28,0x30,0x30,
        0x30,0x38,0x38,0x38,0x40,0x40,0x40,0x48,0x48,0x48,0x50,0x50,
        0x50,0x58,0x58,0x58,0x60,0x60,0x60,0x68,0x68,0x68,0x70,0x70,
        0x70,0x78,0x78,0x78,0x0,0x1,0x40,0x1,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
};


static char vgapal16[48] =
{
        00,00,00,00,00,42,00,42,00,00,42,42,42,00,00,42,00,42,42,21,00,42,42,42,
        21,21,21,21,21,63,21,63,21,21,63,63,63,21,21,63,21,63,63,63,21,63,63,63,
};

static void (__interrupt __far *oldtimerhandler)(void);
static void (__interrupt __far *oldkeyhandler)(void);

extern long setvlinebpl(long);
#pragma aux setvlinebpl parm [eax];

void *kkmalloc(size_t size);
#pragma aux kkmalloc =\
        "call kmalloc",\
        parm [eax]\


void kkfree(void *buffer);
#pragma aux kkfree =\
        "call kfree",\
        parm [eax]\


unsigned char _readlastkeyhit(void)
{
    return(kinp(0x60));
} // _readlastkeyhit


void _uninitengine(void)
{
	long i;

	if (vidoption == 1) uninitvesa();

	if (stereomode) setstereo(0L);

	if (screen != NULL)
	{
		if (screenalloctype == 0) kkfree((void *)screen);
		//if (screenalloctype == 1) suckcache(screen);  //Cache already gone
		screen = NULL;
	}
	for(i=0;i<MAXPALOOKUPS;i++)
		if (palookup[i] != NULL) { kkfree(palookup[i]); palookup[i] = NULL; }
}


long readpixel16(long p)
{
	long mask, dat;

	mask = pow2long[(p&7)^7];

	if ((qsetmode == 480) && (ydim16 <= 336) && (p >= 640*336))
		p -= 640*336;
	else
		p += pageoffset;

	p >>= 3;

	koutp(0x3ce,0x4);
	koutp(0x3cf,0); dat = ((readpixel(p+0xa0000)&mask)>0);
	koutp(0x3cf,1); dat += (((readpixel(p+0xa0000)&mask)>0)<<1);
	koutp(0x3cf,2); dat += (((readpixel(p+0xa0000)&mask)>0)<<2);
	koutp(0x3cf,3); dat += (((readpixel(p+0xa0000)&mask)>0)<<3);
	return(dat);
}

int screencapture(char *filename, char inverseit)
{
	char *ptr;
	long fil, i, bufplc, p, col, ncol, leng, numbytes, xres;

	filename[4] = ((capturecount/1000)%10)+48;
	filename[5] = ((capturecount/100)%10)+48;
	filename[6] = ((capturecount/10)%10)+48;
	filename[7] = (capturecount%10)+48;
	if ((fil=open(filename,O_BINARY|O_CREAT|O_TRUNC|O_WRONLY,S_IWRITE))==-1)
		return(-1);

	if (qsetmode == 200)
	{
		pcxheader[8] = ((xdim-1)&255); pcxheader[9] = (((xdim-1)>>8)&255);
		pcxheader[10] = ((ydim-1)&255); pcxheader[11] = (((ydim-1)>>8)&255);
		pcxheader[12] = (xdim&255); pcxheader[13] = ((xdim>>8)&255);
		pcxheader[14] = (ydim&255); pcxheader[15] = ((ydim>>8)&255);
		pcxheader[66] = (xdim&255); pcxheader[67] = ((xdim>>8)&255);
	}
	else
	{
		pcxheader[8] = ((640-1)&255); pcxheader[9] = (((640-1)>>8)&255);
		pcxheader[10] = ((qsetmode-1)&255); pcxheader[11] = (((qsetmode-1)>>8)&255);
		pcxheader[12] = (640&255); pcxheader[13] = ((640>>8)&255);
		pcxheader[14] = (qsetmode&255); pcxheader[15] = ((qsetmode>>8)&255);
		pcxheader[66] = (640&255); pcxheader[67] = ((640>>8)&255);
	}

	write(fil,&pcxheader[0],128);

	if (qsetmode == 200)
	{
		ptr = (char *)frameplace;
		numbytes = xdim*ydim;
		xres = xdim;
	}
	else
	{
		numbytes = (mul5(qsetmode)<<7);
		xres = 640;
	}

	bufplc = 0; p = 0;
	while (p < numbytes)
	{
		koutp(97,kinp(97)|3);

		if (qsetmode == 200) { col = *ptr; p++; ptr++; }
		else
		{
			col = readpixel16(p);
			p++;
			if ((inverseit == 1) && (((col&7) == 0) || ((col&7) == 7))) col ^= 15;
		}

		leng = 1;

		if (qsetmode == 200) ncol = *ptr;
		else
		{
			ncol = readpixel16(p);
			if ((inverseit == 1) && (((ncol&7) == 0) || ((ncol&7) == 7))) ncol ^= 15;
		}

		while ((ncol == col) && (p < numbytes) && (leng < 63) && ((p%xres) != 0))
		{
			leng++;

			if (qsetmode == 200) { p++; ptr++; ncol = *ptr; }
			else
			{
				p++;
				ncol = readpixel16(p);
				if ((inverseit == 1) && (((ncol&7) == 0) || ((ncol&7) == 7))) ncol ^= 15;
			}
		}

		koutp(97,kinp(97)&252);

		if ((leng > 1) || (col >= 0xc0))
		{
			tempbuf[bufplc++] = (leng|0xc0);
			if (bufplc == 4096) { bufplc = 0; if (write(fil,&tempbuf[0],4096) < 4096) { close(fil); return(-1); } }
		}
		tempbuf[bufplc++] = col;
		if (bufplc == 4096) { bufplc = 0; if (write(fil,&tempbuf[0],4096) < 4096) { close(fil); return(-1); } }
	}

	tempbuf[bufplc++] = 0xc;
	if (bufplc == 4096) { bufplc = 0; if (write(fil,&tempbuf[0],4096) < 4096) { close(fil); return(-1); } }

	if (qsetmode == 200)
	{
		VBE_getPalette(0,256,&tempbuf[4096]);
		for(i=0;i<256;i++)
		{
			tempbuf[bufplc++] = (tempbuf[(i<<2)+4096+2]<<2);
			if (bufplc == 4096) { bufplc = 0; if (write(fil,&tempbuf[0],4096) < 4096) { close(fil); return(-1); } }
			tempbuf[bufplc++] = (tempbuf[(i<<2)+4096+1]<<2);
			if (bufplc == 4096) { bufplc = 0; if (write(fil,&tempbuf[0],4096) < 4096) { close(fil); return(-1); } }
			tempbuf[bufplc++] = (tempbuf[(i<<2)+4096+0]<<2);
			if (bufplc == 4096) { bufplc = 0; if (write(fil,&tempbuf[0],4096) < 4096) { close(fil); return(-1); } }
		}
	}
	else
	{
		for(i=0;i<768;i++)
		{
			if (i < 48)
				tempbuf[bufplc++] = (vgapal16[i]<<2);
			else
				tempbuf[bufplc++] = 0;
			if (bufplc == 4096) { bufplc = 0; if (write(fil,&tempbuf[0],4096) < 4096) { close(fil); return(-1); } }
		}

	}

	if (bufplc > 0)
		if (write(fil,&tempbuf[0],bufplc) < bufplc) { close(fil); return(-1); }

	close(fil);
	capturecount++;
	return(0);
}

void printscreeninterrupt(void)
{
	int5();
}


void drawline16(long x1, long y1, long x2, long y2, char col)
{
	long i, dx, dy, p, pinc, d;
	char lmask, rmask;

	dx = x2-x1; dy = y2-y1;
	if (dx >= 0)
	{
		if ((x1 > 639) || (x2 < 0)) return;
		if (x1 < 0) { if (dy) y1 += scale(0-x1,dy,dx); x1 = 0; }
		if (x2 > 639) { if (dy) y2 += scale(639-x2,dy,dx); x2 = 639; }
	}
	else
	{
		if ((x2 > 639) || (x1 < 0)) return;
		if (x2 < 0) { if (dy) y2 += scale(0-x2,dy,dx); x2 = 0; }
		if (x1 > 639) { if (dy) y1 += scale(639-x1,dy,dx); x1 = 639; }
	}
	if (dy >= 0)
	{
		if ((y1 >= ydim16) || (y2 < 0)) return;
		if (y1 < 0) { if (dx) x1 += scale(0-y1,dx,dy); y1 = 0; }
		if (y2 >= ydim16) { if (dx) x2 += scale(ydim16-1-y2,dx,dy); y2 = ydim16-1; }
	}
	else
	{
		if ((y2 >= ydim16) || (y1 < 0)) return;
		if (y2 < 0) { if (dx) x2 += scale(0-y2,dx,dy); y2 = 0; }
		if (y1 >= ydim16) { if (dx) x1 += scale(ydim16-1-y1,dx,dy); y1 = ydim16-1; }
	}

	setcolor16((long)col);
	if (x1 == x2)
	{
		if (y2 < y1) i = y1, y1 = y2, y2 = i;
		koutpw(0x3ce,0x8+(256<<((x1&7)^7)));  //bit mask
		vlin16((((mul5(y1)<<7)+x1+pageoffset)>>3)+0xa0000,y2-y1+1);
		return;
	}
	if (y1 == y2)
	{
		if (x2 < x1) i = x1, x1 = x2, x2 = i;
		lmask = (0x00ff>>(x1&7));
		rmask = (0xff80>>(x2&7));

		p = (((mul5(y1)<<7)+x1+pageoffset)>>3)+0xa0000;

		dx = (x2>>3)-(x1>>3);
		if (dx == 0)
		{
			koutpw(0x3ce,0x8+((lmask&rmask)<<8)); drawpixel(p,readpixel(p));
			return;
		}

		dx--;

		koutpw(0x3ce,0x8+(lmask<<8)); drawpixel(p,readpixel(p)); p++;
		if (dx > 0) { koutp(0x3cf,0xff); clearbufbyte((void *)p,dx,0L); p += dx; }
		koutp(0x3cf,rmask); drawpixel(p,readpixel(p));
		return;
	}

	dx = klabs(x2-x1)+1; dy = klabs(y2-y1)+1;
	if (dx >= dy)
	{
		if (x2 < x1)
		{
			i = x1; x1 = x2; x2 = i;
			i = y1; y1 = y2; y2 = i;
		}
		p = (mul5(y1)<<7)+x1+pageoffset;
		d = 0;
		if (y2 > y1) pinc = 640; else pinc = -640;
		for(i=dx;i>0;i--)
		{
			drawpixel16(p);
			d += dy;
			if (d >= dx) { d -= dx; p += pinc; }
			p++;
		}
		return;
	}

	if (y2 < y1)
	{
		i = x1; x1 = x2; x2 = i;
		i = y1; y1 = y2; y2 = i;
	}
	p = (mul5(y1)<<7)+x1+pageoffset;
	d = 0;
	if (x2 > x1) pinc = 1; else pinc = -1;
	for(i=dy;i>0;i--)
	{
		drawpixel16(p);
		d += dx;
		if (d >= dy) { d -= dy; p += pinc; }
		p += 640;
	}
}


void qsetmode640350(void)
{
	if (qsetmode != 350)
	{
		stereomode = 0;

		setvmode(0x10);

		pageoffset = 0;
		ydim16 = 350;
		koutpw(0x3d4,0xc+((pageoffset>>11)<<8));

		koutpw(0x3ce,0x0f00);  //set/reset
		koutpw(0x3ce,0x0f01);  //enable set/reset
		fillscreen16(0L,0L,640L*350L);
	}
	qsetmode = 350;
}

void qsetmode640480(void)
{
	short i;

	if (qsetmode != 480)
	{
		stereomode = 0;

		setvmode(0x12);

		i = 479-144;
		koutpw(0x3d4,0x18+((i&255)<<8));             //line compare
		koutp(0x3d4,0x7); koutp(0x3d5,(kinp(0x3d5)&239)|((i&256)>>4));
		koutp(0x3d4,0x9); koutp(0x3d5,(kinp(0x3d5)&191)|((i&512)>>3));

		pageoffset = 92160;
		koutpw(0x3d4,0xc+((pageoffset>>11)<<8));

		koutpw(0x3ce,0x0f00);  //set/reset
		koutpw(0x3ce,0x0f01);  //enable set/reset
		fillscreen16(0L,8L,640L*144L);
		fillscreen16((640L*144L)>>3,0L,640L*336L);
		pageoffset = 92160; ydim16 = 336;
	}

	qsetmode = 480;
}


void printext16(long xpos, long ypos, short col, short backcol, char name[82], char fontsize)
{
	long p, z, zz, charxsiz, daxpos;
	char ch, dat, mask, *fontptr;

	daxpos = xpos;

	koutp(0x3ce,0x5); koutp(0x3cf,(kinp(0x3cf)&(255-3))+2);
	koutp(0x3ce,0x8);

	if (fontsize == 1)
	{
		fontptr = smalltextfont;
		charxsiz = 4;
	}
	else
	{
		fontptr = textfont;
		charxsiz = 8;
	}

	z = 0;
	while (name[z] != 0)
	{
		ch = name[z];
		z++;

		mask = pow2char[8-(daxpos&7)]-1;
		p = ypos*80 + (daxpos>>3)+0xa0000;   //Do not make ylookup!

		if ((daxpos&7) == 0)
		{
			for(zz=0;zz<8;zz++)
			{
				if (backcol >= 0)
				{
					koutp(0x3cf,0xff);
					if (charxsiz == 4) koutp(0x3cf,0x7c);
					readpixel(p), drawpixel(p,(long)backcol);
				}
				koutp(0x3cf,fontptr[(((long)ch)<<3)+zz]);
				if (charxsiz == 4) koutp(0x3cf,0x7c&fontptr[(((long)ch)<<3)+zz]);
				readpixel(p), drawpixel(p,col);
				p += 80;
			}
		}
		else
		{
			for(zz=0;zz<8;zz++)
			{
				if (backcol >= 0)
				{
					if (charxsiz == 8)
					{
						koutp(0x3cf,mask);
						readpixel(p), drawpixel(p,backcol);
						koutp(0x3cf,~mask);
						readpixel(p+1), drawpixel(p+1,backcol);
					}
					else
					{
						koutp(0x3cf,0x7c>>(daxpos&7));
						readpixel(p), drawpixel(p,backcol);
						koutp(0x3cf,0x7c<<(8-(daxpos&7)));
						readpixel(p+1), drawpixel(p+1,backcol);
					}
				}
				dat = fontptr[(((long)ch)<<3)+zz];
				if (charxsiz == 8)
				{
					koutp(0x3cf,mask&(dat>>(daxpos&7)));
					readpixel(p), drawpixel(p,col);
					koutp(0x3cf,(~mask)&(dat<<(8-(daxpos&7))));
					readpixel(p+1), drawpixel(p+1,col);
				}
				else
				{
					koutp(0x3cf,(0x7c&dat)>>(daxpos&7));
					readpixel(p), drawpixel(p,col);
					koutp(0x3cf,(0x7c&dat)<<(8-(daxpos&7)));
					readpixel(p+1), drawpixel(p+1,col);
				}
				p += 80;    //Do not make bytesperline!
			}
		}

		daxpos += charxsiz;
	}
	koutp(0x3ce,0x5); koutp(0x3cf,(kinp(0x3cf)&(255-3))+0);
}

void _nextpage(void)
{
	switch(qsetmode)
	{
		case 200:
			switch(vidoption)
			{
				case 1:
					if (stereomode)
					{
						stereonextpage();
						if (!origbuffermode) buffermode = transarea = totalarea = 0;
					}
					else
					{
						visualpage = activepage;
						setvisualpage(visualpage);
						if (!origbuffermode)
						{
							buffermode = ((transarea<<3) > totalarea);
							transarea = totalarea = 0;
						}
						activepage++; if (activepage >= numpages) activepage = 0;
						setactivepage(activepage);
					}
					break;
				case 2:
					copybuf((void *)frameplace,(void *)0xa0000,64000>>2);
					break;
				case 6:
					if (!activepage) redblueblit(screen,&screen[65536],64000L);
					activepage ^= 1;
					break;
			}
			break;

		case 350:
			koutpw(0x3d4,0xc+((pageoffset>>11)<<8));
			limitrate();
			pageoffset = 225280-pageoffset; //225280 is 352(multiple of 16)*640
			break;

		case 480:
			koutpw(0x3d4,0xc+((pageoffset>>11)<<8));
			limitrate();
			pageoffset = 399360-pageoffset;
			break;
	}
} // _nextpage


void interrupt stereohandler1(void)
{
		//VR flag
	if (kinp(0x3c2)&128)
	{
		laststereoint = 0;
		koutpw(0x3d4,((long)(overtbits)<<8)+0x11);
		koutp(0x3d5,overtbits+16);
	}
	if (laststereoint == 1)
	{
		visualpage ^= 1;
		setvisualpage(visualpage|0x80000000);  //0x80000000 to ignore qlimitrate
	}
	laststereoint++;
	koutp(0x70,0xc); kinp(0x71);
	koutp(0xa0,0x20);
	koutp(0x20,0x20);
}

void interrupt stereohandler2(void)
{
		//VR flag
	if (kinp(0x3c2)&128)
	{
		laststereoint = 0;
		koutp(0x378,0xfb+((visualpage&1^1)<<2));
		koutpw(0x3d4,((long)overtbits<<8)+0x11);
		koutp(0x3d5,overtbits+16);
	}
	if (laststereoint == 1)
	{
		visualpage ^= 1;
		setvisualpage(visualpage|0x80000000);  //0x80000000 to ignore qlimitrate
	}
	laststereoint++;
	koutp(0x70,0xc); kinp(0x71);
	koutp(0xa0,0x20);
	koutp(0x20,0x20);
}

void stereonextpage(void)
{
	koutp(0x70,0xc); kinp(0x71);
	//koutpw(0x70,0x420b);
	if ((activepage&1) == 0)
	{
		if (stereomode == 1)
		{
			clearbuf((void *)(ylookup[ydim-1]+frameplace),xdim>>4,whiteband);
			clearbuf((void *)(ylookup[ydim-1]+frameplace+(xdim>>2)),(xdim>>2)-(xdim>>4),blackband);
		}
		activepage++;
		setactivepage(activepage);
		return;
	}
	if (stereomode == 1)
	{
		clearbuf((void *)(ylookup[ydim-1]+frameplace),(xdim>>2)-(xdim>>4),whiteband);
		clearbuf((void *)(ylookup[ydim-1]+frameplace+xdim-(xdim>>2)),xdim>>4,blackband);
	}
	if (visualpage < (numpages&~1)-2) visualpage += 2; else visualpage &= 1;
	if (activepage < (numpages&~1)-1) activepage++; else activepage = 0;
	setactivepage(activepage);
}

void setstereo(long dastereomode)
{
	//long i, dist, blackdist, whitedist, t1, t2, numlines;
	//char c1, c2;
	long i, dist, blackdist, whitedist;

	if ((vidoption != 1) || (numpages < 2)) return;

	if (stereomode)  //---------------Uninitialize old stereo mode
	{
		if ((xdim == 320) && (ydim == 200))
		{
				//back to 70 hz
			koutp(0x3c2,o3c2);
		}

			//Uninit VR flag
		koutpw(0x3d4,(((long)overtbits+32)<<8)+0x11);

			//Uninit RTC
		_disable();
		koutp(0xa1,(kinp(0xa1)&~1)|(oa1&1));
		koutp(0x70,0xa); koutp(0x71,ortca);
		koutp(0x70,0xb); koutp(0x71,ortcb);
		uninstallbistereohandlers();
		_enable();

		stereomode = 0;
		ostereopixelwidth = -1;
		setview(windowx1,windowy1,windowx2,windowy2);
		if (stereomode == 1)
		{
			for(i=0;i<numpages;i++)
			{
				setactivepage(i);
				clearbuf((void *)(ylookup[ydim-1]+frameplace),xdim>>2,blackband);
			}
			setactivepage(activepage);
		}
	}

	//------------------------------------- Initialize new stereo mode
	stereomode = dastereomode; if (!stereomode) return;

	activepage = (visualpage & ~1)+2;
	if (activepage >= numpages-1) activepage = 0;

	if (stereomode == 1)
	{
		blackdist = 0x7fffffff; whitedist = 0x80000000;
		koutp(0x3c7,0);
		for(i=0;i<256;i++)
		{
			dist = (kinp(0x3c9)&255)+(kinp(0x3c9)&255)+(kinp(0x3c9)&255);
			if (dist < blackdist) { blackdist = dist; blackband = i; }
			if (dist > whitedist) { whitedist = dist; whiteband = i; }
		}
		blackband += (blackband<<8); blackband += (blackband<<16);
		whiteband += (whiteband<<8); whiteband += (whiteband<<16);
	}

	if ((xdim == 320) && (ydim == 200))
	{
			//80 hz
		o3c2 = kinp(0x3cc);
		koutp(0x3c2,(o3c2&0xf3)+4);
	}

		//Init RTC
	_disable();
	if (stereomode == 1) installbistereohandlers(stereohandler1);
	if (stereomode == 2) installbistereohandlers(stereohandler2);
	koutp(0x70,0xa); ortca = kinp(0x71);
	if (stereomode == 1) koutp(0x71,0x28); //+8 = 256hz
	if (stereomode == 2) koutp(0x71,0x26); //+6 = 1024hz
	koutp(0x70,0xb); ortcb = kinp(0x71); koutp(0x71,0x42);
	koutp(0x70,0xc); kinp(0x71);
	oa1 = kinp(0xa1); koutp(0xa1,oa1&~1);
	_enable();

		//Init VR flag
	koutp(0x3d4,0x11);
	overtbits = kinp(0x3d5) & ~(16+32);
	koutp(0x3d5,overtbits);
	koutp(0x3d5,overtbits+16);
}

#define RTCBUFSIZ 16
static unsigned short rtcopmsel, rtcormseg, rtcormoff;
static unsigned long rtcopmoff;
//Use bicomc.asm as a template if this asm code needs re-writing
static char rtcrmbuffer[RTCBUFSIZ] =
{
	0x50,          //push ax
	0xb0,0x0c,     //mov al, 0ch
	0xe6,0x70,     //out 70h, al
	0xe4,0x71,     //in al, 71h
	0xb0,0x20,     //mov al, 20h
	0xe6,0xa0,     //out 0a0h, al
	0xe6,0x20,     //out 20h, al
	0x58,          //pop ax
	0xcf           //iret
};
void *engconvalloc32 (unsigned long size)
{
	 union REGS r;

	 r.x.eax = 0x0100;           //DPMI allocate DOS memory
	 r.x.ebx = ((size+15)>>4);   //Number of paragraphs requested
	 int386(0x31,&r,&r);

	 if (r.x.cflag != 0)         //Failed
		 return ((unsigned long)0);
	 return ((void *)((r.x.eax&0xffff)<<4));   //Returns full 32-bit offset
}

void installbistereohandlers(void far *stereohan)
{
	//char *ptr;
	union REGS r;
	struct SREGS sr;
	void *lowp;
	//int c;

		//Get old protected mode handler
	r.x.eax = 0x3500+0x70;   /* DOS get vector (INT 0Ch) */
	sr.ds = sr.es = 0;
	int386x(0x21,&r,&r,&sr);
	rtcopmsel = (unsigned short)sr.es;
	rtcopmoff = r.x.ebx;

		//Get old real mode handler
	r.x.eax = 0x0200;   /* DPMI get real mode vector */
	r.h.bl = 0x70;
	int386(0x31,&r,&r);
	rtcormseg = (unsigned short)r.x.ecx;
	rtcormoff = (unsigned short)r.x.edx;

		//Allocate memory in low memory to store real mode handler
	if ((lowp = engconvalloc32(RTCBUFSIZ)) == 0)
	{
		printf("Couldn't allocate conventional memory.\n");
		exit(1);
	}

	memcpy(lowp,(void *)rtcrmbuffer,RTCBUFSIZ);

		//Set new protected mode handler
	r.x.eax = 0x2500+0x70;   /* DOS set vector (INT 0Ch) */
	r.x.edx = FP_OFF(stereohan);
	sr.ds = FP_SEG(stereohan);      //DS:EDX == &handler
	sr.es = 0;
	int386x(0x21,&r,&r,&sr);

		//Set new real mode handler (must be after setting protected mode)
	r.x.eax = 0x0201;
	r.h.bl = 0x70;              //CX:DX == real mode &handler
	r.x.ecx = ((((long)lowp)>>4)&0xffff);   //D32realseg
	r.x.edx = (((long)lowp)&0xf);           //D32realoff
	int386(0x31,&r,&r);
}

void uninstallbistereohandlers(void)
{
	union REGS r;
	struct SREGS sr;

		//restore old protected mode handler
	r.x.eax = 0x2500+0x70;   /* DOS set vector (INT 0Ch) */
	r.x.edx = rtcopmoff;
	sr.ds = rtcopmsel;    /* DS:EDX == &handler */
	sr.es = 0;
	int386x(0x21,&r,&r,&sr);

		//restore old real mode handler
	r.x.eax = 0x0201;   /* DPMI set real mode vector */
	r.h.bl = 0x70;
	r.x.ecx = (unsigned long)rtcormseg;     //CX:DX == real mode &handler
	r.x.edx = (unsigned long)rtcormoff;
	int386(0x31,&r,&r);
}

void inittimer(void)
{
	outp(0x43,0x34); outp(0x40,(1193181/120)&255); outp(0x40,(1193181/120)>>8);
	oldtimerhandler = _dos_getvect(0x8);
	_disable(); _dos_setvect(0x8, timerhandler); _enable();
}

void uninittimer(void)
{
	outp(0x43,0x34); outp(0x40,0); outp(0x40,0);           //18.2 times/sec
	_disable(); _dos_setvect(0x8, oldtimerhandler); _enable();
}

void initkeys(void)
{
	oldkeyhandler = _dos_getvect(0x9);
	_disable(); _dos_setvect(0x9, keyhandler); _enable();
}

void uninitkeys(void)
{
	short *ptr;

	_dos_setvect(0x9, oldkeyhandler);
		//Turn off shifts to prevent stucks with quitting
	ptr = (short *)0x417; *ptr &= ~0x030f;
}

int _setgamemode(char davidoption, long daxdim, long daydim)
{
        long i, j, ostereomode;

        if ((qsetmode == 200) && (vidoption == davidoption) && (xdim == daxdim) && (ydim == daydim))
                return(0);
        vidoption = davidoption; xdim = daxdim; ydim = daydim;

        strcpy(kensmessage,"!!!! BUILD engine&tools programmed by Ken Silverman of E.G. RI.  (c) Copyright 1995 Ken Silverman.  Summary:  BUILD = Ken. !!!!");
        if (getkensmessagecrc(FP_OFF(kensmessage)) != 0x56c764d4)
                { setvmode(0x3); printf("Nice try.\n"); exit(0); }

        ostereomode = stereomode; if (stereomode) setstereo(0L);

        activepage = visualpage = 0;
        switch(vidoption)
        {
                case 1: i = xdim*ydim; break;
                case 2: xdim = 320; ydim = 200; i = xdim*ydim; break;
                case 6: xdim = 320; ydim = 200; i = 131072; break;
                default: return(-1);
        }
        j = ydim*4*sizeof(long);  //Leave room for horizlookup&horizlookup2

        if (screen != NULL)
        {
                if (screenalloctype == 0) kkfree((void *)screen);
                if (screenalloctype == 1) suckcache((long *)screen);
                screen = NULL;
        }
        screenalloctype = 0;
        if ((screen = (char *)kkmalloc(i+(j<<1))) == NULL)
        {
                 allocache((long *)&screen,i+(j<<1),&permanentlock);
                 screenalloctype = 1;
        }

        frameplace = FP_OFF(screen);
        horizlookup = (long *)(frameplace+i);
        horizlookup2 = (long *)(frameplace+i+j);
        horizycent = ((ydim*4)>>1);


        switch(vidoption)
        {
                case 1:
                                //bytesperline is set in this function
                        if (setvesa(xdim,ydim) < 0) return(-1);
                        break;
                case 2:
                        horizycent = ((ydim*4)>>1);  //HACK for switching to this mode
                case 6:
                        bytesperline = xdim;
                        setvmode(0x13);
                        break;
                default: return(-1);
        }

                //Force drawrooms to call dosetaspect & recalculate stuff
        oxyaspect = oxdimen = oviewingrange = -1;

        setvlinebpl(bytesperline);
        j = 0;
        for(i=0;i<=ydim;i++) ylookup[i] = j, j += bytesperline;

        numpages = 1;
        if (vidoption == 1) numpages = min(maxpages,8);

        setview(0L,0L,xdim-1,ydim-1);
        clearallviews(0L);
        setbrightness(curbrightness, &palette[0]);

        if (searchx < 0) { searchx = halfxdimen; searchy = (ydimen>>1); }

        if (ostereomode) setstereo(ostereomode);

        qsetmode = 200;
        return(0);
}


void _platform_init(int argc, char **argv, const char *title, const char *icon)
{
    // no op in DOS, currently.  --ryan.
}

void clear2dscreen(void)
{
	if (qsetmode == 350)
		fillscreen16(pageoffset>>3,0L,640L*350L);
	else if (qsetmode == 480)
	{
		if (ydim16 <= 336) fillscreen16(pageoffset>>3,0L,640L*336L);
						  else fillscreen16(pageoffset>>3,0L,640L*480L);
	}
}

void _idle(void)
{
    // no-op in DOS, which is non-multitasking. However, if someone were to
    //  add Desqview/win95/OS2/etc support, timeslicing would be good.
}


void *_getVideoBase(void)
{
    return((void *) 0xa0000);
}

void _updateScreenRect(long x, long y, long w, long h)
{
}

int using_opengl(void)
{
    return(0);
}

// end of dos_driver.c ...

