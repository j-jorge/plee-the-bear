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

(define walking-gorilla
  (lambda (dest_image)

    (let ( (walking_name "walking.xcf.bz2") )
      (let ( (walking_image (car (gimp-file-load 1 walking_name walking_name)))
             )

        ; layer names
        (let ( (right_leg_3  0)
               (right_leg_2  1)
               (right_leg_1  2)
               (right_arm_5  3)
               (right_arm_4  4)
               (right_arm_3  5)
               (right_arm_2  6)
               (right_arm_1  7)
               (body_3       8)
               (body_2       9)
               (body_1      10)
               (left_leg_3  11)
               (left_leg_2  12)
               (left_leg_1  13)
               (left_arm_5  14)
               (left_arm_4  15)
               (left_arm_3  16)
               (left_arm_2  17)
               (left_arm_1  18) )

          (create-layer walking_image
                        (list
                         right_leg_1 right_arm_1 body_1 left_leg_1 left_arm_1)
                        0 0 102 116 dest_image)
          (create-layer walking_image
                        (list
                         right_leg_1 right_arm_2 body_1 left_leg_1 left_arm_2)
                        102 0 102 116 dest_image)
          (create-layer walking_image
                        (list
                         right_leg_2 right_arm_3 body_2 left_leg_2 left_arm_3)
                        204 0 102 116 dest_image)
          (create-layer walking_image
                        (list
                         right_leg_3 right_arm_4 body_3 left_leg_3 left_arm_4)
                        306 0 102 116 dest_image)
          (create-layer walking_image
                        (list
                         right_leg_2 right_arm_5 body_2 left_leg_3 left_arm_5)
                        408 0 102 116 dest_image)

          (create-layer walking_image
                        (list
                         right_leg_1 right_arm_1 body_1 left_leg_3 left_arm_5)
                        0 120 102 116 dest_image)
          (create-layer walking_image
                        (list
                         right_leg_1 right_arm_2 body_1 left_leg_3 left_arm_4)
                        102 120 102 116 dest_image)
          (create-layer walking_image
                        (list
                         right_leg_2 right_arm_3 body_2 left_leg_2 left_arm_3)
                        204 118 102 116 dest_image)
          (create-layer walking_image
                        (list
                         right_leg_3 right_arm_4 body_3 left_leg_1 left_arm_2)
                        306 116 102 116 dest_image)
          (create-layer walking_image
                        (list
                         right_leg_3 right_arm_5 body_3 left_leg_1 left_arm_1)
                        408 116 102 116 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define walking-gorilla

(let ( (dest_name "walking.png") )
  (let ( (dest_image (new-image 512 256)))

    (walking-gorilla dest_image);

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
