BINARIES=sartest kreciptest
OBJS=kreciptest.o krecip.o sartest.o sar.o
CFLAGS=-g -Wall
CC=gcc
ASM=nasm

all: kreciptest sartest

kreciptest: kreciptest.o krecip.o sar.o
	$(CC) $(CFLAGS) -o kreciptest kreciptest.o krecip.o sar.o

kreciptest.o: kreciptest.c
	$(CC) $(CFLAGS) -c kreciptest.c

krecip.o: krecip.asm
	$(ASM) -o krecip.o -f elf krecip.asm

sartest: sartest.o sar.o
	$(CC) $(CFLAGS) -o sartest sartest.o sar.o

sartest.o:
	$(CC) $(CFLAGS) -c sartest.c

sar.o: sar.c sar.h
	$(CC) $(CFLAGS) -c sar.c

clean:
	rm -f *~ core $(BINARIES) $(OBJS)
