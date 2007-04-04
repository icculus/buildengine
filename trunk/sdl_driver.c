/*
 * An SDL replacement for BUILD's VESA code.
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
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifndef PLATFORM_WIN32
#include <sys/param.h>
#endif
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
#endif

/* need VirtualProtect() from win32 API... */
#if ((defined PLATFORM_WIN32) && (defined USE_I386_ASM))
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

typedef enum
{
    RENDERER_SOFTWARE,
    RENDERER_OPENGL3D,
    RENDERER_TOTAL
} sdl_renderer_type;

const char *renderer_name[RENDERER_TOTAL];

#define ENVRSTR_RENDERER_SOFTWARE  "software"
#define ENVRSTR_RENDERER_OPENGL3D  "opengl3d"

static sdl_renderer_type renderer = RENDERER_SOFTWARE;

/* !!! ugh. Clean this up. */
#if (!defined __WATCOMC__)
#include "a.h"
#else
extern long setvlinebpl(long);
#pragma aux setvlinebpl parm [eax];
#endif  /* __WATCOMC__ */

#include "cache1d.h"


/*
 * !!! I'd like this to be temporary. --ryan.
 * !!!  That is, the self-modifying part, so I can ditch the mprotect() stuff.
 */
#if ((defined PLATFORM_UNIX) && (defined USE_I386_ASM))

#include <sys/mman.h>
#include <limits.h>

#ifndef PAGESIZE
#define PAGESIZE 4096
#endif

#endif

#ifdef PLATFORM_MACOSX
#include <CoreServices/CoreServices.h>
#endif


/*
 * !!! remove the surface_end checks, for speed's sake. They are a
 * !!!  needed safety right now. --ryan.
 */

#define DEFAULT_MAXRESWIDTH  1600
#define DEFAULT_MAXRESHEIGHT 1200


#define UNLOCK_SURFACE_AND_RETURN  if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface); return;

static unsigned char tempbuf[MAXWALLS];
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


int _argc = 0;
char **_argv = NULL;

    /* !!! move these elsewhere? */
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
/* so we can make use of setcolor16()... - DDOI */
static unsigned char drawpixel_color=0;
/* These hold the colors for the 256 color palette when in 16-color mode - DDOI */
static char backup_palette[48];
static int in_egapalette = 0;
/* The standard EGA palette in BUILD format - DDOI */
static char egapalette[] = { 0, 0, 0,
			    0, 0, 42,
			    0, 42, 0,
			    0, 42, 42,
			    42, 0, 0,
			    42, 0, 42,
			    42, 21, 0,
			    42, 42, 42,
			    21, 21, 21,
			    21, 21, 63,
			    21, 63, 21,
			    21, 63, 63,
			    63, 21, 21,
			    63, 21, 63,
			    63, 63, 21,
			    63, 63, 63
			   };

static unsigned int scancodes[SDLK_LAST];

static long last_render_ticks = 0;
long total_render_time = 1;
long total_rendered_frames = 0;

static char *titlelong = NULL;
static char *titleshort = NULL;

void restore256_palette (void);
void set16color_palette (void);


static FILE *_sdl_debug_file = NULL;

#ifdef DC
#define sdldebug(fmt,args...) printf("BUILDSDL: " fmt "\n",##args)
#else
static __inline void __out_sdldebug(const char *subsystem,
                                  const char *fmt, va_list ap)
{
    fprintf(_sdl_debug_file, "%s: ", subsystem);
    vfprintf(_sdl_debug_file, fmt, ap);
    fprintf(_sdl_debug_file, "\n");
    fflush(_sdl_debug_file);
} /* __out_sdldebug */


static void sdldebug(const char *fmt, ...)
{
    va_list ap;

    if (_sdl_debug_file)
    {
        va_start(ap, fmt);
        __out_sdldebug("BUILDSDL", fmt, ap);
        va_end(ap);
    } /* if */
} /* sdldebug */
#endif

#if (defined USE_OPENGL)
void sgldebug(const char *fmt, ...)
{
    va_list ap;

    if (_sdl_debug_file)
    {
        va_start(ap, fmt);
        __out_sdldebug("BUILDSDL/GL", fmt, ap);
        va_end(ap);
    } /* if */
} /* sgldebug */
#endif


static void __append_sdl_surface_flag(SDL_Surface *_surface, char *str,
                                      size_t strsize, Uint32 flag,
                                      const char *flagstr)
{
    if (_surface->flags & flag)
    {
        if ( (strlen(str) + strlen(flagstr)) >= (strsize - 1) )
            strcpy(str + (strsize - 5), " ...");
        else
            strcat(str, flagstr);
    } /* if */
} /* append_sdl_surface_flag */


#define append_sdl_surface_flag(a, b, c, fl) __append_sdl_surface_flag(a, b, c, fl, " " #fl)
#define print_tf_state(str, val) sdldebug("%s: {%s}", str, (val) ? "true" : "false" )

static void output_surface_info(SDL_Surface *_surface)
{
    const SDL_VideoInfo *info;
    char f[256];

    if (!_sdl_debug_file)
        return;

    if (_surface == NULL)
    {
        sdldebug("-WARNING- You've got a NULL screen surface!");
    }
    else
    {
        f[0] = '\0';
        sdldebug("screen surface is (%dx%dx%dbpp).",
                _surface->w, _surface->h, _surface->format->BitsPerPixel);

        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_SWSURFACE);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_HWSURFACE);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_ASYNCBLIT);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_ANYFORMAT);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_HWPALETTE);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_DOUBLEBUF);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_FULLSCREEN);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_OPENGL);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_OPENGLBLIT);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_RESIZABLE);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_NOFRAME);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_HWACCEL);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_SRCCOLORKEY);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_RLEACCELOK);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_RLEACCEL);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_SRCALPHA);
        append_sdl_surface_flag(_surface, f, sizeof (f), SDL_PREALLOC);

        if (f[0] == '\0')
            strcpy(f, " (none)");

        sdldebug("New vidmode flags:%s", f);

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

        sdldebug("video memory: (%d)", info->video_mem);
    } /* else */
} /* output_surface_info */


static void output_driver_info(void)
{
    char buffer[256];

    if (!_sdl_debug_file)
        return;

    sdldebug("Using BUILD renderer \"%s\".", renderer_name[renderer]);

    if (SDL_VideoDriverName(buffer, sizeof (buffer)) == NULL)
    {
        sdldebug("-WARNING- SDL_VideoDriverName() returned NULL!");
    } /* if */
    else
    {
        sdldebug("Using SDL video driver \"%s\".", buffer);
    } /* else */
} /* output_driver_info */


static Uint8 *get_framebuffer(void)
{
    assert(renderer != RENDERER_OPENGL3D);

    if (renderer == RENDERER_SOFTWARE)
        return((Uint8 *) surface->pixels);
    else if (renderer == RENDERER_OPENGL3D)
        return((Uint8 *) frameplace);

    return(NULL);
} /* get_framebuffer */


int using_opengl(void)
{
    return(renderer == RENDERER_OPENGL3D);
} /* using_opengl */


