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

(define sign-exit
  (lambda (dest_image)

    (let ( (src_name "end-sign.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (create-layer src_image 
                      '(0 1 2 3 4 5 6 7 8 9 10 11)
                      0 0 80 98 dest_image)
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define sign-exit

(define sign-players
  (lambda (dest_image)

    (let ( (src_name "sign.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
             )

        ; layer names
        (let ( (cood_horizontal           0)
               (single_down               1)
               (single_up                 2)
               (single_horizontal         3)
               (top_notice_down           4)
               (top_notice_up             5)
               (top_notice_horizontal     6)
               (bottom_notice_down        7)
               (bottom_notice_up          8)
               (bottom_notice_horizontal  9)
               (stake                    10) )
          
          (create-layer src_image
                        (list cood_horizontal top_notice_horizontal stake)
                        80 0 80 98 dest_image)
          (create-layer src_image
                        (list single_down top_notice_down stake)
                        160 0 80 98 dest_image)
          (create-layer src_image
                        (list single_up top_notice_up stake)
                        240 0 80 98 dest_image)
          (create-layer src_image
                        (list single_horizontal top_notice_horizontal stake)
                        320 0 80 98 dest_image)
          ) ; let
          ) ; let
      ) ; let
    ) ; lambda
  ) ; define sign-players

(let ( (dest_name "sign.png") )
  (let ( (dest_image (new-image 512 128)) )

    (sign-exit dest_image);
    (sign-players dest_image);

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
