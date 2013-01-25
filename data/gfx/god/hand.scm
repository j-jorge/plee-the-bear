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

; coeff: x=0.497942387 y=0.49851632
(define ball
  (lambda (dest_image)
    (let ( (src_name "ball.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             (frames_count 6)
             )

        (let loop ((i 0))
          (unless (= i frames_count)
                  (create-layer src_image (list i (+ frames_count i))
                                (* i 62) 414 62 63 dest_image)
                  (loop (+ i 1))
                  ) ; unless
          ) ; let loop

        ) ; let
      ) ; let
    ) ; lambda
  ) ; define ball

; coeff: x=0,413625304 y=0,414414414
(define hand-2
  (lambda (dest_image)
    (let ( (src_name "hand.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             (frames_count 18)
             )

        (let loop ((i 0))
          (unless (= i (/ frames_count 2))
                  (create-layer src_image (list i (+ i frames_count))
                                (* (modulo i 3) 170)
                                (* (floor (/ i 3)) 138) 170 138 dest_image)
                  (loop (+ i 1))
                  ) ; unless
          ) ; let loop

        ) ; let
      ) ; let
    ) ; lambda
  ) ; define hand-2

(define hand-1
  (lambda (dest_image)
    (let ( (src_name "hand.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             (frames_count 18)
             )

        (let loop ((i 0))
          (unless (= i (/ frames_count 2))
                  (create-layer
		   src_image
		   (list (+ i (/ frames_count 2))
			 (+ (+ i (/ frames_count 2)) frames_count))
		   (* (modulo i 3) 170)
		   (* (floor (/ i 3)) 138) 170 138 dest_image)
                  (loop (+ i 1))
                  ) ; unless
          ) ; let loop

        ) ; let
      ) ; let
    ) ; lambda
  ) ; define hand-1

(let ( (dest_name_1 "hand-2.png")
       (dest_name_2 "hand-1.png") )
  (let ( (dest_image_1 (new-image 512 512))
	 (dest_image_2 (new-image 512 512)) )

    (hand-2 dest_image_1)
    (hand-1 dest_image_2)
    (ball dest_image_1)

    (save-frames dest_name_1 dest_image_1)
    (save-frames-and-exit dest_name_2 dest_image_2)
    ) ; let
  ) ; let