/*
 * !!! This is almost an entire copy of the original setgamemode().
 * !!!  Figure out what is needed for just 2D mode, and separate that
 * !!!  out. Then, place the original setgamemode() back into engine.c,
 * !!!  and remove our simple implementation (and this function.)
 * !!!  Just be sure to keep the non-DOS things, like the window's
 * !!!  titlebar caption.   --ryan.
 */
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

    if (renderer == RENDERER_OPENGL3D)
        frameplace = (long) NULL;
    else
        frameplace = (long) ( ((Uint8 *) surface->pixels) );

  	if (screen != NULL)
   	{
       	if (screenalloctype == 0) kkfree((void *)screen);
   	    if (screenalloctype == 1) suckcache((long *)screen);
   		screen = NULL;
   	} /* if */

    if (davidoption != -1)
    {
    	switch(vidoption)
    	{
    		case 1:i = xdim*ydim; break;
    		case 2: xdim = 320; ydim = 200; i = xdim*ydim; break;
    		case 6: xdim = 320; ydim = 200; i = 131072; break;
    		default: assert(0);
    	}
    	j = ydim*4*sizeof(long);  /* Leave room for horizlookup&horizlookup2 */

    	screenalloctype = 0;
	    if ((screen = (char *)kkmalloc(i+(j<<1))) == NULL)
    	{
	    	 allocache((long *)&screen,i+(j<<1),&permanentlock);
    		 screenalloctype = 1;
    	}

        /* !!! FIXME: Should screen get allocated above if in opengl3d mode? */

        if (renderer == RENDERER_OPENGL3D)
            frameplace = (long) NULL;
        else
        {
            frameplace = FP_OFF(screen);
          	horizlookup = (long *)(frameplace+i);
           	horizlookup2 = (long *)(frameplace+i+j);
        } /* else */
    } /* if */

    j = 0;
  	for(i = 0; i <= ydim; i++)
    {
        ylookup[i] = j;
        j += bytesperline;
    } /* for */

   	horizycent = ((ydim*4)>>1);

		/* Force drawrooms to call dosetaspect & recalculate stuff */
	oxyaspect = oxdimen = oviewingrange = -1;

	setvlinebpl(bytesperline);

    if (davidoption != -1)
    {
    	setview(0L,0L,xdim-1,ydim-1);
    	clearallviews(0L);
    } /* if */

	setbrightness((char) curbrightness, (unsigned char *) &palette[0]);

	if (searchx < 0) { searchx = halfxdimen; searchy = (ydimen>>1); }
} /* init_new_res_vars */


static void go_to_new_vid_mode(int vidoption, int w, int h)
{
    getvalidvesamodes();
    SDL_ClearError();
    surface = SDL_SetVideoMode(w, h, 8, sdl_flags);
    if (surface == NULL)
    {
        fprintf(stderr, "BUILDSDL: Failed to set %dx%d video mode!\n"
                        "BUILDSDL: SDL_Error() says [%s].\n",
                        w, h, SDL_GetError());
        SDL_Quit();
        exit(13);
    } /* if */

    output_surface_info(surface);
    init_new_res_vars(vidoption);
} /* go_to_new_vid_mode */


static __inline int sdl_mouse_button_filter(SDL_MouseButtonEvent const *event)
{
        /*
         * What bits BUILD expects:
         *  0 left button pressed if 1
         *  1 right button pressed if 1
         *  2 middle button pressed if 1
         *
         *   (That is, this is what Int 33h (AX=0x05) returns...)
         *
         *  additionally 3&4 are set for the mouse wheel
         */
    Uint8 button = event->button;
    if (button >= sizeof (mouse_buttons) * 8)
        return(0);

    if (button == SDL_BUTTON_RIGHT)
        button = SDL_BUTTON_MIDDLE;
    else if (button == SDL_BUTTON_MIDDLE)
        button = SDL_BUTTON_RIGHT;

    if (((const SDL_MouseButtonEvent*)event)->state)
        mouse_buttons |= 1<<(button-1);
    else if (button != 4 && button != 5)
        mouse_buttons ^= 1<<(button-1);

#if 0
    Uint8 bmask = SDL_GetMouseState(NULL, NULL);
    mouse_buttons = 0;
    if (bmask & SDL_BUTTON_LMASK) mouse_buttons |= 1;
    if (bmask & SDL_BUTTON_RMASK) mouse_buttons |= 2;
    if (bmask & SDL_BUTTON_MMASK) mouse_buttons |= 4;
#endif

    return(0);
} /* sdl_mouse_up_filter */


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
    } /* if */
    else
    {
        if (mouse_grabbed)
        {
          	mouse_relative_x += event->motion.xrel;
       	        mouse_relative_y += event->motion.yrel;
           	mouse_x += mouse_relative_x;
           	mouse_y += mouse_relative_y;
        } /* if */
        else
        {
          	mouse_relative_x += event->motion.x - mouse_x;
           	mouse_relative_y += event->motion.y - mouse_y;
           	mouse_x = event->motion.x;
           	mouse_y = event->motion.y;
        } /* else */
    } /* else */

   	if (mouse_x < 0) mouse_x = 0;
   	if (mouse_x > surface->w) mouse_x = surface->w;
   	if (mouse_y < 0) mouse_y = 0;
   	if (mouse_y > surface->h) mouse_y = surface->h;

    return(0);
} /* sdl_mouse_motion_filter */


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
    SDL_Rect clip;
    Uint32 tmpflags = 0;
    int w = 0;
    int h = 0;
    int bpp = 0;
    int grabmouse = (SDL_WM_GrabInput(SDL_GRAB_QUERY) == SDL_GRAB_ON);
    int showmouse = SDL_ShowCursor(-1);

#if 0
    SDL_Color *palette = NULL;
    int ncolors = 0;
#endif

    sdldebug("attempting to toggle fullscreen flag...");

    if ( (!surface) || (!(*surface)) )  /* don't try if there's no surface. */
    {
        sdldebug("Null surface (?!). Not toggling fullscreen flag.");
        return(0);
    } /* if */

    if (SDL_WM_ToggleFullScreen(*surface))
    {
        sdldebug("SDL_WM_ToggleFullScreen() seems to work on this system.");
        if (flags)
            *flags ^= SDL_FULLSCREEN;
        return(1);
    } /* if */

#if !PLATFORM_MACOSX
    if ( !(SDL_GetVideoInfo()->wm_available) )
    {
        sdldebug("No window manager. Not toggling fullscreen flag.");
        return(0);
    } /* if */
#endif

    sdldebug("toggling fullscreen flag The Hard Way...");
    tmpflags = (*surface)->flags;
    w = (*surface)->w;
    h = (*surface)->h;
    bpp = (*surface)->format->BitsPerPixel;

    if (flags == NULL)  /* use the surface's flags. */
        flags = &tmpflags;

    SDL_GetClipRect(*surface, &clip);

        /* save the contents of the screen. */
    if ( (!(tmpflags & SDL_OPENGL)) && (!(tmpflags & SDL_OPENGLBLIT)) )
    {
        framesize = (w * h) * ((*surface)->format->BytesPerPixel);
        pixels = malloc(framesize);
        if (pixels == NULL)
            return(0);
        memcpy(pixels, (*surface)->pixels, framesize);
    } /* if */

