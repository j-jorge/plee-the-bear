#!/bin/sh

FULL_BUILD=1

rm -f CMakeCache.txt

. plee-the-bear/build-scripts/version.sh

do_build() {

    CMAKE_ARGS="$@"
    . plee-the-bear/build-scripts/windows-build.sh

    cp "$COMMON_LIBRARIES_DIR/"* "$INSTALL_PREFIX/bin/"
} # do_build

VERSION=${ASGP_VERSION}

do_build

# create an archive here
# …

wine mingw32-make uninstall
rm -fr "$INSTALL_PREFIX"
