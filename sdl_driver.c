/*
 * An SDL replacement for BUILD's VESA code.
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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "platform.h"

#if (!defined PLATFORM_SUPPORTS_SDL)
#error This platform apparently does not use SDL. Do not compile this.
#endif

#include "SDL.h"
#include "build.h"
#include "display.h"
#include "pragmas.h"
#include "engine.h"

#if (defined USE_OPENGL)
#include "buildgl.h"

// !!! move this to buildgl.c, and add a function to that to abstract
// !!!  SDL_GL_GetProcAddress().
const GLubyte* (*dglGetString)(GLenum name) = NULL;
void (*dglBegin)(GLenum mode) = NULL;
void (*dglEnd)(void) = NULL;
void (*dglClear)(GLbitfield mask) = NULL;
void (*dglClearColor)(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) = NULL;
#endif


// !!! ugh. Clean this up.
#if (defined USE_I386_ASM)
#if (!defined __WATCOMC__)
#include "a.h"
#else
extern long setvlinebpl(long);
#pragma aux setvlinebpl parm [eax];
#endif  // __WATCOMC__
#endif  // USE_I386_ASM


#include "cache1d.h"


// !!! I'd like this to be temporary. --ryan.
// !!!  That is, the self-modifying part, so I can ditch the mprotect() stuff.
#if ((defined PLATFORM_UNIX) && (defined USE_I386_ASM))

#include <sys/mman.h>
#include <limits.h>

#ifndef PAGESIZE
#define PAGESIZE 4096
#endif

#endif


// !!! remove the surface_end checks, for speed's sake. They are a
// !!!  needed safety right now. --ryan.


// environment variables names.
#define BUILD_NOMOUSEGRAB  "BUILD_NO_MOUSE_GRAB"
#define BUILD_WINDOWED     "BUILD_WINDOWED"
#define BUILD_SDLDEBUG     "BUILD_SDLDEBUG"
#define BUILD_GLLIBRARY    "BUILD_GLLIBRARY"
#define BUILD_SCREENRES    "BUILD_SCREENRES"

#define UNLOCK_SURFACE_AND_RETURN  if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface); return;


    // !!! move these elsewhere?
long xres, yres, bytesperline, frameplace, imageSize, maxpages;
char *screen, vesachecked;
long buffermode, origbuffermode, linearmode;
char permanentupdate = 0, vgacompatible;

SDL_Surface *surface = NULL; /* This isn't static so that we can use it elsewhere AH */
static int debug_hall_of_mirrors = 0;
static Uint32 sdl_flags = SDL_HWPALETTE;
static long mouse_x = 0;
static long mouse_y = 0;
static long mouse_relative_x = 0;
static long mouse_relative_y = 0;
static short mouse_buttons = 0;
static int mouse_grabbed = 0;
static unsigned int lastkey = 0;
static SDL_TimerID primary_timer = NULL;
// so we can make use of setcolor16()... - DDOI
static unsigned char drawpixel_color=0;
// These hold the colors for the 256 color palette when in 16-color mode - DDOI
static char backup_palette[48];
static int in_egapalette = 0;
// The standard EGA palette in BUILD format - DDOI
static char egapalette[] = { 0, 0, 0, // 0,
			    0, 0, 42, //0,
			    0, 42, 0, //0,
			    0, 42, 42,// 0,
			    42, 0, 0, //0,
			    42, 0, 42, //0,
			    42, 21, 0, //0,
			    42, 42, 42,// 0,
			    21, 21, 21, //0,
			    21, 21, 63, //0,
			    21, 63, 21, //0,
			    21, 63, 63, //0,
			    63, 21, 21, //0,
			    63, 21, 63, //0,
			    63, 63, 21, //0,
			    63, 63, 63 //, 0
			   };

static unsigned int scancodes[SDLK_LAST];

static long last_render_ticks = 0;
long total_render_time = 1;
long total_rendered_frames = 0;

static char *titlelong = NULL;
static char *titleshort = NULL;

static int audio_disabled = 0;

void restore256_palette (void);
void set16color_palette (void);


#define print_sdl_surface_flag(x) if (_surface->flags & x) fprintf( stderr, " %s", #x )
#define print_tf_state(str, val) fprintf( stderr, "BUILDSDL: %s: {%s}\n", str, (val) ? "true" : "false" )

static void output_surface_info(SDL_Surface *_surface)
{
    const SDL_VideoInfo *info;

    if (getenv(BUILD_SDLDEBUG) == NULL)
        return;

    if (_surface == NULL)
    {
        fprintf(stderr, "BUILDSDL: -WARNING- You've got a NULL screen surface!\n");
    }
    else
    {
        fprintf(stderr, "BUILDSDL: screen surface is (%dx%dx%dbpp).\n",
                _surface->w, _surface->h, _surface->format->BitsPerPixel);
        fprintf(stderr, "BUILDSDL: New vidmode flags:");
        print_sdl_surface_flag(SDL_SWSURFACE);
        print_sdl_surface_flag(SDL_HWSURFACE);
        print_sdl_surface_flag(SDL_ASYNCBLIT);
        print_sdl_surface_flag(SDL_ANYFORMAT);
        print_sdl_surface_flag(SDL_HWPALETTE);
        print_sdl_surface_flag(SDL_DOUBLEBUF);
        print_sdl_surface_flag(SDL_FULLSCREEN);
        print_sdl_surface_flag(SDL_OPENGL);
        print_sdl_surface_flag(SDL_OPENGLBLIT);
        print_sdl_surface_flag(SDL_RESIZABLE);
        print_sdl_surface_flag(SDL_NOFRAME);
        print_sdl_surface_flag(SDL_HWACCEL);
        print_sdl_surface_flag(SDL_SRCCOLORKEY);
        print_sdl_surface_flag(SDL_RLEACCELOK);
        print_sdl_surface_flag(SDL_RLEACCEL);
        print_sdl_surface_flag(SDL_SRCALPHA);
        print_sdl_surface_flag(SDL_PREALLOC);
        fprintf(stderr, "\n");

        info = SDL_GetVideoInfo();
        assert(info != NULL);

        print_tf_state("hardware surface available", info->hw_available);
        print_tf_state("window manager available", info->wm_available);
        print_tf_state("accelerated hardware->hardware blits", info->blit_hw);
        print_tf_state("accelerated hardware->hardware colorkey blits", info->blit_hw_CC);
        print_tf_state("accelerated hardware->hardware alpha blits", info->blit_hw_A);
        print_tf_state("accelerated software->hardware blits", info->blit_sw);
        print_tf_state("accelerated software->hardware colorkey blits", info->blit_sw_CC);
        print_tf_state("accelerated software->hardware alpha blits", info->blit_sw_A);
        print_tf_state("accelerated color fills", info->blit_fill);
        fprintf(stderr, "BUILDSDL: video memory: (%d)\n", info->video_mem);
    } // else
} // output_surface_info


static void output_driver_info(void)
{
    char buffer[256];

    if (getenv(BUILD_SDLDEBUG) == NULL)
        return;

    if (SDL_VideoDriverName(buffer, sizeof (buffer)) == NULL)
    {
        fprintf(stderr, "BUILDSDL: -WARNING- SDL_VideoDriverName() returned NULL!\n");
    } // if
    else
    {
        fprintf(stderr, "BUILDSDL: Using video driver \"%s\".\n", buffer);
    } // else
} // output_driver_info