#if 0
    if ((*surface)->format->palette != NULL)
    {
        ncolors = (*surface)->format->palette->ncolors;
        palette = malloc(ncolors * sizeof (SDL_Color));
        if (palette == NULL)
        {
            free(pixels);
            return(0);
        } /* if */
        memcpy(palette, (*surface)->format->palette->colors,
               ncolors * sizeof (SDL_Color));
    } /* if */
#endif

    if (grabmouse)
        SDL_WM_GrabInput(SDL_GRAB_OFF);

    SDL_ShowCursor(1);

    *surface = SDL_SetVideoMode(w, h, bpp, (*flags) ^ SDL_FULLSCREEN);

    if (*surface != NULL)
        *flags ^= SDL_FULLSCREEN;

    else  /* yikes! Try to put it back as it was... */
    {
        *surface = SDL_SetVideoMode(w, h, bpp, tmpflags);
        if (*surface == NULL)  /* completely screwed. */
        {
            if (pixels != NULL)
                free(pixels);
            if (palette != NULL)
                free(palette);
            return(0);
        } /* if */
    } /* if */

    /* Unfortunately, you lose your OpenGL image until the next frame... */

    if (pixels != NULL)
    {
        memcpy((*surface)->pixels, pixels, framesize);
        free(pixels);
    } /* if */

#if 0
    if (palette != NULL)
    {
            /* !!! FIXME : No idea if that flags param is right. */
        SDL_SetPalette(*surface, SDL_LOGPAL, palette, 0, ncolors);
        free(palette);
    } /* if */
#else
	setbrightness((char) curbrightness, (unsigned char *) &palette[0]);
#endif

    SDL_SetClipRect(*surface, &clip);

    if (grabmouse)
        SDL_WM_GrabInput(SDL_GRAB_ON);

    SDL_ShowCursor(showmouse);

    output_surface_info(*surface);

    return(1);
} /* attempt_fullscreen_toggle */


    /*
     * The windib driver can't alert us to the keypad enter key, which
     *  Ken's code depends on heavily. It sends it as the same key as the
     *  regular return key. These users will have to hit SHIFT-ENTER,
     *  which we check for explicitly, and give the engine a keypad enter
     *  enter event.
     */
static __inline int handle_keypad_enter_hack(const SDL_Event *event)
{
    static int kp_enter_hack = 0;
    int retval = 0;

    if (event->key.keysym.sym == SDLK_RETURN)
    {
        if (event->key.state == SDL_PRESSED)
        {
            if (event->key.keysym.mod & KMOD_SHIFT)
            {
                kp_enter_hack = 1;
                lastkey = scancodes[SDLK_KP_ENTER];
                retval = 1;
            } /* if */
        } /* if */

        else  /* key released */
        {
            if (kp_enter_hack)
            {
                kp_enter_hack = 0;
                lastkey = scancodes[SDLK_KP_ENTER];
                retval = 1;
            } /* if */
        } /* if */
    } /* if */

    return(retval);
} /* handle_keypad_enter_hack */


static int sdl_key_filter(const SDL_Event *event)
{
    SDL_GrabMode grab_mode = SDL_GRAB_OFF;
    int extended;
    int tmp;

    #if PLATFORM_MACOSX  /* Apple-Q */
    {
        static Uint32 cmdqticks = 0;
        if ( (event->key.keysym.sym == SDLK_q) &&
             (event->key.state == SDL_PRESSED) &&
             (event->key.keysym.mod & KMOD_META) )
        {
            Uint32 t = SDL_GetTicks();
            if (t - cmdqticks < 500)  /* 2 hits within .5 second? */
            {
                SDL_Quit();
                exit(0);   
            }
            cmdqticks = t;
        }
    }
    #endif


    if ( (event->key.keysym.sym == SDLK_g) &&
         (event->key.state == SDL_PRESSED) &&
         (event->key.keysym.mod & KMOD_CTRL) )
    {
        mouse_grabbed = ((mouse_grabbed) ? 0 : 1);
        if (mouse_grabbed)
            grab_mode = SDL_GRAB_ON;
        SDL_WM_GrabInput(grab_mode);
        return(0);
    } /* if */

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
    } /* if */

    if (!handle_keypad_enter_hack(event))
        lastkey = scancodes[event->key.keysym.sym];

    if (lastkey == 0x0000)   /* No DOS equivalent defined. */
        return(0);

    extended = ((lastkey & 0xFF00) >> 8);
    if (extended != 0)
    {
        lastkey = extended;
        keyhandler();
        lastkey = (scancodes[event->key.keysym.sym] & 0xFF);
    } /* if */

    if (event->key.state == SDL_RELEASED)
        lastkey += 128;  /* +128 signifies that the key is released in DOS. */

    keyhandler();
    return(0);
} /* sdl_key_filter */


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
	    return(sdl_mouse_button_filter((const SDL_MouseButtonEvent*)event));
        case SDL_QUIT:
            /* !!! rcg TEMP */
            SDL_Quit();
            exit(0);   
    } /* switch */

    return(1);
} /* root_sdl_event_filter */


static void handle_events(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
        root_sdl_event_filter(&event);
} /* handle_events */


/* bleh...public version... */
void _handle_events(void)
{
    handle_events();
} /* _handle_events */


static SDL_Joystick *joystick = NULL;
void _joystick_init(void)
{
    const char *envr = getenv(BUILD_SDLJOYSTICK);
    int favored = 0;
    int numsticks;
    int i;

    if (joystick != NULL)
    {
        sdldebug("Joystick appears to be already initialized.");
        sdldebug("...deinitializing for stick redetection...");
        _joystick_deinit();
    } /* if */

    if ((envr != NULL) && (strcmp(envr, "none") == 0))
    {
        sdldebug("Skipping joystick detection/initialization at user request");
        return;
    } /* if */

    sdldebug("Initializing SDL joystick subsystem...");
    sdldebug(" (export environment variable BUILD_SDLJOYSTICK=none to skip)");

    if (SDL_Init(SDL_INIT_JOYSTICK) != 0)
    {
        sdldebug("SDL_Init(SDL_INIT_JOYSTICK) failed: [%s].", SDL_GetError());
        return;
    } /* if */

    numsticks = SDL_NumJoysticks();
    sdldebug("SDL sees %d joystick%s.", numsticks, numsticks == 1 ? "" : "s");
    if (numsticks == 0)
        return;

    for (i = 0; i < numsticks; i++)
    {
        const char *stickname = SDL_JoystickName(i);
        if ((envr != NULL) && (strcmp(envr, stickname) == 0))
            favored = i;

        sdldebug("Stick #%d: [%s]", i, stickname);
    } /* for */

    sdldebug("Using Stick #%d.", favored);
    if ((envr == NULL) && (numsticks > 1))
        sdldebug("Set BUILD_SDLJOYSTICK to one of the above names to change.");

    joystick = SDL_JoystickOpen(favored);
    if (joystick == NULL)
    {
        sdldebug("Joystick #%d failed to init: %s", favored, SDL_GetError());
        return;
    } /* if */

    sdldebug("Joystick initialized. %d axes, %d buttons, %d hats, %d balls.",
              SDL_JoystickNumAxes(joystick), SDL_JoystickNumButtons(joystick),
              SDL_JoystickNumHats(joystick), SDL_JoystickNumBalls(joystick));

    SDL_JoystickEventState(SDL_QUERY);
} /* _joystick_init */


