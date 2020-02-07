This is both a version of FreeDoom 0.7 (the most recent version of
FreeDoom compatible with dengine 1.8.6; note that newer versions of
FreeDoom are compatible with newer versions of dengine) modified to use
random maps and the random map generator used to make those random maps.
The file DOOM2.WAD is the modified FreeDoom 0.7 wadfile (for any engine
with Doom2 support; note that ancient versions of Doom may have Visplane
errors); ObHack.exe and the other files are the random map generator.

Note that the only randomly generated maps are MAP12, MAP13, and MAP14;
the first two maps come from FreeDoom, MAP30 is a deathmatch map from
a discussion in the FreeDoom message board, and the rest of the maps
are instant exit dummy maps (to save space).

The file Watermark.wad is designed to be used with an ObHack generated
wad to make the ObHack watermarks less obnoxious.

In addition to replacing some of FreeDoom's maps with random maps, I 
have:

* Changed the title screen to make it clear this is not an official
  version of FreeDoom

* Music updates:
  1. MAP03 (d_countd) copied to MAP13 (d_doom2)
  2. MAP09 (d_in_cit) copied to MAP21 (d_count2)
  3. MAP17 (d_stlks3) copied to MAP27 (d_romer2)
  4. MAP28 (d_tense)  copied to MAP08 (d_ddtblu)
  5. MAP12 (d_theda2) uses the theme it had back in early 2009. [1]
     
* Updated the Zombieman and Shotgun Guy graphics to use the 
  FreeDoom 0.9 versions

* Updated RSKY2 as per http://www.doomworld.com/vb/post/1393422

* Updated the Imp to be the version of Raymoohawk's serpentide at
  http://www.doomworld.com/vb/post/1396110
  
* Updated one tree to use Sergeant_Mark_IV's SMITA0 contributed at
  http://www.doomworld.com/vb/freedoom/72566-my-smita0-sprite/

* ObHack level markers in DOOM2.WAD are now pictures of a fire I 
  took in 2014 (including a 64x64 texture I made of the fire's smoke)

* Waterfall texture on DOOM2.WAD is now ObHack's blue waterfall

The DOOM2.WAD is a drop-in replacement for ID's DOOM2.WAD file, and
includes open-source versions of all the resources to play Doom using
an engine, such as dengine:

	http://dengine.net/

The source code for ObHack.exe:

	http://samiam.org/slump/ObHack-src-006b-pl1.7z

How to make the maps:

Using the supplied CONFIG.cfg and the seed "2FreeDoom1" (without the
quotes), one can generate the same maps as MAP12, MAP13, and
MAP14 supplied in the wadfile.

[1] There was concern that the contributor plagiarized other music, but
    there is no evidence he plagiarized this particular song.  See
    https://www.doomworld.com/forum/topic/46675-musical-plagiarism-in-freedoom/
    for discussion.

