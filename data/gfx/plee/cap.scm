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

(define cap
  (lambda (dest_image)

    (let ( (src_name "cap.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (propeller_0 0)
               (propeller_1 1)
               (propeller_2 2)
               (propeller_3 3)
               (propeller_4 4)
               (propeller_5 5)
               (text        6)
               (base        7) )

          (create-layer src_image
                        (list propeller_0 text base)   0  0 34 16 dest_image )
          (create-layer src_image
                        (list propeller_1 text base)  34  0 34 16 dest_image )
          (create-layer src_image
                        (list propeller_2 text base)  68  0 34 16 dest_image )
          (create-layer src_image
                        (list propeller_3 text base)   0 16 34 16 dest_image )
          (create-layer src_image
                        (list propeller_4 text base)  34 16 34 16 dest_image )
          (create-layer src_image
                        (list propeller_5 text base)  68 16 34 16 dest_image )
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define cap

(define bath-cap
  (lambda (dest_image)

    (let ( (src_name "bath-cap.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (base 0) )

          (create-layer src_image (list base)   0  32 34 16 dest_image )
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define cap

(let ( (dest_name "cap.png") )
  (let ( (dest_image (new-image 128 64)) )

    (cap dest_image)
    (bath-cap dest_image)

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
