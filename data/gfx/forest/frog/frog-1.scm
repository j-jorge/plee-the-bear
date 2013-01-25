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

(load "frog-sprites.scm")

(define idle
  (lambda (dest_image)

    (frog-idle-sprite 0 0 0 24 16 dest_image ".")
    (frog-idle-sprite 1 24 0 24 16 dest_image ".")
    (frog-idle-sprite 2 48 0 24 16 dest_image ".")

    ) ; lambda
  ) ; define idle

(define spatter
  (lambda (dest_image)

    (frog-spatter-sprite 0  0 16 64 16 dest_image ".")
    (frog-spatter-sprite 1 64 16 64 16 dest_image ".")
    (frog-spatter-sprite 2  0 32 64 16 dest_image ".")
    (frog-spatter-sprite 3 64 32 64 16 dest_image ".")
    (frog-spatter-sprite 4  0 48 64 16 dest_image ".")
    (frog-spatter-sprite 5 64 48 64 16 dest_image ".")
    (frog-spatter-sprite 6  0 64 64 16 dest_image ".")
    (frog-spatter-sprite 7 64 64 64 16 dest_image ".")
    (frog-spatter-sprite 8  0 80 64 16 dest_image ".")
    (frog-spatter-sprite 9 64 80 64 16 dest_image ".")
    (frog-spatter-sprite 10  0 96 64 16 dest_image ".")
    (frog-spatter-sprite 11 64 96 64 16 dest_image ".")
    (frog-spatter-sprite 12  0 112 64 16 dest_image ".")
    (frog-spatter-sprite 13 64 112 64 16 dest_image ".")

    ) ; lambda
  ) ; define spatter

(let ( (dest_name "frog-1.png") )
  (let ( (dest_image (new-image 128 128)) )

    (idle dest_image);
    (spatter dest_image);

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
