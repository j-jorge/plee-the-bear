#!/bin/sh

SOURCE_ROOT=$(echo $PWD/$0 | sed 's:\(.\+/\)[^/]\+:\1:')../
BINARY_ROOT=static-build-tree

. $SOURCE_ROOT/build-scripts/version.sh

sh $SOURCE_ROOT/build-scripts/build-static.sh
make -j 4 -f Makefile.static

cmake . -DCMAKE_BUILD_TYPE=release \
    -DCMAKE_INSTALL_PREFIX=$BINARY_ROOT \
    -DBEAR_EDITORS_ENABLED=0
cd plee-the-bear/data
make install > /dev/null
cd - > /dev/null

cd bear/bear-engine/desktop/locale/bear-engine/
make install > /dev/null
cd - > /dev/null

cd plee-the-bear/desktop/locale/plee-the-bear/
make install > /dev/null
cd - > /dev/null

RUNTIME_LIB_DIRECTORY=$BINARY_ROOT/bin/lib
rm -fr $RUNTIME_LIB_DIRECTORY
mkdir -p $RUNTIME_LIB_DIRECTORY

ldd $BINARY_ROOT/bin/plee-the-bear \
    | sed 's:^[[:blank:]]::' \
    | grep -v '^/' \
    | grep '/' \
    | sed 's:=>::g;s:(.\+)$::g' \
    | while read LIBRARY_NAME LIBRARY_PATH
do
    cp $LIBRARY_PATH $RUNTIME_LIB_DIRECTORY/$LIBRARY_NAME
done

# Some libraries must not be included
rm $RUNTIME_LIB_DIRECTORY/libc.so*
rm $RUNTIME_LIB_DIRECTORY/libdl.so*
rm $RUNTIME_LIB_DIRECTORY/libdrm.so*
rm $RUNTIME_LIB_DIRECTORY/libGL.so*
rm $RUNTIME_LIB_DIRECTORY/libstdc++.so*

make_tar() {

    EXE_NAME="$1"

    tar cfz ${EXE_NAME}_${PTB_VERSION}_$(uname -p).tar.gz \
        bin/$EXE_NAME \
        bin/lib \
        share/ \
        --transform "s:^bin/::;s:^:$EXE_NAME/:g"
}

cd $BINARY_ROOT
make_tar plee-the-bear

cd - > /dev/null