void _joystick_deinit(void)
{
    if (joystick != NULL)
    {
        sdldebug("Closing joystick device...");
        SDL_JoystickClose(joystick);
        sdldebug("Joystick device closed. Deinitializing SDL subsystem...");
        SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
        sdldebug("SDL joystick subsystem deinitialized.");
        joystick = NULL;
    } /* if */
} /* _joystick_deinit */


int _joystick_update(void)
{
    if (joystick == NULL)
        return(0);

    SDL_JoystickUpdate();
    return(1);
} /* _joystick_update */


int _joystick_axis(int axis)
{
    if (joystick == NULL)
        return(0);

    return(SDL_JoystickGetAxis(joystick, axis));
} /* _joystick_axis */

int _joystick_hat(int hat)
{
    if (joystick == NULL)
    {   
        return(-1);
    }

    return(SDL_JoystickGetHat(joystick, hat));
} /* _joystick_axis */

int _joystick_button(int button)
{
    if (joystick == NULL)
        return(0);

    return(SDL_JoystickGetButton(joystick, button) != 0);
} /* _joystick_button */


unsigned char _readlastkeyhit(void)
{
    return(lastkey);
} /* _readlastkeyhit */


/* !!! I'd like this to be temporary. --ryan. */
#if (defined USE_I386_ASM)

#  if (defined PLATFORM_UNIX)
#    define PROT_R_W_X (PROT_READ | PROT_WRITE | PROT_EXEC)

#  elif (defined PLATFORM_WIN32)
#    ifndef PAGESIZE
#      define PAGESIZE 4096
#    endif
#    define PROT_R_W_X PAGE_EXECUTE_READWRITE

     static int mprotect(void *ptr, size_t len, int prot)
     {
         BOOL rc;
         DWORD old = 0;
         rc = VirtualProtect(ptr, len, prot, &old);
         return(rc == 0);
     }

#endif

#ifdef USE_I386_ASM
int mprotect_align(const void *addr, size_t len, int prot)
{
    int retval;
    unsigned long l = (unsigned long) addr;
    l -= (l % PAGESIZE);
    retval = mprotect((void *) l, len * 2, prot);
    assert(retval == 0);
    return(retval);
} /* mprotect_align */


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
} /* unprotect_ASM_pages */
#endif


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


static __inline void init_debugging(void)
{
    const char *envr = getenv(BUILD_SDLDEBUG); 

    debug_hall_of_mirrors = (getenv(BUILD_HALLOFMIRRORS) != NULL);

    if (_sdl_debug_file != NULL)
    {
        fclose(_sdl_debug_file);
        _sdl_debug_file = NULL;
    } /* if */

    if (envr != NULL)
    {
        if (strcmp(envr, "-") == 0)
	    _sdl_debug_file = stdout;
        else
            _sdl_debug_file = fopen(envr, "w");

        if (_sdl_debug_file == NULL)
            printf("BUILDSDL: -WARNING- Could not open debug file!\n");
        else
            setbuf(_sdl_debug_file, NULL);
    } /* if */
} /* init_debugging */


#if (!defined __DATE__)
#define __DATE__ "a long, long time ago"
#endif

static __inline void output_sdl_versions(void)
{
    const SDL_version *linked_ver = SDL_Linked_Version();
    SDL_version compiled_ver;

    SDL_VERSION(&compiled_ver);

    sdldebug("SDL display driver for the BUILD engine initializing.");
    sdldebug("  sdl_driver.c by Ryan C. Gordon (icculus@clutteredmind.org).");
    sdldebug("Compiled %s against SDL version %d.%d.%d ...", __DATE__,
                compiled_ver.major, compiled_ver.minor, compiled_ver.patch);
    sdldebug("Linked SDL version is %d.%d.%d ...",
                linked_ver->major, linked_ver->minor, linked_ver->patch);
} /* output_sdl_versions */


static int in_vmware = 0;
static __inline void detect_vmware(void)
{
#if 1
    in_vmware = 0;  /* oh well. */
#else
    /* !!! need root access to touch i/o ports on Linux. */
    #if (!defined __linux__)
        in_vmware = (int) is_vmware_running();
    #endif
    sdldebug("vmWare %s running.", (in_vmware) ? "is" : "is not");
#endif
} /* detect_vmware */


/* lousy -ansi flag.  :) */
static char *string_dupe(const char *str)
{
    char *retval = malloc(strlen(str) + 1);
    if (retval != NULL)
        strcpy(retval, str);
    return(retval);
} /* string_dupe */


static void set_sdl_renderer(void)
{
    const char *envr = getenv(BUILD_RENDERER);

#ifdef USE_OPENGL
    int need_opengl_lib = 1;
#endif

    if ((envr == NULL) || (strcmp(envr, ENVRSTR_RENDERER_SOFTWARE) == 0))
        renderer = RENDERER_SOFTWARE;

#ifdef USE_OPENGL
#if 0
    else if (strcmp(envr, ENVRSTR_RENDERER_OPENGL3D) == 0)
    {
        renderer = RENDERER_OPENGL3D;
        need_opengl_lib = 1;
    } /* else if */
#endif

#endif

    else
    {
        fprintf(stderr,
                "BUILDSDL: \"%s\" in the %s environment var is not available.\n",
                envr, BUILD_RENDERER);
        _exit(1);
    } /* else */

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
    {
        fprintf(stderr, "BUILDSDL: SDL_Init() failed!\n");
        fprintf(stderr, "BUILDSDL: SDL_GetError() says \"%s\".\n", SDL_GetError());
        exit(1);
    } /* if */

#ifdef USE_OPENGL
    if (need_opengl_lib)
    {
        if (opengl_load_library() == -1)
        {
            SDL_Quit();
            fprintf(stderr, "BUILDSDL/GL: Failed to load OpenGL library!\n");
            if (getenv(BUILD_SDLDEBUG) == NULL)
            {
                fprintf(stderr, "BUILDSDL/GL: Try setting environment variable"
                                " %s for more info.\n", BUILD_SDLDEBUG);
            } /* if */
            _exit(42);
        } /* if */
    } /* if */
#endif

} /* set_sdl_renderer */


static void init_renderer_names(void)
{
    memset((void *) renderer_name, '\0', sizeof (renderer_name));
    renderer_name[RENDERER_SOFTWARE] = "RENDERER_SOFTWARE";
    renderer_name[RENDERER_OPENGL3D] = "RENDERER_OPENGL3D";
} /* init_renderer_names */


