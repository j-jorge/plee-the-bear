#!/bin/sh
#
#  Plee the Bear
#
#  Copyright (C) 2005-2010 Julien Jorge, Sebastien Angibaud
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License as published by the
#  Free Software Foundation; either version 2 of the License, or (at your
#  option) any later version.
#
#  This program is distributed in the hope that it will be useful, but WITHOUT
#  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
#  more details.
#
#  You should have received a copy of the GNU General Public License along
#  with this program; if not, write to the Free Software Foundation, Inc.,
#  51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
#  contact: plee-the-bear@gamned.org
#
#  Please add the tag [PTB] in the subject of your mails.

# List all the xcf files that without a named author in the "AUTHORS" file.
find . -name "*.xcf*" \
  | grep -v svn \
  | while read f
    do
      FILE=$(basename $f);
      AUTHOR_FILE=$(echo $f | sed 's,[^/]\+$,,')AUTHORS

      if ! grep $FILE $AUTHOR_FILE >/dev/null 2>/dev/null
      then
        echo "No author for $f"
      fi
    done

# List all the files listed in the "AUTHORS" that do not exist.
find . -name "AUTHORS" \
  | grep -v svn \
  | while read f
    do
      grep '^[^ ]' $f \
        | awk '{ if (on==1) print $0; else on=($1=="FILES"); }' \
        | while read IMG
          do
            # remove the comments at the end of the line
            IMG="$( echo $IMG | sed 's, */.\+$,,')"
            IMG_FILE=$(echo $f | sed 's,[^/]\+$,,')"$IMG"

            if [ ! -f "$IMG_FILE" ]
            then
              echo "Can't find file '$IMG_FILE'"
            fi
          done
    done

# List all the non XCF files listed in the "AUTHORS" that have a corresponding
# XCF file.
find . -name "AUTHORS" \
  | grep -v svn \
  | while read f
    do
      grep '^[^ ]' $f \
        | awk '{ if (on==1) print $0; else on=($1=="FILES"); }' \
        | while read IMG
          do
            if ! echo $IMG | grep xcf > /dev/null
            then
              XCF_FILE_NAME=$(echo $IMG | sed 's,\.[^.]\+$,,').xcf

              IMG_FILE=$(echo $f | sed 's,[^/]\+$,,')"$IMG"
              XCF_FILE=$(echo $f | sed 's,[^/]\+$,,')"$XCF_FILE_NAME"
              BZ2_FILE=$(echo $f | sed 's,[^/]\+$,,')"$XCF_FILE_NAME".bz2

              if [ -f "$XCF_FILE" ] || [ -f "$BZ2_FILE" ]
              then
                echo "XCF file for '$IMG_FILE'"
              fi
            fi
          done
    done
