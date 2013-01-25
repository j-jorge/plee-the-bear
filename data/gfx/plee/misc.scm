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

(define soul-effect
  (lambda (dest_image)

    (let ( (src_name "soul-effect.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (rays_m 0)
               (rays   1)
               (colors 2)
               (body   3) )

          (create-layer src_image
                        (list rays_m rays colors body)
                        0 0 175 186 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define soul-effect

(define stars
  (lambda (dest_image)

    (let ( (src_name "stars.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        (create-layer src_image '(0) 175 0 48 13 dest_image)
        (create-layer src_image '(1) 175 13 48 13 dest_image)
        (create-layer src_image '(2) 175 26 48 13 dest_image)
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define stars

(let ( (dest_name "misc.png") )
  (let ( (dest_image (new-image 256 256)) )

    (soul-effect dest_image)
    (stars dest_image)

    (save-frames-and-exit dest_name dest_image);
    ) ; let
  ) ; let
