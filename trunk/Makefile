#----------------------------------------------------------------------------
# Makefile for building BUILD on Unix systems.
#
#  Written by Ryan C. Gordon (icculus@lokigames.com)
#   Do NOT contact Ken Silverman for support of BUILD on Unix or Linux.
#----------------------------------------------------------------------------

# set this to "true" if you are building on Cygwin. Leave it false otherwise.
cygwin = false

# To use a different platform's ASM or portable C, change this.
#  (note that this MUST be -DUSE_I386_ASM right now if you even want a
#   prayer of having a successful compilation.)
USE_ASM = -DUSE_I386_ASM



# Everything below this line is probably okay.



CC = gcc
ASM = nasm
LINKER = gcc
CFLAGS = $(USE_ASM) -funsigned-char -DPLATFORM_UNIX -O2 -g -MMD -Wall $(shell sdl-config --cflags) -fasm -fno-omit-frame-pointer
LDFLAGS = -g $(shell sdl-config --libs)

GAMEEXE = game
GAMESRCS = game.c engine.c cache1d.c sdl_driver.c unix_compat.c
GAMESRCS += a_linux.asm pragmas.c a.c multi_tcpip.c
#GAMESRCS += multi.c k.asm kdmeng.c

BUILDEXE = build
BUILDSRCS = build.c bstub.c engine.c cache1d.c sdl_driver.c unix_compat.c
BUILDSRCS += a_linux.asm pragmas.c a.c

ifeq ($(cygwin), true)
ASMOBJFMT = win32
ASMDEFS = -dC_IDENTIFIERS_UNDERSCORED
CFLAGS += -DC_IDENTIFIERS_UNDERSCORED
else
ASMOBJFMT = elf
endif

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

CLEANUP = $(GAMEOBJS) $(BUILDOBJS) \
          $(GAMEEXE) $(BUILDEXE) \
          core

all: $(BUILDEXE) $(GAMEEXE)

$(GAMEEXE) : $(GAMEOBJS)
	$(LINKER) -o $(GAMEEXE) $(LDFLAGS) $(GAMEOBJS)

$(BUILDEXE) : $(BUILDOBJS)
	$(LINKER) -o $(BUILDEXE) $(LDFLAGS) $(BUILDOBJS)

clean:
	rm -f $(CLEANUP)

