#
# File: Makefile
#
# Written by Tim Niemueller <tim@niemueller.de>
# Created on 2002/05/07
#

# ressource path. some people might want to change this to another
# directory than the source files
R = ./

VERSION = 0.8

CC = m68k-palmos-gcc
CFLAGS = -O2 -Wall

PILRC = pilrc
PFLAGS = -q -I $(R)

PILOTRATE=115200
PILOTXFER=/usr/local/bin/pilot-xfer

OBJECTS=UniSorter.o color.o gadget.o quicksort.o insertionsort.o selectionsort.o bubblesort.o shellsort.o mergesort.o heapsort.o shakersort.o radixsort.o countsort.o
RSCBINS:=$(shell ls *.rcp | sed -e "s/rcp/bin/g")

DISTFILES=UniSorter.prc

UniSorter.prc: UniSorter $(RSCBINS)
	@echo RSCBINS: $(RSCBINS)
	build-prc UniSorter.prc "Uni Sorter" USRT UniSorter *.bin

all: clean UniSorter.prc

UniSorter: $(OBJECTS)


%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.bin: %.rcp UniSorter.h
	$(PILRC) $(PFLAGS) $<

install: clean all
	@echo -e "\n\nNo going to install Uni Sorter on PalmOS device\n"
	@echo -e "If you have a USB device press NOW the HotSync Button"
	@echo -e "and THEN press enter to continue.\n"
	@read foo </dev/tty
	PILOTRATE=$(PILOTRATE) $(PILOTXFER) -i UniSorter.prc

clean:
	-rm UniSorter *.o *.bin

