/*
 * An SDL replacement for BUILD's VESA code.
 *
 *  Written by Ryan C. Gordon. (icculus@lokigames.com)
 *
 * Please do NOT harrass Ken Silverman about any code modifications
 *  (including this file) to BUILD.
 */

// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "SDL.h"
#include "unix_compat.h"
#include "build.h"
#include "display.h"
#include "pragmas.h"
#include "a.h"
#include "cache1d.h"


// !!! I'd like this to be temporary. --ryan.
// !!!  That is, the self-modifying part, so I can ditch the mprotect() stuff.
#ifdef USE_I386_ASM
#include <sys/mman.h>
#include <limits.h>
#ifndef PAGESIZE
#define PAGESIZE 4096
#endif
#else
#error There is currently only I386 asm. Please make your platform work,
#error  ...or write us some portable C code.
#endif

// !!! remove the surface_end checks, for speed's sake. They are a
// !!!  needed safety right now. --ryan.


#define BUILD_NOMOUSEGRAB  "BUILD_NO_MOUSE_GRAB"
#define BUILD_WINDOWED     "BUILD_WINDOWED"

#define UNLOCK_SURFACE_AND_RETURN  if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface); return;

// !!! Take this out later.
//#define DEBUG_HALL_OF_MIRRORS


    // !!! move these elsewhere?
long xres, yres, bytesperline, frameplace, imageSize, maxpages;
char *screen, vesachecked;
long buffermode, origbuffermode, linearmode;
char permanentupdate = 0, vgacompatible;

SDL_Surface *surface = NULL; /* This isn't static so that we can use it elsewhere AH */
static Uint32 sdl_flags = 0;
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

void restore256_palette (void);
void set16color_palette (void);

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


static int sdl_key_filter(const SDL_Event *event)
{
    SDL_GrabMode grab_mode = SDL_GRAB_OFF;
    int extended;

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
        sdl_flags ^= SDL_FULLSCREEN;
        SDL_WM_ToggleFullScreen(surface);
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


unsigned char _readlastkeyhit(void)
{
    return(lastkey);
} // _readlastkeyhit


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


// !!! I'd like this to be temporary. --ryan.
#ifdef USE_I386_ASM

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

void _platform_init(int argc, char **argv, const char *title, const char *icon)
{
    #ifdef USE_I386_ASM
        unprotect_ASM_pages();
    #endif

    if (title == NULL)
        title = "BUILD";

    if (icon == NULL)
        icon = "BUILD";

    titlelong = strdup(title);
    titleshort = strdup(icon);

    setbuf(stderr, NULL);
    setbuf(stdout, NULL);

    if (getenv(BUILD_NOMOUSEGRAB) == NULL)
        mouse_grabbed = 1;
    else
        mouse_grabbed = 0;

    sdl_flags = SDL_HWSURFACE | SDL_FULLSCREEN;
    if (getenv(BUILD_WINDOWED) != NULL)
        sdl_flags &= ~SDL_FULLSCREEN;

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
	scancodes[SDLK_KP_ENTER]		= 0xE01C;

    if (SDL_Init(SDL_INIT_VIDEO |
                 SDL_INIT_TIMER |
                 SDL_INIT_AUDIO ) == -1)
    {
        fprintf(stderr, "SDL_Init() failed!\n");
        fprintf(stderr, "SDL_GetError() says \"%s\".\n", SDL_GetError());
    } // if
} // _platform_init


int setvesa(long x, long y)
{
    fprintf(stderr, "setvesa() called in SDL driver!\n");
    exit(23);
} // setvesa


int screencapture(char *filename, char inverseit)
{
    fprintf(stderr, "screencapture() is a stub in the SDL driver.\n");
    return(0);
} // screencapture


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
    frameplace = (long) ( ((Uint8 *) surface->pixels) );
    horizlookup = horizlookup2 = NULL;

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

        frameplace = FP_OFF(screen);
      	horizlookup = (long *)(frameplace+i);
       	horizlookup2 = (long *)(frameplace+i+j);
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

    SDL_SetEventFilter(root_sdl_event_filter);
} // init_new_res_vars


