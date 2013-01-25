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
(load "../../common.scm")

(let ( (src_name "medal.xcf.bz2")
       (dest_name "medal.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (new-image 256 256)) )

    (let ( (bronze 0)
           (silver 1)
           (gold 2)
           (empty 3)
           (hand 4)
           (candy 5)
	   (candy_shadow 6)
	   (cup 7)
	   (cup_background 8)
	   (star 9)
	   (circle 10)
	   (medal 11)
	   (pillow 12) )

      (create-layer src_image (list empty pillow)
                    0 0 128 128 dest_image)
      (create-layer src_image (list gold cup cup_background medal pillow)
                    128 0 128 128 dest_image)
      (create-layer src_image (list silver hand star medal pillow)
                    0 128 128 128 dest_image)
      (create-layer src_image
		    (list bronze candy circle medal pillow)
                    128 128 128 128 dest_image)
      ) ; let

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
