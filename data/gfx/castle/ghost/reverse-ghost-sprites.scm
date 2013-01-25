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

; "../../../common.scm" must have been loaded

; \brief Copy a sprite of the reverse ghost in an image.
; \param sprite_index The index of the sprite (0 to 4).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define reverse-ghost-appear-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name
            (string-append dir_path "/reverse-ghost-appearing.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (idle 0) (appear_1 1)
               (appear_2 2) (appear_3 3)
               (appear_4 4) )
          
	  (let ( (layers
		  (case sprite_index
		    ((0) (list idle))
		    ((1) (list appear_1))
		    ((2) (list appear_2))
		    ((3) (list appear_3))
		    ((4) (list appear_4))
		    )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define reverse-ghost-appear-sprite

; \brief Copy a sprite of the reverse ghost in an image.
; \param sprite_index The index of the sprite (0 to 2).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the owl images.
(define reverse-ghost-move-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name
            (string-append dir_path "/reverse-ghost-moving.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (arms_1 0) (move_1 1)
               (arms_2 2) (move_2 3)
               (arms_3 4) (move_3 5) )

	  (let ( (layers
		  (case sprite_index
		    ((0) (list arms_1 move_1))
		    ((1) (list arms_2 move_2))
		    ((2) (list arms_3 move_3))
		    )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define reverse-ghost-move-sprite
