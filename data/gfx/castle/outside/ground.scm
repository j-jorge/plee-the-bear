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

(let ( (noise-index 0) (top-left-grass-index 1) (top-grass-index 2)
       (wet-top-left-grass-index 3) (wet-top-grass-index 4) (top-index 5)
       (top-left-index 6) (left-shadows-index 7) (left-index 8)
       (bottom-left-index 9) (bottom-shadows-index 10) (bottom-index 11)
       (shadows-index 12) (shadows-2-index 13) (lines-index 14)
       (back-noise-index 15) (marble-index 16) (wall-fill-index 17) )

  (define create-ground-ceiling
    (lambda (src_image)

      (let ( (dest_name "ground-ceiling.png")
             (top (list noise-index top-grass-index wet-top-grass-index
                        top-index))
             (bottom (list noise-index bottom-shadows-index bottom-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image top 256 0 512 256
                             0  0 256 128 dest_image '() )
          (create-layer-crop src_image bottom 256 768 512 256
                             0  128 256 128 dest_image '() )
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (define create-wall-corner
    (lambda (src_image)

      (let ( (dest_name "wall-corner.png")
             (left (list noise-index left-shadows-index left-index))
             (top-left (list noise-index top-left-grass-index
                             wet-top-left-grass-index top-left-index))
             (bottom-left (list noise-index bottom-left-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image left 0 256 256 512
                             0 0 128 256 dest_image '() )
          (create-layer-crop src_image top-left 0 0 256 256
                             128 0 128 128 dest_image '() )
          (create-layer-crop src_image bottom-left
                             0 768 256 256
                             128 128 128 128 dest_image '() )
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (define create-wall-fill
    (lambda (src_image)

      (let ( (dest_name "wall-fill.png")
             (wall-fill-1 (list noise-index shadows-index lines-index
                                back-noise-index marble-index
                                wall-fill-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image wall-fill-1 256 256 512 512
                             0 0 256 256 dest_image '() )
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let

      ) ; lambda
    ) ; define

  (define create-wall-fill-2
    (lambda (src_image)

      (let ( (dest_name "wall-fill-2.png")
             (wall-fill-1 (list noise-index shadows-2-index lines-index
                                back-noise-index marble-index
                                wall-fill-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image wall-fill-1 256 256 512 512
                             0 0 256 256 dest_image '() )
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let

      ) ; lambda
    ) ; define

  (let ( (src_name "ground.xcf.bz2") )
    (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

      (create-ground-ceiling src_image)
      (create-wall-corner src_image)
      (create-wall-fill src_image)
      (create-wall-fill-2 src_image)

      (gimp-quit 1)

      ) ; let
    ) ; let
  ) ; let
