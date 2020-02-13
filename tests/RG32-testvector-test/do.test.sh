#!/bin/sh

PROG="$1"

if [ -z "$PROG" ] ; then
	echo Usage: $0 {program_name}
	echo Where the program is one that performs RG32 hashes to its
	echo first argument
	exit 255
fi

cat Input | awk '{print "'${PROG}\ \''" $0 "'\''"}' | sh | \
	tr -d '\015' > output.test

if ! cmp output.success output.test > /dev/null 2>&1 ; then
	echo Test failed
	if cmp output.8859-1 output.test > /dev/null 2>&1 ; then
		echo The script is converting UTF-8 strings in to
		echo ISO 8859-1 strings.  It is otherwise generating
		echo correct RadioGatun[32] hashes.
	fi
	exit 255
fi

echo Success
rm output.test
