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

; \brief Copy a sprite of the wasp in an image
; \param sprite_index The index of the sprite (0 to 3).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define wasp-flying-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/wasp-flying.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (sash_3        0)
               (sash_2        1)
               (sash_1        2)
               (buckle_1      3)
               (back_buckle   4)
               (paws_1        5)
               (abdomen_1     6)
               (sting_1       7)
               (left_wing_3   8)
               (left_wing_2   9)
               (left_wing_1  10)
               (eye_1        11)
               (base         12)
               (right_wing_3 13)
               (right_wing_2 14)
               (right_wing_1 15) )

	  (define apply-with-layers
	    (lambda (opacity_1 opacity_2 opacity_3 layers)

	      (set-layer-opacity src_image (list left_wing_1) opacity_1)
	      (set-layer-opacity src_image (list right_wing_1) opacity_1)
	      (set-layer-opacity src_image (list left_wing_2) opacity_2)
	      (set-layer-opacity src_image (list right_wing_2) opacity_2)
	      (set-layer-opacity src_image (list left_wing_3) opacity_3)
	      (set-layer-opacity src_image (list right_wing_3) opacity_3)

	      (create-layer src_image 
			    (append layers
				    (list buckle_1 back_buckle paws_1 abdomen_1
					  eye_1 base) )
			    x y w h dest_image)
	      ) ; lambda
	    ) ; define apply-with-layers

	  (case sprite_index
	    ((0) (apply-with-layers 40 80 0
				    (list sash_1 left_wing_1 left_wing_2
					  right_wing_1 right_wing_2)))
	    ((1) (apply-with-layers 0 40 80
				    (list sash_2 left_wing_2 left_wing_3
					  right_wing_2 right_wing_3)))
	    ((2) (apply-with-layers 0 80 40
				    (list sash_3 left_wing_3 left_wing_2
					  right_wing_3 right_wing_2)))
	    ((3) (apply-with-layers 80 40 0
				    (list sash_1 left_wing_2 left_wing_1
					  right_wing_2 right_wing_1)))
	    ) ; case

          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define wasp-flying-sprite

; \brief Copy a sprite of the wasp in an image
; \param sprite_index The index of the sprite (0 to 3).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define wasp-dying-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/wasp-shooting.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (buckle        0)
               (left_wing_3   1)
               (left_wing_2   2)
               (left_wing_1   3)
               (sash          4)
               (paws          5)
               (paws_1        6)
               (abdomen      10)
               (eyelid       25)
               (base         26)
               (right_wing_3 27)
               (right_wing_2 28)
               (right_wing_1 29) )

	  (define apply-with-layers
	    (lambda (opacity_1 opacity_2 opacity_3 layers)

	      (set-layer-opacity src_image (list left_wing_1) opacity_1)
	      (set-layer-opacity src_image (list right_wing_1) opacity_1)
	      (set-layer-opacity src_image (list left_wing_2) opacity_2)
	      (set-layer-opacity src_image (list right_wing_2) opacity_2)
	      (set-layer-opacity src_image (list left_wing_3) opacity_3)
	      (set-layer-opacity src_image (list right_wing_3) opacity_3)

	      (create-layer src_image 
			    (append layers
				    (list buckle sash paws paws_1 abdomen
					  eyelid base) )
			    x y w h dest_image)
	      ) ; lambda
	    ) ; define apply-with-layers

	  (case sprite_index
	    ((0) (apply-with-layers 40 80 0
				    (list left_wing_1 left_wing_2 right_wing_1
					  right_wing_2)))
	    ((1) (apply-with-layers 0 40 80
				    (list left_wing_2 left_wing_3 right_wing_2
					  right_wing_3)))
	    ((2) (apply-with-layers 0 80 40
				    (list left_wing_3 left_wing_2 right_wing_3
					  right_wing_2)))
	    ((3) (apply-with-layers 80 40 0
				    (list left_wing_2 left_wing_1 right_wing_2
					  right_wing_1)))
	    ) ; case

          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define wasp-dying-sprite

; \brief Copy a sprite of the wasp in an image
; \param sprite_index The index of the sprite (0 to 3).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define wasp-soul-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/soul.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (stars_1  0)
               (stars_2  1)
               (stars_3  2)
               (stars_4  3)
               (merged   4) )

	  (case sprite_index
	    ((0) (create-layer src_image (list stars_1 merged) x y w h
			       dest_image))
	    ((1) (create-layer src_image (list stars_2 merged) x y w h
			       dest_image))
	    ((2) (create-layer src_image (list stars_3 merged) x y w h
			       dest_image))
	    ((3) (create-layer src_image (list stars_4 merged) x y w h
			       dest_image))
	    ) ; case

          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define wasp-soul-sprite
