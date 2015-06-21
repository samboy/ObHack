Obhack 007.4

Added: a 'Brighter' light setting.

Adjusted: Lowered light levels in arches, windows, doorways...etc. 

Adjusted: All light brightness in skylights and roof openings now match
outdoor light setting.

A few other minor internal adjustments.


Obhack 007.3

Reconfigured GUI to three columns for better compability for 800x600.

New parameter: Hallways, to control amount of hallways.

Added: Red and Green torches to outdoor fences.

Added: Chaingun and Dragon Claw to start weapons.

Adjusted: Texture alignment on multiple Arches.

Added: Two themes from mrChris.

And a few other minor fixes.


Obhack 007.2

Added: Icons to execute file.

Added: More enclosures and minor adjustments to older ones.

Added: 'Gigantic' setting to level size parameter.(For upper-end machines)

Added:  Multiple new switches to Doom games.

Added: 'Infested' setting to monsters parameter.

New parameter: 'Quest Length' to adjust length of quests.

Bugfix: Outdoor area lighting more consistent.

Bugfix: Removed Spidermastermind from Deathmatch type maps.



Obhack 007.1

Added: Monster Enclosures(small monster traps with triggers) to all Doom based games.

New parameter: 'Monster Enclosures' in gui, to turn enclosures On or Off.

A few more minor fixes resolved.



Obhack 007.0

Bugfix: Fixed Hexen & Heretic parameters with insane setting.
 
Bugfix: Fixed the infinite loop error when making maps.

Enabled the Bosses for boss-levels.


Obhack 006.9

New parameter: 'Max Level Size' to progressive & expansion level sizes.

Added: 'Insane' & 'Insane+weapons' settings to monster parameter. (Heavy Monsters).

Bugfix: Fixed Cyberdemon's head in ceiling in smaller rooms.

Wokeup the SpiderMastermind, in larger rooms.

A few revisions to the gui and other minor fixes.


Obhack 006.8

Bugfix: Large weapons are now quest items(SSG, Launcher, BFG).

Bugfix: Fixed 2 missing texture issues.

Bugfix: Fixed lighting issue, 'None' setting is now default as in previous versions.

Bugfix: Fixed issue with writing texture patches multiple times.

Replaced some wall textures and wokeup the Cyberdemon.

And a few other minor fixes.


Obhack 006.7

Added 'Random' setting to RoomSize and Steepness parameters.

Bugfix: Fixed issue with Puzzles setting.

Multiple bugfixes concerning making of Deathmatch maps.


Obhack 006.6

New parameter:Room Lighting, changes light levels in cells. 'None' is default lighting.

Much expanded new Doom1 & Doom2 room themes/textures thanks to Mr.Chris.

Added a Rare setting to the health and a Rare & None settings to ammo, Rare gives about half than the Less option.

Renamed start weapons to clarify weapons.

Bugfix: Fixed issue with the making of Heretic maps incorrectly.


Obhack 006.5

Bugfix: Fixed the'secret spoiler'issue outside secret rooms on small maps.

Added a few new room textures.


Obhack 006.4

Bugfix: A few more prefab ceiling issues fixed.

New parameter added to KeyType: Skulls or Cards, randomly chooses skulls 
or keycards per level map.

New parameter:Room Size, enlarges room sizes, nothing drastic here just
nudges the cell size a bit.


Obhack 006.3

Bugfix: We no longer have monsters extending through ceiling on top
of certain structures.

New parameter: KeyType, determines weather keys are skulls or keycards.

New size parameter: Expansion, for Doom2 type games, steadily expanding
from map 1 thru 32.

Added a couple perfabs.


ObHack 006b

Bugfix: Default game is Doom2 again

Bugfix: We no longer have monsters and items on crates (finally fixed)

"Doom 1 Mr. Chris" game now intergrates more of Mr. Chris' changes

ObHack 006a

New parameter: Switches, which determines whether all of the puzzle quests
are key quests, switch quests, or a mixture of the two.

x_{game}.lua file format changed to be more compatible with Oblige II's 
format (to make things easier for third-party modders)

