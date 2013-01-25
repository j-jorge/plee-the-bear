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

(define soul
  (lambda (dest_image)
    ; the ratio of the size is 0.125

    (let ( (src_name "soul.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (stars_3 0)
               (stars_2 1)
               (stars_1 2)
               (blue_shadows 3)
               (white 4)
               (blue 5)
               (beak 6)
               (eyes 7)
               (right_wing 8)
               (right_leg 9)
               (body 10)
               (left_leg 11)
               (left_wing 12) )

          (create-layer src_image
                        (list blue_shadows white blue beak eyes right_wing
                              right_leg body left_leg left_wing stars_1)
                        0 0 36 68 dest_image)
          (create-layer src_image
                        (list blue_shadows white blue beak eyes right_wing
                              right_leg body left_leg left_wing stars_2)
                        36 0 36 68 dest_image)
          (create-layer src_image
                        (list blue_shadows white blue beak eyes right_wing
                              right_leg body left_leg left_wing stars_3)
                        72 0 36 68 dest_image)

          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define soul

(let ( (dest_name "woodpecker-2.png") )
  (let ( (dest_image (new-image 128 128)) )

    (soul dest_image);
    ;(watching dest_image);

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
