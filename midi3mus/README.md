# What is this

This converts standard MIDI files in to the unusual MUS format used by
Doom.

# Where this comes from

See https://www.doomworld.com/forum/topic/55814-midi2mus-64-bit-compatible/?tab=comments#comment-980861

# How to compile

```
make
```

# Other discussion

https://doomwiki.org/wiki/MUS

# Why this is here

https://github.com/samboy/ObHack/issues/15

Doomsday 1.8.6 (an older version I use on my tiny 50-megabyte business
card CD) has issues playing the newer MIDI files in FreeDoom 0.12; the
MIDI does not always start playing, and there is a gap before the MIDI
loop starts.  

By converting these MIDI files in to MUS files, both issues go away in
my fork of the FreeDoom `DOOM2.WAD` file which I call “ObHack FreeDoom”.

# Copyright

See the file COPYING for the license.  There isn’t an actual copyright
notice, so I will presume this is copyright © 2011 Natt, as well as
Copyright © 2020 Sam Trenholme (for adding this README.md file,
the COPYING file, and converting this in to a Git friendly format).

