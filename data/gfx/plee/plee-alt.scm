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
; --
;
; This script is intended to be run in this directory and via gimp-console:
;
;   gimp-console -b - < this_script.scm
;
(load "../../common.scm")

(define apply-to
  (lambda (src_name dest_name src_color threshold new_color)

    (let ( (dest_image (car (gimp-file-load 1 src_name src_name)))
	   )
      (let ( (layer (car (gimp-image-get-active-drawable dest_image)))
	     )

	(gimp-by-color-select layer src_color threshold 2 1 0 0 1)
					; 90 is the threshold
					; 2 is CHANEL-OP-REPLACE
					; 1 is antialiasing = true
					; 0 is feather = false
					; 0 is the feather radius
					; 1 tells to use the composite image

	(gimp-context-set-foreground new_color )
	(gimp-edit-bucket-fill layer 0 21 100 0 1 0 0)
					; 0 is FG-BUCKET-FILL
					; 21 is GRAIN-MERGE-MODE
					; 100 is the opacity of the final bucket
					; 0 is the threshold (not used)
					; 1 tells to use the composite image
					; 0 is the x coordinate of the fill
					; 0 is the y coordinate of the fill


	(save-frames dest_name dest_image)

	) ; let
      ) ; let
    ) ; lambda
  ) ; define apply-to


(define apply-body-to
  (lambda (src_name dest_name)

    (let ( (dest_image (car (gimp-file-load 1 src_name src_name)))
	   )
      (let ( (layer (car (gimp-image-get-active-drawable dest_image)))
	     )

	(gimp-by-color-select layer '(176 118 15) 100 2 1 0 0 1)
					; 100 is the threshold
					; 2 is CHANEL-OP-REPLACE
					; 1 is antialiasing = true
					; 0 is feather = false
					; 0 is the feather radius
					; 1 tells to use the composite image

	(gimp-hue-saturation layer 0 -3 -30 70)
					; 0 is ALL-HUES
                                        ; -3 is the hue offset
                                        ; -30 is the lightness
                                        ; 70 is the saturation

	(gimp-by-color-select layer '(217 212 202) 90 2 1 0 0 1)
        (plug-in-vinvert 1 dest_image layer)
                                        ; 1 is RUN-NONINTERACTIVE

	(save-frames dest_name dest_image)

	) ; let
      ) ; let
    ) ; lambda
  ) ; define apply-to

(apply-body-to "plee.png" "plee-alt.png")
(apply-body-to "plee-1.png" "plee-alt-1.png")
(apply-body-to "plee-2.png" "plee-alt-2.png")
(apply-body-to "plee-3.png" "plee-alt-3.png")
(apply-body-to "plee-4.png" "plee-alt-4.png")
(apply-to "cap.png" "cap-alt.png" '(154 133 142) 63 '(97 37 37))

(gimp-quit 1)
