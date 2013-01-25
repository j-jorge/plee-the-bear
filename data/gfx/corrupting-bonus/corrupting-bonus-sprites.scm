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

; \brief Copy a sprite of the corrupting bonus in an image.
; \param sprite_index The index of the sprite (0 to 7).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the source images.
(define corrupting-bonus-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name
            (string-append dir_path "/corrupting-bonus.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (front_0 0) (front_1 1) (front_2 2) (front_3 3) (front_4 4)
               (front_5 5)
               (tear_0 6) (tear_1 7) (tear_2 8) (tear_3 9)
               (light_0 10) (light_1 11) (light_2 12) (light_3 13) (light_4 14)
               (light_5 15)
               (back_0 16) (back_1 17) (back_2 18) (back_3 19) (back_4 20)
               (halo_0 21) (halo_0_1 22) (halo_1 23) (halo_2 23) (halo_3 24)
               (halo_4 25) (halo_5 26) (halo_5_1 27)
               )
          
	  (let ( (layers
		  (case sprite_index
		    ((0) (list front_0 light_0 tear_0 back_0 halo_0))
		    ((1) (list front_0 light_0 tear_1 back_0 halo_0_1))
		    ((2) (list front_1 light_1 tear_2 back_1 halo_1))
		    ((3) (list front_2 light_2 tear_3 back_2 halo_2))
		    ((4) (list front_3 light_3 tear_3 back_3 halo_3))
		    ((5) (list front_4 light_4 tear_2 back_4 halo_4))
		    ((6) (list front_5 light_5 tear_1        halo_5))
		    ((7) (list front_5 light_5 tear_0        halo_5_1))
		    )
		  ) )

	    (create-layer src_image layers x y w h dest_image)
	    ) ; let
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define corrupting-bonus-sprite
