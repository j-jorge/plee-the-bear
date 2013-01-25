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

; the arrows indicating the players outside the screen
(define arrows
  (lambda (dest_image)
    (let ( (src_name "player_arrow.xcf") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        (create-layer src_image '(0 2 3)   0  0 46 27 dest_image)
        (create-layer src_image '(1 2 4)   0 27 46 27 dest_image)
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define

; the little Plee shown next to the remaining tries
(define little-plee
  (lambda (dest_image)
    (let ( (src_name "../../plee/plee-walking.xcf.bz2")
           (cap_name "../../plee/cap.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             (cap_image (car (gimp-file-load 1 cap_name cap_name))) )

        ; small plee
        (let ( (right_arm_forward 2)
               (right_arm_idle 1)
               (right_arm_backward 0)
               (right_leg_forward 3)
               (right_leg_idle 4)
               (right_leg_backward 5)
               (body 6)
               (left_leg_forward 9)
               (left_leg_idle 10)
               (left_leg_backward 11) )
           
          (create-layer src_image 
                        (list body right_arm_forward right_leg_backward
                              left_leg_forward)
                        46 0 16 30 dest_image)
          ); let

        ; the cap
        ( create-layer cap_image '(0 6 7)  50 -1 10 4 dest_image )
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define

; the shiny honey jar
(define shiny-jar
  (lambda (dest_image)
    (let ( (src_name "../../shiny-honey-jar/shiny-honey-jar.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        (create-layer src_image '(10 11 12 13)  46 30 16 16 dest_image)

        ) ; let
      ) ; let
   ) ; lambda
  ) ; define

; the fast forward symbol
(define fast-forward
  (lambda (dest_image)
    (let ( (src_name "fast-forward.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        (create-layer-from-image src_image 63 0 64 48 dest_image)

        ) ; let
      ) ; let
    ) ; lambda
  ) ; define

(let ( (dest_name "status.png") )
  (let ( (dest_image (new-image 128 64 RGB)) )
    
    (arrows dest_image)
    (little-plee dest_image)
    (shiny-jar dest_image)
    (fast-forward dest_image)

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