// !!! This is almost an entire copy of the original setgamemode().
// !!!  Figure out what is needed for just 2D mode, and separate that
// !!!  out. Then, place the original setgamemode() back into engine.c,
// !!!  and remove our simple implementation (and this function.)
// !!!  Just be sure to keep the non-DOS things, like the window's
// !!!  titlebar caption.   --ryan.
static char screenalloctype = 255;
static void init_new_res_vars(int davidoption)
{
    int i = 0;
    int j = 0;

    setupmouse();

    SDL_WM_SetCaption(titlelong, titleshort);

    xdim = xres = surface->w;
    ydim = yres = surface->h;

    bytesperline = surface->w;
    vesachecked = 1;
    vgacompatible = 1;
    linearmode = 1;
	qsetmode = surface->h;
	activepage = visualpage = 0;
    horizlookup = horizlookup2 = NULL;

    // !!! add me in!
    //if (surface->flags & SDL_OPENGL)
    //    frameplace = NULL;
    //else
        frameplace = (long) ( ((Uint8 *) surface->pixels) );


  	if (screen != NULL)
   	{
       	if (screenalloctype == 0) kkfree((void *)screen);
   	    if (screenalloctype == 1) suckcache((long *)screen);
   		screen = NULL;
   	} // if

    if (davidoption != -1)
    {
    	switch(vidoption)
    	{
    		case 1:i = xdim*ydim; break;
    		case 2: xdim = 320; ydim = 200; i = xdim*ydim; break;
    		case 6: xdim = 320; ydim = 200; i = 131072; break;
    		default: assert(0);
    	}
    	j = ydim*4*sizeof(long);  //Leave room for horizlookup&horizlookup2

    	screenalloctype = 0;
	    if ((screen = (char *)kkmalloc(i+(j<<1))) == NULL)
    	{
	    	 allocache((long *)&screen,i+(j<<1),&permanentlock);
    		 screenalloctype = 1;
    	}

        // !!! add me in!
        //if (surface->flags & SDL_OPENGL)
        //    frameplace = NULL;
        //else
        //{
            frameplace = FP_OFF(screen);
          	horizlookup = (long *)(frameplace+i);
           	horizlookup2 = (long *)(frameplace+i+j);
        //} // else
    } // if

    j = 0;
  	for(i = 0; i <= ydim; i++)
    {
        ylookup[i] = j;
        j += bytesperline;
    } // for

   	horizycent = ((ydim*4)>>1);

		//Force drawrooms to call dosetaspect & recalculate stuff
	oxyaspect = oxdimen = oviewingrange = -1;

	setvlinebpl(bytesperline);

    if (davidoption != -1)
    {
    	setview(0L,0L,xdim-1,ydim-1);
    	clearallviews(0L);
    } // if
	setbrightness((char)curbrightness,(char *)&palette[0]);

	if (searchx < 0) { searchx = halfxdimen; searchy = (ydimen>>1); }
} // init_new_res_vars


static void go_to_new_vid_mode(int vidoption, int w, int h)
{
    getvalidvesamodes();
    SDL_ClearError();
    surface = SDL_SetVideoMode(w, h, 8, sdl_flags);
    if (surface == NULL)
    {
        fprintf(stderr, "BUILDSDL: Failed to set %dx%d video mode!\n"
                        "  SDL_Error() says [%s].\n", w, h, SDL_GetError());
        SDL_Quit();
        exit(13);
    } // if

    output_surface_info(surface);
    init_new_res_vars(vidoption);
} // go_to_new_vid_mode


static int sdl_mouse_button_filter(SDL_Event const *event)
{
        /*
         * What BUILD expects:
         *  0	left button pressed if 1
         *  1	right button pressed if 1
         *  2	middle button pressed if 1
         *
         *   (That is, this is what Int 33h (AX=0x05) returns...)
         */

    Uint8 bmask = SDL_GetMouseState(NULL, NULL);
    mouse_buttons = 0;
    if (bmask & SDL_BUTTON_LMASK) mouse_buttons |= 1;
    if (bmask & SDL_BUTTON_RMASK) mouse_buttons |= 2;
    if (bmask & SDL_BUTTON_MMASK) mouse_buttons |= 4;
    return(0);
} // sdl_mouse_up_filter


static int sdl_mouse_motion_filter(SDL_Event const *event)
{
    if (surface == NULL)
        return(0);

    if (event->type == SDL_JOYBALLMOTION)
    {
        mouse_relative_x = event->jball.xrel/100;
        mouse_relative_y = event->jball.yrel/100;
       	mouse_x += mouse_relative_x;
       	mouse_y += mouse_relative_y;
    } // if
    else
    {
        if (mouse_grabbed)
        {
          	mouse_relative_x = event->motion.xrel;
       	    mouse_relative_y = event->motion.yrel;
           	mouse_x += mouse_relative_x;
           	mouse_y += mouse_relative_y;
        } // if
        else
        {
          	mouse_relative_x = event->motion.x - mouse_x;
           	mouse_relative_y = event->motion.y - mouse_y;
           	mouse_x = event->motion.x;
           	mouse_y = event->motion.y;
        } // else
    } // else

   	if (mouse_x < 0) mouse_x = 0;
   	if (mouse_x > surface->w) mouse_x = surface->w;
   	if (mouse_y < 0) mouse_y = 0;
   	if (mouse_y > surface->h) mouse_y = surface->h;

    return(0);
} // sdl_mouse_motion_filter


/**
 * Attempt to flip the video surface to fullscreen or windowed mode.
 *  Attempts to maintain the surface's state, but makes no guarantee
 *  that pointers (i.e., the surface's pixels field) will be the same
 *  after this call.
 *
 * Caveats: Your surface pointers will be changing; if you have any other
 *           copies laying about, they are invalidated.
 *
 *          Do NOT call this from an SDL event filter on Windows. You can
 *           call it based on the return values from SDL_PollEvent, etc, just
 *           not during the function you passed to SDL_SetEventFilter().
 *
 *          Thread safe? Likely not.
 *
 *   @param surface pointer to surface ptr to toggle. May be different
 *                  pointer on return. MAY BE NULL ON RETURN IF FAILURE!
 *   @param flags   pointer to flags to set on surface. The value pointed
 *                  to will be XOR'd with SDL_FULLSCREEN before use. Actual
 *                  flags set will be filled into pointer. Contents are
 *                  undefined on failure. Can be NULL, in which case the
 *                  surface's current flags are used.
 *  @return non-zero on success, zero on failure.
 */
