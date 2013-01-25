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

(let ( (top-shadows-index 0) (bottom-shadows-index 1) (shadows-index 2)
       (edging-ends-index 3) (edging-index 4)
       (purple-ends-index 5) (purple-curtain-index 6)
       (blue-ends-index 7) (blue-curtain-index 8)
       (rod-index 9) )

  (define create-blue-curtain
    (lambda (src_image dest_image x y)

      (let ( (layers (list top-shadows-index bottom-shadows-index shadows-index
                           edging-ends-index edging-index
                           blue-curtain-index blue-ends-index
                           rod-index)) )
        

          (create-layer src_image layers x y 256 256 dest_image)
          ) ; let
      ) ; lambda
    ) ; define

  (define create-purple-curtain
    (lambda (src_image dest_image x y)

      (let ( (layers (list top-shadows-index bottom-shadows-index shadows-index
                           edging-ends-index edging-index
                           purple-curtain-index purple-ends-index
                           rod-index)) )
        

          (create-layer src_image layers x y 256 256 dest_image)
          ) ; let
      ) ; lambda
    ) ; define

  (let ( (src_name "curtain.xcf.bz2") (dest_name "curtain.png") )
    (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
           (dest_image (new-image 512 256 RGB)))

      (create-blue-curtain src_image dest_image 0 0)
      (create-purple-curtain src_image dest_image 256 0)

      (save-frames-and-exit dest_name dest_image)

      ) ; let
    ) ; let
  ) ; let
