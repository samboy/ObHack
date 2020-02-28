#!/bin/sh
# $Id: autogen.sh,v 1.3 2004/05/31 14:26:36 skyjake Exp $

# Remove any previously created cache files
test -w config.cache && rm config.cache
test -w config.cross.cache && rm config.cross.cache

# Regenerate configuration files
aclocal
autoheader
libtoolize --automake --ltdl
automake --foreign -a
autoconf

echo "Now you are ready to run \"cd Build; ../configure\"."
