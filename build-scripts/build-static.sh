#!/bin/sh

# ln -s /lib64/ld-linux-x86-64.so.2 /lib/ld64.so.1

SOURCE_ROOT=$(echo $0 | sed 's:\(.\+/\)[^/]\+:\1:')../../
BINARY_ROOT=static-build-tree

CXX_FLAGS="-O3 -DNDEBUG -DPTB_STATIC -I/usr/include/freetype2"

mkdir -p $BINARY_ROOT

get_all_static_libraries() {

    PREFIX="$1"

    find /usr/lib/ -name "lib${PREFIX}_*.a" \
        | sed 's:.*/\([^/]\+\):\1:' \
        | sed 's:lib\(.*\)\.a:\1:'
}

if uname -p | grep 64 > /dev/null
then
    LIBASOUND_SO_PATH=/usr/lib/x86_64-linux-gnu/libasound.so.2
    DYNAMIC_LINKER=/lib64/ld-linux-x86-64.so.2
else
    LIBASOUND_SO_PATH=/usr/lib/i386-linux-gnu/libasound.so.2
    DYNAMIC_LINKER=/lib/ld-linux.so.2
fi

CLAW_LIBRARIES="$(get_all_static_libraries claw) claw_logger"
BOOST_LIBRARIES="$(get_all_static_libraries boost)"
SDL_LIBRARIES="png jpeg z SDL2_mixer SDL2 mikmod \
  vorbisfile vorbis ogg FLAC mad X11 Xext caca ncurses tinfo GLU SM ICE \
  slang gpm z xcb m Xau Xdmcp"
FREETYPE_LIBRARIES="freetype"
SHARED_LIBRARIES="-Wl,-Bdynamic \
  -lGL \
  -lpulse \
  -lpulse-simple \
  -lpthread \
  $LIBASOUND_SO_PATH \
  -ldl \
"
EXE_MODULE_LINK_ORDER="ptb generic_items"
EXE_LIBRARY_LINK_ORDER="engine audio communication \
        debug expr gui input net text_interface time universe \
        visual"

