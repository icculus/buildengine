#----------------------------------------------------------------------------
# Makefile for building BUILD on Unix/Cygwin systems.
#
#  Written by Ryan C. Gordon (icculus@linuxgames.com)
#   Do NOT contact Ken Silverman for support of BUILD on Unix or Linux.
#----------------------------------------------------------------------------

#-----------------------------------------------------------------------------#
# If this makefile fails to detect Cygwin correctly, or you want to force
#  the build process's behaviour, set it to "true" or "false" (w/o quotes).
#-----------------------------------------------------------------------------#
#cygwin := true
#cygwin := false
cygwin := autodetect

#-----------------------------------------------------------------------------#
# You only need to set SDL_INC_DIR and SDL_LIB_DIR if you are using cygwin.
#  SDL_INC_DIR is where SDL.h and associated headers can be found, and
#  SDL_LIB_DIR is where SDL.lib and SDL.dll are located. These may be set as
#  environment variables, if you'd prefer to not hack the Makefile.
#
# examples:
#   SDL_INC_DIR := C:/2/SDL-1.1.8/include
#   SDL_LIB_DIR := C:/2/SDL-1.1.8/lib
#-----------------------------------------------------------------------------#
ifeq ($(strip $(SDL_INC_DIR)),)
  SDL_INC_DIR := please_set_me_cygwin_users
endif

ifeq ($(strip $(SDL_LIB_DIR)),)
  SDL_LIB_DIR := please_set_me_cygwin_users
endif


#-----------------------------------------------------------------------------#
# To use a different platform's ASM or portable C, change this.
#  (note that this MUST be -DUSE_I386_ASM right now if you even want a
#   prayer of having a successful compilation.)
#-----------------------------------------------------------------------------#
USE_ASM := -DUSE_I386_ASM


#-----------------------------------------------------------------------------#
# Don't touch this unless you know what you are doing.
#-----------------------------------------------------------------------------#
#useperl := true
useperl := false

#useopengl := true
useopengl := false
GL_INCLDIR := /usr/X11R6/include



#-----------------------------------------------------------------------------#
# Everything below this line is probably okay.
#-----------------------------------------------------------------------------#

ifeq ($(strip $(cygwin)),autodetect)
  ifneq ($(strip $(shell gcc -v 2>&1 |grep "cygwin")),)
    cygwin := true
  else
    cygwin := false
  endif
endif


ifeq ($(strip $(cygwin)),true)
  ifeq ($(strip $(SDL_INC_DIR)),please_set_me_cygwin_users)
    $(error Cygwin users need to set the SDL_INC_DIR envr var.)
  else
    SDL_CFLAGS := -I$(SDL_INC_DIR)
  endif

  ifeq ($(strip $(SDL_LIB_DIR)),please_set_me_cygwin_users)
    $(error Cygwin users need to set the SDL_LIB_DIR envr var.)
  else
    SDL_LDFLAGS := -L$(SDL_LIB_DIR) -lSDL
  endif
else
  SDL_CFLAGS := $(shell sdl-config --cflags)
  SDL_LDFLAGS := $(shell sdl-config --libs)
endif

CC = gcc

ifeq ($(strip $(cygwin)),true)
  ASM = nasmw
  EXE_EXT = .exe
  ASMOBJFMT = win32
  ASMDEFS = -dC_IDENTIFIERS_UNDERSCORED
  CFLAGS += -DC_IDENTIFIERS_UNDERSCORED
else
  ASM = nasm
  EXE_EXT =
  ASMOBJFMT = elf
endif

ifeq ($(strip $(useopengl)),true)
  CFLAGS += -DUSE_OPENGL -I$(GL_INCLDIR)
endif

ifeq ($(strip $(useperl)),true)
  CFLAGS += -DUSE_PERL
  LDPERL := $(shell perl -MExtUtils::Embed -e ldopts)
  CCPERL := $(shell perl -MExtUtils::Embed -e ccopts)
    # !!! can I lose the explicit path somehow?
  PERLOBJS += buildperl.o /usr/lib/perl5/i386-linux/CORE/libperl.a
endif

LINKER = gcc
CFLAGS += $(USE_ASM) -Werror -funsigned-char -DPLATFORM_UNIX -O2 -g -Wall $(SDL_CFLAGS) -fasm -fno-omit-frame-pointer
LDFLAGS += -g $(SDL_LDFLAGS)

