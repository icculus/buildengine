#----------------------------------------------------------------------------
# Makefile for building BUILD utilites on Unix systems.
#
#  Written by Ryan C. Gordon (icculus@lokigames.com)
#   Do NOT contact Ken Silverman for support of BUILD on Unix or Linux.
#----------------------------------------------------------------------------

# Programs to build
BINARIES = grpextract kgroup editart

CC = gcc
LINKER = gcc
CFLAGS = -g -O2 -DPLATFORM_UNIX -DUSE_I386_ASM `sdl-config --cflags`
LDFLAGS = 

# Editart is a beast of a different color
EALDFLAGS = $(LDFLAGS) `sdl-config --libs`

# Rules for turning source files into .o files
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(BINARIES) 

backmap5 : backmap5.o
	$(LINKER) -o backmap5 $(LDFLAGS) backmap5.o

backmap6 : backmap6.o
	$(LINKER) -o backmap6 $(LDFLAGS) backmap6.o

convmap6 : convmap6.o
	$(LINKER) -o convmap6 $(LDFLAGS) convmap6.o

convmap7 : convmap7.o
	$(LINKER) -o convmap7 $(LDFLAGS) convmap7.o

editart : editart.o pragmas.o sdl_driver.o
	$(LINKER) -o editart $(EALDFLAGS) editart.o pragmas.o sdl_driver.o

kextract : kextract.o
	$(LINKER) -o kextract $(LDFLAGS) kextract.o

kgroup : kgroup.o
	$(LINKER) -o kgroup $(LDFLAGS) kgroup.o

clean:
	rm -f $(BINARIES) *.o core

