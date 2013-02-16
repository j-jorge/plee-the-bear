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

(define walking-plee
  (lambda (dest_image)
    ; the ratio of the size is 0.37 (0.379661017 vert., 0.376470588 hor.)

    (let ( (src_name "plee-walking.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (right_arm_0          0)
               (right_arm_1          1)
               (right_arm_2          2)
               (right_leg_front      3)
               (right_leg            4)
               (right_leg_back       5)
               (body                 6)
               (left_arm             7)
               (left_leg_front_down  8)
               (left_leg_front       9)
               (left_leg            10)
               (left_leg_back       11) )

          (create-layer-crop src_image
                             (list right_arm_1)
                             32 73 52 147
                             492 457 19 54 dest_image '())

          (create-layer src_image
                        (list right_leg body)
                        0 0 64 112 dest_image)
          (create-layer src_image
                        (list right_leg_front body left_leg)
                        64 0 64 112 dest_image)
          (create-layer src_image
                        (list right_leg_front body left_leg_back)
                        128 0 64 112 dest_image)
          (create-layer src_image
                        (list right_leg body left_leg_back)
                        192 0 64 112 dest_image)
          ; insert the first frame here
          (create-layer src_image
                        (list right_leg body left_leg_front)
                        256 0 64 112 dest_image)
          (create-layer src_image
                        (list right_leg_back body left_leg_front)
                        320 0 64 112 dest_image)
          (create-layer src_image
                        (list right_leg_back body left_leg)
                        384 0 64 112 dest_image)

          ; this is the frame for the 'waiting' animation
          (create-layer src_image
                        (list right_arm_1 right_leg body left_leg_front_down)
                        448 0 64 112 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define walking-plee

(define slapping-plee
  (lambda (dest_image)

    (let ( (src_name "plee-slapping.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (claws_3          0)
               (claws_2          1)
               (claws_1          2)
               (claws_0          3)
               (arm_5            4)
               (arm_4            5)
               (arm_3            6)
               (arm_2            7)
               (arm_1            8)
               (arm_0            9)
               (right_leg_front 10)
               (right_leg       11)
               (right_leg_back  12)
               (body_2          13)
               (body_1          14)
               (body_0          15)
               (left_leg_front  16)
               (left_leg        17)
               (left_leg_back   18) )

          ; slapping without moving
          (create-layer-crop src_image
                        (list arm_0 right_leg body_0 )
                        10 0 225 295
                        5 112 84 112 dest_image '())
          (create-layer-crop src_image
                        (list claws_0 arm_1 right_leg body_0 )
                        10 0 225 295
                        89 112 84 112 dest_image '())
          (create-layer-crop src_image
                        (list claws_1 arm_2 right_leg body_1 )
                        10 0 225 295
                        173 112 84 112 dest_image '())
          (create-layer-crop src_image
                        (list claws_2 arm_3 right_leg body_2 )
                        10 0 225 295
                        257 112 84 112 dest_image '())
          (create-layer-crop src_image
                        (list claws_3 arm_4 right_leg body_2 )
                        10 0 225 295
                        341 112 84 112 dest_image '())
          (create-layer-crop src_image
                        (list arm_5 right_leg body_1 )
                        10 0 225 295
                        425 112 84 112 dest_image '())

          ; slapping while walking
          ; the first frame is the same as above
          (create-layer src_image
                        (list claws_0 arm_1 right_leg_front body_0 left_leg )
                        0 224 89 112 dest_image)
          (create-layer src_image
                        (list
                         claws_1 arm_2 right_leg_front body_1 left_leg_back)
                        89 224 89 112 dest_image)
          (create-layer src_image
                        (list claws_2 arm_3 right_leg body_2 left_leg_back )
                        178 224 89 112 dest_image)
          (create-layer src_image
                        (list claws_3 arm_4 right_leg body_2 )
                        267 224 89 112 dest_image)
          (create-layer src_image
                        (list arm_5 right_leg body_1 left_leg_front )
                        356 224 89 112 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define slapping-plee

(define looking-upward-plee
  (lambda (dest_image)

    (let ( (src_name "plee-looking-upward.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (body 0) )

          (create-layer src_image
                        (list body )
                        445 224 46 117 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define looking-upward-plee

(define looking-downward-plee
  (lambda (dest_image)

    (let ( (src_name "plee-looking-downward.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (arm       0)
               (right_leg 1)
               (eye       2)
               (body      3) )

          (create-layer src_image
                        (list arm right_leg eye body )
                        0 341 75 103 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define looking-downward-plee

(define power-jumping-plee
  (lambda (dest_image)

    (let ( (src_name "plee-power-jumping.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (right_arm_2 0)
               (right_arm_1 1)
               (right_arm_0 2)
               (right_leg_1 3)
               (right_leg_0 4)
               (body_1      5)
               (body_0      6)
               (left_arm_3  7)
               (left_arm_2  8)
               (left_arm_1  9)
               (left_arm_0 10)
               (left_leg_2 11)
               (left_leg_1 12)
               (left_leg_0 13) )

          (create-layer src_image
                        (list right_arm_0 right_leg_0 body_0 left_arm_0
                              left_leg_0)
                        75 341 61 134 dest_image )
          (create-layer src_image
                        (list right_arm_1 right_leg_1 body_1 left_arm_1
                              left_leg_0)
                        136 341 61 134 dest_image )
          (create-layer src_image
                        (list right_arm_2 right_leg_1 body_1 left_arm_2
                              left_leg_1)
                        197 341 61 134 dest_image )
          (create-layer src_image
                        (list right_arm_2 right_leg_1 body_1 left_arm_3
                              left_leg_2)
                        258 341 61 134 dest_image )
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define power-jumping-plee

(define sleeping-plee
  (lambda (dest_image)

    (let ( (src_name "plee-sleeping.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (right_arm_2 0)
               (right_arm_1 1)
               (right_arm_0 2)
               (right_leg   3)
               (body_2      4)
               (body_1      5)
               (body_0      6) )

          (create-layer src_image
                        (list body_0 right_leg right_arm_0 )
                        319 341 63 108 dest_image)
          (create-layer src_image
                        (list body_1 right_leg right_arm_1 )
                        382 341 63 108 dest_image)
          (create-layer src_image
                        (list body_2 right_leg right_arm_2 )
                        445 341 63 108 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define sleeping-plee

(let ( (dest_name "plee-1.png") )
  (let ( (dest_image (new-image 512 512)) )

    (walking-plee dest_image);
    (slapping-plee dest_image);
    (looking-upward-plee dest_image);
    (looking-downward-plee dest_image);
    (power-jumping-plee dest_image);
    (sleeping-plee dest_image);

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
