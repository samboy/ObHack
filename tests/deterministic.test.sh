#!/bin/bash -e

# Describe the test
cat > /dev/null << EOF
The purpose of this test is to determine whether a given seed generates
a deterministic set of maps.  It does this test by first making the maps
with a given seed and parameters; it then makes the same map set again
and again multiple times to see if anything changes.

The usage of the program is:

./deterministic.test.sh {seed} {number of tries}

Where {seed} is the seed we test and {number of tries} is the number of
times we test if a map changes after making the initial "reference"
version.

{seed} defaults to "1FreeDoom1" (without the quotes)
{number of tries} defaults to 2

The map parameters are default, but this can be varied by editing this
script to change the values in the file CONFIG.cfg
EOF

SEED=$1
if [ -z "$SEED" ] ; then
	SEED=1FreeDoom1
fi
TRIES=$2
if [ -z "$TRIES" ] ; then
	TRIES=2
fi

cd ../ObHack-engine-697
rm -f CONFIG.cfg

# Change this to change map parameters
cat > CONFIG.cfg << EOF
game = freedoom
mons = normal
seed = 1FreeDoom1
port = nolimit
mode = sp
length = full
size = small
steep = some
puzzles = more
traps = normal
health = normal
ammo = normal
outdoors = more
iweapon = none
switches = keys
EOF

cp scripts/writer.lua writer.lua.save
cat scripts/writer.lua | sed 's/if false/if true/' > foo
mv foo scripts/writer.lua

# Now, let's make the reference version
rm -f MAP*txt

./ObHack "$SEED" || true
echo Please ignore the glBSP errors above, we are running ObHack in a 
echo special test mode.
unix2dos MAP*txt

sha256sum MAP*txt | tr '*' ' ' > output.success

A=1
while [ "$A" -le "$TRIES" ] ; do
	rm -f MAP*txt
	./ObHack "$SEED" || true	
	unix2dos MAP*txt
	sha256sum MAP*txt | tr '*' ' ' > output.test

	if ! cmp output.success output.test > /dev/null 2>&1 ; then
		echo Test failed
		mv writer.lua.save scripts/writer.lua
		exit 1
	fi
	A=$( expr $A + 1 )
done

# Clean up
mv writer.lua.save scripts/writer.lua
rm MAP*txt
rm CONFIG.cfg
rm output.test
rm LOGS.txt
echo SHA256 values of maps follow
cat output.success
rm output.success
echo Test success
