/*
 * Experimental OpenGL support code for Build.
 *
 *  Written by Ryan C. Gordon. (icculus@linuxgames.com)
 *
 * Please do NOT harrass Ken Silverman about any code modifications
 *  (including this file) to BUILD.
 */

// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.
// This file IS NOT A PART OF Ken Silverman's original release

#ifndef _INCLUDE_BUILDGL_H_
#define _INCLUDE_BUILDGL_H_

#if (!defined USE_OPENGL)
#error USE_OPENGL is not defined. Do you REALLY want to compile this?
#endif

#include <GL/gl.h>

extern const GLubyte* (*dglGetString)(GLenum name);
extern void (*dglBegin)(GLenum mode);
extern void (*dglEnd)(void);
extern void (*dglClear)(GLbitfield mask);
extern void (*dglClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);

#endif  // !defined _INCLUDE_BUILDGL_H_

// end of buildgl.h ...