get_modules() {

    if [ $# -ne 0 ]
    then
        echo -l$1
        shift
        get_modules $@
    fi
}

link_arguments() {

    for ARG in $@
    do
        case $ARG in
            -*|*/*) echo $ARG ;;
            *) echo -l$ARG ;;
        esac
    done
}

module_directory() {
    echo $SOURCE_ROOT/bear/bear-engine/core/src/$1
}

get_defines() {

    for ARG in $@
    do
        case $ARG in
            -D*) echo $ARG ;;
        esac
    done
}

include_directories() {

    if [ $# -eq 0 ]
    then
        echo
    else
        ARG=$1
        shift

        if expr $ARG : '^-.*$' >/dev/null
        then
            include_directories $@
        elif expr $ARG : '^.*/.*$' >/dev/null
        then
            echo -I$ARG $(include_directories $@)
        else
            echo -I$(module_directory $ARG)/.. $(include_directories $@)
        fi
    fi
}

compile() {
    INCLUDE="$1"
    SOURCES="$2"
    TARGET="$3"

    echo g++ $CXX_FLAGS "$INCLUDE" -c "$SOURCES" -o "$TARGET"
}

build_objects() {

    OBJ_FILES_TMP="$1"
    SOURCE_DIRECTORY="$2"
    TARGET_DIRECTORY="$3"

    shift 3
    COMPILER_ARGUMENTS="$@"

    grep '\.cpp' $SOURCE_DIRECTORY/CMakeLists.txt \
        | grep -v '^ *#' \
        | while read SOURCE
    do
        OBJ=$TARGET_DIRECTORY/$(basename $SOURCE .cpp).o
        echo $OBJ >> $OBJ_FILES_TMP

        echo $OBJ: $SOURCE_DIRECTORY/$SOURCE
        echo "\t@echo '\033[32mBuilding $OBJ\033[0m'"
        echo "\tmkdir -p $TARGET_DIRECTORY"
        echo "\t" $(compile "$COMPILER_ARGUMENTS" \
            $SOURCE_DIRECTORY/$SOURCE $OBJ)
        echo
    done
} # build_objects

build_module() {
    
    MODULE_DIRECTORY="$1"

    shift
    INCLUDE="-I$MODULE_DIRECTORY/.. $(include_directories $@)"
    DEFINES="$(get_defines $@)"

    MODULE_NAME="$(basename $MODULE_DIRECTORY)"

    OBJ_FILES_TMP=$(mktemp)

    build_objects $OBJ_FILES_TMP $MODULE_DIRECTORY \
        $BINARY_ROOT/obj/$MODULE_NAME \
        $INCLUDE $DEFINES

    echo $MODULE_NAME: $BINARY_ROOT/lib/lib$MODULE_NAME.a
    echo

    echo $BINARY_ROOT/lib/lib$MODULE_NAME.a: $(tr -d ' ' < $OBJ_FILES_TMP)
    echo "\tmkdir -p $BINARY_ROOT/lib"
    echo "\tar rs \$@ \$^"
    echo

    rm $OBJ_FILES_TMP
} # build_module

build_exe() {
    
    EXE_NAME="$1"
    shift

    SOURCE_DIRECTORY="$1"
    INCLUDE="$(include_directories $@)"
    DEFINES="$(get_defines $@)"

    OBJ_FILES_TMP=$(mktemp)

    build_objects $OBJ_FILES_TMP $SOURCE_DIRECTORY $BINARY_ROOT/obj/$EXE_NAME \
        $INCLUDE $DEFINES

    echo $EXE_NAME: $EXE_NAME.depends
    echo

    echo $BINARY_ROOT/bin/$EXE_NAME: \
        $EXE_NAME.depends $(tr -d ' ' < $OBJ_FILES_TMP)
    echo "\tmkdir -p $BINARY_ROOT/bin"
    echo "\t" g++ $CXX_FLAGS $DEFINES \
        -fPIE -Wl,--export-dynamic -rdynamic -static \
        $(tr -d ' ' < $OBJ_FILES_TMP) \
        -L$BINARY_ROOT/lib/ \
        -Wl,--no-as-needed -Wl,--whole-archive \
        $(get_modules $EXE_MODULE_LINK_ORDER) \
        -Wl,--as-needed -Wl,--no-whole-archive \
        $(get_modules $EXE_LIBRARY_LINK_ORDER) \
        -o '$@' \
        -Wl,-dynamic-linker=$DYNAMIC_LINKER \
        -Wl,-rpath='\$$ORIGIN/lib' \
        -Wl,-Bstatic \
        $(link_arguments $CLAW_LIBRARIES) \
        $(link_arguments $BOOST_LIBRARIES) \
        $(link_arguments $SDL_LIBRARIES) \
        $(link_arguments $FREETYPE_LIBRARIES) \
        $SHARED_LIBRARIES
    echo

    rm $(cat $OBJ_FILES_TMP)
    rm $OBJ_FILES_TMP
} # build_exe

TARGET_MAKEFILE=Makefile.static

(
    echo all: $BINARY_ROOT/bin/plee-the-bear
    echo

    echo clean:
    echo "\trm -fr $BINARY_ROOT/"
    echo

    echo $TARGET_MAKEFILE: $0
    echo "\tsh $0 > \$@"
    echo "\t\$(MAKE) -f $TARGET_MAKEFILE"
    echo

    build_module $(module_directory audio)
    build_module $(module_directory communication)
    build_module $(module_directory debug)
    build_module $(module_directory engine) \
        $SOURCE_ROOT/bear/bear-engine/common/include
    build_module $(module_directory expr)
    build_module $(module_directory gui)
    build_module $(module_directory input)
    build_module $(module_directory net)
    build_module $(module_directory text_interface)
    build_module $(module_directory time)
    build_module $(module_directory universe)
    build_module $(module_directory visual)

    build_module $SOURCE_ROOT/bear/bear-engine/lib/src/generic_items \
        universe

    build_module $SOURCE_ROOT/plee-the-bear/lib/src/ptb engine \
        $SOURCE_ROOT/bear/bear-engine/lib/src

    build_exe plee-the-bear \
        $SOURCE_ROOT/plee-the-bear/launcher/src \
        $SOURCE_ROOT/bear/bear-engine/core/src

    echo plee-the-bear.depends: audio communication \
        debug engine expr gui input net text_interface time universe \
        visual generic_items ptb
) > $TARGET_MAKEFILE
