#!/bin/bash

if [ -z "$1" ]
then
    echo $0 file.xcf scale_factor 1>&2
    exit 1
fi

SOURCE_XCF="$1"
shift 1

FACTOR=0.5

if [ "$1" != "" ]
then
    FACTOR=$1
    shift 1
fi

OUTPUT_NAME=$(basename $(mktemp --tmpdir=.))
OUTPUT_PNG="$OUTPUT_NAME.png"

TMP_SPRITEDESC=$(mktemp --tmpdir=.)

cat > $TMP_SPRITEDESC <<EOF
sprite_sheet "$OUTPUT_NAME" 10000 x 10000 margin 0

img "$SOURCE_XCF"

"bk" autosize * $FACTOR with img
  glob "*"
  ;
EOF

pack-my-sprites "$TMP_SPRITEDESC" --no-spritepos
image-cutter -X=512 -Y=512 -f=bk_ $OUTPUT_PNG

rm $OUTPUT_PNG $TMP_SPRITEDESC $OUTPUT_NAME