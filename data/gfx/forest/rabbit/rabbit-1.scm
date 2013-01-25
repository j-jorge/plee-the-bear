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

(load "rabbit-sprites.scm")

(define idling
  (lambda (dest_image)
    ; the ratio of the size is 0.25

    (rabbit-idle-sprite 0 0 0 26 32 dest_image ".")
    ) ; lambda
  ) ; define idling

(define walking
  (lambda (dest_image)
    ; the ratio of the size is 0.25

    (rabbit-walk-sprite 0 26 0 46 22 dest_image ".")
    (rabbit-walk-sprite 1 72 0 46 22 dest_image ".")
    (rabbit-walk-sprite 2 118 0 46 22 dest_image ".")
    ) ; lambda
  ) ; define walking

(define digging
  (lambda (dest_image)
    ; the ratio of the size is 0.25

    (rabbit-dig-sprite 0 164 0 29 28 dest_image ".")
    (rabbit-dig-sprite 1 193 0 29 28 dest_image ".")
    (rabbit-dig-sprite 2 222 0 29 28 dest_image ".")
    (rabbit-dig-sprite 3 0 32 29 28 dest_image ".")
    (rabbit-dig-sprite 4 29 32 29 28 dest_image ".")
    (rabbit-dig-sprite 5 58 32 29 28 dest_image ".")
    ) ; lambda
  ) ; define digging

(define dust
  (lambda (dest_image)
    ; the ratio of the size is 0.25

    (rabbit-dust-sprite 0 87 22 32 16 dest_image ".")
    (rabbit-dust-sprite 1 119 22 32 16 dest_image ".")
    (rabbit-dust-sprite 2 87 38 32 16 dest_image ".")
    (rabbit-dust-sprite 3 119 38 32 16 dest_image ".")
    ) ; lambda
  ) ; define dust

(define dust-end
  (lambda (dest_image)
    ; the ratio of the size is 0.25

    (rabbit-dust-end-sprite 0 151 32 19 15 dest_image ".")
    (rabbit-dust-end-sprite 1 170 32 19 15 dest_image ".")
    (rabbit-dust-end-sprite 2 151 48 19 15 dest_image ".")
    (rabbit-dust-end-sprite 3 170 48 19 15 dest_image ".")
    ) ; lambda
  ) ; define dust-end

(define jumping
  (lambda (dest_image)
    ; the ratio of the size is 0.25

    (rabbit-jump-sprite 0 189 32 40 40 dest_image ".")
    (rabbit-jump-sprite 1 0 61 40 40 dest_image ".")
    (rabbit-jump-sprite 2 40 61 40 40 dest_image ".")
    (rabbit-jump-sprite 3 80 61 40 40 dest_image ".")
    ) ; lambda
  ) ; define jumping

(define falling
  (lambda (dest_image)
    ; the ratio of the size is 0.25

    (rabbit-fall-sprite 0 120 61 23 35 dest_image ".")
    ) ; lambda
  ) ; define falling

(define injured
  (lambda (dest_image)
    ; the ratio of the size is 0.25

    (rabbit-injured-sprite 0 143 61 21 35 dest_image ".")
    ) ; lambda
  ) ; define injured

(let ( (dest_name "rabbit-1.png") )
  (let ( (dest_image (new-image 256 128)))

    (idling dest_image)
    (walking dest_image)
    (digging dest_image)
    (dust dest_image)
    (dust-end dest_image)
    (jumping dest_image)
    (falling dest_image)
    (injured dest_image)

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
