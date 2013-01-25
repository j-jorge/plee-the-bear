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

(define target
  (lambda (dest_image)
    ; the ratio of the size is 0.38

    (let ( (src_name "target.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (wood_effect 0)
               (body_lines  1)
               (body_color  2)
               (wood_color  3) )

          (create-layer src_image
                        (list wood_effect body_lines body_color wood_color)
                        0 0 32 98 dest_image)
          ); let
        ); let
      ); let
    ); lambda
  ); define target

(define broken-target
  (lambda (dest_image)
    ; the ratio of the size is 0.38

    (let ( (src_name "broken-target.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (wood_effect       0)
               (top_body          1)
               (top_wood_color    2)
               (bottom_body       3)
               (bottom_wood_color 4) )

          (create-layer src_image
                        (list wood_effect bottom_body bottom_wood_color)
                        32 0 32 98 dest_image)
          (create-layer src_image
                        (list wood_effect top_body top_wood_color)
                        64 0 32 98 dest_image)
          ); let
        ); let
      ); let
    ); lambda
  ); define broken-target

(let ( (dest_name "target.png") )
  (let ( (dest_image (new-image 128 128)) )

    (target dest_image)
    (broken-target dest_image)

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
