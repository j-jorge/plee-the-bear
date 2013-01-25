#!/bin/sh

OUTPUT_FILE=plee-the-bear.pot

if ! which xpath >/dev/null
then
  echo "Can't find xpath command in your paths."
  exit 1
fi

# $1 is the XPath
# $2 is the XML file
xpath_wrapper()
{
    echo '<node/>' | xpath -e "/node" >/dev/null 2>/dev/null

    if [ $? -eq 0 ]
    then
	xpath -q -e "$1" "$2"
    else
	xpath "$2" "$1"
    fi
}

(
    echo "Searching strings in source code." 1>&2
    xgettext --output=- --c++ --trigraphs --sort-output \
	$(find ../../../src/ptb -name "*.[tch]pp") \
      | sed 's/charset=CHARSET/charset=UTF-8/'

    grep '".*break;' ../../../src/ptb/code/player_action.cpp \
	| cut -d'"' -f2 \
	| tr '_' ' ' \
	| awk '{ print toupper(substr($0, 1, 1)) substr($0, 2); }' \
	| sed 's/^/msgid "/;s/$/"\nmsgstr ""\n/'

    echo "Searching strings in levels." 1>&2
    find ../../../data/level/ -name "*.lvl" \
	| while read F
          do
	    echo "$F..." 1>&2

	    xpath_wrapper \
                '/level/layer/items/item/fields/field/string/@value' $F \
		| grep 'value="[^[:lower:]]' \
		| sed "s/&apos;/'/g;"'s/&quot;/"/g' \
                | sed 's/ value="\(.\+\)"/\1/' \
		| sed 's/"/\\"/g;s/^/msgid "/;s/$/"\nmsgstr ""\n/'

	    xpath_wrapper '/level/@name' $F \
                | grep 'name="[^"]' \
                | sed 's/ name="\(.*\)"/\1/' \
		| sed 's/ [aA]ct [0-9]\+//' \
		| sed 's/"/\\"/g;s/^/msgid "/;s/$/"\nmsgstr ""\n/'
          done

    echo "Searching strings in scripts." 1>&2
    find ../../../data/script -name "*.txt" \
	| while read F
          do
	    echo "$F..." 1>&2
	    grep '\.talk(' $F \
		| sed 's:.\+\.talk( *"\(.\+\)" *);:\1:' \
                | while read T
                  do
		    S=$(echo "$T" | cut -c 1)
                    echo $T | cut -c 2- | tr "$S" '\n'
                  done \
		      | sed 's/"/\\"/g;s/^/msgid "/;s/$/"\nmsgstr ""\n/'
          done

    echo 'msgid "act"'
    echo 'msgstr ""'

    echo "Searching strings in mini-game informations." 1>&2
    grep '^[^#].\+_\(informations\|format\) =' \
	../../../data/mini-game/informations.txt \
	| cut -d= -f2 \
	| sed 's/^ \+//;s/"/\\"/g;s/^/msgid "/;s/$/"\nmsgstr ""\n/'

    echo "Searching strings in credits." 1>&2
    grep '^[^#]' \
	../../../data/credits.txt \
	| sed 's/^/msgid "/;s/$/"\nmsgstr ""\n/'

) | iconv --from=iso-8859-15 --to=utf-8 \
    | msguniq | msgcat - --sort-output > "$OUTPUT_FILE"

for f in *.po
do
    msgmerge --update --previous --backup=none "$f" "$OUTPUT_FILE"
done
