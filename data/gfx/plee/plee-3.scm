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
(define clinging-plee
  (lambda (dest_image)

    (let ( (src_name "plee-clinging.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (arm_claws_2 0)
               (arm_claws_1 1)
               (arm_claws_0 2)
               (right_arm_3   3)
               (right_arm_2   4)
               (right_arm_1   5)
               (right_arm_0   6)
               (leg_claws_2   7)
               (leg_claws_1   8)
               (leg_claws_0   9)
               (right_leg_3  10)
               (right_leg_2  11)
               (right_leg_1  12)
               (right_leg_0  13)
               (body_2       14)
               (body_1       15)
               (body_0       16)
               (left_arm_2   17)
               (left_arm_1   18)
               (left_arm_0   19)
               (left_leg_1   20)
               (left_leg_0   21) )

          (create-layer src_image
                        (list body_0 right_leg_0 right_arm_0 left_leg_0)
                        0 0 71 125 dest_image)
          (create-layer src_image
                        (list body_1 right_leg_1 right_arm_1 left_arm_0
                              left_leg_0 leg_claws_0 arm_claws_0)
                        71 0 71 125 dest_image)
          (create-layer src_image
                        (list body_2 right_leg_2 right_arm_2 left_arm_1
                              left_leg_1 leg_claws_1 arm_claws_1)
                        142 0 71 125 dest_image)
          (create-layer src_image
                        (list body_2 right_leg_3 right_arm_3 left_arm_2
                              left_leg_1 leg_claws_2 arm_claws_2)
                        213 0 71 125 dest_image)
          (create-layer src_image
                        (list body_2 right_leg_3 right_arm_3 left_leg_1)
                        284 0 71 125 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define clinging-plee

(define roaring-plee
  (lambda (dest_image)

    (let ( (src_name "plee-roaring.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (arm_6    0)
               (arm_5    1)
               (arm_4    2)
               (arm_3    3)
               (arm_2    4)
               (arm_1    5)
               (arm_0    6)
               (leg      7)
               (body_6   8)
               (body_5   9)
               (teeth_1  10)
               (teeth_0  11)
               (tongue_2 12)
               (tongue_1 13)
               (tongue_0 14)
               (body_4   15)
               (body_3   16)
               (body_2   17)
               (body_1   18)
               (body_0   19) )

          (create-layer src_image
                        (list leg body_0 arm_0)
                        355 0 71 112 dest_image)
          (create-layer src_image
                        (list leg body_1 arm_1)
                        426 0 71 112 dest_image)
          (create-layer src_image
                        (list leg body_2 arm_2)
                        0 125 71 112 dest_image)
          (create-layer src_image
                        (list leg body_3 arm_3)
                        71 125 71 112 dest_image)
          (create-layer src_image
                        (list leg body_4 arm_4)
                        142 125 71 112 dest_image)
          (create-layer src_image
                        (list leg body_5 arm_5 teeth_0 tongue_0)
                        213 125 71 112 dest_image)
          (create-layer src_image
                        (list leg body_6 arm_6 teeth_0 tongue_1)
                        284 125 71 112 dest_image)
          (create-layer src_image
                        (list leg body_6 arm_6 teeth_0 tongue_2)
                        355 125 71 112 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define roaring-plee

(define falling-plee
  (lambda (dest_image)

    (let ( (src_name "plee-falling.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (arm_2        0)
               (arm_1        1)
               (arm_0        2)
               (right_leg_2  3)
               (right_leg_1  4)
               (right_leg_0  5)
               (body_2       6)
               (body_1       7)
               (body_0       8)
               (left_arm_2   9)
               (left_arm_1  10)
               (left_arm_0  11)
               (left_leg_2  12)
               (left_leg_1  13)
               (left_leg_0  14) )

          (create-layer src_image
                        (list arm_0 right_leg_0 body_0 left_arm_0 left_leg_0)
                        426 125 66 114 dest_image)
          (create-layer src_image
                        (list arm_1 right_leg_1 body_1 left_arm_1 left_leg_1)
                        0 239 66 114 dest_image)
          (create-layer src_image
                        (list arm_2 right_leg_2 body_2 left_arm_2 left_leg_2)
                        66 239 66 114 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define falling-plee

(define falling-and-throwing-plee
  (lambda (dest_image)

    (let ( (src_name "plee-falling-and-throwing.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (right_arm_3      0)
               (right_arm_2      1)
               (right_arm_1      2)
               (right_arm_0      3)
               (object_1         4)
               (object_0         5)
               (right_leg_2      6)
               (right_leg_1      7)
               (right_leg_0      8)
               (body_2           9)
               (body_1          10)
               (body_0          11)
               (left_arm_2      12)
               (left_arm_1      13)
               (left_arm_0      14)
               (left_leg_2      15)
               (left_leg_1      16)
               (left_leg_0      17) )

          (create-layer src_image
                        (list right_arm_0 object_0 right_leg_0 body_0 left_arm_0
                              left_leg_0)
                        132 239 76 114 dest_image)
          (create-layer src_image
                        (list right_arm_1 object_1 right_leg_1 body_1 left_arm_1
                              left_leg_1)
                        208 239 76 114 dest_image)
          (create-layer src_image
                        (list right_arm_2 right_leg_2 body_2 left_arm_2
                              left_leg_2)
                        284 239 76 114 dest_image)
          (create-layer src_image
                        (list right_arm_3 right_leg_1 body_1 left_arm_1
                              left_leg_1)
                        360 239 76 114 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define falling-and-throwing-plee

(define swimming-plee
  (lambda (dest_image)

    (let ( (src_name "plee-swimming.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (right_leg_3      0)
               (right_leg_2      1)
               (right_leg_1      2)
               (right_arm_4      3)
               (right_arm_3      4)
               (right_arm_2      5)
               (right_arm_1      6)
               (body_2           7)
               (body_1           8)
               (left_arm_1       9)
               (left_leg_3      10)
               (left_leg_2      11)
               (left_leg_1      12) )

          (create-layer src_image
                        (list right_leg_1 right_arm_1 body_1)
                        0 364 92 125 dest_image)
          (create-layer src_image
                        (list right_leg_2 right_arm_2 body_1 left_leg_1)
                        92 364 92 125 dest_image)
          (create-layer src_image
                        (list right_leg_3 right_arm_3 body_2 left_arm_1
                              left_leg_2)
                        184 364 92 125 dest_image)
          (create-layer src_image
                        (list right_leg_2 right_arm_4 body_1 left_leg_1)
                        276 364 92 125 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define swimming-plee

(define floating-underwater-plee
  (lambda (dest_image)

    (let ( (src_name "plee-swimming.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        ; layer names
        (let ( (right_leg_3      0)
               (right_leg_2      1)
               (right_leg_1      2)
               (right_arm_4      3)
               (right_arm_3      4)
               (right_arm_2      5)
               (right_arm_1      6)
               (body_2           7)
               (body_1           8)
               (left_arm_1       9)
               (left_leg_3      10)
               (left_leg_2      11)
               (left_leg_1      12) )

          (create-layer src_image
                        (list right_leg_2 right_arm_2 body_1 left_leg_2)
                        368 364 92 125 dest_image)
          (create-layer src_image
                        (list right_leg_3 right_arm_4 body_1 left_leg_2)
                        429 364 92 125 dest_image)
          (create-layer src_image
                        (list right_leg_3 right_arm_1 body_1 left_leg_1)
                        436 239 92 125 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define floating-underwater-plee

(let ( (dest_name "plee-3.png") )
  (let ( (dest_image (new-image 512 512)) )

    (clinging-plee dest_image);
    (roaring-plee dest_image);
    (falling-plee dest_image);
    (falling-and-throwing-plee dest_image);
    (swimming-plee dest_image);
    (floating-underwater-plee dest_image);

    (save-frames-and-exit dest_name dest_image);
    ) ; let
  ) ; let
