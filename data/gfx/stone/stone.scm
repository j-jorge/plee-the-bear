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

(let ( (src_name "stone.xcf.bz2")
       (air_fire_water_name "air-fire-water-stone.xcf.bz2")
       (water_name "water-stone.xcf.bz2")
       (air_water_name "air-water-stone.xcf.bz2")
       (air_fire_name "air-fire-stone.xcf.bz2")
       (air_fire_parts_name "air-fire-stone-parts.xcf.bz2")
       (water_fire_name "water-fire-stone.xcf.bz2")
       (dest_name "stone.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         ( air_fire_water_image
           (car (gimp-file-load 1 air_fire_water_name air_fire_water_name)) )
         (water_image (car (gimp-file-load 1 water_name water_name)))
         ( air_water_image
           (car (gimp-file-load 1 air_water_name air_water_name)) )
         (air_fire_image (car (gimp-file-load 1 air_fire_name air_fire_name)))
         ( air_fire_parts_image
           (car (gimp-file-load 1 air_fire_parts_name air_fire_parts_name)) )
         ( water_fire_image
           (car (gimp-file-load 1 water_fire_name water_fire_name)) )
         (dest_image (new-image 256 128))
         )

    ; simple stone
    (create-layer src_image '(0 1)        0  0 16 16 dest_image)

    ; fire stone
    (create-layer src_image '(0 2 7 8)   16  0 16 16 dest_image)
    (create-layer src_image '(0 2 6 8)   32  0 16 16 dest_image)
    (create-layer src_image '(0 2 5 6 8) 48  0 16 16 dest_image)
    (create-layer src_image '(0 2 4 5 6 8) 64  0 16 16 dest_image)
    (create-layer src_image '(0 2 3 4 5 6 8)  80 0 16 16 dest_image)

    ; parts of the air+fire stone
    (create-layer-crop air_fire_parts_image '(0)
                       12 11 23 23
                       96 0 12 12 dest_image '())
    (create-layer-crop air_fire_parts_image '(1)
                       3 2 29 27
                       108 0 15 14 dest_image '())
    (create-layer-crop air_fire_parts_image '(2)
                       0 18 20 21
                       123 0 10 11 dest_image '())
    (create-layer-crop air_fire_parts_image '(3)
                       2 0 30 23
                       133 0 15 12 dest_image '())
    (create-layer-crop air_fire_parts_image '(4)
                       3 15 32 20
                       148 0 16 10 dest_image '())

    ; air+fire+water stone
    (create-layer air_fire_water_image '(2 3 4 5 14)   0 16 32 32 dest_image)
    (create-layer air_fire_water_image '(2 3 4 5 13)  32 16 32 32 dest_image)
    (create-layer air_fire_water_image '(2 3 4 5 12)  64 16 32 32 dest_image)
    (create-layer air_fire_water_image '(2 3 4 5 11)  96 16 32 32 dest_image)
    (create-layer air_fire_water_image '(2 3 4 5 10) 128 16 32 32 dest_image)
    (create-layer air_fire_water_image
                  '(2 3 4 5 6 7 8 9) 160 16 32 32 dest_image)

    (create-layer air_fire_water_image
                  '(0 2 3 4 5 6 7 8 9)     192 16 32 32 dest_image)
    (create-layer air_fire_water_image
                  '(0 1 2 3 4 5 6 7 8 9)   224 16 32 32 dest_image)

    ; water stone
    (create-layer water_image '(0)   0 48 20 20 dest_image)
    (create-layer water_image '(1)  20 48 20 20 dest_image)
    (create-layer water_image '(2)  40 48 20 20 dest_image)
    (create-layer water_image '(3)  60 48 20 20 dest_image)
    (create-layer water_image '(4)  80 48 20 20 dest_image)

    ; air+water stone
    (create-layer air_water_image '(0) 100 48 20 20 dest_image)

    ; air+fire stone
    (create-layer air_fire_image '(0  5 10   )   0 68 28 25 dest_image)
    (create-layer air_fire_image '(1  6 10   )  28 68 28 25 dest_image)
    (create-layer air_fire_image '(2  7 10   )  56 68 28 25 dest_image)
    (create-layer air_fire_image '(3  8 10   )  84 68 28 25 dest_image)
    (create-layer air_fire_image '(4  9 10   ) 112 68 28 25 dest_image)
    (create-layer air_fire_image '(   6 10 11) 140 68 28 25 dest_image)
    (create-layer air_fire_image '(   7 10 12) 168 68 28 25 dest_image)
    (create-layer air_fire_image '(   8 10 13) 196 68 28 25 dest_image)
    (create-layer air_fire_image '(   9 10 14) 224 68 28 25 dest_image)

    ; water+fire stone
    (create-layer water_fire_image '(    9)   0 93 22 21 dest_image)
    (create-layer water_fire_image '(    8)  22 93 22 21 dest_image)
    (create-layer water_fire_image '(    7)  44 93 22 21 dest_image)
    (create-layer water_fire_image '(  0 8)  66 93 22 21 dest_image)
    (create-layer water_fire_image '(  1 9)  88 93 22 21 dest_image)
    (create-layer water_fire_image '(  2 8) 110 93 22 21 dest_image)
    (create-layer water_fire_image '(  3 7) 132 93 22 21 dest_image)
    (create-layer water_fire_image '(  4 8) 154 93 22 21 dest_image)
    (create-layer water_fire_image '(  5 7) 176 93 22 21 dest_image)
    (create-layer water_fire_image '(  6 8) 198 93 22 21 dest_image)
    (create-layer water_fire_image '(   10) 220 93 22 21 dest_image)

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