New Game type: "Doom 1 Mr. Chris"; this is a version of Mr. Chris' expanded
textures that makes levels for Doom 1 (he did some other stuff like Skulltag
and what not, which I didn't feel was worth implementing).

ObHack snap 20090408

Secret doors are now correctly marked as secret, so one can't simply find 
them by glancing at the map.

ObHack snap 20090404

One big part of traditional Doom levels is that every level has some secret
that the player should find.  In addition, the secret is not easily found.

I have made ObHack-generated secrets more in line with traditional Doom 
secrets.  Every level has at least one secret, and secrets are no longer
trivial to find; you have to pay attention to find a secret door.

ObHack 005c

Bugfix: We no longer have the Wolfenstein door in the nature theme (since
there was no door in the nature theme, ObHack defaulted to this door 
because it was the last door listed; tricky bug to find but thankfully
Andrew found it in the Oblige 0.97 update)

FLTK updated to 1.1.9 (I prefer using a supported version, and it makes
the source smaller)

ObHack 005b

Memory leak in new RNG fixed.

Doom2 themes modified to not use any Wolf textures unless in the Wolf secret
levels.

ObHack 005a

This is a simple change to ObHack 004a: The RNG seed now uses RadioGatun32
instead of the Mersenne Twister, which allows the RNG to use an arbitrary
string as the seed; this should satisfy "TheInitialCommand"'s desire for
there to be more possible maps.  RNG seeds now can contain letters, symbols,
etc, and can be up to 16 characters long.

ObHack 004a

This is ObHack snap 20080825 declared stable.  I am, at this point,
freezing ObHack; the only changes will be bug fixes and I have no plans
to implement new features.  This might change when and if the next
major release of Oblige comes out.  We'll see.

ObHack snap 20080825

Backporting a little bit of code which puts the occassional Caco in Doom
levels.  Adding hooks in mosters.lua that allow maps to not have low-level
monsters; not going to be implemented.

ObHack snap 20080817

Bugfix: Putting mosters on crate bugfix ported from Oblige 0.97

ObHack snapshot ReadMe

Enhas a contributed a lot of code here; he has improved the Freedoom
preset so that it doesn't include incomplete monsters, and won't have
ugly things hanging.  He has also tweaked planning.lua so that the
tiny and small levels are a little bigger, but don't have problems
with tiny levels starting in the exit, or having a key in the start
room in small levels.  Also, the megasphere is not as common in
Doom 2; if you need more health, I have already tweaked things
so "more" gives you a lot more health than Oblige gives you at
"more".

I have added a new size: Progressive.  What this does is, for a 
given episode, have earlier levels be smaller and later levels
be bigger.  In Doom 2/Freedoom, levels get bigger in cycles of
11 levels; level 11 is huge, and level 12 is tiny, for example.
The secret levels are the largest levels.

I have added, at Enhas' request, a new outdoors setting: Rare.  
This makes maps where outdoor areas are fairly rare, but still
exist.  This is a good setting for older computers that can't
handle the framerate penalty of large outdoors areas, but when
players still want the occassional outdoors.

There are two new games types added to the ObHack pop-down menu:
DM (no exits), which is DeathMatch without exits; this is useful
for source ports with Quake-style automatic level cycling.  There
is also an option for Cpature the Flag, which currently just makes
standard Deathmatch levels, but allows someone who wants CTF to
modify plan_dm.lua to add CTF support for source ports that support
CTF.

The Heretic preset has been greatly expanded; "Hells maw" now uses 
outdoor-looking textures, giving it a feel more like the original 
"Hells maw" (instead of just putting a castle in hell).  The 
outdoors feel is "wetter" than the original Raven maps; this
is a concession to the fact that Heretic has very few outdoor
textures.

"The Domes" now has its own theme, similar to the E1 castle theme,
but with less grey rocks, and a couple of "Disco" looking 
texture sets, to give it a somewhat different look than E1.

Episode 4 uses its own theme; a very sandy theme that I call
"Egypt".  

Episode 5 has its own rather garish theme. The reason this 
theme is so garish is because the blues and reds in Heretic are 
quite loud; I wanted something different from greys and browns, 
so the episode here is a surrealistic set of blues and reds.

There are now a few hallway presets, allowing heretic maps to 
have hallways indoors.

ObHack 003e ReadMe

ObHack 003e is simply ObHack 003d with some Freedoom preset 
improvments submitted by Enhas.  This otherwise makes levels
identical to ObHack 003d; unless you want to make Freedoom
levels, you will see no change whatsoever.

ObHack 003d ReadMe

First of all, one thing that has been annoying me with these ObHack
maps is that they aren't outdoors enough.  So, I've added a new
user-settable parameter: Outdoors.  This determines how much
outdoors a given map has.  It has five settings:

* Indoors: No outdoor areas whatsoever

* Some: Generate the exact same maps that 003b generates

* More: If the player starts outdoors, this generates pretty much
  the same map 003b generates.  Otherwise, it tweaks the map until
  the player starts outdoors.

* Lots: Like more, but also makes it more likely that there will be
  more outdoor areas.

* Outdoors: Almost completely outdoors, with the exception of a 
  room here or there, and the exit area.

Note that setting outdoors to anything higher than "some" causes 
Doom1 to only use a single theme for the initial area, "Urban", since
this is the only Doom1 theme with outdoor areas.  Doom2 is a lot
better, since it also has the "Nature" outdoors theme.

In addition, huge all-outdoor maps can lower the framerate.  On my system,
using a Core Dual 1.5ghz, with a generic Intel video card, huge outdoor
areas sometimes lower the frame rate to 30fps or so.  This slowdown 
doesn't seem to be as bad with Heretic, since there are more walls put
everywhere.  If you have an older computer, either don't make outdoors
areas, or only make them with smaller maps.

Another new feature is "Start weapon" which can help balance deathmatch.
What this does is put, at each non-coop player's start (both for
single player and deathmatch) a weapon.  The weapon is a shotgun
in Doom(2) and a Crossbow in Heretic when set to "Basic"; the weapon
is a Rocket Launcher in Doom(2) and a Phoenix Rod in Heretic when set
to "Hardcore".  This makes things less unbalanced in tiny deathmatch
maps, since a player can now be guaranteed to have some reasonable
weapon when they spawn.  It's also useful in single player if you
don't feel like playing "hunt for the shotgun/crossbow" when starting
a map.

