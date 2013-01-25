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

(let ( (src_name "spring.xcf.bz2")
       (dest_name "spring.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (car (gimp-image-new 256 256 RGB)))
         )
    (set-layer-position src_image 3 0 30)
    (create-layer src_image '(0 3 9)    0  0 60 45 dest_image)
    (create-layer src_image '(1 3 9)  183  0 60 45 dest_image)
    (create-layer src_image '(2 3 9)  122 46 60 45 dest_image)

    (set-layer-position src_image 3 0 15)
    (create-layer src_image '(0 3 7 8)  61  0 60 45 dest_image)
    (create-layer src_image '(1 3 7 8)   0 46 60 45 dest_image)
    (create-layer src_image '(2 3 7 8) 183 46 60 45 dest_image)

    (set-layer-position src_image 3 0 0)
    (create-layer src_image '(0 3 5 6) 122  0 60 45 dest_image)
    (create-layer src_image '(1 3 5 6)  61 46 60 45 dest_image)
    (create-layer src_image '(2 3 5 6)   0 92 60 45 dest_image)
    
    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
