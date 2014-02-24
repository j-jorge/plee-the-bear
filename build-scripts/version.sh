#!/bin/sh

PTB_VERSION_FILE=./plee-the-bear/lib/src/ptb/version.hpp
PTB_VERSION_MAJOR=$(grep '#define PTB_MAJOR_VERSION' "$PTB_VERSION_FILE" \
    | cut -d' ' -f3)
PTB_VERSION_MINOR=$(grep '#define PTB_MINOR_VERSION' "$PTB_VERSION_FILE" \
    | cut -d' ' -f3)
PTB_VERSION_PATCH=$(grep '#define PTB_PATCH_NUMBER' "$PTB_VERSION_FILE" \
    | cut -d' ' -f3)

PTB_VERSION=$PTB_VERSION_MAJOR.$PTB_VERSION_MINOR.$PTB_VERSION_PATCH
