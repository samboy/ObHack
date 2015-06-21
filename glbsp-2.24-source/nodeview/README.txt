
NodeView README
===============

by Andrew Apted.  21st May 2007


Introduction
------------

NodeView is a small node/subsector browsing tool.
Currently it only works with GL-Nodes.


COLORS
------

purple   : partition lines
pink     : highlighted subsector
red      : bounding boxes
sky blue : minisegs

white    : one-sided line
yellow   : 2S line marked impassible
cyan     : 2S line on a closed door

orange   : gap too narrow for player to pass
green    : dropoff too big for player to climb

gray     : normal (walkable) two-sided line


KEYS
----

mouse click : go down one side of the BSP tree,
              highlight the subsector when reached

CTRL+click : instantly highlight the subsector
             (same as t following by clicking all the way down)

u : go Up the BSP tree
t : go back to Top of BSP tree

p : toggle Partition drawing (below/on-top/none)
b : toggle Bounding-box drawing
m : toggle Minisegs (on/off)
s : toggle Shading mode (dark/no-draw)
g : toggle Grid (on/off)

+/- : zoom in / out

