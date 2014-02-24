#!/bin/sh

# MinGW must be in your path. Edit the registry key
# HKCU/Environment/PATH by typing
#
#  wine regedit
#

[ -z "$WIN_PROGRAM_FILES" ] \
    && WIN_PROGRAM_FILES="C:/Program Files"

[ -z "$WIN_GNU_INCLUDE_DIR" ] \
    && WIN_GNU_INCLUDE_DIR="$WIN_PROGRAM_FILES/GnuWin32/include"

[ -z "$WIN_GNU_BIN_DIR" ] \
    && WIN_GNU_BIN_DIR="$WIN_PROGRAM_FILES/GnuWin32/bin"

[ -z "$WIN_GNU_LIB_DIR" ] \
    && WIN_GNU_LIB_DIR="$WIN_PROGRAM_FILES/GnuWin32/lib"

[ -z "$WIN_BOOST_DIR" ] \
    && WIN_BOOST_DIR="C:/boost_1_45_0"

[ -z "$WIN_SDL_DIR" ] \
    && WIN_SDL_DIR="C:/SDL2-2.0.1/i686-w64-mingw32"

[ -z "$WIN_SDL_INCLUDE_DIR" ] \
    && WIN_SDL_INCLUDE_DIR="$WIN_SDL_DIR/include"

[ -z "$WIN_SDL_MIXER_INCLUDE_DIR" ] \
    && WIN_SDL_MIXER_INCLUDE_DIR="$WIN_SDL_INCLUDE_DIR"

[ -z "$COMMON_LIBRARIES_DIR" ] \
    && COMMON_LIBRARIES_DIR="$HOME/.wine/drive_c/Programmation/libs4plee"

# Libraries paths
[ -z "$WIN_LIBCLAW_DIR" ] \
    && WIN_LIBCLAW_DIR="$WIN_PROGRAM_FILES/claw/"

[ -z "$WIN_LIBCLAW_CMAKE_DIR" ] \
    && WIN_LIBCLAW_CMAKE_DIR="$WIN_LIBCLAW_DIR/lib/cmake/libclaw/"

[ -z "$WIN_FREETYPE_INCLUDE_DIR" ] \
    && WIN_FREETYPE_INCLUDE_DIR="$WIN_GNU_INCLUDE_DIR/freetype2"

[ -z "$WIN_FREETYPE_LIBRARY" ] \
    && WIN_FREETYPE_LIBRARY="$WIN_GNU_LIB_DIR/libfreetype.dll.a"

[ -z "$WIN_JPEG_INCLUDE_DIR" ] \
    && WIN_JPEG_INCLUDE_DIR="$WIN_GNU_INCLUDE_DIR"

[ -z "$WIN_JPEG_LIBRARY_PATH" ] \
    && WIN_JPEG_LIBRARY_PATH="$WIN_GNU_LIB_DIR/libjpeg.dll.a"

[ -z "$WIN_PNG_INCLUDE_DIR" ] \
    && WIN_PNG_INCLUDE_DIR="$WIN_GNU_INCLUDE_DIR"

[ -z "$WIN_PNG_LIBRARY_PATH" ] \
    && WIN_PNG_LIBRARY_PATH="$WIN_GNU_LIB_DIR/libpng.dll.a"

[ -z "$WIN_BOOST_INCLUDE_DIR" ] \
    && WIN_BOOST_INCLUDE_DIR="$WIN_BOOST_DIR"

[ -z "$WIN_SDL_LIBRARY_PATH" ] \
    && WIN_SDL_LIBRARY_PATH="$WIN_SDL_DIR/bin/SDL2.dll"

[ -z "$WIN_SDL_MIXER_LIBRARY_PATH" ] \
    && WIN_SDL_MIXER_LIBRARY_PATH="$WIN_SDL_DIR/bin/SDL2_mixer.dll"

# Programs
[ -z "$GETTEXT_MSGMERGE_PATH" ] \
    && GETTEXT_MSGMERGE_PATH="$WIN_GNU_BIN_DIR/msgmerge.exe"

[ -z "$GETTEXT_MSGFMT_PATH" ] \
    && GETTEXT_MSGFMT_PATH="$WIN_GNU_BIN_DIR/msgfmt.exe"

# Compilation flags
[ -z "$BUILD_TYPE" ] && BUILD_TYPE=release

[ -z "$INSTALL_PREFIX" ] && INSTALL_PREFIX=/tmp/install/win

[ -z "$BEAR_BUILD_TAG" ] && BEAR_BUILD_TAG="$(date --rfc-2822)"

# Compilation

wine C:/Program\ Files/CMake\ 2.8/bin/cmake.exe -G "MinGW Makefiles" . \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DCLAW_ROOT_DIRECTORY:PATH="$WIN_LIBCLAW_DIR" \
    -Dlibclaw_DIR:PATH="$WIN_LIBCLAW_CMAKE_DIR" \
    -DJPEG_INCLUDE_DIR:PATH="$WIN_JPEG_INCLUDE_DIR" \
    -DJPEG_LIBRARY:FILEPATH="$WIN_JPEG_LIBRARY_PATH" \
    -DPNG_PNG_INCLUDE_DIR:PATH="$WIN_PNG_INCLUDE_DIR" \
    -DPNG_LIBRARY:FILEPATH="$WIN_PNG_LIBRARY_PATH" \
    -DBoost_INCLUDE_DIR:PATH="$WIN_BOOST_INCLUDE_DIR" \
    -DSDL_INCLUDE_DIR:PATH="$WIN_SDL_INCLUDE_DIR" \
    -DSDL_LIBRARY:FILEPATH="$WIN_SDL_LIBRARY_PATH" \
    -DSDL_MIXER_INCLUDE_DIR:PATH="$WIN_SDL_MIXER_INCLUDE_DIR" \
    -DSDL_MIXER_LIBRARY:FILEPATH="$WIN_SDL_MIXER_LIBRARY_PATH" \
    -DGETTEXT_MSGMERGE_EXECUTABLE:FILEPATH="$GETTEXT_MSGMERGE_PATH" \
    -DGETTEXT_MSGFMT_EXECUTABLE:FILEPATH="$GETTEXT_MSGFMT_PATH" \
    -DFREETYPE_LIBRARY:FILEPATH="$WIN_FREETYPE_LIBRARY" \
    -DFREETYPE_INCLUDE_DIRS:PATH="$WIN_FREETYPE_INCLUDE_DIR" \
    -DCMAKE_SHARED_LINKER_FLAGS='-Wl,--enable-auto-import,--enable-stdcall-fixup' \
    -DCMAKE_EXE_LINKER_FLAGS='-Wl,--enable-auto-import,--enable-stdcall-fixup' \
    -DBEAR_EDITORS_ENABLED=0 \
    -DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX" \
    -DBEAR_BUILD_TAG="$BEAR_BUILD_TAG" \
    $CMAKE_ARGS

wine mingw32-make -i

wine strip bear/bear-engine/bin/*.dll bear/bear-engine/bin/*.exe
wine strip plee-the-bear/bin/*.dll plee-the-bear/bin/*.exe

wine mingw32-make install
