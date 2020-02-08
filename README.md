# Important note

This is a special .697 release of ObHack which is sized optimized
and designed to always create the exact same maps when given the
same parameters.

This is an older, outdated release of ObHack; most people will
want to use the most recent release instead (or, likewise, Oblige 6
or Oblige 7)

## Determinism

ObHack, has, until recently, had issues with making different maps
when given the same parameters because one of Lua’s table (think
dictionary) iterators is non-deterministic.  I have updated the
ObHack code to never use that iterator.  In addition, glbsp would
add a timestamp to the generated wads; I have removed this time stamp.

Now, if I run the ObHack program with the same seed and parameters, I will
get a given .wad file; multiple invocations will give me a file with the
same size and exact same contents (i.e. its SHA-256 sum is the same for
all .wad files).  

Curiously, if I run the program in Windows XP instead of Windows 10, I will
get a different file, but multiple invocations make the same file there,
and the underlying maps in the file are exactly the same.  For some reason,
Windows XP packs the .wad file differently than Windows 10 does.

As a side effect, the maps are different than the maps generated before
making the code deterministic.

## About

ObHack is my name for some modifications Fritz and myself have made
to Oblige, a random map generator for the original Doom, Doom 2, and
Heretic. It is name thusly because it is a hacked Oblige, and as a tribute
to the ObHacks posted to the once-great Usenet newsgroup alt.hackers.

ObHack is a fork of version 2 of Oblige (Oblige 0.81-0.97). It has the
following features that Oblige2 does not have:

* Real secret areas that take work to find
* Improved random number generator which allows arbitrary English or 
  Spanish text to be the seed, resulting in a nearly infinite number of 
  possible seeds
* New modes: Single Player + Deathmatch, Deathmatch without exits, and 
  Capture the Flag
* Progressive level size: Levels get bigger as one gets to higher levels 
  in the wad
* Enclosures and variable room sizes
* Adjustable light level
* Tiny and gigantic level sizes
* Option to have swarms or even more mosters
* Monster traps are back (removed in Oblige 0.94)
* Boss levels now have boss monsters in them
* Choice of player starting weapon
* More texture packs, including contributions from Mr. Chris
* Deathmatch starts in single player maps
* And other features not listed here 

Oblige URL: http://oblige.sourceforge.net/

## How to compile

These are the files needed to make the Win32 binary of ObHack.  To compile, 
you will need to install both MinGW-3.1.0-1 and MSYS-1.0.10.  Once you do 
that, do something like this:

```
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
```

MinGW and MSYS install directions are here:

http://samiam.org/blog/old-200903-mingw-310-1-last-real-mingw-release.html

