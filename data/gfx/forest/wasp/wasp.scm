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

(load "wasp-sprites.scm")

(define flying-wasp
  (lambda (dest_image)

    (wasp-flying-sprite 0 0 0 92 63 dest_image ".")
    (wasp-flying-sprite 1 92 0 92 63 dest_image ".")
    (wasp-flying-sprite 2 184 0 92 63 dest_image ".")
    (wasp-flying-sprite 3 276 0 92 63 dest_image ".")
    ) ; lambda
  ) ; define flying-wasp

(define dying-wasp
  (lambda (dest_image)

    (wasp-dying-sprite 0 0 63 89 91 dest_image ".")
    (wasp-dying-sprite 1 89 63 89 91 dest_image ".")
    (wasp-dying-sprite 2 178 63 89 91 dest_image ".")
    (wasp-dying-sprite 3 267 63 89 91 dest_image ".")
    ) ; lambda
  ) ; define dying-wasp

(define wasp-soul
  (lambda (dest_image)

    (wasp-soul-sprite 0 0 153 95 90 dest_image ".")
    (wasp-soul-sprite 1 95 153 95 90 dest_image ".")
    (wasp-soul-sprite 2 190 153 95 90 dest_image ".")
    (wasp-soul-sprite 3 285 153 95 90 dest_image ".")
    ) ; lambda
  ) ; define wasp-soul

(let ( (dest_name "wasp.png") )
  (let ( (dest_image (new-image 512 256)))

    (flying-wasp dest_image);
    (dying-wasp dest_image);
    (wasp-soul dest_image);

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
