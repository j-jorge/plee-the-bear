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

(define soul-gorilla
  (lambda (dest_image)

    (let ( (soul_name "soul.xcf.bz2") )
      (let ( (soul_image (car (gimp-file-load 1 soul_name soul_name)))
             )

        ; layer names
        (let ( (stars_3 0)
               (stars_2 1)
               (stars_1 2)
               (right_leg 3)
               (body 4)
               (left_leg 5)
               (hand_1 6)
               (hand_2 7)
               (hand_3 8)
               (hand_4 9)
               (hand_5 10) )

          (create-layer soul_image
                        (list hand_1 stars_1 right_leg body left_leg)
                        0 0 91 193 dest_image)
          (create-layer soul_image
                        (list hand_2 stars_2 right_leg body left_leg)
                        91 0 91 193 dest_image)
          (create-layer soul_image
                        (list hand_3 stars_3 right_leg body left_leg)
                        182 0 91 193 dest_image)
          (create-layer soul_image
                        (list hand_4 stars_3 right_leg body left_leg)
                        273 0 91 193 dest_image)
          (create-layer soul_image
                        (list hand_5 stars_2 right_leg body left_leg)
                        364 0 91 193 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define soul-gorilla

(let ( (dest_name "soul.png") )
  (let ( (dest_image (new-image 512 256)))

    (soul-gorilla dest_image);

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
