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

(let ( (crack-index 0) (noise-index 1) (streaks-index 2)

       (fill-3-index 3) (fill-2-index 4) (fill-1-index 5) (background-index 6) )

  (define create-crack
    (lambda (src_image)

      (let ( (dest_name "crack.png")
             (layers (list crack-index noise-index streaks-index fill-3-index
                              background-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer src_image layers
                        0 0 256 256 dest_image)
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let

      ) ; lambda
    ) ; define

  (define create-wall-fill-1
    (lambda (src_image)

      (let ( (dest_name "wall-fill.png")
             (wall-fill (list noise-index streaks-index fill-1-index
                              background-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer src_image wall-fill
                        0 0 256 256 dest_image)
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let

      ) ; lambda
    ) ; define

  (define create-wall-fill-2
    (lambda (src_image)

      (let ( (dest_name "wall-fill-2.png")
             (wall-fill (list noise-index streaks-index fill-2-index
                              background-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer src_image wall-fill
                        0 0 256 256 dest_image)
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let

      ) ; lambda
    ) ; define

  (define create-wall-fill-3
    (lambda (src_image)

      (let ( (dest_name "wall-fill-3.png")
             (wall-fill (list noise-index streaks-index fill-3-index
                              background-index)) )
        
        (let ( (dest_image (car (gimp-image-new 256 256 RGB))) )

          (create-layer src_image wall-fill
                        0 0 256 256 dest_image)
          
          (save-frames dest_name dest_image)
          ) ; let
        ) ; let

      ) ; lambda
    ) ; define

  (let ( (src_name "room-wall.xcf.bz2") )
    (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

      (create-crack src_image)
      (create-wall-fill-1 src_image)
      (create-wall-fill-2 src_image)
      (create-wall-fill-3 src_image)

      (gimp-quit 1)
      ) ; let
    ) ; let
  ) ; let