void set_splash(void)
{
    SDL_Surface *screen;
    SDL_Surface *bmp = SDL_LoadBMP("splash.bmp");
    if (bmp == NULL)
        return;

    putenv("SDL_VIDEO_WINDOW_POS=center");
    screen  = SDL_SetVideoMode(bmp->w, bmp->h, 0, SDL_NOFRAME);
    putenv("SDL_VIDEO_WINDOW_POS=nopref");

    if (screen != NULL)
    {
        SDL_BlitSurface(bmp, NULL, screen, NULL);
        SDL_Flip(screen);
    }

    SDL_FreeSurface(bmp);
} /* set_splash */


void _platform_init(int argc, char **argv, const char *title, const char *icon)
{
    #if (defined PLATFORM_MACOSX)
    char buf[MAXPATHLEN];
    char realbuf[MAXPATHLEN];
    long cpufeature = 0;
    OSErr err;

	has_altivec = 0;
    err = Gestalt(gestaltPowerPCProcessorFeatures, &cpufeature);
    if (err == noErr)
    {
        if ((1 << gestaltPowerPCHasVectorInstructions) & cpufeature)
	       has_altivec = 1;
    } /* if */

    /* deal with Application Bundles on MacOS X... */
    if ((argv[0] != NULL) && (strchr(argv[0], '/') != NULL))
        strcpy(buf, argv[0]);
    else
    {
        if ((getcwd(buf, sizeof (buf)) == NULL) || (strcmp(buf, "/") == 0))
            buf[0] = '\0'; /* oh well. */
    } /* else */

    if (buf[0])
    {
        buf[sizeof (buf) - 1] = '\0';
        if (realpath(buf, realbuf) != NULL)
        {
            char *ptr = strstr(realbuf, "/Contents/MacOS/");
            if (ptr != NULL)
            {
                *ptr = '\0';  /* chop off bundle dirs... */
                chdir(realbuf);
            } /* if */
        } /* if */
    } /* if */
    #endif

    _argc = argc;
    _argv = argv;

    init_renderer_names();

    init_debugging();

    #if (defined USE_I386_ASM)
        unprotect_ASM_pages();
    #endif

    if (title == NULL)
        title = "BUILD";

    if (icon == NULL)
        icon = "BUILD";

    titlelong = string_dupe(title);
    titleshort = string_dupe(icon);

    if (getenv(BUILD_NOMOUSEGRAB) == NULL)
        mouse_grabbed = 1;
    else
        mouse_grabbed = 0;

    sdl_flags = ((getenv(BUILD_WINDOWED) == NULL) ? SDL_FULLSCREEN : 0);

    sdl_flags |= SDL_HWPALETTE;
    /*sdl_flags |= SDL_HWSURFACE;   !!! */
    /*sdl_flags |= SDL_DOUBLEBUF; */

    set_sdl_renderer();
    set_splash();

    output_sdl_versions();
    output_driver_info();
    detect_vmware();

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
    scancodes[SDLK_MINUS]           = 0x0C; /* was 0x4A */
    scancodes[SDLK_EQUALS]          = 0x0D; /* was 0x4E */
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
    scancodes[SDLK_KP_MULTIPLY]     = 0x37;
    scancodes[SDLK_LALT]            = 0x38;
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
    scancodes[SDLK_NUMLOCK]         = 0x45;
    scancodes[SDLK_SCROLLOCK]       = 0x46;
    scancodes[SDLK_KP7]             = 0x47;
    scancodes[SDLK_KP8]             = 0x48;
    scancodes[SDLK_KP9]             = 0x49;
    scancodes[SDLK_KP_MINUS]        = 0x4A;
    scancodes[SDLK_KP4]             = 0x4B;
    scancodes[SDLK_KP5]             = 0x4C;
    scancodes[SDLK_KP6]             = 0x4D;
    scancodes[SDLK_KP_PLUS]         = 0x4E;
    scancodes[SDLK_KP1]             = 0x4F;
    scancodes[SDLK_KP2]             = 0x50;
    scancodes[SDLK_KP3]             = 0x51;
    scancodes[SDLK_KP0]             = 0x52;
    scancodes[SDLK_KP_PERIOD]       = 0x53;
    scancodes[SDLK_F11]             = 0x57;
    scancodes[SDLK_F12]             = 0x58;
    scancodes[SDLK_PAUSE]           = 0x59; /* SBF - technically incorrect */

    /* Some AZERTY keys... */
    scancodes[SDLK_AMPERSAND]       = 0x70;
    scancodes[SDLK_QUOTEDBL]        = 0x71;
    scancodes[SDLK_LEFTPAREN]       = 0x72;
    scancodes[SDLK_EXCLAIM]         = 0x73;
    scancodes[SDLK_CARET]           = 0x74;
    scancodes[SDLK_DOLLAR]          = 0x75;
    scancodes[SDLK_WORLD_0]         = 0x76;
    scancodes[SDLK_WORLD_1]         = 0x77;
    scancodes[SDLK_WORLD_2]         = 0x78;
    scancodes[SDLK_WORLD_3]         = 0x79;
    scancodes[SDLK_WORLD_4]         = 0x7A;
    scancodes[SDLK_WORLD_5]         = 0x7B;
    scancodes[SDLK_RIGHTPAREN]      = 0x7C;
    scancodes[SDLK_COLON]           = 0x7D;
    scancodes[SDLK_LESS]            = 0x7E;

    /* extended DOS scancodes... */
    scancodes[SDLK_KP_ENTER]        = 0xE01C;
    scancodes[SDLK_RCTRL]           = 0xE01D;
    scancodes[SDLK_KP_DIVIDE]       = 0xE035;
    scancodes[SDLK_PRINT]           = 0xE037; /* SBF - technically incorrect */
    scancodes[SDLK_SYSREQ]          = 0xE037; /* SBF - for windows... */
    scancodes[SDLK_RALT]            = 0xE038;
    scancodes[SDLK_HOME]            = 0xE047;
    scancodes[SDLK_UP]              = 0xE048;
    scancodes[SDLK_PAGEUP]          = 0xE049;
    scancodes[SDLK_LEFT]            = 0xE04B;
    scancodes[SDLK_RIGHT]           = 0xE04D;
    scancodes[SDLK_END]             = 0xE04F;
    scancodes[SDLK_DOWN]            = 0xE050;
    scancodes[SDLK_PAGEDOWN]        = 0xE051;
    scancodes[SDLK_INSERT]          = 0xE052;
    scancodes[SDLK_DELETE]          = 0xE053;

    if (has_altivec)
        sdldebug("CPU feature: Altivec\n");
} /* _platform_init */


int setvesa(long x, long y)
{
    fprintf(stderr, "setvesa() called in SDL driver!\n");
    exit(23);
    return(0);
} /* setvesa */

