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

(let ( (noise-index 0)
       (top-effect-index 1) (top-index 2) (top-shadows-index 3)
       (top-bricks-index 4)

       (top-left-effect-index 5) (top-left-index 6) (top-left-shadows-index 7)
       (top-left-wall-index 8) (top-left-bricks-index 9)

       (left-stone-effect-index 10) (left-shadows-index 11) (left-index 12)
       (left-bricks-index 13)

       (bottom-left-stone-effect-index 14) (bottom-left-shadows-index 15)
       (bottom-left-index 16) (bottom-left-bricks-index 17)

       (bottom-stone-effect-index 18) (bottom-shadows-index 19)
       (bottom-index 20) (bottom-bricks-index 21)

       (bricks-index 22) (stone-effect-index 23) (shadows-index 24)
       (bricks-volume-index 25)

       (bricks-2-index 26) (stone-effect-2-index 27) (shadows-2-index 28)
       (bricks-volume-2-index 29) )

  (define create-ground-ceiling
    (lambda (src_image)

      (let ( (dest_name "ground-ceiling.png")
             (top (list noise-index top-effect-index top-index top-bricks-index
                        top-shadows-index))
             (bottom (list noise-index bottom-stone-effect-index
                           bottom-shadows-index bottom-index
                           bottom-bricks-index)) )
        
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
             (left (list noise-index left-stone-effect-index left-index
                         left-bricks-index))
             (top-left (list noise-index top-left-effect-index top-left-index
                             top-left-shadows-index top-left-wall-index
                             top-left-bricks-index))
             (bottom-left (list noise-index bottom-left-stone-effect-index
                                bottom-left-shadows-index bottom-left-index
                                bottom-left-bricks-index)) )
        
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
             (wall-fill-1 (list noise-index bricks-index shadows-index
                                stone-effect-index bricks-volume-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image wall-fill-1 256 256 512 512
                             0 0 256 256 dest_image '() )
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let

      (let ( (dest_name "wall-fill-2.png")
             (wall-fill-2 (list noise-index bricks-2-index shadows-2-index
                                stone-effect-2-index bricks-volume-2-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image wall-fill-2 256 256 512 512
                             0 0 256 256 dest_image '() )
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (let ( (src_name "base-block.xcf.bz2") )
    (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

      (create-ground-ceiling src_image)
      (create-wall-corner src_image)
      (create-wall-fill src_image)

      (gimp-quit 1)

      ) ; let
    ) ; let
  ) ; let
