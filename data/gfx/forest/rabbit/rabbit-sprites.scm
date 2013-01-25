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

; \brief Copy a sprite of the rabbit in an image
; \param sprite_index The index of the sprite (0).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define rabbit-idle-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/idle.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (right_arm 0)
               (cap 1)
               (head 2)
               (tooth 3)
               (right_leg 4)
               (body 5)
               (left_arm 6)
               (left_leg 7) )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list right_arm cap head tooth right_leg body left_arm
			       left_leg))
		    )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define rabbit-idle-sprite

; \brief Copy a sprite of the rabbit in an image
; \param sprite_index The index of the sprite (0 to 2).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define rabbit-walk-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/walk.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (right_leg_1 0)
               (right_leg_3 1)
               (right_leg_4 2)
               (right_arm_1 3)
               (right_arm_3 4)
               (right_arm_4 5)
               (head_1 6)
               (ear_1 7)
               (ear_3 8)
               (ear_4 9)
               (body_1 10)
               (body_3 11)
               (body_4 12)
	       )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list head_1 right_leg_1 right_arm_1 ear_1 body_1))
		    ((1) (list head_1 right_leg_3 right_arm_3 ear_3 body_3))
		    ((2) (list head_1 right_leg_4 right_arm_4 ear_4 body_4))
		    )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let

          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define rabbit-walk-sprite

; \brief Copy a sprite of the rabbit in an image
; \param sprite_index The index of the sprite (0 to 5).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define rabbit-dig-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/dig.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (foot_5_1 0)
               (foot_5_2 1)
               (body_1 2)
               (body_2 3)
               (body_3 4)
               (body_4 5)
               (body_5 6)
	       )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list body_1))
		    ((1) (list body_2))
		    ((2) (list body_3))
		    ((3) (list body_4))
		    ((4) (list body_5 foot_5_1))
		    ((5) (list body_5 foot_5_2))
		  )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let

          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define rabbit-dig-sprite

; \brief Copy a sprite of the rabbit in an image
; \param sprite_index The index of the sprite (0 to 3).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define rabbit-dust-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/dust.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (dust_1 0)
               (dust_2 1)
               (dust_3 2)
               (dust_4 3)
	       )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list dust_1))
		    ((1) (list dust_2))
		    ((2) (list dust_3))
		    ((3) (list dust_4))
		  )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let

          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define rabbit-dust-sprite

; \brief Copy a sprite of the rabbit in an image
; \param sprite_index The index of the sprite (0 to 3).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define rabbit-dust-end-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/dust-end.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (dust_end_1 0)
               (dust_end_2 1)
               (dust_end_3 2)
               (dust_end_4 3)
	       )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list dust_end_1))
		    ((1) (list dust_end_2))
		    ((2) (list dust_end_3))
		    ((3) (list dust_end_4))
		  )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let

          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define rabbit-dust-end-sprite

; \brief Copy a sprite of the rabbit in an image
; \param sprite_index The index of the sprite (0 to 3).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define rabbit-jump-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/jump.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (body_1 0)
               (body_2 1)
               (body_3 2)
               (body_4 3)
	       )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list body_1))
		    ((1) (list body_2))
		    ((2) (list body_3))
		    ((3) (list body_4))
		  )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let

          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define rabbit-jump-sprite

; \brief Copy a sprite of the rabbit in an image
; \param sprite_index The index of the sprite (0).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define rabbit-fall-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/fall.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (right_leg 0)
               (right_arm 1)
               (head 2)
               (right_ear 3)
	       (body 4)
	       (left_ear 5)
	       (left_arm 6)
	       (left_leg 7)
	       )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list right_leg right_arm head right_ear body left_ear
			       left_arm left_leg))
		    )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let

          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define rabbit-fall-sprite

; \brief Copy a sprite of the rabbit in an image
; \param sprite_index The index of the sprite (0).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define rabbit-injured-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/injured.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (right_leg 0)
               (right_arm 1)
	       (eye 2)
               (head 3)
               (right_ear 4)
	       (body 5)
	       (left_leg 6)
	       (left_ear 7)
	       )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list right_leg right_arm eye head right_ear body
			       left_leg left_ear))
		    )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let

          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define rabbit-injured-sprite