static int attempt_fullscreen_toggle(SDL_Surface **surface, Uint32 *flags)
{
    long framesize = 0;
    void *pixels = NULL;
    SDL_Color *palette = NULL;
    SDL_Rect clip;
    int ncolors = 0;
    Uint32 tmpflags = 0;
    int w = 0;
    int h = 0;
    int bpp = 0;

    if ( (!surface) || (!(*surface)) )  // don't bother if there's no surface.
        return(0);

    tmpflags = (*surface)->flags;
    w = (*surface)->w;
    h = (*surface)->h;
    bpp = (*surface)->format->BitsPerPixel;

    if (flags == NULL)  // use the surface's flags.
        flags = &tmpflags;

    SDL_GetClipRect(*surface, &clip);

        // save the contents of the screen.
    framesize = (w * h) * ((*surface)->format->BytesPerPixel);
    pixels = malloc(framesize);
    if (pixels == NULL)
        return(0);
    memcpy(pixels, (*surface)->pixels, framesize);

    if ((*surface)->format->palette != NULL)
    {
        ncolors = (*surface)->format->palette->ncolors;
        palette = malloc(ncolors * sizeof (SDL_Color));
        if (palette == NULL)
        {
            free(pixels);
            return(0);
        } // if
        memcpy(palette, (*surface)->format->palette->colors,
               ncolors * sizeof (SDL_Color));
    } // if

    *surface = SDL_SetVideoMode(w, h, bpp, (*flags) ^ SDL_FULLSCREEN);

    if (*surface != NULL)
        *flags ^= SDL_FULLSCREEN;

    else  // yikes! Try to put it back as it was...
    {
        *surface = SDL_SetVideoMode(w, h, bpp, tmpflags);
        if (*surface == NULL)  // completely screwed.
        {
            free(pixels);
            return(0);
        } // if
    } // if

    memcpy((*surface)->pixels, pixels, framesize);
    free(pixels);

    if (palette != NULL)
    {
            // !!! FIXME : No idea if that flags param is right.
        SDL_SetPalette(*surface, SDL_LOGPAL, palette, 0, ncolors);
        free(palette);
    } // if

    SDL_SetClipRect(*surface, &clip);

    output_surface_info(*surface);

    return(1);
} // attempt_fullscreen_toggle


static int sdl_key_filter(const SDL_Event *event)
{
    SDL_GrabMode grab_mode = SDL_GRAB_OFF;
    int extended;
    int tmp;

    if ( (event->key.keysym.sym == SDLK_g) &&
         (event->key.state == SDL_PRESSED) &&
         (event->key.keysym.mod & KMOD_CTRL) )
    {
        mouse_grabbed = ((mouse_grabbed) ? 0 : 1);
        if (mouse_grabbed)
            grab_mode = SDL_GRAB_ON;
        SDL_WM_GrabInput(grab_mode);
        return(0);
    } // if

    else if ( ( (event->key.keysym.sym == SDLK_RETURN) ||
                (event->key.keysym.sym == SDLK_KP_ENTER) ) &&
              (event->key.state == SDL_PRESSED) &&
              (event->key.keysym.mod & KMOD_ALT) )
    {
        tmp = ((void *) frameplace == (void *) surface->pixels);
        attempt_fullscreen_toggle(&surface, &sdl_flags);
        assert(surface != NULL);
        if (tmp)
            frameplace = (long) surface->pixels;
        return(0);
    } // if

    lastkey = scancodes[event->key.keysym.sym];
    if (lastkey == 0x0000)   // No DOS equivalent defined.
        return(0);

    extended = ((lastkey & 0xFF00) >> 8);
    if (extended != 0)
    {
        lastkey = extended;
        keyhandler();
        lastkey = (scancodes[event->key.keysym.sym] & 0xFF);
    } // if

    if (event->key.state == SDL_RELEASED)
        lastkey += 128;  // +128 signifies that the key is released in DOS.

    keyhandler();
    return(0);
} // sdl_key_filter


static int root_sdl_event_filter(const SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_KEYUP:
        case SDL_KEYDOWN:
            return(sdl_key_filter(event));
        case SDL_JOYBALLMOTION:
        case SDL_MOUSEMOTION:
            return(sdl_mouse_motion_filter(event));
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
            return(sdl_mouse_button_filter(event));
        case SDL_QUIT:
            exit(0);   // !!! rcg TEMP
    } // switch

    return(1);
} // root_sdl_event_filter


static void handle_events(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
        root_sdl_event_filter(&event);
} // handle_events


unsigned char _readlastkeyhit(void)
{
    return(lastkey);
} // _readlastkeyhit


// !!! I'd like this to be temporary. --ryan.
#if ((defined PLATFORM_UNIX) && (defined USE_I386_ASM))

#define PROT_R_W_X (PROT_READ | PROT_WRITE | PROT_EXEC)

int mprotect_align(const void *addr, size_t len, int prot)
{
    int retval;
    unsigned long l = (unsigned long) addr;
    l -= (l % PAGESIZE);
    retval = mprotect((void *) l, len * 2, prot);
    assert(retval == 0);
    return(retval);
} // mprotect_align


void unprotect_ASM_pages(void)
{
    mprotect_align((const void *) asm_sethlinesizes, PAGESIZE, PROT_R_W_X);
    mprotect_align((const void *) asm_setpalookupaddress, PAGESIZE, PROT_R_W_X);
    mprotect_align((const void *) asm_setuphlineasm4, PAGESIZE, PROT_R_W_X);
    mprotect_align((const void *) asm_hlineasm4, PAGESIZE, PROT_R_W_X);
    mprotect_align((const void *) asm_setupvlineasm, PAGESIZE, PROT_R_W_X);
    mprotect_align((const void *) asm_vlineasm4, PAGESIZE, PROT_R_W_X);
    mprotect_align((const void *) asm_tvlineasm1, PAGESIZE, PROT_R_W_X);
    mprotect_align((const void *) asm_tvlineasm2, PAGESIZE, PROT_R_W_X);
    mprotect_align((const void *) asm_tspritevline, PAGESIZE, PROT_R_W_X);
    mprotect_align((const void *) asm_thline, PAGESIZE, PROT_R_W_X);
    mprotect_align((const void *) asm_prohlineasm4, PAGESIZE, PROT_R_W_X);
    mprotect_align((const void *) asm_stretchhline, PAGESIZE, PROT_R_W_X);
} // unprotect_ASM_pages


/*
  global _sethlinesizes


  global _prosethlinesizes
  global _setvlinebpl
  global _setpalookupaddress
  global _prosetpalookupaddress
  global _setuphlineasm4
  global _hlineasm4
  global _prohlineasm4
  global _setupvlineasm
  global _prosetupvlineasm
  global _setupmvlineasm
  global _setuptvlineasm
  global _prevlineasm1
  global _vlineasm1
  global _mvlineasm1
  global _fixtransluscence
  global _settransnormal
  global _settransreverse
  global _tvlineasm1
  global _vlineasm4
  global _provlineasm4
  global _mvlineasm4
  global _setupspritevline
  global _spritevline
  global _msetupspritevline
  global _mspritevline
  global _tsetupspritevline
  global _tspritevline
  global _msethlineshift
  global _mhline
  global _mhlineskipmodify
  global _tsethlineshift
  global _thline
  global _thlineskipmodify
  global _setuptvlineasm2
  global _tvlineasm2
  global _setupslopevlin2
  global _slopevlin2
  global _setupslopevlin
  global _slopevlin
  global _setuprhlineasm4
  global _rhlineasm4
  global _setuprmhlineasm4
  global _rmhlineasm4
  global _setupqrhlineasm4
  global _qrhlineasm4
  global _setupdrawslab
  global _drawslab
  global _stretchhline
  global _mmxoverlay
*/

#endif


#ifdef USE_OPENGL
static int opengl_lib_is_loaded = 0;

static char *default_gl_libs[] = {
#ifdef PLATFORM_UNIX
"libGL.so.1", "libGL.so"
#elif PLATFORM_WIN32
"opengl32.dll"
#else
#error Fill in your platform-specific GL libs!
#endif
};

