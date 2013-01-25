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
(load "../../../common.scm")

(load "../../owl/nut-sprites.scm")
(load "../../owl/owl-sprites.scm")

(load "../../headstone-sprites.scm")
(load "../../shiny-honey-jar/shiny-honey-jar-sprites.scm")

(define carnage
  (lambda (x y dest_image)

    (let loop-i ((i 2) (local_bottom 48))
      (if (<= i 6)
	  (let ( (w (/ 44 i)) )
	    (let ( (h (/ (* 90 w) 109) ) )

	      ; create the line on the back before the current line of
	      ; headstones
	      (loop-i (+ i 1) (- local_bottom (/ h 2)))

	      ; add a shadow on the farthest lines of headstones
	      (let ( (shadow (car (gimp-layer-new dest_image 48 48 RGBA-IMAGE
						  "shadow" 25 MULTIPLY-MODE)))
		     (layers_count (length (gimp-image-get-layers dest_image)))
		     )
		(gimp-image-add-layer dest_image shadow layers_count)
		(gimp-layer-set-offsets shadow x y)
		(gimp-context-set-foreground '(0 0 0))
		(gimp-drawable-fill shadow FOREGROUND-FILL)
		)

	      ; then draw the line of headstones
	      (let loop-j ((j 0))
		(if (< j i)
		    (begin
		      (headstone-sprite 0 (+ 2 (+ x (* w j)))
					(+ y (- local_bottom h))
					w h dest_image "../../")
		      (loop-j (+ j 1))
		      ) ; begin
		    ) ; if
		) ; loop-j
	      ) ; let h
	    ) ; let w
	  ) ; if
      ) ; loop-i

    ) ; lambda
  ) ; define carnage

(define bonus-boxes
  (lambda (x y w h dest_image)

    (let ( (boxes_1_name "../../bonus-box-1.png")
	   (boxes_2_name "../../bonus-box-2.png") )
      (let ( (boxes_1_image (car (gimp-file-load 1 boxes_1_name boxes_1_name)))
	     (boxes_2_image (car (gimp-file-load 1 boxes_2_name boxes_2_name)))
             )
	(let ( (angle (/ (* 2 3.14159) 6)) (box_h 15) )
	  (let ( (box_w (/ (* 60 box_h) 80)) )
	    (let ( (ref_x (+ x (/ (- w box_w) 2) )) )

	      (define create-box
		(lambda (src_image loc_x loc_y loc_w loc_h angle_step)
		  (let ( (layer (create-layer-crop src_image '(0)
						   loc_x loc_y loc_w loc_h
						   ref_x y box_w box_h
						   dest_image '()))
			 )
		    (gimp-drawable-transform-rotate-default
		     layer (* angle angle_step) FALSE
		     (+ x (/ w 2)) (+ y (/ h 2)) TRUE
		     TRANSFORM-RESIZE-ADJUST)
		    ) ; let
		  ) ; lambda
		) ; define

	      (create-box boxes_1_image 0 0 60 80 0)
	      (create-box boxes_1_image 0 80 60 80 1)
	      (create-box boxes_1_image 60 80 60 80 2)
	      (create-box boxes_1_image 0 160 60 80 3)
	      (create-box boxes_2_image 120 176 60 80 4)
	      (create-box boxes_2_image 180 176 60 80 5)
	      ) ; let
	    ) ; let
	  ) ; let
	) ; let

      ) ; let
    ) ; lambda
  ) ; define bonus-boxes

(define bonus-energy
  (lambda (x y w h dest_image)

    (let ( (src_name "../../bonus-box-2.png") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )
	(let ( (box_h 30) )
	  (let ( (box_w (/ (* 60 box_h) 80)) )

	    (create-layer-crop src_image '(0)
			       0 176 60 80
			       (+ x (/ (- w box_w) 2)) (+ y (/ (- h box_h) 2))
			       box_w box_h dest_image '())
	    ) ; let
	  ) ; let
	) ; let
      ) ; let

    ) ; lambda
  ) ; define bonus-energy

(define background-sprite
  (lambda (dest_image)

    (let ( (src_name "bonus-icons-background.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (background 0) )
          
          (create-layer src_image 
                        (list background)
                        0 0 48 48 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define background-sprite

(define bonus-time
  (lambda (x y w h dest_image)

    (let ( (src_name "bonus-icons-background.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (background 1) )
          
          (create-layer src_image 
                        (list background)
                        x y w h dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define bonus-time

(define bonus-cooperation
  (lambda (x y w h dest_image)

    (let ( (src_name "bonus-icons-background.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (background 2) )
          
          (create-layer src_image 
                        (list background)
                        x y w h dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define bonus-cooperation

(define bonus-ray
  (lambda (x y w h dest_image)

    (let ( (src_name "bonus-icons-background.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (background 3) )
          
          (create-layer src_image 
                        (list background)
                        x y w h dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define bonus-ray

(define bonus-exits
  (lambda (x y w h dest_image)

    (let ( (src_name "bonus-icons-background.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (background 4) )
          
          (create-layer src_image 
                        (list background)
                        x y w h dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define bonus-exits

(define bonus-hideouts
  (lambda (x y w h dest_image)

    (let ( (src_name "bonus-icons-background.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (background 5) )
          
          (create-layer src_image 
                        (list background)
                        x y w h dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define bonus-hideouts

(define honeypot
  (lambda (index x y w h dest_image)

    (shiny-honey-jar-sprite index x y w h dest_image "../../shiny-honey-jar/")

    (gimp-context-set-foreground '(255 255 255))
    (let ( (number (car (gimp-text-layer-new dest_image
					     (number->string (+ index 1))
					     "Sans Bold" (/ h 4) PIXELS)))
	   (shadow (car (gimp-text-layer-new dest_image
					     (number->string (+ index 1))
					     "Sans Bold" (/ h 4) PIXELS)))
	   )
      (gimp-image-add-layer dest_image shadow -1)
      (gimp-image-add-layer dest_image number -1)

      (gimp-text-layer-set-color shadow '(0 0 0))
      (gimp-text-layer-set-color number '(255 255 255))

      (gimp-text-layer-set-antialias shadow TRUE)
      (gimp-text-layer-set-antialias number TRUE)

      (let ( (number_w (car (gimp-drawable-width number)))
	     (number_h (car (gimp-drawable-height number)))
	     )
	(gimp-layer-set-offsets number (+ x (/ (- w number_w) 2))
				(- (- (+ y h) number_h) 7))
	(gimp-layer-set-offsets shadow (+ (+ x (/ (- w number_w) 2)) 1)
				(- (- (+ y h) number_h) 6))
	) ; let
      ) ; let
    ) ; lambda
  ) ; define honeypot

(let ( (dest_name "bonus-icons.png") )
  (let ( (dest_image (new-image 512 128)) )

    (background-sprite dest_image)
    (owl-with-nut-sprite 0 (+ (* 48 1) 3) 0 39 48 dest_image "../../owl/")
    (owl-tears-sprite    4 (+ (* 48 2) 4) 0 40 48 dest_image "../../owl/")
    (nut-sprite          0 (+ (* 48 3) 6) 6 36 36 dest_image "../../owl/")
    (carnage (* 48 4) -10 dest_image)
    (honeypot 0 (+ (* 48 5) 4) 4 40 40 dest_image)
    (honeypot 1 (+ (* 48 6) 4) 4 40 40 dest_image)
    (honeypot 2 (+ (* 48 7) 4) 4 40 40 dest_image)
    (honeypot 3 (+ (* 48 8) 4) 4 40 40 dest_image)
    (honeypot 4 (+ (* 48 9) 4) 4 40 40 dest_image)
    (bonus-boxes (+ (* 48 0) 1) (+ (* 48 1) 1) 46 46 dest_image)
    (bonus-energy (* 48 1) (* 48 1) 48 48 dest_image)
    
    (bonus-time (* 48 2) (* 48 1) 48 48 dest_image)
    (bonus-cooperation (* 48 3) (* 48 1) 48 48 dest_image)
    (bonus-ray (* 48 4) (* 48 1) 48 48 dest_image)
    (bonus-exits (* 48 5) (* 48 1) 48 48 dest_image)
    (bonus-hideouts (* 48 6) (* 48 1) 48 48 dest_image)

    (save-frames-and-exit dest_name dest_image)

    ) ; let
  ) ; let
