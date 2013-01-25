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

; \brief Copy a sprite of the shinny honey jar in an image
; \param sprite_index The index of the sprite (0 to 7).
; \param x The x-coordinate of the sprite in the destination image.
; \param y The y-coordinate of the sprite in the destination image.
; \param w The width of the sprite in the destination image.
; \param h The height of the sprite in the destination image.
; \param dest_image The destination image.
; \param dir_path The path of the directory containing the xcf images.
(define shiny-honey-jar-sprite
  (lambda (sprite_index x y w h dest_image dir_path)

    (let ( (src_name (string-append dir_path "/shiny-honey-jar.xcf.bz2")) )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
	     )

	(define apply-with-layers
	  (lambda (layers)
	    ( create-layer src_image (append layers '(10 11 12 13))
			   x y w h dest_image )
	    ) ; lambda
	  ) ; define apply-with-layers

	(case sprite_index
	  ((0) (apply-with-layers '(0 5)))
	  ((1) (apply-with-layers '(1 6)))
	  ((2) (apply-with-layers '(2 7)))
	  ((3) (apply-with-layers '(3 8)))
	  ((4) (apply-with-layers '(4 9)))
	  ((5) (apply-with-layers '(3 5)))
	  ((6) (apply-with-layers '(2 7)))
	  ((7) (apply-with-layers '(1 9)))
	  ) ; case

	) ; let
      ) ; let
    ) ; lambda
  ) ; define shiny-honey-jar-sprite
