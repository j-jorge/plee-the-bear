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

(let ( (src_name "woodlog-thrower.xcf.bz2")
       (dest_name "woodlog-thrower.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (new-image 256 256 RGB))
         )

    (let ( (wheel_2 0)
           (wheel_1 1)
           (wheel_0 2)
           (cable_2 3)
           (cable_1 4)
           (cable_0 5)
           (shadows 6)
           (lights 7)
           (x_3 8)
           (x_2 9)
           (x_1 10)
           (x_0 11)
           (d_noise 12)
           (h_noise 13)
           (rod 14) )

      ( create-layer src_image
                     (list wheel_0 cable_0 x_0
                           shadows lights d_noise h_noise rod )
                     0 0 80 93 dest_image )
      ( create-layer src_image
                     (list wheel_1 cable_1 x_1
                           shadows lights d_noise h_noise rod )
                     80 0 80 93 dest_image )
      ( create-layer src_image
                     (list wheel_2 cable_2 x_2
                           shadows lights d_noise h_noise rod )
                     0 93 80 93 dest_image )
      ( create-layer src_image
                     (list wheel_1 cable_1 x_3
                           shadows lights d_noise h_noise rod )
                     80 93 80 93 dest_image )
      ) ; let

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
