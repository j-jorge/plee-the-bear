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

(let ( (src_name "totem.xcf.bz2")
       (dest_name "totem.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (new-image 512 512)) )

    (let ( (green_lights 0)
           (right_light_on 1)
           (right_light_off 2)
           (left_light_on 3)
           (left_light_off 4)
           (rope 5)
           (hook 6)
           (noise 7)
           (brown_block 8)
           (block 9) )

      (create-layer src_image 
                    (list hook noise block rope right_light_off left_light_off)
                    0 0 142 128 dest_image)
      (create-layer src_image 
                    (list hook noise block rope right_light_off left_light_on)
                    142 0 142 128 dest_image)
      (create-layer src_image 
                    (list hook noise block rope right_light_on left_light_off)
                    284 0 142 128 dest_image)
      (create-layer src_image 
                    (list hook noise block rope green_lights)
                    0 128 142 128 dest_image)

      (create-layer src_image 
                    (list noise brown_block right_light_off left_light_off)
                    142 128 142 128 dest_image)
      (create-layer src_image 
                    (list noise brown_block right_light_off left_light_on)
                    284 128 142 128 dest_image)
      (create-layer src_image 
                    (list noise brown_block right_light_on left_light_off)
                    0 256 142 128 dest_image)
      (create-layer src_image 
                    (list noise brown_block green_lights)
                    142 256 142 128 dest_image)

      (create-layer src_image 
                    (list hook noise block right_light_off left_light_off)
                    284 256 142 128 dest_image)

      ) ; let

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
