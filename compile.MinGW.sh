#!/bin/sh -e

export FLAGS=-O3
export CFLAGS=-O3
cd fltk-1.1.9
./configure --enable-localpng
make
cd ..
cd zlib-1.2.3
./configure
make
cd ..
cd glbsp-2.24-source
make
cd ..
cd ObHack-engine-697
cd gui
make
