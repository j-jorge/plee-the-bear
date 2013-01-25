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

; \brief Copy a sprite of the headstone in an image
; \param sprite_index The index of the sprite (should be 0).
; \param x The x-coordinate of the hazelnut in the destination image.
; \param y The y-coordinate of the hazelnut in the destination image.
; \param w The width of the hazelnut in the destination image.
; \param h The height of the hazelnut in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define headstone-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/headstone.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (dust_6 0)
               (dust_5 1)
               (dust_4 2)
               (dust_3 3)
               (dust_2 4)
               (dust_1 5)
	       (dust_ground_5 6)
	       (dust_ground_4 7)
	       (dust_ground_3 8)
	       (dust_ground_2 9)
	       (dust_ground_1 10)
               (stone 11) )
          
          (create-layer src_image 
                        (list dust_ground_4 stone)
                        x y w h dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define headstone-sprite
