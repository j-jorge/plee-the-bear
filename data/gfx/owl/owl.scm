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

(load "nut-sprites.scm")
(load "owl-sprites.scm")

(define owl-waiting
  (lambda (dest_image)

    (owl-waiting-sprite 0 0 0 62 85 dest_image ".")
    (owl-waiting-sprite 1 62 0 62 85 dest_image ".")
    (owl-waiting-sprite 2 124 0 62 85 dest_image ".")
    ); lambda
  ); define owl-waiting-anim

(define owl-tears
  (lambda (dest_image)

    (owl-tears-sprite 0 0 85 72 85 dest_image ".")
    (owl-tears-sprite 1 72 85 72 85 dest_image ".")
    (owl-tears-sprite 2 144 85 72 85 dest_image ".")
    (owl-tears-sprite 3 0 170 72 85 dest_image ".")
    (owl-tears-sprite 4 72 170 72 85 dest_image ".")

    ) ; lambda
  ) ; define owl-tears

(let ( (dest_name "owl.png") )
  (let ( (dest_image (new-image 256 256)) )

    (owl-waiting dest_image)
    (owl-with-nut-sprite 0 186 0 70 85 dest_image ".")
    (owl-tears dest_image)
    (nut-sprite 0 216 85 24 24 dest_image ".")

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
