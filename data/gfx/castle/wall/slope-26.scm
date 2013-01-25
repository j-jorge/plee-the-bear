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

(let ( (ground-line-index 0) (ground-line-S-index 1) (noise-index 2)
       (mask-index 3) (mask-S-index 4)

       (ground-effect-index 5) (ground-index 6) (ground-shadows-index 7)

       (ground-S-effect-index 8) (ground-S-index 9) (ground-S-shadows-index 10)

       (back-index 11) )

  (define create-left-slope
    (lambda (src_image)

      (let ( (dest_name "slope-26-left.png")
             (layers (list noise-index
                           ground-effect-index ground-index ground-shadows-index
                           back-index))
             (mask (list mask-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image layers 0 256 512 512
                             0  0 256 256 dest_image mask )
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (define create-right-slope
    (lambda (src_image)

      (let ( (dest_name "slope-26-right.png")
             (layers (list noise-index
                           ground-effect-index ground-index ground-shadows-index
                           back-index))
             (mask (list mask-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image layers 512 0 512 512
                             0  0 256 256 dest_image mask )
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (define create-left-S-slope
    (lambda (src_image)

      (let ( (dest_name "slope-26s-left.png")
             (layers (list noise-index
                           ground-S-effect-index ground-S-index
                           ground-S-shadows-index
                           back-index))
             (mask (list mask-S-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image layers 0 256 512 512
                             0  0 256 256 dest_image mask )
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (define create-right-S-slope
    (lambda (src_image)

      (let ( (dest_name "slope-26s-right.png")
             (layers (list noise-index
                           ground-S-effect-index ground-S-index
                           ground-S-shadows-index
                           back-index))
             (mask (list mask-S-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image layers 512 0 512 512
                             0  0 256 256 dest_image mask )
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (let ( (src_name "slope-26.xcf.bz2") )
    (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

      (create-left-slope src_image)
      (create-right-slope src_image)
      (create-left-S-slope src_image)
      (create-right-S-slope src_image)

      (gimp-quit 1)

      ) ; let
    ) ; let
  ) ; let
