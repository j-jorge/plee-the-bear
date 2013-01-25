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

(define fall
  (lambda (dest_image)
    (let ( (src_name "fall.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (fall_1 0) )

          (create-layer src_image
                        (list fall_1)
                        0 0 25 21 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define fall

(define jump
  (lambda (dest_image)
    (let ( (src_name "jump.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (jump_0    0)
               (jump_1    1)
               (jump_2    2) )

          (create-layer src_image
                        (list jump_0)
                        25 0 25 29 dest_image)
          (create-layer src_image
                        (list jump_1)
                        50 0 25 29 dest_image)
          (create-layer src_image
                        (list jump_2)
                        75 0 25 29 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define jump

(let ( (dest_name "frog-2.png") )
  (let ( (dest_image (new-image 128 32)) )

    (fall dest_image);
    (jump dest_image);

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
