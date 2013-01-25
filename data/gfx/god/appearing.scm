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

; coeff: x=0.497942387 y=0.49851632
(define appearing
  (lambda (dest_image)
    (let ( (src_name "appearing.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             (frames_count 12)
             )

        (let loop ((i 0))
          (unless (= i frames_count)
                  (create-layer src_image (list i (+ i frames_count))
                                (* (modulo i 4) 121)
                                (* (floor (/ i 4)) 168) 121 168 dest_image)
                  (loop (+ i 1))
                  ) ; unless
          ) ; let loop

        ) ; let
      ) ; let
    ) ; lambda
  ) ; define appearing

(let ( (dest_name "appearing.png") )
  (let ( (dest_image (new-image 512 512)) )

    (appearing dest_image);

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
