#----------------------------------------------------------------------------
# Makefile for building BUILD on Unix systems.
#
#  Written by Ryan C. Gordon (icculus@lokigames.com)
#   Do NOT contact Ken Silverman for support of BUILD on Unix or Linux.
#----------------------------------------------------------------------------

USE_ASM = -DUSE_I386_ASM

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


# Rules for turning source files into .o files
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule for getting list of objects from source
GAMEOBJS1 := $(GAMESRCS:.c=.o)
GAMEOBJS := $(GAMEOBJS1:.asm=.o)
BUILDOBJS1 := $(BUILDSRCS:.c=.o)
BUILDOBJS := $(BUILDOBJS1:.asm=.o)

all: $(BUILDEXE) $(GAMEEXE)

$(GAMEEXE) : $(GAMEOBJS)
	$(LINKER) -o $(GAMEEXE) $(LDFLAGS) $(GAMEOBJS)

$(BUILDEXE) : $(BUILDOBJS)
	$(LINKER) -o $(BUILDEXE) $(LDFLAGS) $(BUILDOBJS)

a_linux.o: a_linux.asm
	$(ASM) -o a_linux.o -f elf a_linux.asm

k.o: k.asm
	$(ASM) -o k.o -f elf k.asm

clean:
	rm -f $(GAMEOBJS) $(BUILDOBJS) $(GAMEEXE) $(BUILDEXE) core

