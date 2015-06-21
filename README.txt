These are the files needed to make the Win32 binary of ObHack.  To compile, 
you will need to install both MinGW-3.1.0-1 and MSYS-1.0.10.  Once you do 
that, do something like this:

export FLAGS=-Os
export CFLAGS=-Os
cd fltk-1.1.9
./configure
make
cd ..
cd zlib-1.2.3
./configure
make
cd ..
cd glbsp-2.24-source
# You may have to edit the makefile
make
cd ..
cd ObHack-engine-*
cd gui
# You may have to edit the Makefile
make

MinGW and MSYS install directions are here:

http://maradns.blogspot.com/2009/03/mingw-310-1-last-real-mingw-release.html
