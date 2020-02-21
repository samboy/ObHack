#!/bin/bash -e

# This needs Bash because of job control.  This is *NOT* a POSIX script.

# Describe the test
cat > /dev/null << EOF
The purpose of this test is to determine whether we get the same map
when generating multiple megawads without re-opening ObHack.

The usage of the program is:

./multirun.test.sh {TRIES}

TRIES is the number of times to make a map; make this 2 or higher.

The map parameters are default, but this can be varied by editing this
script to change the values in the file CONFIG.cfg

EOF

TRIES="$1"
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

./ObHack &
echo Please generate a map once.  Hit enter when done
echo Please ignore the glBSP error.
read FOO
unix2dos MAP*txt

sha256sum MAP*txt | tr '*' ' ' > output.success

A=1
while [ "$A" -lt "$TRIES" ] ; do
	rm -f MAP*txt
	echo Please generate a map again.  Hit enter when done
	echo Please ignore the glBSP error.
	read FOO
	unix2dos MAP*txt
	sha256sum MAP*txt | tr '*' ' ' > output.test

	if ! cmp output.success output.test > /dev/null 2>&1 ; then
		echo Test failed
		mv writer.lua.save scripts/writer.lua
		diff -u output.test output.success
		exit 1
	fi
	A=$( expr $A + 1 )
done

echo Please exit ObHack.
echo Press enter when done.
read FOO

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
