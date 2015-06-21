#
# glBSP Plugin: < Win32 + MinGW MAKEFILE >
#
# (Note: requires GNU make)
# 

# SHELL=bash.exe

BIN=libglbsp.a

#ZLIB_DIR="C:/Program Files/GnuWin32/src/zlib/1.2.3/zlib-1.2.3"
ZLIB_DIR=C:/Program\ Files/GnuWin32/src/zlib/1.2.3/zlib-1.2.3

INCS=-I$(ZLIB_DIR) 

CC=gcc
CFLAGS=-O2 -Wall $(INCS) -DGLBSP_PLUGIN -DWIN32 -DINLINE_G=inline

AR=ar r
RANLIB=ranlib

# ----- OBJECTS ------------------------------------------------------

OBJS= \
    src/analyze.o \
    src/blockmap.o \
    src/glbsp.o \
    src/level.o \
    src/node.o \
    src/reject.o \
    src/seg.o \
    src/system.o \
    src/util.o \
    src/wad.o

# ----- TARGETS ------------------------------------------------------

all: $(BIN)

clean:
	rm -f $(OBJS) $(BIN) 

%.o: %.c
	$(CC) $(CFLAGS) $(DEFINES) -c $< -o $@	

$(BIN): $(OBJS)
	$(AR) $(BIN) $(OBJS)
	$(RANLIB) $(BIN)
 
.PHONY: all clean

