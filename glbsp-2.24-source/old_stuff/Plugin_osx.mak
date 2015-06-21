#
# glBSP Plugin Makefile for MacOSX
#

BIN=libglbsp.a

CC=gcc
CFLAGS=-O2 -Wall -DGLBSP_PLUGIN -DMACOSX -DINLINE_G=inline

# ----- OBJECTS ------------------------------------------------------

OBJS= \
     src/analyze.o  \
     src/blockmap.o \
     src/glbsp.o    \
     src/level.o    \
     src/node.o     \
     src/reject.o   \
     src/seg.o      \
     src/system.o   \
     src/util.o     \
     src/wad.o

# ----- TARGETS ------------------------------------------------------

all:    $(BIN)

clean:
	rm -f $(BIN) *.o

$(BIN): $(OBJS)
	libtool -static -o $(BIN) - $(OBJS)
	ranlib $(BIN)

.PHONY: all clean

