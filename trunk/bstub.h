/*
 * The following functions must be implemented by someone extending Ken's
 *  BUILD editor; these are called by the editor to allow you to make hooks
 *  into the program without having to touch build.c yourself. See Ken's
 *  bstub.c for an example.
 *
 * Moved to separate header file by Ryan C. Gordon (icculus@clutteredmind.org).
 *
 * Please do NOT harrass Ken Silverman about any code modifications
 *  (including this file) to BUILD.
 */

/*
 * "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
 * Ken Silverman's official web site: "http://www.advsys.net/ken"
 * See the included license file "BUILDLIC.TXT" for license info.
 * This file IS NOT A PART OF Ken Silverman's original release
 */

#ifndef _INCLUDE_BSTUB_H_
#define _INCLUDE_BSTUB_H_

void ExtInit(void);
void ExtUnInit(void);
void ExtLoadMap(const char *mapname);
void ExtSaveMap(const char *mapname);
const char *ExtGetSectorCaption(short sectnum);
const char *ExtGetWallCaption(short wallnum);
const char *ExtGetSpriteCaption(short spritenum);
void ExtShowSectorData(short sectnum);
void ExtShowWallData(short wallnum);
void ExtShowSpriteData(short spritenum);
void ExtEditSectorData(short sectnum);
void ExtEditWallData(short wallnum);
void ExtEditSpriteData(short spritenum);
void ExtPreCheckKeys(void);
void ExtAnalyzeSprites(void);
void ExtCheckKeys(void);

#endif /* !defined _INCLUDE_BSTUB_H_ */

/* end of bstub.h ... */



