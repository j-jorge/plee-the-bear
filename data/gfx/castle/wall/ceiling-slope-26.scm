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

(let ( (ground-line-index 0) (stones-index 1) (wall-index 2)
       )

  (define create-left-ceiling
    (lambda (src_image)

      (let ( (dest_name "ceiling-slope-26-left.png")
             (layers (list stones-index wall-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image layers 0 0 512 512
                             0  0 256 256 dest_image '() )
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (define create-right-ceiling
    (lambda (src_image)

      (let ( (dest_name "ceiling-slope-26-right.png")
             (layers (list stones-index wall-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image layers 512 256 512 512
                             0  0 256 256 dest_image '() )
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (let ( (src_name "ceiling-slope-26.xcf.bz2") )
    (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

      (create-left-ceiling src_image)
      (create-right-ceiling src_image)

      (gimp-quit 1)

      ) ; let
    ) ; let
  ) ; let
