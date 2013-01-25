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

(load "reverse-ghost-sprites.scm")

(define reverse-appearing
  (lambda (dest_image)
    ; the ratio of the size is 0.3

    (reverse-ghost-appear-sprite 0 0 0 36 43 dest_image ".")
    (reverse-ghost-appear-sprite 1 36 0 36 43 dest_image ".")
    (reverse-ghost-appear-sprite 2 72 0 36 43 dest_image ".")
    (reverse-ghost-appear-sprite 3 108 0 36 43 dest_image ".")
    (reverse-ghost-appear-sprite 4 144 0 36 43 dest_image ".")
    ) ; lambda
  ) ; define reverse-appearing

(define reverse-moving
  (lambda (dest_image)
    ; the ratio of the size is 0.3

    (reverse-ghost-move-sprite 0 180 0 35 46 dest_image ".")
    (reverse-ghost-move-sprite 1 215 0 35 46 dest_image ".")
    (reverse-ghost-move-sprite 2 0 43 35 46 dest_image ".")
    ) ; lambda
  ) ; define reverse-moving

(let ( (dest_name "ghost-1.png") )
  (let ( (dest_image (new-image 256 128)) )

    (reverse-appearing dest_image)
    (reverse-moving dest_image)

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
