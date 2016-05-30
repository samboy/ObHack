## What is ObHack?

ObHack is my name for some modifications Fritz and myself have made
to Oblige, a random map generator for the original Doom, Doom 2, and
Heretic. It is name thusly because it is a hacked Oblige, and as a tribute
to the ObHacks posted to the once-great Usenet newsgroup alt.hackers.

ObHack can make random maps for Doom, Doom2, TNT, Plutonia, FreeDoom (Phase 
II), Heretic, and Blasphemer. 

ObHack is a fork of version 2 of Oblige (Oblige 0.81-0.97). 

### Features

ObHack has the following features that Oblige2 does not have:

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
* Option to have swarms or even more monsters
* Monster traps are back (removed in Oblige 0.94)
* Boss levels now have boss monsters in them
* Choice of player starting weapon
* More texture packs, including contributions from Mr. Chris
* Deathmatch starts in single player maps
* And other features not listed here 

Oblige URL: http://oblige.sourceforge.net/

### Using ObHack

To use ObHack in Windows, copy over the ObHack.exe binary from Win32-binary/
to the directory ObHack-engine-00#.# (replace "#" with numbers), and then
run the ObHack binary from that directory. To use ObHack in other operating
systems, compile ObHack (see below for instructions) and then run the built
binary.

### ObHack settings

* Random seed: This determines the random numbers used to generate the 
  .wad file. Using the same settings and seed will generate the same
  levels again. Note that, unlike Oblige, the seed is a string, not a
  number.  
* New seed: Change the seed, replacing it by a four digit number.
* Game: The game to generate wad files for.
* Length: How many levels to put in the randomly generated megawad.  Note
  that, as of ObHack 008.3, generating an episode or full game results
  in there being boss arenas in the final episode levels (E#M8 or MAP30).
* Port: This was originally planned to allow a level to have, say, Boom
  extensions, but was never implemented (later versions of Oblige did end
  up implementing this)
* Mode: Single player makes a monster fight.  Co-op makes a harder monster
  fight, but one can have multiple players fight the monsters together.
  Deathmatch makes maps without monsters and a different layout designed
  for players to fight each other. "SP and DM" makes single player maps
  which can also be used for deathmatch matches.  "DM (no exit)" removes
  the exit from the no-monster deathmatch maps; these are for ports which
  allow the level to change after a certain number of frags or time.
  "CTF", as of ObHack 008.2, generates random Capture the Flag maps for 
  Doom ports with CTF support; note that the CTF maps are not symmetric.
* Level size: How big the levels are. "Progressive" makes the maps in a
  megawad bigger as one goes through the levels, resetting the size to small
  at the beginning of an episode. "Expansive" is similar, but keeps making
  the levels bigger until making the boss arena.  
* Prog/Exp. Max Level Size: If using the "Progressive" or "Expansive" level
  sizes, this caps how big the levels will become.
* Quest length: This adjusts how many rooms one has to go through in a
  single player (not deathmatch) map before getting a prize (key, weapon, 
  item, etc.)  
* Monsters: How many monsters the level has.  Only used for single player
  maps.
* Players: How many player starts to have in a deathmatch map.
* Puzzles: How many keys or switches one has to find before being able to
  open a door and continue the map.  Only used in single player maps.
* Weapons: How many weapons to place in a deathmatch map.
* Outdoors: How common outdoors areas are
* Stairs: This determines if the map generator randomly places a lift or 
  stair when going up or down in the map.  If set to "lifts + stairs", the
  map generator decides; if set to "Mostly stairs", the generator will 
  only place a lift if it can not fir a stairway.
* Enclosures: Whether to have monster traps in Doom single player maps.
* Room size: How big to make each room on the map.  
* Rm lighting: How dark or bright to make the rooms.
* Steepness: How much up and down the levels should have.  
* Hallways: How common hallways between rooms are.
* Health: How much health to give the player.
* Ammo: How much ammo for weapons to give the player.
* Switches: In single player maps with puzzles, whether we have only key 
  puzzles, switch puzzles, or a mixture of the two.
* Key type: In Doom levels, what kind of keys can a level have.
* Start weapon: This lets a player start with a weapon at the beginning of
  a level.
* Secrets: How common secret areas are in single player maps.

### Batch mode

ObHack can make maps in batch mode, where a megawad can be generated
without interacting with the GUI.  This allows .bat files or *NIX shell
scripts to generate a large number of .wad files.

To do this:

* Open up the GUI and slect the settings one wishes to have when generating
  batch levels.
* Close the GUI, which will save these settings in the file CONFIG.cfg
* From the command line, invoke ObHack with a single argument: A seed
  number, which is also the filename ObHack will write when invoked in
  batch mode.  The seed needs to start with a number, but can have non-numeric
  characters in it (such as ending with .wad)
* ObHack will open up the GUI, generate the map, then terminate when the map 
  is made.
* When generating a level in batch mode, in addition to outputting 
  the logs in to the file LOGS.txt, ObHack outputs them to the 
  standard output.
* In batch mode, the generated levels will be in the same directory
  as the ObHack binary.

One can use a *NIX shell script (Windows users can use Cygwin, MSYS, 
UWIN, or other *NIX-in-Windows environments to run this script) to 
generate a large number of levels automatically.  This script also writes
CONFIG.cfg to determine the settings in the megawad:

----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----
#!/bin/sh

cat > CONFIG.cfg << EOF
-- Settings --
seed = 5464
game = freedoom
port = nolimit
mode = sp
length = full

-- Adjustments --
size = small
maxsize = huge
steep = little
puzzles = more
mons = normal
health = more
ammo = more
outdoors = more
iweapon = hardcore2
switches = keys
keytype = both
roomsize = normal
lighting = bright
enclosure = true
questlength = normal
hallways = normal
stairs = stairs
secrets = common

EOF
A=1
while [ $A -lt 10000 ] ; do
	./ObHack $A-FreeDoom.wad
	A=$( expr $A + 1 )
done
----8<----8<----8<----8<----8<----8<----8<----8<----8<----8<----

