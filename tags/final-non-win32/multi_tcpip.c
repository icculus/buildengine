/*
 * The original KenBuild networking code was just an interface between
 *  COMit and BUILD. This is useless to us, so here are the functions
 *  that KenBuild needs implemented. Have fun.  --ryan.
 */

// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.

#include "build.h"

short numplayers = 0, myconnectindex = 0;
short connecthead, connectpoint2[MAXPLAYERS];
long syncbufleng, outbufindex[128], outcnt;
long myconnectnum, otherconnectnum, mypriority;
long crctable[256];
char syncstate = 0;
long connectnum[MAXPLAYERS];

void initmultiplayers(char damultioption, char dacomrateoption, char dapriority)
{
	long i;

	connecthead = 0;
	for(i=MAXPLAYERS-1;i>=0;i--)
		connectpoint2[i] = -1, connectnum[i] = 0x7fffffff;

	numplayers = 1;
}

void uninitmultiplayers()
{
}

void sendlogon(void)
{
} // sendlogon

void sendlogoff(void)
{
} // sendlogoff

int getoutputcirclesize(void)
{
    return(0);
} // getoutputcirclesize

void sendpacket (short otherconnectindex, char *bufptr, short messleng)
{
} // sendpacket

short getpacket (short *other, char *bufptr)
{
    return(0);
} // getpacket

/* end of multi_tcpip.c ... */

