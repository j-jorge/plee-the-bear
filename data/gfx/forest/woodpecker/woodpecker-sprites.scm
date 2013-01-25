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

; \brief Copy a sprite of the woodpecker in an image
; \param sprite_index The index of the sprite (0 to 3).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define woodpecker-pecking-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    ; the ratio of the size is 0.125 (0.125739640 vert., 0.125 hor.)
    (let ( (src_name (string-append dir_path "/pecking.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (wing_4 3)
               (wing_3 4)
               (wing_2 5)
               (wing_1 6)
               (leg    7)
               (merged_body_4  8)
               (merged_body_3  9)
               (merged_body_2 10)
               (merged_body_1 11)
               (leg_back 14) )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list leg leg_back wing_1 merged_body_1))
		    ((1) (list leg leg_back wing_2 merged_body_2))
		    ((2) (list leg leg_back wing_3 merged_body_3))
		    ((3) (list leg leg_back wing_4 merged_body_4))
		  )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define woodpecker-pecking-sprite

; \brief Copy a sprite of the woodpecker in an image
; \param sprite_index The index of the sprite (0 to 1).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define woodpecker-watching-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (if (= sprite_index 0)
	(let ( (src_name (string-append dir_path "/watching.xcf.bz2")) )
	  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
		 )

	    ; layer names
	    (let ( (sunglasses 0)
		   (hair 1)
		   (beak 2)
		   (wing 3)
		   (leg 4)
		   (body 5)
		   (leg_back 6) )

	      (create-layer src_image
			    (list sunglasses hair beak wing leg body leg_back)
			    x y w h dest_image)
	      ) ; let
	    ) ; let
	  ) ; let
        ; else
	(let ( (src_name (string-append dir_path "/watching-right.xcf.bz2")) )
	  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
		 )

            ; layer names
	    (let ( (sunglasses 0)
		   (hair 1)
		   (beak 2)
		   (wing 3)
		   (leg 4)
		   (body 5)
		   (leg_back 6) )

	      (create-layer src_image
			    (list sunglasses hair beak wing leg body leg_back)
			    x y w h dest_image)
	      ) ; let
	    ) ; let
	  ) ; let
	) ; if
    ) ; lambda
  ) ; define woodpecker-watching-sprite

; \brief Copy a sprite of the woodpecker in an image
; \param sprite_index The index of the sprite (0 to 5).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define woodpecker-attacking-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/attacking.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (merged  0)
               (speed_3 1)
               (speed_2 2)
               (speed_1 3) )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list merged speed_1))
		    ((1) (list merged speed_1 speed_2))
		    ((2) (list merged speed_1 speed_2 speed_3))
		    ((3) (list merged speed_2 speed_3))
		    ((4) (list merged speed_3))
		    ((5) (list merged))
		  )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define woodpecker-attacking-sprite

; \brief Copy a sprite of the woodpecker in an image
; \param sprite_index The index of the sprite (0).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define woodpecker-wig-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/wig.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (main 0) )

          (create-layer src_image (list main) x y w h dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define woodpecker-wig-sprite

; \brief Copy a sprite of the woodpecker in an image
; \param sprite_index The index of the sprite (0 to 2).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define woodpecker-feather-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/feather.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (green 0)
               (red 1)
               (main 2) )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list main))
		    ((1) (list main red))
		    ((2) (list main green))
		  )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define woodpecker-feather-sprite

; \brief Copy a sprite of the woodpecker in an image
; \param sprite_index The index of the sprite (0).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define woodpecker-hole-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/hole.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (main 0) )

          (create-layer src_image (list main) x y w h dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define woodpecker-hole-sprite

; \brief Copy a sprite of the woodpecker in an image
; \param sprite_index The index of the sprite (0 to 7).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define woodpecker-flying-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/flying.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (sunglasses  0)
               (hair 1)
               (beak 2)
               (eyes 3)
               (right_wing_1 4)
               (right_wing_2 5)
               (right_wing_3 6)
               (right_wing_4 7)
               (right_leg 8)
               (body 9)
               (left_leg 10)
               (left_wing_1 11)
               (left_wing_2 12)
               (left_wing_3 13)
               (left_wing_4 14) )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list sunglasses hair beak eyes body right_leg left_leg
			       right_wing_1 left_wing_1))
		    ((1) (list sunglasses hair beak eyes body right_leg left_leg
			       right_wing_2 left_wing_2))
		    ((2) (list sunglasses hair beak eyes body right_leg left_leg
			       right_wing_3 left_wing_3))
		    ((3) (list sunglasses hair beak eyes body right_leg left_leg
			       right_wing_4 left_wing_4))

                    ; and dying too
		    ((4) (list beak eyes body right_leg left_leg
			       right_wing_1 left_wing_4))
		    ((5) (list beak eyes body right_leg left_leg
			       right_wing_2 left_wing_3))
		    ((6) (list beak eyes body right_leg left_leg
			       right_wing_3 left_wing_2))
		    ((7) (list beak eyes body right_leg left_leg
			       right_wing_4 left_wing_1))
		  )
		  ) )

	    (create-layer src_image layers x y w h dest_image)

	    ) ; let
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define woodpecker-flying-sprite
