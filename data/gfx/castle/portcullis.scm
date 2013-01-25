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

(let ( (heads-index 0) (bolts-index 1) (horizontal-index 2)
       (vertical-index 3) (corners-index 4) )

  (define create-complete
    (lambda (src_image dest_image)

      (create-layer src_image (list heads-index bolts-index horizontal-index
                                    vertical-index corners-index)
                    0 0 256 128 dest_image)
      ) ; lambda
    ) ; define

  (define create-no-corners
    (lambda (src_image dest_image)

      (create-layer src_image (list heads-index bolts-index horizontal-index
                                    vertical-index)
                    0 128 256 128 dest_image)
      ) ; lambda
    ) ; define

  (let ( (src_name "portcullis.xcf.bz2")
         (dest_name "portcullis.png") )
    (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
           (dest_image (car (gimp-image-new 256 256 RGB)))
           )

      (create-complete src_image dest_image)
      (create-no-corners src_image dest_image)

      (save-frames-and-exit dest_name dest_image)
      ) ; let
    ) ; let
  ) ; let
