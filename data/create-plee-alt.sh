#!/bin/sh

if ! [ -d gfx/plee ]
then
  echo "Cannot find directory gfx/plee. Run this script from the data directory" 1>&2
  exit 1
fi

cd gfx/plee
gimp-console -b - < plee-alt.scm
cd -

mkdir animation/plee-alt

for f in animation/plee/*.anim
do
    sed 's/plee-\([1-4]\).png/plee-alt-\1.png/g' "$f" \
	> animation/plee-alt/$(basename $f)
done

for f in gfx/plee/*-alt*.png
do
  SOURCE_SPRITEPOS=$(echo $f | sed 's:-alt::;s:\.png$:.spritepos:')

  if [ -f $SOURCE_SPRITEPOS ]
  then
    cp $SOURCE_SPRITEPOS $(echo $f | sed 's:\.png:.spritepos:')
  fi
done

sed -i 's/cap.png/cap-alt.png/g' animation/plee-alt/cap.anim

sed 's:animation/plee/:animation/plee-alt/:g;s/plee-\([1-4]\).png/plee-alt-\1.png/g' model/player/plee.mdl > model/player/plee-alt.mdl

../../bear-factory/bin/bf-animation-editor -c animation/plee-alt/*.anim
../../bear-factory/bin/bf-model-editor -c model/player/plee-alt.mdl
