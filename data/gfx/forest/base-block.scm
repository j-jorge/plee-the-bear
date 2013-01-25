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

(let ( (src_name "base-block.xcf.bz2")
       (dest_name "ground-ceiling.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (car (gimp-image-new 256 256 RGB)))
         )
    ( create-layer-crop
      src_image
      '(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17    19 20 21 22)
      256 0 512 256
      0  0 256 128 dest_image '() )
    ( create-layer-crop
      src_image
      '(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17    19 20 21 22)
      256 768 512 256
      0  128 256 128 dest_image '()  )
    
    (save-frames dest_name dest_image)
    ) ; let
  ) ; let

(let ( (src_name "base-block.xcf.bz2")
       (dest_name "wall-corner.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (car (gimp-image-new 256 256 RGB)))
         )
    ( create-layer-crop
      src_image
      '(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17    19 20 21 22)
      0 256 256 512
      0 0 128 256 dest_image  '() )
    ( create-layer-crop
      src_image
      '(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17    19 20 21 22)
      0 0 256 256
      128 0 128 128 dest_image  '() )
    ( create-layer-crop
      src_image
      '(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17    19 20 21 22)
      0 768 256 256
      128 128 128 128 dest_image  '() )
    
    (save-frames dest_name dest_image)
    ) ; let
  ) ; let

(let ( (src_name "base-block.xcf.bz2")
       (dest_name "wall-fill.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (car (gimp-image-new 256 256 RGB)))
         )
    ( create-layer-crop
      src_image
      '(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17    19 20 21 22)
      256 256 512 512
      0 0 256 256 dest_image  '() )
    
    (save-frames dest_name dest_image)
    ) ; let
  ) ; let

(let ( (src_name "base-block.xcf.bz2")
       (dest_name "wall-fill-2.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (car (gimp-image-new 256 256 RGB)))
         )
    ( create-layer-crop
      src_image
      '(0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18    20 21 22)
      256 256 512 512
      0 0 256 256 dest_image  '() )
    
    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let