void go_to_new_vid_mode(int vidoption, int w, int h)
{
    getvalidvesamodes();
    SDL_ClearError();
    surface = SDL_SetVideoMode(w, h, 8, sdl_flags);
    if (surface == NULL)
    {
        fprintf(stderr, "Failed to set %dx%d video mode!\n"
                        "  SDL_Error() says [%s].\n", w, h, SDL_GetError());
        SDL_Quit();
        exit(13);
    } // if

    init_new_res_vars(vidoption);
} // go_to_new_vid_mode



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
    if (in_egapalette)
        restore256_palette();	    
    go_to_new_vid_mode((int) davidoption, daxdim, daydim);
    qsetmode = 200;
    last_render_ticks = SDL_GetTicks();
    return(0);
} // setgamemode


void qsetmode640350(void)
{
    assert(0);
    go_to_new_vid_mode(-1, 640, 350);
} // qsetmode640350


void qsetmode640480(void)
{
    if (!in_egapalette)
    	set16color_palette();
    go_to_new_vid_mode(-1, 640, 480);
    pageoffset = 0;	// Make sure it goes to the right place - DDOI
    fillscreen16(0L,8L,640L*144L);
} // qsetmode640480


void getvalidvesamodes(void)
{
    int i = 0;
    const SDL_VideoInfo *vidInfo = NULL;
    SDL_Rect **modes = NULL;
    static int already_checked = 0;
    int inserted = 0;
    int pos = 0;

    if (already_checked)
        return;

    already_checked = 1;
   	validmodecnt = 0;



    vidoption = 1;  //!!! tmp




    vidInfo = SDL_GetVideoInfo();
    modes = SDL_ListModes(vidInfo->vfmt, sdl_flags);
    if (modes == NULL)
    {
        sdl_flags &= ~SDL_FULLSCREEN;
        modes = SDL_ListModes(vidInfo->vfmt, sdl_flags); // try without fullscreen.
        if (modes == NULL)
        {
            sdl_flags &= ~SDL_HWSURFACE;
            modes = SDL_ListModes(vidInfo->vfmt, sdl_flags);   // give me ANYTHING.
            if (modes == NULL)
            {
                fprintf(stderr, "SDL: SDL_ListModes() failed.\n");
                return;
            } // if
        } // if
    } // if

    if (modes == (SDL_Rect **) -1)   // anything is fine; put some standard
    {                                //  sizes in here...
        validmode[0] = 0;
       	validmodexdim[0] = 320;
       	validmodeydim[0] = 200;
        validmodecnt++;
        validmode[1] = 1;
       	validmodexdim[1] = 640;
       	validmodeydim[1] = 350;
        validmodecnt++;
        validmode[2] = 2;
       	validmodexdim[2] = 640;
       	validmodeydim[2] = 480;
        validmodecnt++;
        validmode[3] = 3;
       	validmodexdim[3] = 800;
       	validmodeydim[3] = 600;
        validmodecnt++;
        validmode[4] = 4;
       	validmodexdim[4] = 1024;
       	validmodeydim[4] = 768;
        validmodecnt++;
    } // if
    else
    {
        // BUILD wants this array sorted smallest to largest. SDL gives it
        //  to us largest to smallest. Argh.
        //  320 by 200 needs to be in here. SDL will emulate if need be.

        for (i = 0; modes[i] != NULL; i++);   // get to end of array.

        for (i--; i >= 0; i--, pos++)
        {
            validmode[pos] = 1;

            if ((modes[i]->w == 320) && (modes[i]->h == 200))
                inserted = 1;   // don't need to insert it ourselves.

            if ((modes[i]->w > 320) && (modes[i]->h > 200) && (inserted == 0))
            {
                validmodexdim[pos] = 320;
               	validmodeydim[pos] = 200;
                inserted = 1;
            } // if
            else
            {
                validmodexdim[pos] = modes[i]->w;
               	validmodeydim[pos] = modes[i]->h;
            } // else

           	validmodecnt++;
        } // for
    } // else
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
    SDL_Color fmt_swap[start + num];
    SDL_Color *sdlp = fmt_swap + start;
    char *p = palettebuffer + (start * 4);
    int i;

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


#ifdef DEBUG_HALL_OF_MIRRORS
    static unsigned char mirrorcolor = 0;
#endif

void _nextpage(void)
{
    Uint32 ticks;

    SDL_PumpEvents();

    if (qsetmode == 200)
    {
        memcpy(surface->pixels, (const void *) frameplace, surface->w * surface->h);

        #ifdef DEBUG_HALL_OF_MIRRORS
            memset((void *) frameplace, mirrorcolor, surface->w * surface->h);
            mirrorcolor++;
        #endif
    }

    SDL_UpdateRect(surface, 0, 0, 0, 0);

    if (qsetmode == 200)
    {
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
    } // if
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

    surface_end = (surface->pixels + (surface->w * surface->h)) - 2;
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

    surface_end = (surface->pixels + (surface->w * surface->h)) - 2;
    pos = (Uint32 *) (((Uint8 *) surface->pixels) + offset);
    if ((pos >= (Uint32 *) surface->pixels) && (pos < (Uint32 *) surface_end))
        *pos = pixelses;

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);
} // drawpixelses


