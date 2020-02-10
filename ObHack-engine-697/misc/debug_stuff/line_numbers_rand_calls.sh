#!/bin/bash

# This is a script which will, for all rand_* calls, add a filename and line
# number so we can debug cases where the code is non-deterministic

# Donated to the public domain by Sam Trenholme in 2020

FILE="$1"

if [ -z "$FILE" ] ; then
	echo Usage: $0 {filename}
	exit 1
fi

# rand_odds
cat $FILE | perl -pe '
	$line++;s/(rand_odds\([^\)]*)/\1,\"'$FILE' line $line\"/' > foo
mv foo $FILE

# rand_range
cat $FILE | perl -pe '
	$line++;s/(rand_range\([^\)]*)/\1,\"'$FILE' line $line\"/' > foo
mv foo $FILE

# rand_irange
cat $FILE | perl -pe '
	$line++;s/(rand_irange\([^\)]*)/\1,\"'$FILE' line $line\"/' > foo
mv foo $FILE

# rand_sel
cat $FILE | perl -pe '
	$line++;s/(rand_sel\([^\)]*)/\1,\"'$FILE' line $line\"/' > foo
mv foo $FILE

# rand_index_by_probs
cat $FILE | perl -pe '
	$line++;s/(rand_index_by_probs\([^\)]*)/\1,\"'$FILE' line $line\"/' > foo
mv foo $FILE

# rand_skew (which does not take any arguments, so no comma here)
cat $FILE | perl -pe '
	$line++;s/(rand_skew\([^\)]*)/\1\"builder.lua line $line\"/' > foo
mv foo $FILE

# rand_element
cat $FILE | perl -pe '
	$line++;s/(rand_element\([^\)]*)/\1,\"'$FILE' line $line\"/' > foo
mv foo $FILE

# rand_shuffle
cat $FILE | perl -pe '
	$line++;s/(rand_shuffle\([^\,\)]*)/\1,\"'$FILE' line $line\"/' > foo
mv foo $FILE

# dual_odds
cat $FILE | perl -pe '
	$line++;s/(dual_odds\([^\)]*)/\1,\"'$FILE' line $line\"/' > foo
mv foo $FILE

