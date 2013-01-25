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

; \brief Copy a sprite of the frog in an image
; \param sprite_index The index of the sprite (0 to 2).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define frog-idle-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/idle.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (idle_3 0)
               (idle_2 1)
               (idle_1 2) )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list idle_1))
		    ((1) (list idle_1 idle_2))
		    ((2) (list idle_1 idle_3))
		  )
		  ) )

	    (create-layer src_image 
			  layers
			  x y w h dest_image)
	    ) ; let
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define frog-idle-sprite

; \brief Copy a sprite of the frog in an image
; \param sprite_index The index of the sprite (0 to 13).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define frog-spatter-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/spatter.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (frame_0    0)
               (frame_1    1)
               (spatter_1  2)
               (spatter_2  3)
               (frame_2    4)
               (eye        5)
               (eye_1      6)
               (eye_2      7)
               (eye_3      8)
               (eye_4      9)
               (eye_5     10)
               (eye_6     11)
               (eye_7     12)
               (eye_8     13)
               (eye_9     14)
               (eye_10    15)
               (frame_3   16)
               (spatter_3 17)
               (spatter_4 18)
               (spatter_5 19)
               (spatter_6 20) )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list frame_0))
		    ((1) (list frame_1 spatter_1))
		    ((2) (list frame_2 spatter_2))
		    ((3) (list frame_3 spatter_3 eye))
		    ((4) (list frame_3 spatter_4 eye_1))
		    ((5) (list frame_3 spatter_5 eye_2))
		    ((6) (list frame_3 spatter_6 eye_3))
		    ((7) (list frame_3 spatter_6 eye_4))
		    ((8) (list frame_3 spatter_6 eye_5))
		    ((9) (list frame_3 spatter_6 eye_6))
		    ((10) (list frame_3 spatter_6 eye_7))
		    ((11) (list frame_3 spatter_6 eye_8))
		    ((12) (list frame_3 spatter_6 eye_9))
		    ((13) (list frame_3 spatter_6 eye_10))
		  )
		  ) )

	    (create-layer src_image layers x y w h dest_image)

	    ) ; let
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define frog-spatter-sprite
