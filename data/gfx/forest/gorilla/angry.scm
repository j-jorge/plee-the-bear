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

(define angry-gorilla
  (lambda (dest_image)

    (let ( (angry_name "angry.xcf.bz2") )
      (let ( (angry_image (car (gimp-file-load 1 angry_name angry_name)))
             )

        ; layer names
        (let ( (right_arm_up     0)
               (right_arm_middle 1)
               (right_arm_down   2)
               (right_leg        3)
               (left_arm_down    4)
               (body             5)
               (left_leg         6)
               (left_arm_middle  7)
               (left_arm_up      8) )

          (create-layer angry_image
                        (list
                         right_arm_up body left_arm_up right_leg left_leg)
                        0 0 98 228 dest_image)
          (create-layer angry_image
                        (list
                         right_arm_up body left_arm_middle right_leg
                         left_leg)
                        98 0 98 228 dest_image)
          (create-layer angry_image
                        (list
                         right_arm_up body left_arm_down right_leg left_leg)
                        196 0 98 228 dest_image)
          (create-layer angry_image
                        (list
                         right_arm_middle body left_arm_up right_leg left_leg)
                        294 0 98 228 dest_image)
          (create-layer angry_image
                        (list
                         right_arm_middle body left_arm_middle right_leg
                         left_leg)
                        392 0 98 228 dest_image)
          (create-layer angry_image
                        (list
                         right_arm_middle body left_arm_down right_leg left_leg)
                        0 228 98 228 dest_image)
          (create-layer angry_image
                        (list
                         right_arm_down body left_arm_up right_leg left_leg)
                        98 228 98 228 dest_image)
          (create-layer angry_image
                        (list
                         right_arm_down body left_arm_middle right_leg left_leg)
                        196 228 98 228 dest_image)
          (create-layer angry_image
                        (list
                         right_arm_down body left_arm_down right_leg left_leg)
                        294 228 98 228 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define angry-gorilla

(let ( (dest_name "angry.png") )
  (let ( (dest_image (new-image 512 512)))

    (angry-gorilla dest_image);

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
