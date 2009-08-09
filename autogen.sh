#!/bin/sh
# Run this to generate all the initial makefiles, etc.

srcdir=`dirname $0`
test -z "$srcdir" && srcdir=.

PKG_NAME="tuxchan"

which gnome-autogen.sh || {
        echo "Missing gnome-autogen.sh: you need to install gnome-common"
        exit 1
}

USE_GNOME2_MACROS=1 . gnome-autogen.sh