Yet another feature I have added in this release of ObHack is Single Player
+ Deathmatch maps.  These are maps that try to be both reasonable Single
Player and Deathmatch maps; they are single player maps where the only
things you find when looking for goodies are weapons, and where no doors
are opened by switches.  These maps also have coop starts, in case you
feel like playing coop with these maps.  If there is a "start weapon"
in these maps, all the deathmatch starts will have the start weapon, but
only when playing multiplayer (coop or deathmatch).

And, oh, for hardcore players who think the maps are far too easy, you can
now have twice as many monsters as "hordes"; "swarms" should be enough 
monsters to satisfy even the kind of people who wake up every morning, 
play Doom for eight hours, and have been doing this every day since Doom 
came out in 1993.  If that is you, just set monsters to "swarms", health
to "none", and ammo to "less", and play through an entire 32-map Doom2
megawad.

I have also fixed some bugs:

* No longer do we have cracks in the floors when steepness is "some" or
  "a little"

* I have somewhat solved the problem with rooms in secrets being a lot
  lower or higher than the room they are next to.  In particular, "flat"
  should now always be completely flat.

ObHack 003b ReadMe

--ObHack 003b; a fork of OBLIGE by Sam Trenholme--

Late 2007

OK, Since Andrew has noted that he is in the process of re-writing 
OBLIGE, I figured I would get my hands dirty with the code and fix
some bugs and add some features to the code.

First of all, I have changed the size of the maps.  There are now
five sizes: Tiny, Small, Medium, Large, and Huge.  Tiny is *really*
tiny; a map will be between two and seven "cells" (rooms, but also 
outdoor areas) in size.  Small is also really small; between five 
and ten cells in size.  Medium is Oblige's "small" size; "large"
is Oblige's "medium" size, and "huge" is Oblige's "large" size.
I tried making huge bigger, but not only do the maps take a long
time to generate, they also have a very poor framerate.

Why does ObHack support single player maps that are so small?
Well, sometimes it's fun to play a mini-megawad of Doom 2 that
one can finish in about an hour.  Did I mention that single 
player maps now have deathmatch starts?  The tiny SP maps
make for an interesting change of pace when playing deathmatch,
such as having a few monsters in the way to kill while hunting
for you opponent.  Keep in mind that SP maps are optimized for
single player; I don't guarantee that there will be enough
weapons for good DM play when playing Deathmatch in a SP
map.

