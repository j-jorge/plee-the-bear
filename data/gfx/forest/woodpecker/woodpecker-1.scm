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

(load "woodpecker-sprites.scm")

(define pecking
  (lambda (dest_image)
    ; the ratio of the size is 0.125 (0.125739640 vert., 0.125 hor.)

    (woodpecker-pecking-sprite 0 0 0 43 85 dest_image ".")
    (woodpecker-pecking-sprite 1 43 0 43 85 dest_image ".")
    (woodpecker-pecking-sprite 2 86 0 43 85 dest_image ".")
    (woodpecker-pecking-sprite 3 129 0 43 85 dest_image ".")

    ) ; lambda
  ) ; define pecking

(define watching
  (lambda (dest_image)

    (woodpecker-watching-sprite 0 172 0 40 81 dest_image ".")
    (woodpecker-watching-sprite 1 212 0 37 80 dest_image ".")
    ) ; lambda
  ) ; define watching

(define attacking
  (lambda (dest_image)

    (woodpecker-attacking-sprite 0 0 85 107 37 dest_image ".")
    (woodpecker-attacking-sprite 1 107 85 107 37 dest_image ".")
    (woodpecker-attacking-sprite 2 0 122 107 37 dest_image ".")
    (woodpecker-attacking-sprite 3 107 122 107 37 dest_image ".")
    (woodpecker-attacking-sprite 4 0 159 107 37 dest_image ".")
    (woodpecker-attacking-sprite 5 107 159 107 37 dest_image ".")
    ) ; lambda
  ) ; define attacking

(define wig
  (lambda (dest_image)

    (woodpecker-wig-sprite 0 0 196 26 17 dest_image ".")
    ) ; lambda
  ) ; define wig

(define feather
  (lambda (dest_image)

    (woodpecker-feather-sprite 0 26 196 24 7 dest_image ".")
    (woodpecker-feather-sprite 1 50 196 24 7 dest_image ".")
    (woodpecker-feather-sprite 2 74 196 24 7 dest_image ".")
    ) ; lambda
  ) ; define feather

(define hole
  (lambda (dest_image)

    (woodpecker-hole-sprite 0 98 196 2 4 dest_image ".")
    ) ; lambda
  ) ; define hole

(define flying
  (lambda (dest_image)

    (woodpecker-flying-sprite 0 214 80 96 80 dest_image ".")
    (woodpecker-flying-sprite 1 214 160 96 80 dest_image ".")
    (woodpecker-flying-sprite 2 310 0 96 80 dest_image ".")
    (woodpecker-flying-sprite 3 406 0 96 80 dest_image ".")

          ; and dying too
    (woodpecker-flying-sprite 4 310 80 96 80 dest_image ".")
    (woodpecker-flying-sprite 5 406 80 96 80 dest_image ".")
    (woodpecker-flying-sprite 6 310 160 96 80 dest_image ".")
    (woodpecker-flying-sprite 7 406 160 96 80 dest_image ".")
    ) ; lambda
  ) ; define flying

(let ( (dest_name "woodpecker-1.png") )
  (let ( (dest_image (new-image 512 256)) )

    (pecking dest_image);
    (watching dest_image);
    (feather dest_image);
    (hole dest_image);
    (attacking dest_image);
    (flying dest_image)
    (wig dest_image)

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
