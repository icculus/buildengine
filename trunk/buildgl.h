/*
 * Experimental OpenGL support code for Build.
 *
 *  Written by Ryan C. Gordon. (icculus@linuxgames.com)
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

#ifndef _INCLUDE_BUILDGL_H_
#define _INCLUDE_BUILDGL_H_

#if (!defined USE_OPENGL)
#error USE_OPENGL is not defined. Do you REALLY want to compile this?
#endif

#include <GL/gl.h>

typedef const GLubyte* (*glGetString_t)(GLenum name);
extern glGetString_t dglGetString;

typedef void (*glBegin_t)(GLenum mode);
extern glBegin_t dglBegin;

typedef void (*glEnd_t)(void);
extern glEnd_t dglEnd;

typedef void (*glClear_t)(GLbitfield mask);
extern glClear_t dglClear;

typedef void (*glClearColor_t)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
extern glClearColor_t dglClearColor;

typedef void (*glDrawPixels_t)(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
extern glDrawPixels_t dglDrawPixels;

typedef void (*glPixelMapfv_t)(GLenum map, GLint mapsize, const GLfloat *values);
extern glPixelMapfv_t dglPixelMapfv;

typedef void (*glPixelStorei_t)(GLenum pname, GLint param);
extern glPixelStorei_t dglPixelStorei;

#endif  /* !defined _INCLUDE_BUILDGL_H_ */

/* end of buildgl.h ... */