static void *try_glsym_load(const char *sym)
{
    void *retval = NULL;

    fprintf(stderr, "BUILDGL: Looking up \"%s\"...", sym);
    SDL_ClearError();
    retval = SDL_GL_GetProcAddress(sym);
    if (retval == NULL)
        fprintf(stderr, "failure: [%s]\n", SDL_GetError());
    else
        fprintf(stderr, "success!\n");
    return(retval);
} // try_glsym_load


static int load_opengl_symbols(void)
{
    if (!(dglGetString = try_glsym_load("glGetString"))) return(-1);
    if (!(dglBegin = try_glsym_load("glBegin"))) return(-1);
    if (!(dglEnd = try_glsym_load("glEnd"))) return(-1);
    if (!(dglClear = try_glsym_load("glClear"))) return(-1);
    if (!(dglClearColor = try_glsym_load("glClearColor"))) return(-1);

    return(0);
} // load_opengl_symbols


static int try_opengl_libname(const char *libname)
{
    int rc = -1;

    if (libname != NULL)
    {
        fprintf(stderr, "BUILDGL: Trying to open \"%s\"...", libname);
        SDL_ClearError();
        rc = SDL_GL_LoadLibrary(libname);

        if (rc == -1)
            fprintf(stderr, "failure: [%s]\n", SDL_GetError());
        else
        {
            fprintf(stderr, "success!\n");
            rc = load_opengl_symbols();
        } // else
    } // if

    return(rc);
} // try_gl_libname


static int load_opengl_library(void)
{
    char *envlib = getenv(BUILD_GLLIBRARY);
    int rc = 0;
    int i;

    if (!opengl_lib_is_loaded)  // it's cool. Go on.
    {
        if (envlib)
            rc = try_opengl_libname(envlib);
        else
        {
            for (i = 0; i < sizeof (default_gl_libs) / sizeof (char *); i++)
            {
                rc = try_opengl_libname(default_gl_libs[i]);
                if (rc != -1)
                    break;
            } // for
        } // else

        if (rc == -1)
        {
            fprintf(stderr, "BUILDGL: Out of ideas. Giving up.\n");
            return(-1);
        } // if

        opengl_lib_is_loaded = 1;
    } // if
    return(0);
} // load_opengl_library

#endif  // defined USE_OPENGL


void _platform_init(int argc, char **argv, const char *title, const char *icon)
{
    #if ((PLATFORM_UNIX) && (defined USE_I386_ASM))
        unprotect_ASM_pages();
    #endif

    setbuf(stderr, NULL);
    setbuf(stdout, NULL);

    if (title == NULL)
        title = "BUILD";

    if (icon == NULL)
        icon = "BUILD";

    titlelong = strdup(title);
    titleshort = strdup(icon);

    if (getenv(BUILD_NOMOUSEGRAB) == NULL)
        mouse_grabbed = 1;
    else
        mouse_grabbed = 0;

    sdl_flags = ((getenv(BUILD_WINDOWED) == NULL) ? SDL_FULLSCREEN : 0);

    sdl_flags |= SDL_HWPALETTE;
    //sdl_flags |= SDL_HWSURFACE;  // !!!
    //sdl_flags |= SDL_DOUBLEBUF;

    memset(scancodes, '\0', sizeof (scancodes));
    scancodes[SDLK_ESCAPE]          = 0x01;
    scancodes[SDLK_1]               = 0x02;
    scancodes[SDLK_2]               = 0x03;
    scancodes[SDLK_3]               = 0x04;
    scancodes[SDLK_4]               = 0x05;
    scancodes[SDLK_5]               = 0x06;
    scancodes[SDLK_6]               = 0x07;
    scancodes[SDLK_7]               = 0x08;
    scancodes[SDLK_8]               = 0x09;
    scancodes[SDLK_9]               = 0x0A;
    scancodes[SDLK_0]               = 0x0B;
    scancodes[SDLK_EQUALS]          = 0x4E;
    scancodes[SDLK_BACKSPACE]       = 0x0E;
    scancodes[SDLK_TAB]             = 0x0F;
    scancodes[SDLK_q]               = 0x10;
    scancodes[SDLK_w]               = 0x11;
    scancodes[SDLK_e]               = 0x12;
    scancodes[SDLK_r]               = 0x13;
    scancodes[SDLK_t]               = 0x14;
    scancodes[SDLK_y]               = 0x15;
    scancodes[SDLK_u]               = 0x16;
    scancodes[SDLK_i]               = 0x17;
    scancodes[SDLK_o]               = 0x18;
    scancodes[SDLK_p]               = 0x19;
    scancodes[SDLK_LEFTBRACKET]     = 0x1A;
    scancodes[SDLK_RIGHTBRACKET]    = 0x1B;
    scancodes[SDLK_RETURN]          = 0x1C;
    scancodes[SDLK_LCTRL]           = 0x1D;
    scancodes[SDLK_a]               = 0x1E;
    scancodes[SDLK_s]               = 0x1F;
    scancodes[SDLK_d]               = 0x20;
    scancodes[SDLK_f]               = 0x21;
    scancodes[SDLK_g]               = 0x22;
    scancodes[SDLK_h]               = 0x23;
    scancodes[SDLK_j]               = 0x24;
    scancodes[SDLK_k]               = 0x25;
    scancodes[SDLK_l]               = 0x26;
    scancodes[SDLK_SEMICOLON]       = 0x27;
    scancodes[SDLK_QUOTE]           = 0x28;
    scancodes[SDLK_BACKQUOTE]       = 0x29;
    scancodes[SDLK_LSHIFT]          = 0x2A;
    scancodes[SDLK_BACKSLASH]       = 0x2B;
    scancodes[SDLK_z]               = 0x2C;
    scancodes[SDLK_x]               = 0x2D;
    scancodes[SDLK_c]               = 0x2E;
    scancodes[SDLK_v]               = 0x2F;
    scancodes[SDLK_b]               = 0x30;
    scancodes[SDLK_n]               = 0x31;
    scancodes[SDLK_m]               = 0x32;
    scancodes[SDLK_COMMA]           = 0x33;
    scancodes[SDLK_PERIOD]          = 0x34;
    scancodes[SDLK_SLASH]           = 0x35;
    scancodes[SDLK_RSHIFT]          = 0x36;
    scancodes[SDLK_KP_DIVIDE]       = 0xE035;
    scancodes[SDLK_KP_MULTIPLY]     = 0x37;
    scancodes[SDLK_LALT]            = 0x38;
    scancodes[SDLK_RALT]            = 0xB8;
    scancodes[SDLK_RCTRL]           = 0x9D;
    scancodes[SDLK_SPACE]           = 0x39;
    scancodes[SDLK_CAPSLOCK]        = 0x3A;
    scancodes[SDLK_F1]              = 0x3B;
    scancodes[SDLK_F2]              = 0x3C;
    scancodes[SDLK_F3]              = 0x3D;
    scancodes[SDLK_F4]              = 0x3E;
    scancodes[SDLK_F5]              = 0x3F;
    scancodes[SDLK_F6]              = 0x40;
    scancodes[SDLK_F7]              = 0x41;
    scancodes[SDLK_F8]              = 0x42;
    scancodes[SDLK_F9]              = 0x43;
    scancodes[SDLK_F10]             = 0x44;
    scancodes[SDLK_F11]             = 0x57;
    scancodes[SDLK_F12]             = 0x58;
    scancodes[SDLK_NUMLOCK]         = 0x45;
    scancodes[SDLK_SCROLLOCK]       = 0x46;
    scancodes[SDLK_MINUS]           = 0x4A;
    scancodes[SDLK_KP7]             = 0x47;
    scancodes[SDLK_KP8]             = 0x48;
    scancodes[SDLK_KP9]             = 0x49;
    scancodes[SDLK_HOME]            = 0xE047;
    scancodes[SDLK_UP]              = 0xE048;
    scancodes[SDLK_PAGEUP]          = 0xE0C9;
    scancodes[SDLK_KP_MINUS]        = 0xE04A;
    scancodes[SDLK_KP4]             = 0x4B;
    scancodes[SDLK_KP5]             = 0x4C;
    scancodes[SDLK_KP6]             = 0x4D;
    scancodes[SDLK_LEFT]            = 0xE04B;
    scancodes[SDLK_RIGHT]           = 0xE04D;
    scancodes[SDLK_KP_PLUS]         = 0xE04E;
    scancodes[SDLK_KP1]             = 0x4F;
    scancodes[SDLK_KP2]             = 0x50;
    scancodes[SDLK_KP3]             = 0x51;
    scancodes[SDLK_END]             = 0xE04F;
    scancodes[SDLK_DOWN]            = 0xE050;
    scancodes[SDLK_PAGEDOWN]        = 0xE0D1;
    scancodes[SDLK_DELETE]          = 0xE0D3;
    scancodes[SDLK_KP0]             = 0xE052;
    scancodes[SDLK_INSERT]          = 0xE052;
    scancodes[SDLK_KP_ENTER]        = 0xE01C;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
    {
        fprintf(stderr, "BUILDSDL: SDL_Init() failed!\n");
        fprintf(stderr, "BUILDSDL: SDL_GetError() says \"%s\".\n", SDL_GetError());
        exit(1);
    } // if

    debug_hall_of_mirrors = (getenv(BUILD_SDLDEBUG) != NULL);

    output_driver_info();

    #ifdef USE_OPENGL
        if (load_opengl_library() == -1)
        {
            SDL_Quit();
            _exit(42);
        } // if
    #endif
} // _platform_init