GAMEEXE = game
GAMESRCS = game.c engine.c cache1d.c sdl_driver.c unix_compat.c
GAMESRCS += a_linux.asm pragmas.c a.c multi_tcpip.c
#GAMESRCS += multi.c k.asm kdmeng.c

BUILDEXE = build
BUILDSRCS = build.c bstub.c engine.c cache1d.c sdl_driver.c unix_compat.c
BUILDSRCS += a_linux.asm pragmas.c a.c

ASMFLAGS = -f $(ASMOBJFMT) $(ASMDEFS)

# Rules for turning source files into .o files
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<

# Rule for getting list of objects from source
GAMEOBJS1 := $(GAMESRCS:.c=.o)
GAMEOBJS := $(GAMEOBJS1:.asm=.o)
BUILDOBJS1 := $(BUILDSRCS:.c=.o)
BUILDOBJS := $(BUILDOBJS1:.asm=.o)

CLEANUP = $(GAMEOBJS) $(BUILDOBJS) $(PERLOBJS) \
          $(GAMEEXE) $(BUILDEXE) \
          $(wildcard *.exe) $(wildcard *.obj) \
          $(wildcard *~) $(wildcard *.err) \
          $(wildcard .\#*) core

all: $(BUILDEXE) $(GAMEEXE)

ifeq ($(strip $(useperl)),true)
buildperl.o : buildperl.c
	$(CC) -c -o $@ $< $(CFLAGS) $(CCPERL)
endif

$(GAMEEXE) : $(GAMEOBJS) $(PERLOBJS)
	$(LINKER) -o $(GAMEEXE) $(LDFLAGS) $(LDPERL) $(PERLOBJS) $(GAMEOBJS)

$(BUILDEXE) : $(BUILDOBJS)
	$(LINKER) -o $(BUILDEXE) $(LDFLAGS) $(BUILDOBJS)

clean:
	rm -f $(CLEANUP)


#-----------------------------------------------------------------------------#
# This section is pretty much just for Ryan's use to make distributions.
#  You Probably Should Not Touch.
#-----------------------------------------------------------------------------#

# These are the files needed in a binary distribution, regardless of what
#  platform is being used.
BINSCOMMON  = build$(strip $(EXE_EXT)) game$(strip $(EXE_EXT))
BINSCOMMON += ascboard.map boards.map evilal.map kensig.map nsnoal.map
BINSCOMMON += test.map nukeland.map
BINSCOMMON += stuff.dat
BINSCOMMON += BUILDLIC.TXT
BINSCOMMON += names.h


package: clean
	cd .. ; zip -9rz ./BUILD-engine-$(shell date +%m%d%Y).zip buildengine -x "*CVS*" < buildengine/FILEID.DIZ


ifeq ($(strip $(cygwin)),true)
msbins: win32bins dosbins

win32bins:
	wmake -f Makefile.w32 clean
	wmake -f Makefile.w32
	cp $(SDL_LIB_DIR)/SDL.dll .
	echo -e "\r\n\r\n\r\nHEY YOU.\r\n\r\n\r\nTake a look at README-win32bins.txt FIRST.\r\n\r\n\r\n--ryan. (icculus@linuxgames.com)\r\n\r\n" |zip -9rz ../BUILD-win32bins-$(shell date +%m%d%Y).zip $(BINSCOMMON) SDL.dll README-win32bins.txt README CHANGELOG

dosbins:
	wmake -f Makefile.dos clean
	wmake -f Makefile.dos
	cp C:/WATCOM/BINW/DOS4GW.EXE .
	echo -e "\r\n\r\n\r\nHEY YOU.\r\n\r\n\r\nTake a look at README-dosbins.txt FIRST.\r\n\r\n\r\n--ryan. (icculus@linuxgames.com)\r\n\r\n" |zip -9rz ../BUILD-dosbins-$(shell date +%m%d%Y).zip $(BINSCOMMON) README-dosbins.txt README CHANGELOG DOS4GW.EXE

else
msbins: nocygwin
win32bins: nocygwin
dosbins: nocygwin
endif

nocygwin:
	@echo This must be done on a Windows box in the Cygwin environment.

#-----------------------------------------------------------------------------#
# End packaging section.
#-----------------------------------------------------------------------------#

# end of Makefile ...

