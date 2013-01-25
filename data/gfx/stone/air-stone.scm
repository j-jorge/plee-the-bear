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

(let ( (air_name "air-stone.xcf.bz2")
       (air_parts_name "air-stone-parts.xcf.bz2")
       (dest_name "air-stone.png") )
  (let ( ( air_image(car (gimp-file-load 1 air_name air_name)) )
         ( air_parts_image
           (car (gimp-file-load 1 air_parts_name air_parts_name)) )
         ( dest_image (new-image 256 64)) )

    ; air stone
    (create-layer air_image '(0 1 6)   0  0 32 23 dest_image)
    (create-layer air_image '(2 3 6)  32  0 32 23 dest_image)
    (create-layer air_image '(4 5 6)  64  0 32 23 dest_image)
    (create-layer air_image '(1   6)  96  0 32 23 dest_image)
    (create-layer air_image '(3   6) 128  0 32 23 dest_image)
    (create-layer air_image '(5   6) 160  0 32 23 dest_image)
    (create-layer air_image '(1   7) 192  0 32 23 dest_image)
    (create-layer air_image '(3   7) 224  0 32 23 dest_image)
    (create-layer air_image '(5   7)   0 23 32 23 dest_image)
    (create-layer air_image '(1   8)  32 23 32 23 dest_image)
    (create-layer air_image '(3   8)  64 23 32 23 dest_image)
    (create-layer air_image '(5   8)  96 23 32 23 dest_image)
    (create-layer air_image '(1   9) 128 23 32 23 dest_image)
    (create-layer air_image '(3   9) 160 23 32 23 dest_image)
    (create-layer air_image '(5   9) 192 23 32 23 dest_image)

    ; air stone parts
    (create-layer air_parts_image '(0)  0 46 14 11 dest_image)
    (create-layer air_parts_image '(1) 14 46  8 14 dest_image)
    (create-layer air_parts_image '(2) 22 46 15  8 dest_image)
    (create-layer air_parts_image '(3) 37 46 13  8 dest_image)
    (create-layer air_parts_image '(4) 50 46 15 10 dest_image)

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