int setvesa(long x, long y)
{
    fprintf(stderr, "setvesa() called in SDL driver!\n");
    exit(23);
    return(0);
} // setvesa


int screencapture(char *filename, char inverseit)
{
    fprintf(stderr, "screencapture() is a stub in the SDL driver.\n");
    return(0);
} // screencapture


void setvmode(int mode)
{
    int w = -1;
    int h = -1;

    if (mode == 0x3)  // text mode.
    {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        return;
    } // if

    if (mode == 0x13)
    {
        w = 800;
        h = 600;
    } // if

    else
    {
        fprintf(stderr, "setvmode(0x%x) is unsupported in SDL driver.\n", mode);
        exit(13);
    } // if

    assert(w > 0);
    assert(h > 0);

    go_to_new_vid_mode(-1, w, h);
} // setvmode


int _setgamemode(char davidoption, long daxdim, long daydim)
{
    #ifdef USE_OPENGL
        static int shown_gl_strings = 0;
        sdl_flags |= SDL_OPENGL;
    #endif

    if (in_egapalette)
        restore256_palette();	    

    go_to_new_vid_mode((int) davidoption, daxdim, daydim);

    #ifdef USE_OPENGL
        if (!shown_gl_strings)
        {
            fprintf(stderr, "BUILDGL: GL_VENDOR [%s]\n",
                        (char *) dglGetString(GL_VENDOR));

            fprintf(stderr, "BUILDGL: GL_RENDERER [%s]\n",
                        (char *) dglGetString(GL_RENDERER));

            fprintf(stderr, "BUILDGL: GL_VERSION [%s]\n",
                        (char *) dglGetString(GL_VERSION));

            fprintf(stderr, "BUILDGL: GL_EXTENSIONS [%s]\n",
                        (char *) dglGetString(GL_EXTENSIONS));

            shown_gl_strings = 1;
        } // if
    #endif

    qsetmode = 200;
    last_render_ticks = SDL_GetTicks();
    return(0);
} // setgamemode


void qsetmode640350(void)
{
    assert(0);

    #ifdef USE_OPENGL
        sdl_flags ^= SDL_OPENGL;
    #endif

    go_to_new_vid_mode(-1, 640, 350);
} // qsetmode640350


void qsetmode640480(void)
{
    if (!in_egapalette)
    	set16color_palette();

    #ifdef USE_OPENGL
        sdl_flags ^= SDL_OPENGL;
    #endif

    go_to_new_vid_mode(-1, 640, 480);
    pageoffset = 0;	// Make sure it goes to the right place - DDOI
    fillscreen16(0L,8L,640L*144L);
} // qsetmode640480


// Let the user specify a specific mode via environment variable.
static void add_user_defined_resolution(int debugging)
{
    const char *envr = getenv(BUILD_SCREENRES);
    char *xptr = NULL;
    char *ptr = NULL;
    long w = -1;
    long h = -1;
    int bogus = 0;

    if (envr == NULL)
        return;

    xptr = strchr(envr, 'x');
    if (xptr == NULL)
        bogus = 1;
    else
    {
        w = strtol(envr, &ptr, 10);
        if (ptr != xptr)
            bogus = 1;
        else
        {
            xptr++;
            h = strtol(xptr, &ptr, 10);
            if ( (*xptr == '\0') || (*ptr != '\0') )
                bogus = 1;
            else
            {
                if ((w <= 1) || (h <= 1))
                    bogus = 1;
            } // else
        } // else
    } // else

    if (debugging)
    {
        if (bogus)
        {
            fprintf(stderr,
                    "BUILDSDL: User defined resolution [%s] is bogus!\n",
                    envr);
        } // if
        else
        {
            fprintf(stderr,
                    "BUILDSDL: Added user defined resolution: (%ldx%ld)\n",
                    w, h);
        } // else
    } // if

    if (!bogus)
    {
        validmode[validmodecnt] = validmodecnt;
       	validmodexdim[validmodecnt] = w;
       	validmodeydim[validmodecnt] = h;
        validmodecnt++;
    } // if
} // add_user_defined_resolution


#define swap_macro(tmp, x, y) { tmp = x; x = y; y = tmp; }

