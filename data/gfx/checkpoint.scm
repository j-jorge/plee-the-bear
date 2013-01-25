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
(load "../common.scm")

(let ( (src_name "checkpoint.xcf.bz2")
       (dest_name "checkpoint.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (new-image 512 256)) )

    (let ( (plinth 0)
           (green_bulbs 1)
           (red_bulbs 2)
           (green_lights 3)
           (red_lights 4)
           (shadows 5)
           (plee 6)
           (panels 7) )

      (set-layer-position src_image plee 0 168)
      (set-layer-position src_image panels 0 168)
      (create-layer src_image
                    (list plinth red_bulbs red_lights shadows plee panels)
                    0 0 100 120 dest_image)

      (create-layer src_image
                    (list plinth green_bulbs green_lights shadows plee panels)
                    100 0 100 120 dest_image)

      (set-layer-position src_image plee 0 147)
      (set-layer-position src_image panels 0 147)
      (create-layer src_image
                    (list plinth green_bulbs green_lights shadows plee panels)
                    200 0 100 120 dest_image)

      (set-layer-position src_image plee 0 126)
      (set-layer-position src_image panels 0 126)
      (create-layer src_image
                    (list plinth green_bulbs green_lights shadows plee panels)
                    300 0 100 120 dest_image)

      (set-layer-position src_image plee 0 105)
      (set-layer-position src_image panels 0 105)
      (create-layer src_image
                    (list plinth green_bulbs green_lights shadows plee panels)
                    400 0 100 120 dest_image)

      (set-layer-position src_image plee 0 84)
      (set-layer-position src_image panels 0 84)
      (create-layer src_image
                    (list plinth green_bulbs green_lights shadows plee panels)
                    0 120 100 120 dest_image)

      (set-layer-position src_image plee 0 63)
      (set-layer-position src_image panels 0 63)
      (create-layer src_image
                    (list plinth green_bulbs green_lights shadows plee panels)
                    100 120 100 120 dest_image)

      (set-layer-position src_image plee 0 42)
      (set-layer-position src_image panels 0 42)
      (create-layer src_image
                    (list plinth green_bulbs green_lights shadows plee panels)
                    200 120 100 120 dest_image)

      (set-layer-position src_image plee 0 21)
      (set-layer-position src_image panels 0 21)
      (create-layer src_image
                    (list plinth green_bulbs green_lights shadows plee panels)
                    300 120 100 120 dest_image)

      (set-layer-position src_image plee 0 0)
      (set-layer-position src_image panels 0 0)
      (create-layer src_image
                    (list plinth green_bulbs green_lights shadows plee panels)
                    400 120 100 120 dest_image)
      ) ; let

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
