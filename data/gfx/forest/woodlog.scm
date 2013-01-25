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

(let ( (image_name "woodlog.xcf.bz2")
       (dest_name "woodlog.png") )
  (let ( (src_image (car (gimp-file-load 1 image_name image_name)))
         (dest_image (new-image 256 256))
         )

    (let ( (acorn 0)
	   (left_leaf 1)
	   (right_leaf 2)
	   (branch 3)
	   (mushroom_bottom 4)
	   (mushroom 5)
	   (spikes 6)
	   (large_left 7)
	   (foreground 8)
	   (wood_effect 9)
	   (inside 10)
	   (background 11) )
      ( create-layer-crop src_image
			  (list acorn left_leaf right_leaf branch
				mushroom_bottom mushroom foreground wood_effect
				inside background)
			  82 18 253 206
			  0  0 127 103 dest_image '() )
      ( create-layer-crop src_image
			  (list acorn left_leaf right_leaf branch foreground
				wood_effect inside background)
			  82  18 253 206
			  0 103 127 103 dest_image '() )
      ( create-layer-crop src_image
			  (list mushroom_bottom mushroom foreground wood_effect
				inside background)
			  93 94 242 130
			  127  0 121  65 dest_image '() )
      ( create-layer-crop src_image
			  (list foreground wood_effect inside background)
			  93 113 242 111
			  127  65 121  56 dest_image '() )
      ( create-layer-crop src_image
			  (list large_left spikes foreground wood_effect inside
				background)
			  93 108 242 123
			  127 121 121 62 dest_image '() )
      ( create-layer-crop src_image
			  (list spikes foreground wood_effect inside background)
			  93 108 242 123
			  127 183 121 62 dest_image '() )
    ) ; let

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let