// !!! FIXME : Break this up into subfunctions.
void getvalidvesamodes(void)
{
    static int already_checked = 0;
    int debugging;
    int tmp;
    int i = 0;
    const SDL_VideoInfo *vidInfo = NULL;
    SDL_Rect **modes = NULL;
    int sorted = 0;
    int pos = 0;
    int stdres[][2] = {   // !!! is this legal C?!
                       {320, 200}, {640, 350}, {640, 480},
                       {800, 600}, {1024, 768}, {999, 999}
                     };

    if (already_checked)
        return;

    already_checked = 1;
   	validmodecnt = 0;
    debugging = (getenv(BUILD_SDLDEBUG) != NULL);
    vidoption = 1;  //!!! tmp

    vidInfo = SDL_GetVideoInfo();
    modes = SDL_ListModes(vidInfo->vfmt, sdl_flags | SDL_FULLSCREEN);
    if (modes == NULL)
    {
        sdl_flags &= ~SDL_FULLSCREEN;
        modes = SDL_ListModes(vidInfo->vfmt, sdl_flags); // try without fullscreen.
        if (modes == NULL)
            modes = (SDL_Rect **) -1;  // fuck it.
    } // if

        // BUILD wants this array sorted smallest to largest. SDL gives it
        //  to us largest to smallest. Argh.
        //  320 by 200 needs to be in here. SDL will emulate if need be.

        // ...find the largest hardware resolution...
    if (modes == (SDL_Rect **) -1)
    {
        pos = -1;
        if (debugging)
            fprintf(stderr, "BUILDSDL: Apparently we're windowed.\n");
    } // if
    else
    {
        pos = 0;
        if (debugging)
        {
            fprintf(stderr, "BUILDSDL: Largest resolution: (%dx%d).\n",
                    modes[0]->w, modes[0]->h);
        } // if
    } // else

        // fill in the standard resolutions...
    for (i = 0; i < sizeof (stdres) / sizeof (stdres[0]); i++)
    {
        if ( (pos != -1) &&
             ( (modes[pos]->w < stdres[i][0]) ||
               (modes[pos]->h < stdres[i][1]) ) )
        {
            if (debugging)
            {
                fprintf(stderr,
                    "BUILDSDL: Standard resolution (%dx%d) is too big.\n",
                    stdres[i][0], stdres[i][1]);
            } // if

            continue;
        } // if

        if (debugging)
        {
            fprintf(stderr,
                "BUILDSDL: Adding standard resolution (%dx%d).\n",
                stdres[i][0], stdres[i][1]);
        } // if

        validmode[validmodecnt] = validmodecnt;
       	validmodexdim[validmodecnt] = stdres[i][0];
       	validmodeydim[validmodecnt] = stdres[i][1];
        validmodecnt++;
    } // for


        //  Anything the hardware can specifically do is added now if it
        //   isn't in our standard list already.

    add_user_defined_resolution(debugging);

    if (modes != (SDL_Rect **) -1)
    {
        for (i = 0; modes[i] != NULL; i++)
        {
                // make sure this resolution isn't already listed...
            for (pos = 0; pos < validmodecnt; pos++)
            {
                if ( (modes[i]->w == validmodexdim[pos]) &&
                     (modes[i]->h == validmodeydim[pos]) )
                {
                    if (debugging)
                    {
                        fprintf(stderr,
                            "BUILDSDL: Hardware resolution (%dx%d) is standard.\n",
                            modes[i]->w, modes[i]->h);
                    } // if
                    pos = -1;
                    break;
                } // if
            } // for

            if (pos != -1)
            {
                if (debugging)
                {
                    fprintf(stderr,
                        "BUILDSDL: Adding hardware resolution (%dx%d).\n",
                        modes[i]->w, modes[i]->h);
                } // if
                validmode[validmodecnt] = validmodecnt;
                validmodexdim[validmodecnt] = modes[i]->w;
                validmodeydim[validmodecnt] = modes[i]->h;
                validmodecnt++;
            } // if
        } // for
    } // if

        // now, sort the list, smallest to largest, and be done with it.
    do
    {
        sorted = 1;
        for (i = 0; i < validmodecnt - 1; i++)
        {
            if ( (validmodexdim[i] >= validmodexdim[i+1]) &&
                 (validmodeydim[i] >= validmodeydim[i+1]) )
            {
                sorted = 0;
                swap_macro(tmp, validmode[i], validmode[i+1]);
                swap_macro(tmp, validmodexdim[i], validmodexdim[i+1]);
                swap_macro(tmp, validmodeydim[i], validmodeydim[i+1]);
            } // if
        } // for
    } while (!sorted);

    if (debugging)
    {
        fprintf(stderr, "BUILDSDL: Final sorted modelist:");
        for (i = 0; i < validmodecnt; i++)
            fprintf(stderr, " (%ldx%ld)", validmodexdim[i], validmodeydim[i]);
        fprintf(stderr, "\n");
    } // if

    // (*whew!*)
} // getvalidvesamodes


int VBE_setPalette(long start, long num, char *palettebuffer)
/*
 * (From Ken's docs:)
 *   Set (num) palette palette entries starting at (start)
 *   palette entries are in a 4-byte format in this order:
 *       0: Blue (0-63)
 *       1: Green (0-63)
 *       2: Red (0-63)
 *       3: Reserved
 *
 * Naturally, the bytes are in the reverse order that SDL wants them...
 *  More importantly, SDL wants the color elements in a range from 0-255,
 *  so we do a conversion.
 */
{
    SDL_Color fmt_swap[256];  // !!! used to be: [start + num];
    SDL_Color *sdlp = &fmt_swap[start];
    char *p = palettebuffer;
    int i;

    assert( (start + num) <= (sizeof (fmt_swap) / sizeof (SDL_Color)) );

    for (i = 0; i < num; i++)
    {
        sdlp->b = (Uint8) ((((float) *p++) / 63.0) * 255.0);
        sdlp->g = (Uint8) ((((float) *p++) / 63.0) * 255.0);
        sdlp->r = (Uint8) ((((float) *p++) / 63.0) * 255.0);
        sdlp->unused = *p++;   // This byte is unused in BUILD, too.
        sdlp++;
    } // for

    return(SDL_SetColors(surface, fmt_swap, start, num));
} // VBE_setPalette


int VBE_getPalette(long start, long num, char *palettebuffer)
{
    SDL_Color *sdlp = surface->format->palette->colors + start;
    char *p = palettebuffer + (start * 4);
    int i;

    for (i = 0; i < num; i++)
    {
        *p++ = (Uint8) ((((float) sdlp->b) / 255.0) * 63.0);
        *p++ = (Uint8) ((((float) sdlp->g) / 255.0) * 63.0);
        *p++ = (Uint8) ((((float) sdlp->r) / 255.0) * 63.0);
        *p++ = sdlp->unused;   // This byte is unused in both SDL and BUILD.
        sdlp++;
    } // for

    return(1);
} // VBE_getPalette


void _uninitengine(void)
{
   SDL_QuitSubSystem(SDL_INIT_VIDEO);
} // _uninitengine


void uninitvesa(void)
{
   SDL_QuitSubSystem(SDL_INIT_VIDEO);
} // uninitvesa


int setupmouse(void)
{
    SDL_GrabMode mode = SDL_GRAB_OFF;

    if (surface == NULL)
        return(0);

    if (mouse_grabbed)
        mode = SDL_GRAB_ON;

    SDL_WM_GrabInput(mode);
    SDL_ShowCursor(0);

    mouse_x = surface->w / 2;
    mouse_y = surface->h / 2;
    mouse_relative_x = mouse_relative_y = 0;

        // this global usually gets set by BUILD, but it's a one-shot
        //  deal, and we may not have an SDL surface at that point. --ryan.
    moustat = 1;

    return(1);
} // setupmouse


void readmousexy(short *x, short *y)
{
    if (x) *x = mouse_relative_x << 2;
    if (y) *y = mouse_relative_y << 2;

    mouse_relative_x = mouse_relative_y = 0;
} // readmousexy


void readmousebstatus(short *bstatus)
{
    if (bstatus)
        *bstatus = mouse_buttons;
} // readmousebstatus


static unsigned char mirrorcolor = 0;


