I have added this directory so that, when checking out from Git, one does
not need to go through the long compiling process (documented in README.txt)
to update the Win32 binary.

To use this binary, place ObHack.exe in the ObHack-engine-00#.# directory

ObHack-debug.exe is a file that:

* Has debugging symbols 
* Is compiled with -O3 instead of -Os
* Does not remove TEMP.wad after running glBSP

