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
(define throwing-plee
  (lambda (dest_image)

    (let ( (src_name "plee-throwing.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (arm_4            0)
               (arm_3            1)
               (arm_2            2)
               (arm_1            3)
               (arm_0            4)
               (object_1         5)
               (object_0         6)
               (right_leg_front  7)
               (right_leg        8)
               (right_leg_back   9)
               (body_2          10)
               (body_1          11)
               (body_0          12)
               (left_leg_front  13)
               (left_leg        14)
               (left_leg_back   15)
               (left_arm        16) )

          ; throwing without moving
          (create-layer src_image
                        (list object_0 arm_0 right_leg body_0 )
                        0 0 87 112 dest_image)
          (create-layer src_image
                        (list object_1 arm_1 right_leg body_1 )
                        87 0 87 112 dest_image)
          (create-layer src_image
                        (list arm_2 right_leg body_1 )
                        174 0 87 112 dest_image)
          (create-layer src_image
                        (list arm_3 right_leg body_2 left_arm )
                        261 0 87 112 dest_image)
          (create-layer src_image
                        (list arm_4 right_leg body_2 left_arm )
                        348 0 87 112 dest_image)
          ; then repeat frame number 3

          ; throwing while walking
          ; the first frame is the same as above
          ; then we walk while maintaining the object
          (create-layer src_image
                        (list object_1 arm_1 body_1
                              right_leg_front left_leg )
                        0 112 87 112 dest_image)
          (create-layer src_image
                        (list object_1 arm_1 body_1
                              right_leg_front left_leg_back )
                        87 112 87 112 dest_image)
          (create-layer src_image
                        (list object_1 arm_1 body_1
                              right_leg left_leg_back )
                        174 112 87 112 dest_image)
          ; insert the second frame of the first animation here
          (create-layer src_image
                        (list object_1 arm_1 body_1
                              right_leg left_leg_front )
                        261 112 87 112 dest_image)
          (create-layer src_image
                        (list object_1 arm_1 body_1
                              right_leg_back left_leg_front )
                        348 112 87 112 dest_image)
          (create-layer src_image
                        (list object_1 arm_1 body_1
                              right_leg_back left_leg )
                        0 224 87 112 dest_image)

          ; finally, we walk and throw the object
          ; insert the third frame of the first animation here
          (create-layer src_image
                        (list arm_3 body_2 left_arm
                              right_leg_front left_leg )
                        87 224 87 112 dest_image)
          (create-layer src_image
                        (list arm_4 body_2 left_arm
                              right_leg_front left_leg_back)
                        174 224 87 112 dest_image)
          (create-layer src_image
                        (list arm_2 body_1
                              right_leg left_leg_back)
                        261 224 87 112 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define throwing-plee

(define jumping-plee
  (lambda (dest_image)

    (let ( (src_name "plee-jumping.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (right_arm_2 0)
               (right_arm_1 1)
               (right_arm_0 2)
               (right_leg_1 3)
               (right_leg_0 4)
               (body_2      5)
               (body_1      6)
               (body_0      7)
               (left_arm_2  8)
               (left_arm_1  9)
               (left_arm_0 10)
               (left_leg_2 11)
               (left_leg_1 12)
               (left_leg_0 13) )

          (create-layer src_image
                        (list right_arm_0 right_leg_0 body_0 left_arm_0
                              left_leg_0)
                        435 15 66 130 dest_image )
          (create-layer src_image
                        (list right_arm_1 right_leg_1 body_1 left_arm_1
                              left_leg_1)
                        435 130 66 130 dest_image )
          (create-layer src_image
                        (list right_arm_2 right_leg_1 body_2 left_arm_2
                              left_leg_2)
                        435 260 66 130 dest_image )
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define jumping-plee

(define running-plee
  (lambda (dest_image)

    (let ( (src_name "plee-running.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (right_arm_2      0)
               (right_arm_1      1)
               (right_arm_0      2)
               (right_leg_front  3)
               (right_leg_up     4)
               (right_leg        5)
               (right_leg_back   6)
               (body_2           7)
               (body_1           8)
               (body_0           9)
               (left_leg_front  10)
               (left_leg_up     11)
               (left_leg        12)
               (left_leg_back   13)
               (left_arm_2      14)
               (left_arm_1      15)
               (left_arm_0      16) )

          (create-layer src_image
                        (list right_arm_0 right_leg_up body_0 left_leg
                              left_arm_0)
                        348 224 72 107 dest_image )
          (create-layer src_image
                        (list right_arm_1 right_leg_front body_1 left_leg_back
                              left_arm_1)
                        0 336 72 107 dest_image )
          (create-layer src_image
                        (list right_arm_2 right_leg body_2 left_leg_up
                              left_arm_2)
                        72 336 72 107 dest_image )
          (create-layer src_image
                        (list right_arm_1 right_leg_back body_1 left_leg_front
                              left_arm_1)
                        144 336 72 107 dest_image )
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define running-plee

(define injured-plee
  (lambda (dest_image)

    (let ( (src_name "plee-injured.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (right_arm 0)
               (right_leg 1)
               (body      2)
               (head      3)
               (left_arm  4)
               (left_leg  5) )

          (create-layer src_image
                        (list right_arm right_leg head body left_arm left_leg)
                        216 336 68 101 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define injured-plee

(define dream
  (lambda (dest_image)

    (let ( (src_name "dream.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (run_3 0)
               (run_2 1)
               (run_1 2)
               (run_0 3)
               (balloon_2 4)
               (balloon_1 5)
               (balloon_0 6) )

          (create-layer src_image
                        (list balloon_0 )
                        0 456 83 52 dest_image)
          (create-layer src_image
                        (list balloon_0 balloon_1 )
                        83 456 83 52 dest_image)
          (create-layer src_image
                        (list balloon_0 balloon_1 balloon_2 run_0)
                        166 456 83 52 dest_image)
          (create-layer src_image
                        (list balloon_0 balloon_1 balloon_2 run_1)
                        249 456 83 52 dest_image)
          (create-layer src_image
                        (list balloon_0 balloon_1 balloon_2 run_2)
                        332 456 83 52 dest_image)
          (create-layer src_image
                        (list balloon_0 balloon_1 balloon_2 run_3)
                        415 456 83 52 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define dream

(let ( (dest_name "plee-2.png") )
  (let ( (dest_image (new-image 512 512)) )

    (throwing-plee dest_image);
    (jumping-plee dest_image);
    (running-plee dest_image);
    (injured-plee dest_image);
    (dream dest_image)

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
