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

; \brief Copy a the sprites of the flash
; \param src_image The image in which we take the sprites.
; \param dest_image The destination image.
; \param top The index of the layer for the top part.
; \param bottom The index of the layer for the bottom part.
; \param x The x-coordinate of the sprite group.
; \param x The y-coordinate of the sprite group.
(define create-star
  (lambda (src_image dest_image top bottom x y)

    ; we increase the top alone
    (create-layer src_image (list top)  (+ x 12) (+ y 12)  8  8 dest_image)
    (create-layer src_image (list top)  (+ x 41) (+ y  8) 14 14 dest_image)
    (create-layer src_image (list top)  (+ x 70) (+ y  6) 20 20 dest_image)
    (create-layer src_image (list top)  (+ x 99) (+ y  3) 26 26 dest_image)

    ; we increase the bottom
    (create-layer src_image (list bottom)  (+ x 12) (+ y 44)  8  8 dest_image)
    (create-layer src_image (list bottom)  (+ x 41) (+ y 41) 14 14 dest_image)
    (create-layer src_image (list bottom)  (+ x 70) (+ y 38) 20 20 dest_image)
    (create-layer src_image (list bottom)  (+ x 99) (+ y 35) 26 26 dest_image)
    ; and we keep the full size for the top
    (create-layer src_image (list top) (+ x  0) (+ y 32) 32 32 dest_image)
    (create-layer src_image (list top) (+ x 32) (+ y 32) 32 32 dest_image)
    (create-layer src_image (list top) (+ x 64) (+ y 32) 32 32 dest_image)
    (create-layer src_image (list top) (+ x 96) (+ y 32) 32 32 dest_image)

    ; we keep the full size for the bottom
    (create-layer src_image (list bottom) (+ x  0) (+ y 64) 32 32 dest_image)
    (create-layer src_image (list bottom) (+ x 32) (+ y 64) 32 32 dest_image)
    (create-layer src_image (list bottom) (+ x 64) (+ y 64) 32 32 dest_image)
    (create-layer src_image (list bottom) (+ x 96) (+ y 64) 32 32 dest_image)
    ; and we decrease the top
    (create-layer src_image (list top) (+ x   3) (+ y 67) 26 26 dest_image)
    (create-layer src_image (list top) (+ x  38) (+ y 70) 20 20 dest_image)
    (create-layer src_image (list top) (+ x  73) (+ y 73) 14 14 dest_image)
    (create-layer src_image (list top) (+ x 108) (+ y 76)  8  8 dest_image)

    ; then we decrease the bottom
    (create-layer src_image (list bottom) (+ x   3) (+ y  99) 26 26 dest_image)
    (create-layer src_image (list bottom) (+ x  38) (+ y 102) 20 20 dest_image)
    (create-layer src_image (list bottom) (+ x  73) (+ y 105) 14 14 dest_image)
    (create-layer src_image (list bottom) (+ x 108) (+ y 108)  8  8 dest_image)
    
    ) ; lambda
  ) ; define create-star

(let ( (src_name "corrupting-bonus-disapearing.xcf.bz2")
       (dest_name "corrupting-bonus-disapearing.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (new-image 256 128)) )

    (create-star src_image dest_image 0 1   0 0)
    (create-star src_image dest_image 2 3 128 0)

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
