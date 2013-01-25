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


(let ( (src_name "power-filter-door.xcf.bz2")
       (dest_name_1 "power-filter-door-1.png")
       (dest_name_2 "power-filter-door-2.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image_1 (car (gimp-image-new 256 256 RGB)))
         (dest_image_2 (car (gimp-image-new 128 256 RGB)))
         )

    ; layers
    (let ( (shadows 0)
           (lights 1)
           (stripes 2)
           (air_light 3)
           (air_dark 4)
           (air_back 5)
           (water_light 6)
           (water_dark 7)
           (water_back 8)
           (fire_light 9)
           (fire_dark 10)
           (fire_back 11) )

      ; air
      (create-layer src_image (list shadows lights stripes
                                    air_light air_dark air_back)
                    0 0 32 256 dest_image_1)
      (shift-layers src_image (list air_light air_dark) 0 128)
      (create-layer src_image (list shadows lights stripes
                                    air_light air_dark air_back)
                    32 0 32 256 dest_image_1)
      (shift-layers src_image (list air_light air_dark) 0 128)
      (create-layer src_image (list shadows lights stripes
                                    air_light air_dark air_back)
                    64 0 32 256 dest_image_1)
      (shift-layers src_image (list air_light air_dark) 0 128)
      (create-layer src_image (list shadows lights stripes
                                    air_light air_dark air_back)
                    96 0 32 256 dest_image_1)

      ; water
      (create-layer src_image (list shadows lights stripes
                                    water_light water_dark water_back)
                    128 0 32 256 dest_image_1)
      (shift-layers src_image (list water_light water_dark) 0 128)
      (create-layer src_image (list shadows lights stripes
                                    water_light water_dark water_back)
                    160 0 32 256 dest_image_1)
      (shift-layers src_image (list water_light water_dark) 0 128)
      (create-layer src_image (list shadows lights stripes
                                    water_light water_dark water_back)
                    192 0 32 256 dest_image_1)
      (shift-layers src_image (list water_light water_dark) 0 128)
      (create-layer src_image (list shadows lights stripes
                                    water_light water_dark water_back)
                    224 0 32 256 dest_image_1)

      ; fire
      (create-layer src_image (list shadows lights stripes
                                    fire_light fire_dark fire_back)
                    0 0 32 256 dest_image_2)
      (shift-layers src_image (list fire_light fire_dark) 0 128)
      (create-layer src_image (list shadows lights stripes
                                    fire_light fire_dark fire_back)
                    32 0 32 256 dest_image_2)
      (shift-layers src_image (list fire_light fire_dark) 0 128)
      (create-layer src_image (list shadows lights stripes
                                    fire_light fire_dark fire_back)
                    64 0 32 256 dest_image_2)
      (shift-layers src_image (list fire_light fire_dark) 0 128)
      (create-layer src_image (list shadows lights stripes
                                    fire_light fire_dark fire_back)
                    96 0 32 256 dest_image_2)

      ) ; let

    (save-frames dest_name_1 dest_image_1)
    (save-frames-and-exit dest_name_2 dest_image_2)
    ) ; let
  ) ; let
