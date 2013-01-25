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

(let ( (src_name "frame.xcf.bz2")
       (dest_name "frame.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (new-image 128 32)) )

    (let ( (cursor 0)
           (cursor_shadow 1)
	   (slider 2)
	   (slider_bar 3)
	   (check 4)
	   (check_shadow 5)
	   (checkbox 6)
	   (radio_check 7)
	   (radio 8) )

      ; we increase the top alone
      (create-layer src_image (list cursor cursor_shadow)
		    0 0 32 32 dest_image)
      (create-layer-crop src_image (list checkbox)
			 0 0 46 41
			 32 0 23 20 dest_image '())
      (create-layer-crop src_image (list checkbox check check_shadow)
			 0 0 46 41
			 55 0 23 20 dest_image '())
      (create-layer-crop src_image (list checkbox slider)
			 0 0 20 44
			 78 0 10 22 dest_image '())
      (create-layer-crop src_image (list checkbox slider_bar)
			 0 0 2 6
			 78 22 1 3 dest_image '())
      (create-layer-crop src_image (list radio)
			 0 0 30 30
			 88 0 15 15 dest_image '())
      (create-layer-crop src_image (list radio radio_check)
			 0 0 30 30
			 88 15 15 15 dest_image '())
      ) ; let

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
