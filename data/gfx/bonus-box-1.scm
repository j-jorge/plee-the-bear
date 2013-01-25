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
(load "../common.scm")

(let ( (src_name "bonus-box.xcf.bz2")
       (dest_name "bonus-box-1.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (new-image 256 256)) )

    (let ( (water_plinth 0)
           (fire_plinth 1)
           (stone_plinth 3)
           (invincibility_plinth 6)
           (glass 8)
           (stones 11)
           (more_stones 12)
           (water_1 13)
           (water_2 14)
           (water_3 15)
           (fire_3 16)
           (fire_2 17)
           (fire_1 18)
           (invincibility_4 25)
           (invincibility_3 26)
           (invincibility_2 27)
           (invincibility_1 28)
           (statue          29)
           (water_pot 30)
           (fire_pot 31)
           (air_pot 32)
           (pot 33) )

      ; water
      (create-layer src_image (list water_plinth glass water_1 pot)
                    0  0 60 80 dest_image)
      (create-layer src_image (list water_plinth glass water_2 pot)
                    60  0 60 80 dest_image)
      (create-layer src_image (list water_plinth glass water_3 pot)
                    120  0 60 80 dest_image)

      ; stones
      (create-layer src_image (list stone_plinth glass stones)
                    180  0 60 80 dest_image)

      ; more stones
      (create-layer src_image (list stone_plinth glass more_stones)
                    0 80 60 80 dest_image)

      ; fire
      (create-layer src_image (list fire_plinth glass fire_1 pot)
                     60  80 60 80 dest_image)
      (create-layer src_image (list fire_plinth glass fire_2 pot)
                    120  80 60 80 dest_image)
      (create-layer src_image (list fire_plinth glass fire_3 pot)
                    180  80 60 80 dest_image)

      ; invincibility
      (create-layer src_image
                    (list invincibility_plinth glass statue invincibility_1)
                    0 160 60 80 dest_image)
      (create-layer src_image
                    (list invincibility_plinth glass statue invincibility_2)
                    60 160 60 80 dest_image)
      (create-layer src_image
                    (list invincibility_plinth glass statue invincibility_3)
                    120 160 60 80 dest_image)
      (create-layer src_image
                    (list invincibility_plinth glass statue invincibility_4)
                    180 160 60 80 dest_image)
    
      ; water pot
      (create-layer-crop src_image (list water_pot)
                         39 54 37 39
                         0 240 15 16 dest_image (list) )

      ; fire pot
      (create-layer-crop src_image (list fire_pot)
                         39 54 37 39
                         15 240 15 16 dest_image (list) )

      ; air pot
      (create-layer-crop src_image (list air_pot)
                         39 54 37 39
                         30 240 15 16 dest_image (list) )
      ) ; let

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
