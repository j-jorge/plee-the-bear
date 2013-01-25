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

; \brief Copy a sprite of the waiting owl in an image
; \param sprite_index The index of the sprite (0 to 2).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define owl-waiting-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/owl-waiting.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (noise  1)
               (eye_r  2)
               (eye_l  3)
               (beak_2 4)
               (beak_1 5)
               (beak_0 6)
               (body   7)
               (foot   8) )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list noise eye_r eye_l beak_0 body foot))
		    ((1) (list noise eye_r eye_l beak_1 body foot))
		    ((2) (list noise eye_r eye_l beak_2 body foot))
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
  ) ; define owl-waiting-sprite

; \brief Copy a sprite of the owl with the hazelnut in an image
; \param sprite_index The index of the sprite (should be 0).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define owl-with-nut-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/owl-with-nut.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (noise       1)
               (eye         2)
               (body        3)
               (feet        4)
               (nut_shadows 5)
               (nut         6) )
          
          (create-layer src_image 
                        (list noise eye body feet nut_shadows nut)
                        x y w h dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define owl-with-nut-sprite

; \brief Copy a sprite of the crying owl in an image
; \param sprite_index The index of the sprite (0 to 4).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define owl-tears-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/owl-tears.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (noise  0)
               (beak   1)
               (tears  2)
               (body   3)
               (wing_4 4)
               (wing_3 5)
               (wing_2 6)
               (wing_1 7)
               (wing_0 8) )
          
	  (let ( (layers
		  (case sprite_index
		    ((0) (list noise beak tears body wing_0))
		    ((1) (list noise beak tears body wing_1))
		    ((2) (list noise beak tears body wing_2))
		    ((3) (list noise beak tears body wing_3))
		    ((4) (list noise beak tears body wing_4))
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
  ) ; define owl-tears-sprite
