#/bin/sh

DEV_DIR="$(echo $0 | sed s:$(basename $0):../..:)"

# find the file containing the version number
read VERSION_FILE <<EOF
  $(find "$DEV_DIR" -name "version.hpp")
EOF

if [ "$VERSION_FILE" != "" ]
then
    read VERSION <<EOF
    $(grep "#define BEAR_MAJOR_VERSION" "$VERSION_FILE" -A 2 \
        | cut -d' ' -f3 \
        | tr '\n' '.' \
        | sed 's/.$/\n/')
EOF
fi

WD="$(pwd)"
cd "$DEV_DIR"

SUFFIX=""

if [ -d .svn ]
then
  svn update
  REVISION=$(svn info | head -n 5 | tail -n 1 | cut -d' ' -f3)
  SUFFIX="svn$REVISION"
fi

cmake . -DCMAKE_BUILD_TYPE=release -DBEAR_NO_EDITORS=1 && make || exit 1

DEST_DIR_NAME="plee-the-bear_${VERSION}$SUFFIX"
DEST_DIR="/tmp/$DEST_DIR_NAME"

rm -fr "$DEST_DIR"
mkdir "$DEST_DIR"

# copy the libraries
mkdir "$DEST_DIR/lib"

ldd bear-engine/bin/* plee-the-bear/bin/* \
  | grep '=> [^ ]' \
  | sed 's/^\t\(.\+\) => \(.\+\) (.\+$/\1 \2/' \
  | while read n p
    do
      cp -L $p "$DEST_DIR/lib/"$n
    done

# grep lines beginning with a tabulation
ldd bear-engine/bin/* plee-the-bear/bin/* \
  | (grep '^	/' | cut -d' ' -f1; echo "$DEST_DIR/lib/") \
  | xargs cp -L

cp plee-the-bear/bin/* "$DEST_DIR/lib/"
strip "$DEST_DIR/lib/"*

# copy the binaries
mkdir "$DEST_DIR/bin"
cp bear-engine/bin/running-bear "$DEST_DIR/bin"
strip "$DEST_DIR/bin/"*

# copy the datas
cd plee-the-bear

(
  find data/animation -name "*.canim"
  find data/font -name "*.png" -o -name "*.tga" -o -name "*.fnt" \
    -o -name "AUTHORS"
  find data/gfx -name "*.png" -o -name "*.tga" -o -name "*.spritepos" \
    -o -name "AUTHORS"
  find data/level -name "*.cl"
  find data/model -name "*.cm"
  find data/music -name "*.ogg" -o -name "AUTHORS"
  find data/script -name "*.txt"
  find data/sound -name "*.ogg" -o -name "*.wav" -o -name "AUTHORS"
) | grep -v '!' \
  | while read f
    do
      cp --parent $f "$DEST_DIR/"
    done

cd -

# write the launcher
(
  echo '#/bin/sh'
  echo 'export LD_LIBRARY_PATH="./lib:$LD_LIBRARY_PATH"'
  tail -n +2 ./plee-the-bear/release/plee-the-bear \
    | sed 's:^DATA_PATH=.\+$:DATA_PATH=./data:' \
    | sed 's:/.*/lib/:./lib/:' \
    | sed 's:/.*/bin/:./bin/:';
) > "$DEST_DIR/plee-the-bear.sh"

chmod u+x "$DEST_DIR/plee-the-bear.sh"

cd "$DEST_DIR"
find . -name ".svn" -type d \
  | while read f
    do
      rm -fr $f;
    done

cd ..
tar cfz "$WD/$DEST_DIR_NAME.tar.gz" "$DEST_DIR_NAME"

# back to the initial directory
cd "$WD"
