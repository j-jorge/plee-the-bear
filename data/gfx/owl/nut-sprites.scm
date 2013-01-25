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

; "../../common.scm" must have been loaded

; \brief Copy a sprite of the hazelnut in an image
; \param sprite_index The index of the sprite (should be 0).
; \param x The x-coordinate of the hazelnut in the destination image.
; \param y The y-coordinate of the hazelnut in the destination image.
; \param w The width of the hazelnut in the destination image.
; \param h The height of the hazelnut in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define nut-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/nut.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (noise   0)
               (shadows 1)
               (nut     2) )
          
          (create-layer src_image 
                        (list noise shadows nut)
                        x y w h dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define nut-sprite
