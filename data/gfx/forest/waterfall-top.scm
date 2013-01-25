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

(let ( (src_name "waterfall.xcf.bz2")
       (dest_name "waterfall-top.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (car (gimp-image-new 512 512 RGB)))
         )
    (let loop_y ((y 0))
      (unless (= y 512)
              (let loop_x ((x 0))
                (unless (= x 512)
                        (begin
                          (create-layer-crop src_image '(1 2 3 4 5)
                                             0 256 512 256 
                                             x y 256 128 dest_image '(0))
                          (shift-layers src_image '(3 4) 0 32)
                          (shift-layers src_image '(5 2 )   0 64)
                          ) ; begin
                        (loop_x (+ x 256))
                        ) ; unless
                ) ; let
              (loop_y (+ y 128))
              ) ; unless
      ) ; let

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
