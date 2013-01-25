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

(let ( (nails-index 0) (yellow-index 1) (orange-index 2)
       (red-index 3) (top-index 4)
       (front-3-index 5) (back-3-index 6)
       (front-2-index 7) (back-2-index 8)
       (front-1-index 9) )

  (define create-spring
    (lambda (src_image dest_image top_layer_index y)

      (set-layer-position src_image top_layer_index 0 30)
      (create-layer src_image (list top_layer_index front-1-index)
                    0  y 60 45 dest_image)

      (set-layer-position src_image top_layer_index 0 15)
      (create-layer src_image (list top_layer_index front-2-index back-2-index)
                    61  y 60 45 dest_image)

      (set-layer-position src_image top_layer_index 0 0)
      (create-layer src_image (list top_layer_index front-3-index back-3-index)
                    122  y 60 45 dest_image)

      ) ; lambda
    ) ; define

  (define create-spikes
    (lambda (dest_image y)

      (let ( (src_name "spikes.xcf.bz2") )
        (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

          (create-layer-from-image src_image 0  y 128 64 dest_image)

          ) ; let
        ) ; let

      ) ; lambda
    ) ; define

  (let ( (src_name "spring.xcf.bz2")
         (dest_name "spring.png") )
    (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
           (dest_image (car (gimp-image-new 256 256 RGB)))
           )

      (create-spring src_image dest_image yellow-index 0)
      (create-spring src_image dest_image orange-index 46)
      (create-spring src_image dest_image red-index 92)
      (create-spikes dest_image 138)

      (save-frames-and-exit dest_name dest_image)
      ) ; let
    ) ; let
  ) ; let
