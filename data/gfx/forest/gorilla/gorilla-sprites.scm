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

; \brief Copy a sprite of the gorilla in an image
; \param sprite_index The index of the sprite (0 to 3).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define gorilla-idle-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/idle.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (mouth_3   0)
               (mouth_2   1)
               (mouth_1   2)
               (right_arm 3)
               (right_leg 4)
               (left_foot 5)
               (body      6)
               (grass     7)
               (face      8)
               (left_leg  9) )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list grass right_arm right_leg left_foot body face
			       left_leg))
		    ((1) (list mouth_1 right_arm right_leg left_foot body face
			       left_leg))
		    ((2) (list mouth_2 right_arm right_leg left_foot body face
			       left_leg))
		    ((3) (list mouth_3 right_arm right_leg left_foot body face
			       left_leg))
		  )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let

          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define gorilla-idle-sprite
