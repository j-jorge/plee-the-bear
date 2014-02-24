#!/bin/sh

# This is the directory containing this script
SOURCE_ROOT=$(echo $PWD/$0 | sed 's:\(.\+/\)[^/]\+:\1:')../

INITIAL_DIRECTORY=$PWD

# The Git repositories from which we take the sources.
PTB_GIT_PATH=$SOURCE_ROOT/
BEAR_GIT_PATH=$SOURCE_ROOT/../bear/

# Finds the version of Plee the Bear
. $SOURCE_ROOT/build-scripts/version.sh

# This directory will receive the source tree
WORKING_DIRECTORY=$(mktemp --directory)

# Now we start the real work
cd "$WORKING_DIRECTORY"

# This directory is the root of the source tree
RESULT_DIRECTORY_NAME=plee-the-bear-$PTB_VERSION

# The full path to the source root
SOURCE_DIRECTORY=$WORKING_DIRECTORY/$RESULT_DIRECTORY_NAME
mkdir $SOURCE_DIRECTORY

# Takes the source from the repositories.
# git archive only works from inside a local repository.
cd $PTB_GIT_PATH
git archive master --prefix=plee-the-bear/ | tar -x -C $SOURCE_DIRECTORY

cd $BEAR_GIT_PATH
git archive master --prefix=bear/ | tar -x -C $SOURCE_DIRECTORY

# Cleans up the source
cd $SOURCE_DIRECTORY

find . -name ".gitignore" -exec rm {} +

# We must create a CMakeLists.txt file to build the engine and the game, and to
# add an uninstall rule.

cat > CMakeLists.txt <<EOF
cmake_minimum_required( VERSION 2.8 )

add_subdirectory( bear )
add_subdirectory( plee-the-bear )

set( BEAR_ROOT_DIRECTORY "\${CMAKE_CURRENT_SOURCE_DIR}/bear" )
set( CMAKE_MODULE_PATH "\${BEAR_ROOT_DIRECTORY}/cmake-helper" )
include( uninstall )
EOF

mv plee-the-bear/build-scripts/wine-make.sh .

# Creates the final archive in the directory from which the script was started.
cd $WORKING_DIRECTORY/
tar cfz $INITIAL_DIRECTORY/plee-the-bear_$PTB_VERSION.tar.gz \
    $RESULT_DIRECTORY_NAME

# And clean up the temporary files before leaving.
rm -fr "$WORKING_DIRECTORY"