int screencapture(char *_filename, char inverseit)
{
	char *ptr = NULL;
	int fil = -1;
    long i, bufplc, p, col, ncol, leng, numbytes, xres;
    int captcnt;
    size_t flen = strlen(_filename);
    char *filename = alloca(flen + 1);
    strcpy(filename, _filename);

    for (captcnt = 0; (captcnt <= 9999) && (fil == -1); captcnt++)
    {
        filename[flen-8] = ((captcnt/1000)%10)+48;
        filename[flen-7] = ((captcnt/100)%10)+48;
        filename[flen-6] = ((captcnt/10)%10)+48;
        filename[flen-5] = (captcnt%10)+48;
        fil = open(filename, O_BINARY|O_CREAT|O_EXCL|O_WRONLY,
                    S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    }

    if (fil == -1)
        return -1;

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
//		koutp(97,kinp(97)|3);

		if (qsetmode == 200) { col = *ptr; p++; ptr++; }
		else
		{
			col = readpixel(p);
			p++;
			if ((inverseit == 1) && (((col&7) == 0) || ((col&7) == 7))) col ^= 15;
		}

		leng = 1;

		if (qsetmode == 200) ncol = *ptr;
		else
		{
			ncol = readpixel(p);
			if ((inverseit == 1) && (((ncol&7) == 0) || ((ncol&7) == 7))) ncol ^= 15;
		}

		while ((ncol == col) && (p < numbytes) && (leng < 63) && ((p%xres) != 0))
		{
			leng++;

			if (qsetmode == 200) { p++; ptr++; ncol = *ptr; }
			else
			{
				p++;
				ncol = readpixel(p);
				if ((inverseit == 1) && (((ncol&7) == 0) || ((ncol&7) == 7))) ncol ^= 15;
			}
		}

		//koutp(97,kinp(97)&252);

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
	return(0);
} /* screencapture */


void setvmode(int mode)
{
    int w = -1;
    int h = -1;

    if (mode == 0x3)  /* text mode. */
    {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        return;
    } /* if */

    if (mode == 0x13)
    {
        w = 800;
        h = 600;
    } /* if */

    else
    {
        fprintf(stderr, "setvmode(0x%x) is unsupported in SDL driver.\n", mode);
        exit(13);
    } /* if */

    assert(w > 0);
    assert(h > 0);

    go_to_new_vid_mode(-1, w, h);
} /* setvmode */


int _setgamemode(char davidoption, long daxdim, long daydim)
{
#ifdef USE_OPENGL
    static int shown_gl_strings = 0;
    int gl = using_opengl();
    if (gl)
        sdl_flags |= SDL_OPENGL;
#endif

    if (daxdim > MAXXDIM || daydim > MAXYDIM)
    {
	    daxdim = 1600;
	    daydim = 1200;
    }

    if (in_egapalette)
        restore256_palette();	    

    go_to_new_vid_mode((int) davidoption, daxdim, daydim);

    #ifdef USE_OPENGL
        if (gl)
        {
            if (!shown_gl_strings)
            {
                sgldebug("GL_VENDOR [%s]", (char *) dglGetString(GL_VENDOR));
                sgldebug("GL_RENDERER [%s]", (char *) dglGetString(GL_RENDERER));
                sgldebug("GL_VERSION [%s]", (char *) dglGetString(GL_VERSION));
                sgldebug("GL_EXTENSIONS [%s]", (char *) dglGetString(GL_EXTENSIONS));
                shown_gl_strings = 1;
            } /* if */

            dglViewport(0, 0, daxdim, daydim);
            dglEnable(GL_TEXTURE_2D);
            dglPixelTransferi(GL_MAP_COLOR, GL_TRUE);
            dglPixelTransferi(GL_INDEX_SHIFT, 0);
            dglPixelTransferi(GL_INDEX_OFFSET, 0);
            dglClearDepth(1.0);
            dglDepthFunc(GL_LESS);
            dglEnable(GL_DEPTH_TEST);
            dglShadeModel(GL_SMOOTH);
            dglMatrixMode(GL_PROJECTION);
            dglLoadIdentity();
            dglMatrixMode(GL_MODELVIEW);
        } /* if */
    #endif

    qsetmode = 200;
    last_render_ticks = SDL_GetTicks();
    return(0);
} /* setgamemode */


void qsetmode640350(void)
{
    assert(0);

    #ifdef USE_OPENGL
        if (using_opengl())
            sdl_flags |= SDL_OPENGL;
    #endif

    go_to_new_vid_mode(-1, 640, 350);
} /* qsetmode640350 */


void qsetmode640480(void)
{
    if (!in_egapalette)
    	set16color_palette();

    #ifdef USE_OPENGL
        if (using_opengl())
            sdl_flags |= SDL_OPENGL;
    #endif

    go_to_new_vid_mode(-1, 640, 480);
    pageoffset = 0;	/* Make sure it goes to the right place - DDOI */
    fillscreen16(0L,8L,640L*144L);
} /* qsetmode640480 */


static int get_dimensions_from_str(const char *str, long *_w, long *_h)
{
    char *xptr = NULL;
    char *ptr = NULL;
    long w = -1;
    long h = -1;

    if (str == NULL)
        return(0);

    xptr = strchr(str, 'x');
    if (xptr == NULL)
        return(0);

    w = strtol(str, &ptr, 10);
    if (ptr != xptr)
        return(0);

    xptr++;
    h = strtol(xptr, &ptr, 10);
    if ( (*xptr == '\0') || (*ptr != '\0') )
        return(0);

    if ((w <= 1) || (h <= 1))
        return(0);

    if (_w != NULL)
        *_w = w;

    if (_h != NULL)
        *_h = h;

    return(1);
} /* get_dimensions_from_str */


static __inline void get_max_screen_res(long *max_w, long *max_h)
{
    long w = DEFAULT_MAXRESWIDTH;
    long h = DEFAULT_MAXRESHEIGHT;
    const char *envr = getenv(BUILD_MAXSCREENRES);

    if (envr != NULL)
    {
        if (!get_dimensions_from_str(envr, &w, &h))
        {
            sdldebug("User's resolution ceiling [%s] is bogus!", envr);
            w = DEFAULT_MAXRESWIDTH;
            h = DEFAULT_MAXRESHEIGHT;
        } /* if */
    } /* if */

    if (max_w != NULL)
        *max_w = w;

    if (max_h != NULL)
        *max_h = h;
} /* get_max_screen_res */


static void add_vesa_mode(const char *typestr, int w, int h)
{
    sdldebug("Adding %s resolution (%dx%d).", typestr, w, h);
    validmode[validmodecnt] = validmodecnt;
    validmodexdim[validmodecnt] = w;
    validmodeydim[validmodecnt] = h;
    validmodecnt++;
} /* add_vesa_mode */


/* Let the user specify a specific mode via environment variable. */
static __inline void add_user_defined_resolution(void)
{
    long w;
    long h;
    const char *envr = getenv(BUILD_USERSCREENRES);

    if (envr == NULL)
        return;

    if (get_dimensions_from_str(envr, &w, &h))
        add_vesa_mode("user defined", w, h);
    else
        sdldebug("User defined resolution [%s] is bogus!", envr);
} /* add_user_defined_resolution */


static __inline SDL_Rect **get_physical_resolutions(void)
{
    const SDL_VideoInfo *vidInfo = SDL_GetVideoInfo();
    SDL_Rect **modes = SDL_ListModes(vidInfo->vfmt, sdl_flags | SDL_FULLSCREEN);
    if (modes == NULL)
    {
        sdl_flags &= ~SDL_FULLSCREEN;
        modes = SDL_ListModes(vidInfo->vfmt, sdl_flags); /* try without fullscreen. */
        if (modes == NULL)
            modes = (SDL_Rect **) -1;  /* fuck it. */
    } /* if */

    if (modes == (SDL_Rect **) -1)
        sdldebug("Couldn't get any physical resolutions.");
    else
    {
        sdldebug("Highest physical resolution is (%dx%d).",
                  modes[0]->w, modes[0]->h);
    } /* else */

    return(modes);
} /* get_physical_resolutions */


static void remove_vesa_mode(int index, const char *reason)
{
    int i;

    assert(index < validmodecnt);
    sdldebug("Removing resolution #%d, %dx%d [%s].",
              index, validmodexdim[index], validmodeydim[index], reason);

    for (i = index; i < validmodecnt - 1; i++)
    {
        validmode[i] = validmode[i + 1];
        validmodexdim[i] = validmodexdim[i + 1];
        validmodeydim[i] = validmodeydim[i + 1];
    } /* for */

    validmodecnt--;
} /* remove_vesa_mode */


static __inline void cull_large_vesa_modes(void)
{
    long max_w;
    long max_h;
    int i;

    get_max_screen_res(&max_w, &max_h);
    sdldebug("Setting resolution ceiling to (%ldx%ld).", max_w, max_h);

    for (i = 0; i < validmodecnt; i++)
    {
        if ((validmodexdim[i] > max_w) || (validmodeydim[i] > max_h))
        {
            remove_vesa_mode(i, "above resolution ceiling");
            i--;  /* list shrinks. */
        } /* if */
    } /* for */
} /* cull_large_vesa_modes */


static __inline void cull_duplicate_vesa_modes(void)
{
    int i;
    int j;

    for (i = 0; i < validmodecnt; i++)
    {
        for (j = i + 1; j < validmodecnt; j++)
        {
            if ( (validmodexdim[i] == validmodexdim[j]) &&
                 (validmodeydim[i] == validmodeydim[j]) )
            {
                remove_vesa_mode(j, "duplicate");
                j--;  /* list shrinks. */
            } /* if */
        } /* for */
    } /* for */
} /* cull_duplicate_vesa_modes */


#define swap_macro(tmp, x, y) { tmp = x; x = y; y = tmp; }

/* be sure to call cull_duplicate_vesa_modes() before calling this. */
static __inline void sort_vesa_modelist(void)
{
    int i;
    int sorted;
    long tmp;

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
            } /* if */
        } /* for */
    } while (!sorted);
} /* sort_vesa_modelist */


