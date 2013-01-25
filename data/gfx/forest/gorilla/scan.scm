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

(define scan-gorilla
  (lambda (dest_image)

    (let ( (scan_name "scan.xcf.bz2") )
      (let ( (scan_image (car (gimp-file-load 1 scan_name scan_name)))
             )

        ; layer names
        (let ( (right_arm    0)
               (right_leg    1)
               (left_foot    2)
               (grass_left   3)
               (face_left    4)
               (grass_right  5)
               (face_right   6)
               (grass_up     7)
               (face_up      8)
               (body         9)
               (left_leg    10) )

          (create-layer scan_image
                        (list grass_right face_right
                         right_arm right_leg left_foot body left_leg)
                        0 0 113 103 dest_image)
          (create-layer scan_image
                        (list grass_up face_up
                         right_arm right_leg left_foot body left_leg)
                        113 0 113 103 dest_image)
          (create-layer scan_image
                        (list grass_left face_left
                         right_arm right_leg left_foot body left_leg)
                        226 0 113 103 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define scan-gorilla

(let ( (dest_name "scan.png") )
  (let ( (dest_image (new-image 512 128)))

    (scan-gorilla dest_image);

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
