#!/bin/sh

# This is a "gremlin" test: We build 100 megawads to ensure that there are
# no fatal errors which occur when attempting to make a wad

if [ ! -e $HOME/tmp ] ; then
    echo Please mkdir $HOME/tmp
    exit 1
fi
if [ ! -d ../ObHack-engine-697 ] ; then
    echo Please run this from the tests directory
    exit 1
fi

cp ../ObHack-engine-697/scripts/writer.lua $HOME/tmp/writer-save.lua

for A in 0 1 2 3 4 5 6 7 8 9 ; do 
    for B in 0 1 2 3 4 5 6 7 8 9 ; do 
        ./deterministic.test.sh ${A}FreeDoom${B} | \
          tail -35 > $HOME/tmp/${A}FreeDoom${B}.out
    done
done