static __inline void cleanup_vesa_modelist(void)
{
    cull_large_vesa_modes();
    cull_duplicate_vesa_modes();
    sort_vesa_modelist();
} /* cleanup_vesa_modelist */


static __inline void output_vesa_modelist(void)
{
    char buffer[256];
    char numbuf[20];
    int i;

    if (!_sdl_debug_file)
        return;

    buffer[0] = '\0';

    for (i = 0; i < validmodecnt; i++)
    {
        sprintf(numbuf, " (%ldx%ld)",
                  (long) validmodexdim[i], (long) validmodeydim[i]);

        if ( (strlen(buffer) + strlen(numbuf)) >= (sizeof (buffer) - 1) )
            strcpy(buffer + (sizeof (buffer) - 5), " ...");
        else
            strcat(buffer, numbuf);
    } /* for */

    sdldebug("Final sorted modelist:%s", buffer);
} /* output_vesa_modelist */


void getvalidvesamodes(void)
{
    static int already_checked = 0;
    int i;
    SDL_Rect **modes = NULL;
    int stdres[][2] = {
                        {320, 200}, {320, 240}, {640, 350},
			{640, 480}, {800, 600}, {1024, 768}
                      };

    if (already_checked)
        return;

    already_checked = 1;
   	validmodecnt = 0;
    vidoption = 1;  /* !!! tmp */

        /* fill in the standard resolutions... */
    for (i = 0; i < sizeof (stdres) / sizeof (stdres[0]); i++)
        add_vesa_mode("standard", stdres[i][0], stdres[i][1]);

         /* Anything the hardware can specifically do is added now... */
    modes = get_physical_resolutions();
    for (i = 0; (modes != (SDL_Rect **) -1) && (modes[i] != NULL); i++)
        add_vesa_mode("physical", modes[i]->w, modes[i]->h);

        /* Now add specific resolutions that the user wants... */
    add_user_defined_resolution();

        /* get rid of dupes and bogus resolutions... */
    cleanup_vesa_modelist();

        /* print it out for debugging purposes... */
    output_vesa_modelist();
} /* getvalidvesamodes */


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
    SDL_Color fmt_swap[256];
    SDL_Color *sdlp = &fmt_swap[start];
    char *p = palettebuffer;
    int i;

#if (defined USE_OPENGL)
    int gl = using_opengl();
    GLfloat gl_reds[256];
    GLfloat gl_greens[256];
    GLfloat gl_blues[256];
    GLfloat gl_alphas[256];

    if (gl)
    {
        return 255;
        dglGetPixelMapfv(GL_PIXEL_MAP_I_TO_R, gl_reds);
        dglGetPixelMapfv(GL_PIXEL_MAP_I_TO_G, gl_greens);
        dglGetPixelMapfv(GL_PIXEL_MAP_I_TO_B, gl_blues);
        dglGetPixelMapfv(GL_PIXEL_MAP_I_TO_A, gl_alphas);
    } /* if */
#endif

    assert( (start + num) <= (sizeof (fmt_swap) / sizeof (SDL_Color)) );

    for (i = 0; i < num; i++)
    {
        sdlp->b = (Uint8) ((((float) *p++) / 63.0) * 255.0);
        sdlp->g = (Uint8) ((((float) *p++) / 63.0) * 255.0);
        sdlp->r = (Uint8) ((((float) *p++) / 63.0) * 255.0);
        sdlp->unused = *p++;   /* This byte is unused in BUILD, too. */

#if (defined USE_OPENGL)
        if (gl)
        {
            gl_reds[i+start]   = ((GLfloat) sdlp->r) / 255.0f;
            gl_greens[i+start] = ((GLfloat) sdlp->g) / 255.0f;
            gl_blues[i+start]  = ((GLfloat) sdlp->b) / 255.0f;
            gl_alphas[i+start] = 1.0f;
        } /* if */
#endif

        sdlp++;
    } /* for */

#if (defined USE_OPENGL)
    if (gl)
    {
        dglPixelMapfv(GL_PIXEL_MAP_I_TO_R, start + num, gl_reds);
        dglPixelMapfv(GL_PIXEL_MAP_I_TO_G, start + num, gl_greens);
        dglPixelMapfv(GL_PIXEL_MAP_I_TO_B, start + num, gl_blues);
        dglPixelMapfv(GL_PIXEL_MAP_I_TO_A, start + num, gl_alphas);
    } /* if */