void _nextpage(void)
{
    Uint32 ticks;

    handle_events();

    if (qsetmode != 200)
    {
        SDL_UpdateRect(surface, 0, 0, 0, 0);
        //SDL_Flip(surface);  // !!!
        return;
    } // if

    #ifdef USE_OPENGL
        if (surface->flags & SDL_OPENGL)
        {
            SDL_GL_SwapBuffers();
            if (debug_hall_of_mirrors)
            {
                dglClearColor3ub(mirrorcolor, 0, 0);
                mirrorcolor++;
            } // if
            dglClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            return;
        } // if
    #endif

    memcpy(surface->pixels, (const void *) frameplace, surface->w * surface->h);

    if (debug_hall_of_mirrors)
    {
        memset((void *) frameplace, mirrorcolor, surface->w * surface->h);
        mirrorcolor++;
    } // if

    SDL_UpdateRect(surface, 0, 0, 0, 0);
    //SDL_Flip(surface);  // !!!

    ticks = SDL_GetTicks();
    total_render_time = (ticks - last_render_ticks);
    if (total_render_time > 1000)
    {
        //printf("fps == (%.2f).\n", (double) (total_rendered_frames / ((double) total_render_time / 1000.0)));
        total_rendered_frames = 0;
        total_render_time = 1;
        last_render_ticks = ticks;
    } // if
    total_rendered_frames++;
} // _nextpage


unsigned char readpixel(long offset)
{
    return( *((unsigned char *) offset) );
}

void drawpixel(long offset, Uint8 pixel)
{
    *((unsigned char *) offset) = pixel;
}


// !!! These are incorrect.
void drawpixels(long offset, Uint16 pixels)
{
    Uint8 *surface_end;
    Uint16 *pos;

                printf("Blargh!\n");
                exit(91);

    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    surface_end = (((Uint8 *) surface->pixels) + (surface->w * surface->h)) - 2;
    pos = (Uint16 *) (((Uint8 *) surface->pixels) + offset);
    if ((pos >= (Uint16 *) surface->pixels) && (pos < (Uint16 *) surface_end))
        *pos = pixels;

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);
} // drawpixels


void drawpixelses(long offset, Uint32 pixelses)
{
    Uint8 *surface_end;
    Uint32 *pos;

                printf("Blargh!\n");
                exit(91);

    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    surface_end = (((Uint8 *)surface->pixels) + (surface->w * surface->h)) - 2;
    pos = (Uint32 *) (((Uint8 *) surface->pixels) + offset);
    if ((pos >= (Uint32 *) surface->pixels) && (pos < (Uint32 *) surface_end))
        *pos = pixelses;

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);
} // drawpixelses


// Fix this up The Right Way (TM) - DDOI
void setcolor16 (int col)
{
	drawpixel_color = col;
}

void drawpixel16(long offset)
{
    drawpixel(((long) surface->pixels + offset), drawpixel_color);
} // drawpixel16


void fillscreen16 (long offset, long color, long blocksize)
{
    Uint8 *surface_end;
    Uint8 *wanted_end;

    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    // Make this function pageoffset aware - DDOI
    if (!pageoffset) { 
	    offset = offset << 3;
	    offset += 640*336;
    }

    surface_end = (((Uint8 *) surface->pixels) + (surface->w * surface->h)) - 1;
    wanted_end = (((Uint8 *) surface->pixels) + offset) + blocksize;

    if (offset < 0)
        offset = 0;

    if (wanted_end > surface_end)
        blocksize = ((unsigned long) surface_end) - ((unsigned long) surface->pixels + offset);

    memset(((Uint8 *)surface->pixels) + offset, (int) color, blocksize);

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);

    SDL_UpdateRect(surface, 0, 0, 0, 0);
} // fillscreen16


/* Most of this line code is taken from Abrash's "Graphics Programming Blackbook".
Remember, sharing code is A Good Thing. AH */
inline void DrawHorizontalRun (char **ScreenPtr, int XAdvance, int RunLength, char Color)
{
    int i;
    char *WorkingScreenPtr = *ScreenPtr;

    for (i=0; i<RunLength; i++)
    {
        *WorkingScreenPtr = Color;
        WorkingScreenPtr += XAdvance;
    }
    WorkingScreenPtr += surface->w;
    *ScreenPtr = WorkingScreenPtr;
}

inline void DrawVerticalRun (char **ScreenPtr, int XAdvance, int RunLength, char Color)
{
    int i;
    char *WorkingScreenPtr = *ScreenPtr;

    for (i=0; i<RunLength; i++)
    {
      	*WorkingScreenPtr = Color;
    	WorkingScreenPtr += surface->w;
    }
    WorkingScreenPtr += XAdvance;
    *ScreenPtr = WorkingScreenPtr;
}

void drawline16(long XStart, long YStart, long XEnd, long YEnd, char Color)
{
    int Temp, AdjUp, AdjDown, ErrorTerm, XAdvance, XDelta, YDelta;
    int WholeStep, InitialPixelCount, FinalPixelCount, i, RunLength;
    char *ScreenPtr;
    long dx, dy;

    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

	dx = XEnd-XStart; dy = YEnd-YStart;
	if (dx >= 0)
	{
		if ((XStart > 639) || (XEnd < 0)) return;
		if (XStart < 0) { if (dy) YStart += scale(0-XStart,dy,dx); XStart = 0; }
		if (XEnd > 639) { if (dy) YEnd += scale(639-XEnd,dy,dx); XEnd = 639; }
	}
	else
	{
		if ((XEnd > 639) || (XStart < 0)) return;
		if (XEnd < 0) { if (dy) YEnd += scale(0-XEnd,dy,dx); XEnd = 0; }
		if (XStart > 639) { if (dy) YStart += scale(639-XStart,dy,dx); XStart = 639; }
	}
	if (dy >= 0)
	{
		if ((YStart >= ydim16) || (YEnd < 0)) return;
		if (YStart < 0) { if (dx) XStart += scale(0-YStart,dx,dy); YStart = 0; }
		if (YEnd >= ydim16) { if (dx) XEnd += scale(ydim16-1-YEnd,dx,dy); YEnd = ydim16-1; }
	}
	else
	{
		if ((YEnd >= ydim16) || (YStart < 0)) return;
		if (YEnd < 0) { if (dx) XEnd += scale(0-YEnd,dx,dy); YEnd = 0; }
		if (YStart >= ydim16) { if (dx) XStart += scale(ydim16-1-YStart,dx,dy); YStart = ydim16-1; }
	}

	// Make sure the status bar border draws correctly - DDOI
	if (!pageoffset) { YStart += 336; YEnd += 336; }

    /* We'll always draw top to bottom */
    if (YStart > YEnd) {
        Temp = YStart;
        YStart = YEnd;
        YEnd = Temp;
        Temp = XStart;
        XStart = XEnd;
        XEnd = Temp;
    }

    /* Point to the bitmap address first pixel to draw */
    ScreenPtr = ((Uint8 *) surface->pixels) + XStart + (surface->w * YStart);

    /* Figure out whether we're going left or right, and how far we're going horizontally */
    if ((XDelta = XEnd - XStart) < 0)
    {
        XAdvance = (-1);
        XDelta = -XDelta;
    } else {
        XAdvance = 1;
    }

    /* Figure out how far we're going vertically */
    YDelta = YEnd - YStart;

    /* Special cases: Horizontal, vertical, and diagonal lines */
    if (XDelta == 0)
    {
        for (i=0; i <= YDelta; i++)
        {
            *ScreenPtr = Color;
            ScreenPtr += surface->w;
        }

        UNLOCK_SURFACE_AND_RETURN;
    }
    if (YDelta == 0)
    {
    	for (i=0; i <= XDelta; i++)
    	{
      	    *ScreenPtr = Color;
    	    ScreenPtr += XAdvance;
    	}
        UNLOCK_SURFACE_AND_RETURN;
    }
    if (XDelta == YDelta)
    {
    	for (i=0; i <= XDelta; i++)
        {
            *ScreenPtr = Color;
            ScreenPtr += XAdvance + surface->w;
        }
        UNLOCK_SURFACE_AND_RETURN;
    }

    /* Determine whether the line is X or Y major, and handle accordingly */
    if (XDelta >= YDelta) /* X major line */
    {
        WholeStep = XDelta / YDelta;
        AdjUp = (XDelta % YDelta) * 2;
        AdjDown = YDelta * 2;
        ErrorTerm = (XDelta % YDelta) - (YDelta * 2);

        InitialPixelCount = (WholeStep / 2) + 1;
        FinalPixelCount = InitialPixelCount;

        if ((AdjUp == 0) && ((WholeStep & 0x01) == 0)) InitialPixelCount--;
        if ((WholeStep & 0x01) != 0) ErrorTerm += YDelta;

        DrawHorizontalRun(&ScreenPtr, XAdvance, InitialPixelCount, Color);

        for (i=0; i<(YDelta-1); i++)
        {
            RunLength = WholeStep;
            if ((ErrorTerm += AdjUp) > 0)
            {
        	RunLength ++;
        	ErrorTerm -= AdjDown;
            }

            DrawHorizontalRun(&ScreenPtr, XAdvance, RunLength, Color);
         }

         DrawHorizontalRun(&ScreenPtr, XAdvance, FinalPixelCount, Color);

         UNLOCK_SURFACE_AND_RETURN;
    } else {	/* Y major line */
    	WholeStep = YDelta / XDelta;
    	AdjUp = (YDelta % XDelta) * 2;
    	AdjDown = XDelta * 2;
        ErrorTerm = (YDelta % XDelta) - (XDelta * 2);
        InitialPixelCount = (WholeStep / 2) + 1;
        FinalPixelCount = InitialPixelCount;

        if ((AdjUp == 0) && ((WholeStep & 0x01) == 0)) InitialPixelCount --;
        if ((WholeStep & 0x01) != 0) ErrorTerm += XDelta;

        DrawVerticalRun(&ScreenPtr, XAdvance, InitialPixelCount, Color);

        for (i=0; i<(XDelta-1); i++)
        {
            RunLength = WholeStep;
            if ((ErrorTerm += AdjUp) > 0)
            {
            	RunLength ++;
            	ErrorTerm -= AdjDown;
            }

            DrawVerticalRun(&ScreenPtr, XAdvance, RunLength, Color);
        }

        DrawVerticalRun(&ScreenPtr, XAdvance, FinalPixelCount, Color);
        UNLOCK_SURFACE_AND_RETURN;
     }
} // drawline16


