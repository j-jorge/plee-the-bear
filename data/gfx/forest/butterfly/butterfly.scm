;
;  Plee the Bear -- gfx script tools
;
;  Copyright (C) 2005-2010 Julien Jorge, Sebastien Angibaud
;
;  This program is free software; you can redistribute it and/or modify it
;  under the terms of the GNU General Public License as published by the
;  Free Software Foundation; either version 2 of the License, or (at your
;  option) any later version.
;
;  This program is distributed in the hope that it will be useful, but WITHOUT
;  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
;  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
;  more details.
;
;  You should have received a copy of the GNU General Public License along
;  with this program; if not, write to the Free Software Foundation, Inc.,
;  51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
;
;  contact: plee-the-bear@gamned.org
;
;  Please add the tag [PTB] in the subject of your mails.
;
; --
;
; This script is intended to be run in this directory and via gimp-console:
;
;   gimp-console -b - < this_script.scm
;
(load "../../../common.scm")

(let ( (src_name "butterfly.xcf.bz2")
       (dest_name "butterfly.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (new-image 256 32)) )

   ; layer names
    (let ( (pattern_2 0)
           (pattern_1 1)
           (tricolor  2)
           (bicolor   3)
           (wing_3    4)
           (body      5)
           (wing_2    6)
           (wing_1    7) )

      (create-layer src_image
                    (list body pattern_1 wing_1)
                    0 0 14 12 dest_image)
      (create-layer src_image
                    (list body pattern_2 wing_2)
                    14 0 14 12 dest_image)
      (create-layer src_image
                    (list body wing_3)
                    28 0 14 12 dest_image)

      (create-layer src_image
                    (list body pattern_1 wing_1 bicolor)
                    42 0 14 12 dest_image)
      (create-layer src_image
                    (list body pattern_2 wing_2 bicolor)
                    56 0 14 12 dest_image)
      (create-layer src_image
                    (list body wing_3 bicolor)
                    70 0 14 12 dest_image)

      (create-layer src_image
                    (list body pattern_1 wing_1 tricolor)
                    84 0 14 12 dest_image)
      (create-layer src_image
                    (list body pattern_2 wing_2 tricolor)
                    98 0 14 12 dest_image)
      (create-layer src_image
                    (list body wing_3 tricolor)
                    112 0 14 12 dest_image)

      (create-layer src_image
                    (list body pattern_1 wing_1 bicolor tricolor)
                    126 0 14 12 dest_image)
      (create-layer src_image
                    (list body pattern_2 wing_2 bicolor tricolor)
                    140 0 14 12 dest_image)
      (create-layer src_image
                    (list body wing_3 bicolor tricolor)
                    154 0 14 12 dest_image)

      (create-layer src_image
                    (list body wing_1)
                    168 0 14 12 dest_image)
      (create-layer src_image
                    (list body wing_2)
                    182 0 14 12 dest_image)
      (create-layer src_image
                    (list body wing_3)
                    196 0 14 12 dest_image)

      (create-layer src_image
                    (list body wing_1 bicolor)
                    210 0 14 12 dest_image)
      (create-layer src_image
                    (list body wing_2 bicolor)
                    224 0 14 12 dest_image)
      (create-layer src_image
                    (list body wing_3 bicolor)
                    238 0 14 12 dest_image)

      (create-layer src_image
                    (list body wing_1 tricolor)
                    0 12 14 12 dest_image)
      (create-layer src_image
                    (list body wing_2 tricolor)
                    14 12 14 12 dest_image)
      (create-layer src_image
                    (list body wing_3 tricolor)
                    28 12 14 12 dest_image)

      (create-layer src_image
                    (list body wing_1 bicolor tricolor)
                    42 12 14 12 dest_image)
      (create-layer src_image
                    (list body wing_2 bicolor tricolor)
                    56 12 14 12 dest_image)
      (create-layer src_image
                    (list body wing_3 bicolor tricolor)
                    70 12 14 12 dest_image)

      ) ; let

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
