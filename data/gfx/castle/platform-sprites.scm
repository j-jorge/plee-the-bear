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

; \brief Copy a sprite of the platform in an image.
; \param sprite_index The index of the sprite (0 to 3).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the source images.
(define platform-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name
            (string-append dir_path "/platform.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (block 0)
               (halos_1 1) (halos_2 2) (halos_3 3) (halos_4 4)
               (eyes_1 5) (eyes_2 6) (eyes_3 7) (eyes_4 8)
               (right_gargoyle 9) (left_gargoyle 10)
               (balls_1 11) (balls_2 12) (balls_3 13) (balls_4 14)
               (candles 15)
               (flames_1 16) (flames_2 17) (flames_3 18) (flames_4 19) )
          
	  (let ( (layers
		  (case sprite_index
		    ((0) (list block right_gargoyle candles left_gargoyle
                               halos_1 eyes_1 balls_1 flames_1))
		    ((1) (list block right_gargoyle candles left_gargoyle
                               halos_2 eyes_2 balls_2 flames_2))
		    ((2) (list block right_gargoyle candles left_gargoyle
                               halos_3 eyes_3 balls_3 flames_3))
		    ((3) (list block right_gargoyle candles left_gargoyle
                               halos_4 eyes_4 balls_4 flames_4))
		    )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define platform-sprite
