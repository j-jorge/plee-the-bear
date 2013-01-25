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

(define eating
  (lambda (dest_image)
    ; the ratio of the size is 0.25

    (let ( (src_name "eat.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (carrot_9 0)
               (carrot_8 1)
               (carrot_7 2)
               (carrot_6 3)
               (carrot_5 4)
               (right_arm_4 5)
               (right_arm_3 6)
               (right_arm_2 7)
               (right_arm_1 8)
               (carrot_4 9)
               (carrot_3 10)
               (carrot_2 11)
               (carrot_1 12)
               (head_3 13)
               (head_2 14)
               (head 15)
               (body_big_belly 16)
               (body 17)
               )

          (create-layer src_image
                        (list body head carrot_1 right_arm_1)
                        0 0 26 32 dest_image)
          (create-layer src_image
                        (list body head carrot_2 right_arm_2)
                        26 0 26 32 dest_image)
          (create-layer src_image
                        (list body head carrot_3 right_arm_3)
                        56 0 26 32 dest_image)
          (create-layer src_image
                        (list body head carrot_4 right_arm_4)
                        82 0 26 32 dest_image)

          (create-layer src_image
                        (list body head carrot_5 right_arm_4)
                        108 0 26 32 dest_image)
          (create-layer src_image
                        (list body head carrot_6 right_arm_3)
                        134 0 26 32 dest_image)
          (create-layer src_image
                        (list body head_2 carrot_7 right_arm_2)
                        160 0 26 32 dest_image)
          (create-layer src_image
                        (list body head_2 carrot_8 right_arm_1)
                        186 0 26 32 dest_image)
          (create-layer src_image
                        (list body head_2 carrot_9 right_arm_1)
                        212 0 26 32 dest_image)

          (create-layer src_image
                        (list body head_3 right_arm_1)
                        0 32 26 32 dest_image)
          (create-layer src_image
                        (list body_big_belly head right_arm_1)
                        26 32 26 32 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define eating

(let ( (dest_name "rabbit-2.png") )
  (let ( (dest_image (new-image 256 64)))

    (eating dest_image)

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
