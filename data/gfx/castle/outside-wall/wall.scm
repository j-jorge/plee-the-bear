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

(let ( (entry-mask-index 0)

       (wall-mask-index 1) (left-wall-mask-index 2) (top-wall-mask-index 3)

       (entry-top-index 4)

       (wall-holes-index 5) (wall-stone-effect-index 6) (wall-shadows-index 7)
       (wall-index 8)
       
       (moss-index 9) (stone-effect-index 10) (joints-index 11)
       (joints-noise-index 12) (shadows-index 13) (bricks-index 14)

       (wall-offset (/ -128 2)) )

  (define create-entry
    (lambda (src_image)

      (let ( (dest_name "entry.png")
             (layers (list entry-top-index
                           moss-index stone-effect-index joints-index
                           joints-noise-index shadows-index bricks-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image layers 0 0 512 512
                             0  0 256 256 dest_image (list entry-mask-index) )
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (define create-entry-bottom
    (lambda (src_image)

      (let ( (dest_name "entry-bottom.png")
             (layers (list wall-holes-index wall-stone-effect-index
                           wall-shadows-index wall-index
                           moss-index stone-effect-index joints-index
                           joints-noise-index shadows-index bricks-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image layers 0 0 512 512
                             0  0 256 256 dest_image (list wall-mask-index) )
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (define create-wall
    (lambda (src_image)

      (let ( (dest_name "wall.png")
             (wall (list wall-holes-index wall-stone-effect-index
                         wall-shadows-index wall-index))
             (bricks (list moss-index stone-effect-index joints-index
                           joints-noise-index shadows-index bricks-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer src_image bricks 0 0 256 256 dest_image)
          (create-layer src_image wall wall-offset 0 256 256 dest_image)
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (define create-left-wall
    (lambda (src_image)

      (let ( (dest_name "left-wall.png")
             (layers (list moss-index stone-effect-index joints-index
                           joints-noise-index shadows-index bricks-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image layers 0 0 512 512
                             0 0 256 256 dest_image (list left-wall-mask-index))
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (define create-top-wall
    (lambda (src_image)

      (let ( (dest_name "top-wall.png")
             (layers (list moss-index stone-effect-index joints-index
                           joints-noise-index shadows-index bricks-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer-crop src_image layers 0 0 512 512
                             0 0 256 256 dest_image (list top-wall-mask-index))
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (define create-wall-fill
    (lambda (src_image)

      (let ( (dest_name "wall-fill.png")
             (layers (list moss-index stone-effect-index joints-index
                           joints-noise-index shadows-index bricks-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer src_image layers 0 0 256 256 dest_image)
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let
      ) ; lambda
    ) ; define

  (let ( (src_name "wall.xcf.bz2") )
    (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

      (create-entry src_image)
      (create-entry-bottom src_image)
      (create-wall src_image)
      (create-wall-fill src_image)
      (create-left-wall src_image)
      (create-top-wall src_image)

      (gimp-quit 1)

      ) ; let
    ) ; let
  ) ; let
