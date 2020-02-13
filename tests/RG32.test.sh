#!/bin/bash -e

# This test makes sure that the implementation of RadioGatún[32] inside
# ObHack generates correct numbers

# Have ObHack generate the numbers based on the 1FreeDoom1 seed
cc -o ../ObHack-engine-697/rg32-floats rg32-floats.c
cd ../ObHack-engine-697
cp scripts/oblige.lua oblige.lua.save
cat scripts/oblige.lua | sed 's/1234 == 5678/true/' > foo
mv foo scripts/oblige.lua
./ObHack 1FreeDoom1 2>&1 | grep RG32 | tr -d '\015' > output.1

# Have our separate RG32 implementation generate the same numbers
rm -f output.2
for map in $( awk 'BEGIN{for(a=1;a<=32;a++){print a}}' ) ; do
	./rg32-floats 1FreeDoom1-101-ObHack-006-${map} ObHack >> output.2
done

# The lowest digit when Lua prints the numbers varies from the numbers
# our 64-bit RG32 implementation prints, so remove the lowest digit.
for FILE in output.1 output.2 ; do
	cat $FILE | awk '{if(/test/){print substr($0,0,20)}else{print}}' > foo
	mv foo $FILE
done

# See if the numbers are the same as our reference-compatible RG32
# implementation
if ! cmp output.1 output.2 > /dev/null 2>&1 ; then
	echo Test failed
	mv oblige.lua.save scripts/oblige.lua
	exit 1
fi

echo Test success

# Clean up
mv oblige.lua.save scripts/oblige.lua
rm -f LOGS.txt
rm -f output.1 output.2 rg32-floats* 1FreeDoom1
