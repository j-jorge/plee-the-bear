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

(let ( (src_name "air-blast.xcf.bz2")
       (dest_name "air-blast.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (new-image 512 256)) )

    (create-layer src_image '(0 1)
                  0 0 100 100 dest_image)
    (create-layer src_image '(0 1 2 3)
                  100 0 100 100 dest_image)
    (create-layer src_image '(2 3 4 5)
                  200 0 100 100 dest_image)
    (create-layer src_image '(2 3 4 5 6 7)
                  300 0 100 100 dest_image)
    (create-layer src_image '(2 3 4 5 6 7 8 9)
                  400 0 100 100 dest_image)

    (create-layer src_image '(2 3 4 5 6 7 8 9 10 11)
                  0 100 100 100 dest_image)
    (create-layer src_image '(4 5 6 7 8 9 10 11)
                  100 100 100 100 dest_image)
    (create-layer src_image '(6 7 8 9 10 11)
                  200 100 100 100 dest_image)
    (create-layer src_image '(8 9 10 11)
                  300 100 100 100 dest_image)
    (create-layer src_image '(10 11)
                  400 100 100 100 dest_image)

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