#endif

    return(SDL_SetColors(surface, fmt_swap, start, num));
} /* VBE_setPalette */


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
        *p++ = sdlp->unused;   /* This byte is unused in both SDL and BUILD. */
        sdlp++;
    } /* for */

    return(1);
} /* VBE_getPalette */


void _uninitengine(void)
{
   SDL_QuitSubSystem(SDL_INIT_VIDEO);
} /* _uninitengine */


void uninitvesa(void)
{
   SDL_QuitSubSystem(SDL_INIT_VIDEO);
} /* uninitvesa */


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

        /*
         * this global usually gets set by BUILD, but it's a one-shot
         *  deal, and we may not have an SDL surface at that point. --ryan.
         */
    moustat = 1;

    return(1);
} /* setupmouse */


void readmousexy(short *x, short *y)
{
    if (x) *x = mouse_relative_x << 2;
    if (y) *y = mouse_relative_y << 2;

    mouse_relative_x = mouse_relative_y = 0;
} /* readmousexy */


void readmousebstatus(short *bstatus)
{
    if (bstatus)
        *bstatus = mouse_buttons;

    // special wheel treatment
    if(mouse_buttons&8) mouse_buttons ^= 8;
    if(mouse_buttons&16) mouse_buttons ^= 16;

} /* readmousebstatus */


static unsigned char mirrorcolor = 0;

void _updateScreenRect(long x, long y, long w, long h)
{
    if (renderer == RENDERER_SOFTWARE)
        SDL_UpdateRect(surface, x, y, w, h);
} /* _updatescreenrect */


void _nextpage(void)
{
    Uint32 ticks;

    handle_events();

    if (renderer == RENDERER_SOFTWARE)
    {
        if (qsetmode == 200)
            memcpy(surface->pixels, (const void *) frameplace, surface->w * surface->h);
        SDL_UpdateRect(surface, 0, 0, 0, 0);
        /*SDL_Flip(surface);  !!! */
    } /* if */

#ifdef USE_OPENGL
    else if (renderer == RENDERER_OPENGL3D)
    {
        opengl_swapbuffers();
    } /* else if */
#endif

    if ((debug_hall_of_mirrors) && (qsetmode == 200) && (frameplace))
    {
        memset((void *) frameplace, mirrorcolor, surface->w * surface->h);
        mirrorcolor++;
    } /* if */

    ticks = SDL_GetTicks();
    total_render_time = (ticks - last_render_ticks);
    if (total_render_time > 1000)
    {
        total_rendered_frames = 0;
        total_render_time = 1;
        last_render_ticks = ticks;
    } /* if */
    total_rendered_frames++;
} /* _nextpage */


unsigned char readpixel(long offset)
{
    return( *((unsigned char *) offset) );
} /* readpixel */

void drawpixel(long offset, unsigned char pixel)
{
    *((unsigned char *) offset) = pixel;
} /* drawpixel */


/* !!! These are incorrect. */
void drawpixels(long offset, unsigned short pixels)
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
} /* drawpixels */


void drawpixelses(long offset, unsigned int pixelses)
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
} /* drawpixelses */


/* Fix this up The Right Way (TM) - DDOI */
void setcolor16(int col)
{
	drawpixel_color = col;
}

void drawpixel16(long offset)
{
    drawpixel(((long) surface->pixels + offset), drawpixel_color);
} /* drawpixel16 */


void fillscreen16(long offset, long color, long blocksize)
{
    Uint8 *surface_end;
    Uint8 *wanted_end;
    Uint8 *pixels;

#if (defined USE_OPENGL)
    if (renderer == RENDERER_OPENGL3D)
    {
        /* !!! dglClearColor() ... */
        return;
    } /* if */
#endif

    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    pixels = get_framebuffer();

    /* Make this function pageoffset aware - DDOI */
    if (!pageoffset) { 
	    offset = offset << 3;
	    offset += 640*336;
    }

    surface_end = (pixels + (surface->w * surface->h)) - 1;
    wanted_end = (pixels + offset) + blocksize;

    if (offset < 0)
        offset = 0;

    if (wanted_end > surface_end)
        blocksize = ((unsigned long) surface_end) - ((unsigned long) pixels + offset);

    memset(pixels + offset, (int) color, blocksize);

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);

    _nextpage();
} /* fillscreen16 */


/* Most of this line code is taken from Abrash's "Graphics Programming Blackbook".
Remember, sharing code is A Good Thing. AH */
static __inline void DrawHorizontalRun (char **ScreenPtr, int XAdvance, int RunLength, char Color)
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

static __inline void DrawVerticalRun (char **ScreenPtr, int XAdvance, int RunLength, char Color)
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

	/* Make sure the status bar border draws correctly - DDOI */
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
    ScreenPtr = (char *) (get_framebuffer()) + XStart + (surface->w * YStart);

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
} /* drawline16 */


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
	} /* else if */

    SDL_FillRect(surface, &rect, 0);
} /* clear2dscreen */


void _idle(void)
{
    if (surface != NULL)
        handle_events();
    SDL_Delay(1);
} /* _idle */

void *_getVideoBase(void)
{
    return((void *) surface->pixels);
}

void setactivepage(long dapagenum)
{
	/* !!! Is this really still needed? - DDOI */
    /*fprintf(stderr, "%s, line %d; setactivepage(): STUB.\n", __FILE__, __LINE__);*/
} /* setactivepage */

void limitrate(void)
{
    /* this is a no-op in SDL. It was for buggy VGA cards in DOS. */
} /* limitrate */

static Uint32 _timer_catcher(Uint32 interval, void *bleh)
{
    timerhandler();
    return(1);
} /* _timer_catcher */

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
    } /* if */
}

void uninittimer(void)
{
    if (primary_timer != NULL)
    {
        SDL_RemoveTimer(primary_timer);
        primary_timer = NULL;
    } /* if */
}

void initkeys(void)
{
    /* does nothing in SDL. Key input handling is set up elsewhere. */
    /* !!! why not here? */
}

void uninitkeys(void)
{
    /* does nothing in SDL. Key input handling is set up elsewhere. */
}

void set16color_palette(void)
{
	/* Backup old palette */
	/*VBE_getPalette (0, 16, (char *)&backup_palette);*/
	memcpy (&backup_palette, &palette, 16*3);

	/* Set new palette */
	/*VBE_setPalette (0, 16, (char *)&egapalette);*/
	memcpy (&palette, &egapalette, 16*3);
	in_egapalette = 1;
} /* set16color_palette */

void restore256_palette(void)
{
	/*VBE_setPalette (0, 16, (char *)&backup_palette);*/
	memcpy (&palette, &backup_palette, 16*3);
	in_egapalette = 0;
} /* restore256_palette */

unsigned long getticks(void)
{
    return(SDL_GetTicks());
} /* getticks */

/* end of sdl_driver.c ... */

