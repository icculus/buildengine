#----------------------------------------------------------------------------
# Makefile for building BUILD utilites on Unix systems.
#
#  Written by Ryan C. Gordon (icculus@lokigames.com)
#   Do NOT contact Ken Silverman for support of BUILD on Unix or Linux.
#----------------------------------------------------------------------------

# // "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
# // Ken Silverman's official web site: "http://www.advsys.net/ken"
# // See the included license file "BUILDLIC.TXT" for license info.

# Programs to build
BINARIES = grpextract kgroup

CC = gcc
LINKER = gcc
CFLAGS = -g -O2 -Wall -DPLATFORM_UNIX
LDFLAGS = 

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

editart : editart.o
	$(LINKER) -o editart $(LDFLAGS) editart.o

kextract : kextract.o
	@echo WARNING! kextract is BROKEN. Use grpextract instead!
	$(LINKER) -o kextract $(LDFLAGS) kextract.o

grpextract : grpextract.o
	$(LINKER) -o grpextract $(LDFLAGS) grpextract.o

kgroup : kgroup.o
	$(LINKER) -o kgroup $(LDFLAGS) kgroup.o

clean:
	rm -f $(BINARIES) *.o core

