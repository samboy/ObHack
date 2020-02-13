#!/bin/bash -e

cc -o ../ObHack-engine-697/rg32-floats rg32-floats.c
cd ../ObHack-engine-697
cp scripts/oblige.lua oblige.lua.save
cat scripts/oblige.lua | sed 's/1234 == 5678/true/' > foo
mv foo scripts/oblige.lua
./ObHack 1FreeDoom1 2>&1 | grep RG32 > output.1

# Clean up
mv oblige.lua.save scripts/oblige.lua
cat output.1
rm LOGS.txt