Speaking of DM, Deathmatch maps have also been made smaller, with 
the current "huge" being Oblige's "large" deathmatch map, "large" 
being Oblige's "medium" deathmatch, "medium" being the size of 
Oblige's small DM maps, and with both "small" and "tiny" making 
really, really small DM maps suitable for Overload-style 1-on-1 
deathmatching.

Some other adjustment tweaks: It is now possible to have monsters
be "rare"; this gives the level about half as many monsters as
a level with "scarce" monsters.  This is useful for people who 
play Doom as well as I play Doom; this is also useful for people
playing a single player map in deathmatch mode.  It's also possible
for ObHack to now make levels without health at all; this is mainly
for deathmatch play, but may be useful for hardcore Doom players
who feel Oblige's maps are far too easy; they can now try to 
complete a Doom2 megawad without any health whatsoever.

I have also added another parameter: Steepness.  People have 
complained that Oblige's maps have too much going up and down
stairs; steepness controls this.  If set to flat, the map will
usually be completely flat without stairs, with only a staircase
(or lift) once in a blue moon.  At "steep", Oblige's original 
amount of staircases is kept.  The other two steepness values 
cover a middle ground.

As another feature, I have some good news and some bad news.  The 
good news is that Heretic support is greatly improved; the bad 
news is that I have dropped support for Hexen and Wolf3D, since 
I don't have either of those games to playtest against.  

In addition, it is now possible to make maps from the command 
line without having to mouse around in the editor.  I added this
feature to help me test the code (to make sure it can, for 
example, make 100 maps without crashing).   To do this, first
open up ObHack normally and select the parameters you want
(type of game, type of map, size, difficulty, steepness, etc.)
Now close ObHack and invoke it from the command line thusly
in the directory with ObHack(.exe):

ObHack {seed}

Where {seed} is a number from 0 to 500000 or so.  This will
open up the GUI, which will proceed to make the map with the
parameters you have already selected and the seed selected
from the command line.  

Once the map is made, the ObHack window will close and the
map will be generated.  The map will be saved in a file with
the same name as the seed you chose (without the .wad 
filename extension, alas) in the same directory as ObHack.

This allows people familiar with *NIX shell scripts of .bat
files to write small scripts that automatically make a large 
number of maps.  It's also useful on older, slower computers 
where you may wish to render a series of large megawads 
overnight unattended.

I have also fixed a number of bugs in the code and have made
the source code a little harder to read (Sorry, Andrew) :)

- Sam

OBLIGE 0.94 Read-Me
===================

by Andrew Apted.   July 2007


INTRODUCTION

  OBLIGE is a random level maker for the following games: DOOM 1,
  DOOM 2, Final DOOM, FreeDOOM, Wolfenstein-3D, Heretic 1 and
  Hexen 1. These games all share the same basic level structure
  (except for Wolf3d which is much more limited).

  OBLIGE will have the following features which set it apart from
  existing programs (like the famous SLIGE by David Chess) :-

    * higher quality levels, e.g. outdoor areas!
    * easy to use GUI interface (no messing with command lines)
    * built-in node builder, so the levels are ready to play
    * uses the LUA scripting language for easy customisation
    * can create Deathmatch levels
    * Heretic and Hexen support!


STATUS

  OBLIGE 0.94 is the current version, which was released pending a
  rewrite of the core level-making algorithms. The GUI interface
  is simple but very usable. The battle simulator produces
  reasonable ammo and health to fight the monsters in the map.

  NOTE WELL: The 0.94 release does have some problems.  I am
  releasing it so that I can begin rewriting the level-building
  code to fix these problems (and also to generate better
  architecture).  For example, you might get an error message
  saying that some stairs or a switch could not be added into a
  room.  The only workaround is to try a different SEED value.

  See below for the status of each game...

  There is still a lot to do however. There is no support (yet)
  for the special levels, such as the end-of-episode levels of
  DOOM 1 and the end-of-game level (MAP30) of DOOM 2. Other
  desirable features are: nicer (non-square) architecture,
  player teleporters, and better lighting.


CHANGES IN 0.94

  +  new prefab system.
  +  new theme system for more consistent levels.
  +  different sized rooms.
  +  greatly improved Hexen support.

  -  new adjustments for level size and puzzles.
  -  adjustments for deathmatch games.
  -  secret areas and levels.
  -  balconies.

  -  experimental Wolfenstein-3D support.
  -  later levels get progressively harder.
  -  slightly better Heretic maps.
  -  more DOOM themes.

