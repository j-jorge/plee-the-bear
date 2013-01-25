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

; the ratio of the size is 0.38
(define floating-plee
  (lambda (dest_image)

    (let ( (src_name "plee-floating.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (right_leg_3      0)
               (right_leg_2      1)
               (right_leg_1      2)
               (right_arm_4      3)
               (right_arm_3      4)
               (right_arm_2      5)
               (right_arm_1      6)
               (body_4           7)
               (body_3           8)
               (body_2           9)
               (body_1          10)
               (left_arm_1      11)
               (left_leg_3      12)
               (left_leg_2      13)
               (left_leg_1      14) )

          (create-layer src_image
                        (list right_leg_1 right_arm_1 body_1)
                        0 0 92 125 dest_image)
          (create-layer src_image
                        (list right_leg_2 right_arm_2 body_1 left_leg_1)
                        92 0 92 125 dest_image)
          (create-layer src_image
                        (list right_leg_3 right_arm_3 body_2 left_arm_1
                              left_leg_2)
                        184 0 92 125 dest_image)
          (create-layer src_image
                        (list right_leg_2 right_arm_4 body_1 left_leg_1)
                        276 0 92 125 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define floating-plee

(define floating-idle-plee
  (lambda (dest_image)

    (let ( (src_name "plee-floating.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (right_leg_3      0)
               (right_leg_2      1)
               (right_leg_1      2)
               (right_arm_4      3)
               (right_arm_3      4)
               (right_arm_2      5)
               (right_arm_1      6)
               (body_4           7)
               (body_3           8)
               (body_2           9)
               (body_1          10)
               (left_arm_1      11)
               (left_leg_3      12)
               (left_leg_2      13)
               (left_leg_1      14) )

          (create-layer src_image
                        (list right_leg_2 right_arm_2 body_1 left_leg_2)
                        368 0 92 125 dest_image)
          (create-layer src_image
                        (list right_leg_3 right_arm_4 body_4 left_leg_2)
                        429 0 92 125 dest_image)
          (create-layer src_image
                        (list right_leg_3 right_arm_1 body_3 left_leg_1)
                        0 125 92 125 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define floating-idle-plee

(define changing-hat-plee
  (lambda (dest_image)

    (let ( (src_name "plee-changing-hat.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (right_arm_1           0)
               (right_arm_2           1)
               (right_arm_3           2)
               (right_arm_4           3)
               (right_arm_5           4)
               (right_arm_6           5)
               (right_arm_7           6)
               (floating_right_arm_7  7)
               (eye_3                 8)
               (eye_4                 9)
               (eye_5                10)
               (eye_7                11)
               (right_leg            12)
               (body                 13)
               (left_leg             14)
               (left_arm_3           15)
               (left_arm_4           16)
               (left_arm_5           17) )

          (create-layer src_image
                        (list right_arm_1 right_leg body left_leg)
                        92 125 68 120 dest_image)
          (create-layer src_image
                        (list right_arm_2 right_leg body left_leg)
                        160 125 68 120 dest_image)
          (create-layer src_image
                        (list
                         right_arm_3 eye_3 right_leg body left_leg left_arm_3)
                        228 125 68 120 dest_image)
          (create-layer src_image
                        (list
                         right_arm_4 eye_4 right_leg body left_leg left_arm_4)
                        296 125 68 120 dest_image)
          (create-layer src_image
                        (list
                         right_arm_5 eye_5 right_leg body left_leg left_arm_5)
                        364 125 68 120 dest_image)
          (create-layer src_image
                        (list right_arm_6 eye_5 right_leg body left_leg)
                        432 125 68 120 dest_image)

          ; right arm, alone
          (create-layer src_image (list floating_right_arm_7)
                        470 0 68 120 dest_image)

          ; then the last frame, on which we will draw the arm
          (create-layer src_image
                        (list right_arm_7 eye_7 right_leg body left_leg)
                        0 250 68 120 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define changing-hat-plee

(define drowning-plee
  (lambda (dest_image)

    (let ( (src_name "plee-drowning.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (right_leg_3      0)
               (right_leg_2      1)
               (right_leg_1      2)
               (right_arm_3      3)
               (right_arm_2      4)
               (right_arm_1      5)
               (body_3           6)
               (body_2           7)
               (body_1           8)
               (left_leg_3       9)
               (left_leg_2      10)
               (left_leg_1      11) )

          (create-layer src_image
                        (list right_leg_1 right_arm_1 body_1 left_leg_1)
                        68 245 78 129 dest_image)
          (create-layer src_image
                        (list right_leg_2 right_arm_2 body_2 left_leg_2)
                        146 245 78 129 dest_image)
          (create-layer src_image
                        (list right_leg_3 right_arm_3 body_3 left_leg_3)
                        224 245 78 129 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define drowning-plee

(let ( (dest_name "plee-4.png") )
  (let ( (dest_image (new-image 512 512)) )

    (floating-plee dest_image)
    (floating-idle-plee dest_image)
    (changing-hat-plee dest_image)
    (drowning-plee dest_image)

    (save-frames-and-exit dest_name dest_image);
    ) ; let
  ) ; let
