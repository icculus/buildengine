/*
 * OpenGL support code.
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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "platform.h"
#include "SDL.h"
#include "display.h"
#include "buildgl.h"

glGetString_t dglGetString = NULL;
glBegin_t dglBegin = NULL;
glEnd_t dglEnd = NULL;
glClear_t dglClear = NULL;
glClearColor_t dglClearColor = NULL;
glDrawPixels_t dglDrawPixels = NULL;
glGetPixelMapfv_t dglGetPixelMapfv = NULL;
glPixelMapfv_t dglPixelMapfv = NULL;
glPixelStorei_t dglPixelStorei = NULL;
glEnable_t dglEnable = NULL;
glDisable_t dglDisable = NULL;
glViewport_t dglViewport = NULL;
glGenTextures_t dglGenTextures = NULL;
glDeleteTextures_t dglDeleteTextures = NULL;
glBindTexture_t dglBindTexture = NULL;
glTexParameteri_t dglTexParameteri = NULL;
glTexImage2D_t dglTexImage2D = NULL;
glTexCoord2f_t dglTexCoord2f = NULL;
glVertex2f_t dglVertex2f = NULL;
glVertex3f_t dglVertex3f = NULL;
glColor3f_t dglColor3f = NULL;
glGetError_t dglGetError = NULL;
glGetIntegerv_t dglGetIntegerv = NULL;
glClearDepth_t dglClearDepth = NULL;
glDepthFunc_t dglDepthFunc = NULL;
glShadeModel_t dglShadeModel = NULL;
glMatrixMode_t dglMatrixMode = NULL;
glLoadIdentity_t dglLoadIdentity = NULL;
glPixelTransferi_t dglPixelTransferi = NULL;


void sgldebug(const char *fmt, ...);
static int debug_hall_of_mirrors = 0;


static void *opengl_symload(void **ptr, const char *sym)
{
    void *retval = NULL;

    retval = SDL_GL_GetProcAddress(sym);
    if (retval == NULL)
        sgldebug("Symbol \"%s\" NOT located.", sym);
    else
        sgldebug("Symbol \"%s\" located.", sym);

    if (ptr != NULL)
        *ptr = retval;

    return(retval);
} /* open_symload */


static int opengl_load_symbols(void)
{
    if (!opengl_symload((void **) &dglGetString, "glGetString")) return(-1);
    if (!opengl_symload((void **) &dglBegin, "glBegin")) return(-1);
    if (!opengl_symload((void **) &dglEnd, "glEnd")) return(-1);
    if (!opengl_symload((void **) &dglClear, "glClear")) return(-1);
    if (!opengl_symload((void **) &dglClearColor, "glClearColor")) return(-1);
    if (!opengl_symload((void **) &dglDrawPixels, "glDrawPixels")) return(-1);
    if (!opengl_symload((void **) &dglPixelStorei, "glPixelStorei")) return(-1);
    if (!opengl_symload((void **) &dglGetPixelMapfv, "glGetPixelMapfv")) return(-1);
    if (!opengl_symload((void **) &dglPixelMapfv, "glPixelMapfv")) return(-1);
    if (!opengl_symload((void **) &dglEnable, "glEnable")) return(-1);
    if (!opengl_symload((void **) &dglDisable, "glDisable")) return(-1);
    if (!opengl_symload((void **) &dglViewport, "glViewport")) return(-1);
    if (!opengl_symload((void **) &dglGenTextures, "glGenTextures")) return(-1);
    if (!opengl_symload((void **) &dglDeleteTextures, "glDeleteTextures")) return(-1);
    if (!opengl_symload((void **) &dglBindTexture, "glBindTexture")) return(-1);
    if (!opengl_symload((void **) &dglTexParameteri, "glTexParameteri")) return(-1);
    if (!opengl_symload((void **) &dglTexImage2D, "glTexImage2D")) return(-1);
    if (!opengl_symload((void **) &dglTexCoord2f, "glTexCoord2f")) return(-1);
    if (!opengl_symload((void **) &dglVertex2f, "glVertex2f")) return(-1);
    if (!opengl_symload((void **) &dglVertex3f, "glVertex3f")) return(-1);
    if (!opengl_symload((void **) &dglColor3f, "glColor3f")) return(-1);
    if (!opengl_symload((void **) &dglGetError, "glGetError")) return(-1);
    if (!opengl_symload((void **) &dglGetIntegerv, "glGetIntegerv")) return(-1);
    if (!opengl_symload((void **) &dglClearDepth, "glClearDepth")) return(-1);
    if (!opengl_symload((void **) &dglDepthFunc, "glDepthFunc")) return(-1);
    if (!opengl_symload((void **) &dglShadeModel, "glShadeModel")) return(-1);
    if (!opengl_symload((void **) &dglMatrixMode, "glMatrixMode")) return(-1);
    if (!opengl_symload((void **) &dglLoadIdentity, "glLoadIdentity")) return(-1);
    if (!opengl_symload((void **) &dglPixelTransferi, "glPixelTransferi")) return(-1);

    return(0);
} /* opengl_load_symbols */


static int opengl_try_libname(const char *libname)
{
    int rc = -1;

    sgldebug("Trying to open library \"%s\"...",
                libname ? libname : "[default]");
    SDL_ClearError();
    rc = SDL_GL_LoadLibrary(libname);

    if (rc == -1)
        sgldebug("Library opening failed; [%s].", SDL_GetError());
    else
    {
        sgldebug("Library opened successfully!");
        rc = opengl_load_symbols();
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    } /* else */

    return(rc);
} /* opengl_try_libname */


static int opengl_lib_is_loaded = 0;

int opengl_load_library(void)
{
    char *envlib = getenv(BUILD_GLLIBRARY);
    int rc = 0;

    debug_hall_of_mirrors = (getenv(BUILD_HALLOFMIRRORS) != NULL);

    if (!opengl_lib_is_loaded)  /* it's cool. Go on. */
    {
        rc = opengl_try_libname(envlib);
        if (rc == -1)
        {
            sgldebug("Out of ideas. Giving up.");
            return(-1);
        } /* if */

        opengl_lib_is_loaded = 1;
    } /* if */

    return(0);
} /* opengl_load_library */


static Uint8 mirrorcolor = 0;

void opengl_swapbuffers(void)
{
    if (using_opengl())
    {
        SDL_GL_SwapBuffers();
        if (debug_hall_of_mirrors)
        {
            dglClearColor( ((GLfloat) mirrorcolor) / 255.0, 0.0f, 0.0f, 0.0f );
            mirrorcolor++;
        } /* if */
        dglClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        dglEnable(GL_DEPTH_TEST);
    } /* if */
} /* opengl_swapbuffers */

/* end of buildgl.c ... */