Note: some things also broke in this release, e.g. traps :-(


CHANGES IN 0.85

  +  Hallways!  Crates!  New Exits!
  +  better algorithm for choosing floor/ceiling heights.
  +  user adjustments for health/ammo/monsters/traps.
  +  current settings are remembered when you quit.

  -  support for FreeDOOM, TNT Evilution and Plutonia.
  -  levels are watermarked with some Oblige logos.
  -  delete temporary wad when build has finished.
  -  collect all log messages into a file (LOGS.txt).
  -  removed the unnecessary menu bar.

  -  fixed the (rare) non-working switches and lifts.
  -  surprise traps: improved placement, fairer monsters.
  -  tweaked battle simulation to provide more ammo.
  -  neater placement for health and ammo items.


USAGE GUIDE

  The graphical interface for OBLIGE is quite easy to use.

  At the top is the Settings panel, which contains the most
  important settings.

  The first control is the "SEED" number. Each SEED number makes
  a unique, distinctive level. Using the same SEED number always
  produces the exact same level (as long as the other settings
  are the same).

  Other settings include:

    * the "Game" type (DOOM, WOLF3D, HERETIC or HEXEN),
    * the "Mode" of the game (SINGLE-PLAYER, CO-OP, or DEATHMATCH)
    * the "Length" of the output wad (SINGLE-LEVEL, ONE-EPISODE,
      or FULL-GAME).

  In the Adjustments panel you can control the size of the created
  levels, as well as how much health, ammunition and how many
  monsters and puzzles are added. OBLIGE also implements the various
  skill levels for each map (e.g. Hurt-me-Plenty vs Ultra-Violence).

  After you've chosen the desired settings, press the "Build..."
  button, which will open a Save-File dialog asking you what the
  output file should be. Enter something appropriate, e.g. TEST,
  and after that OBLIGE will starting building the levels.

  In Wolfenstein-3D mode, the "Build..." button does not bring up
  a dialog box. OBLIGE simply creates the output files in the same
  folder where it is installed. These files are called GAMEMAPS.WL6
  and MAPHEAD.WL6 and you need to copy them into your Wolf3d folder
  (after making a backup!).

  To exit, press the "Quit" button in the bottom right corner.

  The levels created by OBLIGE are ready to play. There is no need
  to run the output WAD file through a node-builder program, since
  OBLIGE does this automatically.

  You should use a Source Port to play the levels, because the
  original DOOM.EXE, DOOM2.EXE (etc..) may not cope with the
  architecture which OBLIGE creates. For example, you might get
  the "Visplane Overflow" error, which quits the game.


STATUS OF EACH GAME

  DOOM 1: fairly well tested and working well.

  DOOM 2: the most well tested game and produces the best results.

  HERETIC: tested and working quite well, though very lacking in
  different themes and scenery.

  HEXEN: tested and works pretty well (greatly improved since
  the last v0.85 release). The sequence of hubs is not working
  properly yet.

  WOLF 3D: very buggy and incomplete at the moment.  It lacks:
  pushwall secrets, patrolling enemies, treasure rooms, proper
  episode endings, and may create levels with too many actors
  or static objects.


ACKNOWLEDGEMENTS

  Thanks to Derek "Dittohead" Braun for making a whole swag of
  Prefab structures, which kicked off some big improvements to
  the way OBLIGE builds stuff.

  Thanks to JohnnyRancid who also created heaps of prefabs for
  OBLIGE.

  Thanks to DoomJedi for his help.

  I'm grateful to everyone who provided positive feedback, bug
  reports and ideas for improvements, both in email and on the
  various forums. Cheers guys!

  OBLIGE uses the cool FLTK widget library (http://www.fltk.org).


COPYRIGHT and LICENSE

  OBLIGE Level Maker

  Copyright (C) 2006-2007 Andrew Apted

  OBLIGE is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 2 of the License,
  or (at your option) any later version.

  OBLIGE is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.


CONTACT DETAILS

  Email: <ajapted@users.sf.net>

  Website: http://oblige.sourceforge.net/

  Project page: http://sourceforge.net/projects/oblige/

