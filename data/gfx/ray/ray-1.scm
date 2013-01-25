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

(define idle-ray
  (lambda (dest_image)
    ; the ratio of the size is 0.38

    (let ( (src_name "ray-idle.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (head       0)
               (arm        1)
               (arm_shadow 2)
               (pant       3)
               (body       4)
               (feet       5) )

          (create-layer src_image
                        (list head arm arm_shadow pant body feet)
                        0 0 28 87 dest_image)
          ); let
        ); let
      ); let
    ); lambda
  ); define idle-ray

(define walking-ray
  (lambda (dest_image)
    ; the ratio of the size is 0.38

    (let ( (src_name "ray-walking.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (right_arm_toward        0)
               (right_arm_bit_toward    1)
               (right_arm_bit_backward  2)
               (right_arm_backward      3)
               (head                    4)
               (body                    5)
               (right_leg               6)
               (right_leg_backward      7)
               (right_leg_up            8)
               (right_leg_toward        9)
               (left_leg               10)
               (left_leg_backward      11)
               (left_leg_up            12)
               (left_leg_toward        13)
               (left_arm_bit_backward  14)
               (left_arm_backward      15) )

          (create-layer src_image
                        (list head body right_arm_backward
                              right_leg_toward left_leg)
                        28 0 55 87 dest_image)
          (create-layer src_image
                        (list head body right_arm_bit_backward
                              right_leg_toward left_leg_backward)
                        83 0 55 87 dest_image)
          (create-layer src_image
                        (list head body right_arm_bit_toward
                              right_leg left_leg_backward left_arm_bit_backward)
                        138 0 55 87 dest_image)
          (create-layer src_image
                        (list head body right_arm_toward
                              right_leg left_leg_up left_arm_backward)
                        193 0 55 87 dest_image)
          (create-layer src_image
                        (list head body right_arm_toward
                              right_leg left_leg_toward left_arm_bit_backward)
                        248 0 55 87 dest_image)
          (create-layer src_image
                        (list head body right_arm_bit_toward
                              right_leg_backward left_leg_toward)
                        303 0 55 87 dest_image)
          (create-layer src_image
                        (list head body right_arm_bit_backward
                              right_leg_backward left_leg)
                        358 0 55 87 dest_image)
          (create-layer src_image
                        (list head body right_arm_backward
                              right_leg_up left_leg)
                        413 0 55 87 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define walking-ray

(define looking-upward-ray
  (lambda (dest_image)
    ; the ratio of the size is 0.38

    (let ( (src_name "ray-look-up.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (arm        0)
               (arm_shadow 1)
               (head       2)
               (pant       3)
               (body       4)
               (feet       5) )

          (create-layer src_image
                        (list head arm arm_shadow pant body feet)
                        468 0 27 91 dest_image)
          ); let
        ); let
      ); let
    ); lambda
  ); define looking-upward-ray

(define walking-crying-ray
  (lambda (dest_image)
    ; the ratio of the size is 0.38

    (let ( (src_name "ray-crying.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (right_arm_backward  0)
               (tears_1             1)
               (tears_2             2)
               (tears_3             3)
               (tears_4             4)
               (head                5)
               (body                6)
               (right_leg           7)
               (right_leg_backward  8)
               (left_leg            9)
               (left_leg_backward  10) )

          ; walking
          (create-layer src_image
                        (list right_arm_backward head body tears_1
                              right_leg left_leg)
                        0 87 41 90 dest_image)
          (create-layer src_image
                        (list right_arm_backward head body tears_2
                              right_leg left_leg_backward)
                        41 87 41 90 dest_image)
          (create-layer src_image
                        (list right_arm_backward head body tears_3
                              right_leg left_leg)
                        82 87 41 90 dest_image)
          (create-layer src_image
                        (list right_arm_backward head body tears_4
                              right_leg_backward left_leg)
                        123 87 41 90 dest_image)

          ; idle
          (create-layer-crop src_image
                             (list right_arm_backward head body tears_1
                                   right_leg left_leg)
                             37 0 71 236
                             164 87 27 90 dest_image '())
          (create-layer-crop src_image
                             (list right_arm_backward head body tears_2
                                   right_leg left_leg)
                             37 0 71 236
                             191 87 27 90 dest_image '())
          (create-layer-crop src_image
                             (list right_arm_backward head body tears_3
                                   right_leg left_leg)
                             37 0 71 236
                             218 87 27 90 dest_image '())
          (create-layer-crop src_image
                             (list right_arm_backward head body tears_4
                                   right_leg left_leg)
                             37 0 71 236
                             245 87 27 90 dest_image '())
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define walking-crying-ray

(define jumping-ray
  (lambda (dest_image)
    ; the ratio of the size is 0.38

    (let ( (src_name "ray-jumping.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (right_arm_up           0)
               (head_up                1)
               (right_leg_up           2)
               (left_leg_up            3)
               (body_up                4)
               (left_arm_up            5)

               (right_arm_push         6)
               (right_arm_push_shadow  7)
               (head_push              8)
               (right_leg_push         9)
               (body_push             10)
               (left_leg_push         11)
               (left_arm_push         12)

               (right_arm_init        13)
               (right_arm_init_shadow 14)
               (head_init             15)
               (right_leg_init        16)
               (left_leg_init         17)
               (body_init             18) )
               
          (create-layer src_image
                        (list right_arm_init right_arm_init_shadow head_init
                              right_leg_init left_leg_init body_init)
                        272 87 39 95 dest_image)
          (create-layer src_image
                        (list right_arm_push right_arm_push_shadow head_push
                              right_leg_push body_push left_leg_push
                              left_arm_push)
                        311 87 39 95 dest_image)
          (create-layer src_image
                        (list right_arm_up head_up right_leg_up left_leg_up
                              body_up left_arm_up)
                        350 87 39 95 dest_image)
          ); let
        ); let
      ); let
    ); lambda
  ); define jumping-ray

(define falling-ray
  (lambda (dest_image)
    ; the ratio of the size is 0.38

    (let ( (src_name "ray-falling.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (right_arm_back         0)
               (right_arm_back_shadow  1)
               (right_arm              2)
               (right_arm_shadow       3)
               (right_arm_front        4)
               (right_arm_front_shadow 5)
               (head_back              6)
               (head                   7)
               (head_front             8)
               (right_leg_back         9)
               (right_leg             10)
               (right_leg_front       11)
               (left_leg_back         12)
               (left_leg              13)
               (left_leg_front        14)
               (body_back             15)
               (body                  16)
               (body_front            17)
               (left_arm_back         18)
               (left_arm              19)
               (left_arm_front        20) )
               
          (create-layer src_image
                        (list right_arm_back right_arm_back_shadow head_back
                              right_leg_back left_leg_back
                              body_back left_arm_back)
                        389 87 40 86 dest_image)
          (create-layer src_image
                        (list right_arm right_arm_shadow head
                              right_leg left_leg
                              body left_arm)
                        429 91 40 86 dest_image)
          (create-layer src_image
                        (list right_arm_front right_arm_front_shadow head_front
                              right_leg_front left_leg_front
                              body_front left_arm_front)
                        469 91 40 86 dest_image)
          ); let
        ); let
      ); let
    ); lambda
  ); define falling-ray

(define injured-ray
  (lambda (dest_image)
    ; the ratio of the size is 0.38

    (let ( (src_name "ray-injured.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (head 0)
               (body 1) )
               
          (create-layer src_image
                        (list body head)
                        0 177 43 81 dest_image)
          ); let
        ); let
      ); let
    ); lambda
  ); define injured-ray

(let ( (dest_name "ray-1.png") )
  (let ( (dest_image (new-image 512 512)) )

    (idle-ray dest_image)
    (walking-ray dest_image)
    (looking-upward-ray dest_image)
    (walking-crying-ray dest_image)
    (jumping-ray dest_image)
    (falling-ray dest_image)
    (injured-ray dest_image)

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