void clear2dscreen(void)
{
    SDL_Rect rect;

    rect.x = rect.y = 0;
    rect.w = surface->w;

	if (qsetmode == 350)
        rect.h = 350;
	else if (qsetmode == 480)
	{
		if (ydim16 <= 336)
            rect.h = 336;
        else
            rect.h = 480;
	} // else if

    SDL_FillRect(surface, &rect, 0);
} // clear2dscreen


void _idle(void)
{
    handle_events();
    SDL_Delay(1);
} // _idle

void *_getVideoBase(void)
{
    return((void *) surface->pixels);
}

void setactivepage(long dapagenum)
{
	// Is this really still needed? - DDOI
    //fprintf(stderr, "%s, line %d; setactivepage(): STUB.\n", __FILE__, __LINE__);
} // setactivepage

void limitrate(void)
{
    // this is a no-op in SDL. It was for buggy VGA cards in DOS.
} // limitrate

Uint32 _timer_catcher(Uint32 interval, void *bleh)
{
    timerhandler();
    return(1);
} // _timer_catcher

void inittimer(void)
{
    SDL_ClearError();
    primary_timer = SDL_AddTimer(1000 / PLATFORM_TIMER_HZ, _timer_catcher, NULL);
    if (primary_timer == NULL)
    {
        fprintf(stderr, "BUILDSDL: -ERROR- Problem initializing primary timer!\n");
        fprintf(stderr, "BUILDSDL:  Reason: [%s]\n", SDL_GetError());
        SDL_Quit();
        exit(2);
    } // if
}

void uninittimer(void)
{
    if (primary_timer != NULL)
    {
        SDL_RemoveTimer(primary_timer);
        primary_timer = NULL;
    } // if
}

void _initkeys(void)
{
    // does nothing in SDL. Key input handling is set up elsewhere.
    // !!! why not here?
}

void uninitkeys(void)
{
    // does nothing in SDL. Key input handling is set up elsewhere.
}

void initsb(char dadigistat, char damusistat, long dasamplerate, char danumspeakers, char dabytespersample, char daintspersec, char daquality)
{
    audio_disabled = (SDL_Init(SDL_INIT_AUDIO) == -1);

    if (audio_disabled)
    {
        fprintf(stderr, "BUILDSDL: SDL_Init(SDL_INIT_AUDIO) failed!\n");
        fprintf(stderr, "BUILDSDL: SDL_GetError() says \"%s\".\n", SDL_GetError());
        fprintf(stderr, "BUILDSDL: We'll continue without sound.\n");
        audio_disabled = 1;
        return;
    } // if

    

} // initsb

void uninitsb(void)
{
    fprintf(stderr, "%s, line %d; uninitsb(): STUB.\n", __FILE__, __LINE__);
} // uninitsb

int loadsong(char *filename)
{
    fprintf(stderr, "%s, line %d; loadsong(): STUB.\n", __FILE__, __LINE__);
    return 0;
} // loadsong

void musicon(void)
{
    fprintf(stderr, "%s, line %d; musicon(): STUB.\n", __FILE__, __LINE__);
} // musicon

void musicoff(void)
{
    fprintf(stderr, "%s, line %d; musicoff(): STUB.\n", __FILE__, __LINE__);
} // musicoff

void wsayfollow(char *dafilename, long dafreq, long davol, long *daxplc, long *dayplc, char followstat)
{
    fprintf(stderr, "%s, line %d; wsayfollow(): STUB.\n", __FILE__, __LINE__);
} // wsayfollow    

void wsay(char *dafilename, long dafreq, long volume1, long volume2)
{
    fprintf(stderr, "%s, line %d; wsay(): STUB.\n", __FILE__, __LINE__);
} // wsay

void preparesndbuf(void)
{
    fprintf(stderr,"%s, line %d; preparesndbuf(): STUB.\n", __FILE__, __LINE__);
} // preparesndbuf

void setears(long daposx, long daposy, long daxvect, long dayvect)
{
//    fprintf(stderr, "%s, line %d; setears(): STUB.\n", __FILE__, __LINE__);
} // setears

void set16color_palette (void)
{
	// Backup old palette
	//VBE_getPalette (0, 16, (char *)&backup_palette);
	memcpy (&backup_palette, &palette, 16*3);

	// Set new palette
	//VBE_setPalette (0, 16, (char *)&egapalette);
	memcpy (&palette, &egapalette, 16*3);
	in_egapalette = 1;
}

void restore256_palette (void)
{
	//VBE_setPalette (0, 16, (char *)&backup_palette);
	memcpy (&palette, &backup_palette, 16*3);
	in_egapalette = 0;
}

unsigned long getticks()
{
    return(SDL_GetTicks());
} // getticks

