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

(load "../frog/frog-sprites.scm")
(load "../gorilla/gorilla-sprites.scm")
(load "../rabbit/rabbit-sprites.scm")
(load "../wasp/wasp-sprites.scm")
(load "../woodpecker/woodpecker-sprites.scm")

(load "../../headstone-sprites.scm")

(define headstones
  (lambda (x y count dest_image)

    (let ( (w 22) )
      (let ( (h (/ (* 90 w) 109) ) )

	(let loop ((i 0))
	  (unless (= i count)
		  (begin
		    (headstone-sprite 0 (+ x (* 48 i)) (+ y (- 48 h)) w h
				      dest_image "../../")
		    (loop (+ i 1))
		    ) ; begin
		  ) ; unless
	  ) ; let
	) ; let
      ) ; let
    ) ; lambda
  ) ; define headstones

(define mini-games
  (lambda (x y w h dest_image)

    (let ( (src_name "mini-games.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (waterfall 0)
               (sequencer 1) )

          (create-layer src_image (list waterfall)
                        x y w h dest_image)
          (create-layer src_image (list sequencer)
                        (+ x w) y w h dest_image)

          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define mini-games

(define boss
  (lambda (x y w h dest_image)

    (let ( (src_name "boss.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        (create-layer src_image '(0) x y w h dest_image)
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define boss

(let ( (dest_name "bonus-icons.png") 
       (dest_image (new-image 256 128))
       (icon_size 48)
       )

  (frog-spatter-sprite 0 (/ (- icon_size 96) 2) (/ (- icon_size 24) 2 )
		       96 24 dest_image
		       "../frog/")

  (let ((w (- icon_size 2)))
    (let ((h (/ (* 638 w) 770)))
      (woodpecker-flying-sprite 2 (+ icon_size (/ (- icon_size w) 2))
				(+ 0 (/ (- icon_size h) 2))
				w h dest_image "../woodpecker/")
      ) ; let
    ) ; let

  (let ((w (- icon_size 2)))
    (let ((h (/ (* 607 w) 665)))
      (gorilla-idle-sprite 0 (+ (* icon_size 2) (/ (- icon_size w) 2))
			   (+ 0 (/ (- icon_size h) 2))
			   w h dest_image "../gorilla/")
      ) ; let
    ) ; let
  
  (let ((w (- icon_size 2)))
    (let ((h (/ (* 125 w) 184)))
      (wasp-flying-sprite 0 (+ (* icon_size 3) (/ (- icon_size w) 2))
			  (+ 0 (/ (- icon_size h) 2))
			  w h dest_image "../wasp/")
      ) ; let
    ) ; let

  (let ((h (- icon_size 2)))
    (let ((w (/ (* 104 h) 128)))
      (rabbit-idle-sprite 0 (+ (* icon_size 4) (/ (- icon_size w) 2))
			  (+ 0 (/ (- icon_size h) 2))
			  w h dest_image "../rabbit/")
      ) ; let
    ) ; let

  (headstones 1 -1 5 dest_image)

  (mini-games 0 48 48 48 dest_image)
  (boss 96 48 48 48 dest_image)
  (headstones 97 47 1 dest_image)

  (save-frames-and-exit dest_name dest_image)

  ) ; let
