// "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
// Ken Silverman's official web site: "http://www.advsys.net/ken"
// See the included license file "BUILDLIC.TXT" for license info.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "SDL.h"
#include "unix_compat.h"

#define BUILD_NOMOUSEGRAB  "BUILD_NO_MOUSE_GRAB"
#define BUILD_WINDOWED     "BUILD_WINDOWED"

long xres, yres, bytesperline, frameplace, imageSize, maxpages;
char *screen, vesachecked;
long buffermode, origbuffermode, linearmode;
char permanentupdate = 0, vgacompatible;

SDL_Surface *surface = NULL;
static Uint32 sdl_flags = 0;
static long mouse_x = 0;
static long mouse_y = 0;
static long mouse_relative_x = 0;
static long mouse_relative_y = 0;
static short mouse_buttons = 0;
static int mouse_grabbed = 0;
static unsigned int lastkey = 0;
static SDL_TimerID primary_timer = NULL;

static unsigned int scancodes[SDLK_LAST];

static long last_render_ticks = 0;
long total_render_time = 1;
long total_rendered_frames = 0;

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

void _platform_init(int argc, char **argv)
{
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
    scancodes[SDLK_DELETE]          = 0xD3;
    scancodes[SDLK_KP0]             = 0xE052;
    scancodes[SDLK_INSERT]          = 0xE052;
	scancodes[SDLK_KP_ENTER]		= 0xE01C;

    if (SDL_Init(SDL_INIT_VIDEO |
                 SDL_INIT_TIMER |
                 SDL_INIT_AUDIO |
                 SDL_INIT_EVENTTHREAD) == -1)
    {
        fprintf(stderr, "SDL_Init() failed!\n");
        fprintf(stderr, "SDL_GetError() says \"%s\".\n", SDL_GetError());
    } // if
} // _platform_init

int screencapture(char *filename, char inverseit)
{
    fprintf(stderr, "screencapture() is a stub in the SDL driver.\n");
    return(0);
} // screencapture

void go_to_new_vid_mode(int vidoption, int w, int h)
{
    SDL_ClearError();
    surface = SDL_SetVideoMode(w, h, 8, sdl_flags);
    if (surface == NULL)
    {
        fprintf(stderr, "Failed to set %dx%d video mode!\n"
                        "  SDL_Error() says [%s].\n", w, h, SDL_GetError());
        SDL_Quit();
        exit(13);
    } // if
} // go_to_new_vid_mode

void setvmode(int mode)
{
    if (mode == 0x3)  // text mode.
    {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        return;
    }

    if (mode == 0x13)
    {
	go_to_new_vid_mode(-1, 320, 200);
    }

    else
    {
        fprintf(stderr, "setvmode(0x%x) is unsupported in SDL driver.\n", mode);
        exit(13);
    }
}

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

void cleartopbox (void)
{
	fprintf (stderr, "FILLME: cleartopbox\n");
}

void drawchainpixel (long edi, long ebx)
{
	fprintf (stderr, "FILLME: drawchainpixel\n");
}

void cleartext (void)
{
	fprintf (stderr, "FILLME: cleartext\n");
}

int gifgetdat (long eax, long ebx, long ecx)
{
	fprintf (stderr, "FILLME: gifgetdat\n");
	return 0;
}

unsigned char getpixel(long offset)
{
    return( *((unsigned char *) offset) );
}

void drawpixel(long offset, Uint8 pixel)
{
    *((Uint8 *) offset) = pixel;
}

void drawpixels(long offset, Uint16 pixel)
{
	*((Uint16 *) offset) = pixel;
}

void drawpixelses(long offset, Uint32 pixel)
{
	*((Uint32 *) offset) = pixel;
}

void clear2dscreen(void)
{
    SDL_Rect rect;

    rect.x = rect.y = 0;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_FillRect(surface, &rect, 0);
} // clear2dscreen

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
