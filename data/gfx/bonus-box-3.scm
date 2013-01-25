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

(let ( (bonus_name "bonus-box.xcf.bz2")
       (dest_name "bonus-box-3.png") )
  (let ( (bonus_image (car (gimp-file-load 1 bonus_name bonus_name)))
         (dest_image (new-image 256 256)) )

    (let ( (air_plinth 2)
           (life_plinth 4)
           (energy_plinth 5)
           (plinth 7)
           (glass 8)
           (air 9)
           (plee 10)
           (energy_5 19)
           (energy_4 20)
           (energy_3 21)
           (energy_2 22)
           (energy_1 23)
           (energy_0 24)
           (pot 33)
           (broken_glass 34)
           (broken_glass_top 35) )

      ; energy
      (create-layer bonus_image (list energy_0)
                    0 0 60 80 dest_image)
      (create-layer bonus_image (list energy_1)
                    60 0 60 80 dest_image)
      (create-layer bonus_image (list energy_2)
                    120 0 60 80 dest_image)
      (create-layer bonus_image (list energy_3)
                    180 0 60 80 dest_image)
      (create-layer bonus_image (list energy_4)
                    0 80 60 80 dest_image)
      (create-layer bonus_image (list energy_5)
                    60 80 60 80 dest_image)

      (gimp-context-set-foreground '(0 183 191) )
      (let ( (color_layer
              (car (gimp-layer-new dest_image 256 256 RGBA-IMAGE "color" 100
                                   HUE-MODE)))
             )
        (gimp-image-add-layer dest_image color_layer -1)
        (gimp-selection-invert dest_image)

        (gimp-edit-bucket-fill color_layer FG-BUCKET-FILL NORMAL-MODE 100 0
                               FALSE 0 0)
                                        ; 100 is the opacity of the final bucket
                                        ; 0 is the threshold (not used)
                                        ; 1 tells to use the composite image
                                        ; 0 is the x coordinate of the fill
                                        ; 0 is the y coordinate of the fill
        (gimp-selection-invert dest_image)
        ) ; color_layer

      ; boxes
      (create-layer bonus_image (list energy_plinth glass)
                    0 0 60 80 dest_image)
      (create-layer bonus_image (list energy_plinth glass)
                    60 0 60 80 dest_image)
      (create-layer bonus_image (list energy_plinth glass)
                    120 0 60 80 dest_image)
      (create-layer bonus_image (list energy_plinth glass)
                    180 0 60 80 dest_image)
      (create-layer bonus_image (list energy_plinth glass)
                    0 80 60 80 dest_image)
      (create-layer bonus_image (list energy_plinth glass)
                    60 80 60 80 dest_image)

      ) ; let

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
