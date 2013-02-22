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

    echo "Searching strings, sprites and animations in levels." 1>&2
    find ../../../data/level/ -name "*.lvl" \
	| while read F
          do
	    echo "$F..." 1>&2

            #string in .lvl
	    xpath_wrapper \
                '/level/layer/items/item/fields/field/string/@value' $F \
		| grep 'value="[^[:lower:]]' \
		| sed "s/&apos;/'/g;"'s/&quot;/"/g' \
                | sed 's/ value="//;s/"$//' \
		| sed 's/"/\\\\"/g' \
                | while read MSG
                  do
                    echo "#: $F"
                    echo 'msgid "'$MSG'"'
                    echo 'msgstr ""'
                  done

            # sprite in .lvl
            xpath_wrapper \
                '//sprite/@image' $F \
		| sed "s/&apos;/'/g;"'s/&quot;/"/g' \
                | sed 's/ image="//;s/"$//' \
		| sed 's/"/\\\\"/g' \
                | while read MSG
                  do
                    echo "#: $F"
                    echo 'msgid "'$MSG'"'
                    echo 'msgstr ""'
                  done
            
            # animation in .lvl
            xpath_wrapper \
                '/level/layer/items/item/fields/field/animation_file//@path' $F \
		| sed "s/&apos;/'/g;"'s/&quot;/"/g' \
                | sed 's/ path="//;s/"$//' \
		| sed 's/"/\\\\"/g' \
                | while read MSG
                  do
                    echo "#: $F"
                    echo 'msgid "'$MSG'"'
                    echo 'msgstr ""'
                  done
          done

    echo "Searching sprites and animations in models." 1>&2
    find ../../../data/model/ -name "*.mdl" \
	| while read F
          do
	    echo "$F..." 1>&2

            # sprite in .mdl
            xpath_wrapper \
                '/model/action/marks/mark/animation/frame/sprite/@image' $F \
		| sed "s/&apos;/'/g;"'s/&quot;/"/g' \
                | sed 's/ image="//;s/"$//' \
		| sed 's/"/\\\\"/g' \
                | while read MSG
                  do
                    echo "#: $F"
                    echo 'msgid "'$MSG'"'
                    echo 'msgstr ""'
                  done
            
            # animation in .mdl
            xpath_wrapper \
                '/model/action/marks/mark/animation_file//@path' $F \
		| sed "s/&apos;/'/g;"'s/&quot;/"/g' \
                | sed 's/ path="//;s/"$//' \
		| sed 's/"/\\\\"/g' \
                | while read MSG
                  do
                    echo "#: $F"
                    echo 'msgid "'$MSG'"'
                    echo 'msgstr ""'
                  done
          done

    echo "Searching sprites in animation." 1>&2
    find ../../../data/animation/ -name "*.anim" \
	| while read F
          do
	    echo "$F..." 1>&2

            # sprite in .anim
            xpath_wrapper \
                '/animation/frame/sprite/@image' $F \
		| sed "s/&apos;/'/g;"'s/&quot;/"/g' \
                | sed 's/ image="//;s/"$//' \
		| sed 's/"/\\\\"/g' \
                | while read MSG
                  do
                    echo "#: $F"
                    echo 'msgid "'$MSG'"'
                    echo 'msgstr ""'
                  done
          done

    echo "Searching strings in scripts." 1>&2
    find ../../../data/script -name "*.txt" \
	| while read F
          do
	    echo "$F..." 1>&2
            grep '\.\(talk\|speak\)(' $F \
		| sed 's:.\+\.\(talk\|speak\)( *"\(.\+\)" *);:\2:' \
                | while read T
                  do
		    echo "$T" \
                        | sed 's/"/\\\\\\"/g;s/^/msgid "/;s/$/"\nmsgstr ""\n/'
                  done
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
