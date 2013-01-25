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

(define ground-blast
  (lambda (dest_image)

    (let ( (src_name "ground-blast.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        (create-layer src_image '(0 1 5) 0 0 256 190 dest_image)
        (create-layer src_image '(0 2 6) 256 0 256 190 dest_image)
        (create-layer src_image '(0 3 7) 0 190 256 190 dest_image)
        (create-layer src_image '(0 4 8) 256 190 256 190 dest_image)
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define ground-blast

(define bubbles
  (lambda (dest_image x y)

    (let ( (src_name "bubbles.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        (create-layer src_image '(1) x y 36 36 dest_image)
        (create-layer src_image '(2) (+ x (* 1 36)) y 36 36 dest_image)
        (create-layer src_image '(3) (+ x (* 2 36)) y 36 36 dest_image)
        (create-layer src_image '(4) (+ x (* 3 36)) y 36 36 dest_image)
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define bubbles

(define clod
  (lambda (dest_image x y)

    (let ( (src_name "clod.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        (create-layer src_image '(1) x y 36 36 dest_image)
        (create-layer src_image '(2) (+ x (* 1 36)) y 36 36 dest_image)
        (create-layer src_image '(3) (+ x (* 2 36)) y 36 36 dest_image)
        (create-layer src_image '(4) (+ x (* 3 36)) y 36 36 dest_image)
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define clod

(let ( (src_name "ground-blast.xcf.bz2")
       (dest_name "ground-blast.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (new-image 512 512)) )

    (ground-blast dest_image)
    (bubbles dest_image 0 380)
    (clod dest_image 0 416)

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
