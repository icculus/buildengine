/*
 * Experimental OpenGL support code for Build.
 *
 *  Written by Ryan C. Gordon. (icculus@clutteredmind.org)
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

typedef void (*glGetPixelMapfv_t)(GLenum map, GLfloat *values);
extern glGetPixelMapfv_t dglGetPixelMapfv;

typedef void (*glPixelMapfv_t)(GLenum map, GLint mapsize, const GLfloat *values);
extern glPixelMapfv_t dglPixelMapfv;

typedef void (*glPixelStorei_t)(GLenum pname, GLint param);
extern glPixelStorei_t dglPixelStorei;

typedef void (*glEnable_t)(GLenum cap);
extern glEnable_t dglEnable;

typedef void (*glDisable_t)(GLenum cap);
extern glDisable_t dglDisable;

typedef void (*glViewport_t)(GLint x, GLint y, GLsizei width, GLsizei height);
extern glViewport_t dglViewport;

typedef void (*glGenTextures_t)(GLsizei n, GLuint *textures);
extern glGenTextures_t dglGenTextures;

typedef void (*glDeleteTextures_t)(GLsizei n, const GLuint *textures);
extern glDeleteTextures_t dglDeleteTextures;

typedef void (*glBindTexture_t)(GLenum target, GLuint texture);
extern glBindTexture_t dglBindTexture;

typedef void (*glTexParameteri_t)(GLenum target, GLenum pname, GLint param);
extern glTexParameteri_t dglTexParameteri;

typedef void (*glTexImage2D_t)(GLenum target, GLint level,
                               GLint internalFormat, GLsizei width,
                               GLsizei height, GLint border, GLenum format,
                               GLenum type, const GLvoid *pixels);
extern glTexImage2D_t dglTexImage2D;

typedef void (*glTexCoord2f_t)(GLfloat s, GLfloat t);
extern glTexCoord2f_t dglTexCoord2f;

typedef void (*glVertex2f_t)(GLfloat x, GLfloat y);
extern glVertex2f_t dglVertex2f;

typedef void (*glVertex3f_t)(GLfloat x, GLfloat y, GLfloat z);
extern glVertex3f_t dglVertex3f;

typedef void (*glColor3f_t)(GLfloat red, GLfloat green, GLfloat blue);
extern glColor3f_t dglColor3f;

typedef GLenum (*glGetError_t)(void);
extern glGetError_t dglGetError;

typedef void (*glGetIntegerv_t)(GLenum pname, GLint *params);
extern glGetIntegerv_t dglGetIntegerv;

typedef void (*glClearDepth_t)(GLclampd depth);
extern glClearDepth_t dglClearDepth;

typedef void (*glDepthFunc_t)(GLenum func);
extern glDepthFunc_t dglDepthFunc;

typedef void (*glShadeModel_t)(GLenum mode);
extern glShadeModel_t dglShadeModel;

typedef void (*glMatrixMode_t)(GLenum mode);
extern glMatrixMode_t dglMatrixMode;

typedef void (*glLoadIdentity_t)(void);
extern glLoadIdentity_t dglLoadIdentity;

typedef void (*glPixelTransferi_t)(GLenum pname, GLint param);
extern glPixelTransferi_t dglPixelTransferi;

int opengl_load_library(void);
void opengl_gen_2d_textures(int xdim, int ydim);
void opengl_build_2d_quads(int x, int y, int w, int h);
void opengl_swapbuffers(void);

#endif  /* !defined _INCLUDE_BUILDGL_H_ */

/* end of buildgl.h ... */