// Fix this up The Right Way (TM) - DDOI
void setcolor16 (long col)
{
	drawpixel_color = col;
}

void drawpixel16(long offset)
{
    drawpixel((long) (surface->pixels + offset), drawpixel_color);
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

    surface_end = (surface->pixels + (surface->w * surface->h)) - 1;
    wanted_end = (((Uint8 *) surface->pixels) + offset) + blocksize;

    if (offset < 0)
        offset = 0;

    if (wanted_end > surface_end)
        blocksize = ((unsigned long) surface_end) - ((unsigned long) surface->pixels + offset);

    memset(surface->pixels + offset, (int) color, blocksize);

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
    ScreenPtr = surface->pixels + XStart + (surface->w * YStart);

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

     UNLOCK_SURFACE_AND_RETURN;
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
    SDL_PumpEvents();
    SDL_Delay(1);
} // _idle

void *_getVideoBase(void)
{
    return((void *) surface->pixels);
}

void setactivepage(long dapagenum)
{
    fprintf(stderr, "%s, line %d; setactivepage(): STUB.\n", __FILE__, __LINE__);
} // setactivepage

void limitrate(void)
{
    // this is a no-op in SDL. It was for buggy VGA cards in DOS.
} // limitrate

Uint32 _timer_catcher(Uint32 interval, void *bleh)
{
    // SDL (or rather, Linux) cannot fire timer events as fast as BUILD needs
    //  them, so we fire two in a row if we get behind.

    static long total_fires = 0;
    long ticks = SDL_GetTicks();

    do
    {
        timerhandler();
        total_fires++;
    } while ( ( ((double) ticks) / ((double) total_fires) ) >= (1000.0 / 120.0) );

    return(1);
} // _timer_catcher

void inittimer(void)
{
    primary_timer = SDL_AddTimer(1000 / 120, _timer_catcher, NULL);
    if (primary_timer == NULL)
    {
        SDL_Quit();
        fprintf(stderr, "Error initializing primary timer!\n");
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
}

void uninitkeys(void)
{
    // does nothing in SDL. Key input handling is set up elsewhere.
}

void initsb(char dadigistat, char damusistat, long dasamplerate, char danumspeakers, char dabytespersample, char daintspersec, char daquality)
{
    fprintf(stderr, "%s, line %d; initsb(): STUB.\n", __FILE__, __LINE__);
} // initsb

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

void uninitsb(void)
{
    fprintf(stderr, "%s, line %d; uninitsb(): STUB.\n", __FILE__, __LINE__);
} // uninitsb

void preparesndbuf(void)
{
    fprintf(stderr,"%s, line %d; preparesndbuf(): STUB.\n", __FILE__, __LINE__);
} // preparesndbuf

void wsayfollow(char *dafilename, long dafreq, long davol, long *daxplc, long *dayplc, char followstat)
{
    fprintf(stderr, "%s, line %d; wsayfollow(): STUB.\n", __FILE__, __LINE__);
} // wsayfollow    

void setears(long daposx, long daposy, long daxvect, long dayvect)
{
//    fprintf(stderr, "%s, line %d; setears(): STUB.\n", __FILE__, __LINE__);
} // setears

void wsay(char *dafilename, long dafreq, long volume1, long volume2)
{
    fprintf(stderr, "%s, line %d; wsay(): STUB.\n", __FILE__, __LINE__);
} // wsay

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

