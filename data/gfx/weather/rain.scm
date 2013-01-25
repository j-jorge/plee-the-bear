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

(let ( (src_name "rain.xcf.bz2")
       (dest_name "rain.png")
       (intro_dest_name "rain-light.png")
       (medium_dest_name "rain-medium.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (car (gimp-image-new 512 512 RGB)))
         (intro_dest_image (car (gimp-image-new 512 512 RGB)))
         (medium_dest_image (car (gimp-image-new 512 512 RGB)))
         )
    (let loop_y ((y 0))
      (unless (= y 512)
              (let loop_x ((x 0))
                (unless (= x 512)
                        (begin
                          (create-layer src_image '(0 1) x y 64 64 dest_image)
                          (create-layer src_image '(0 1)
                                        (+ x 64) y 64 64 dest_image)
                          (create-layer src_image '(0 1)
                                        x (+ y 64) 64 64 dest_image)
                          (create-layer src_image '(0 1)
                                        (+ x 64) (+ y 64) 64 64 dest_image)
                          (shift-layers src_image '(0 1) -8 8)
                          ) ; begin
                        (loop_x (+ x 128))
                        ) ; unless
                ) ; let
              (loop_y (+ y 128))
              ) ; unless
      ) ; let
    
    (let loop_y ((y 0))
      (unless (= y 512)
              (let loop_x ((x 0))
                (unless (= x 512)
                        (begin
                          (create-layer src_image '(0) x y 32 32
                                        intro_dest_image)
                          (create-layer src_image '(0)
                                        (+ x 32) y 32 32 intro_dest_image)
                          (create-layer src_image '(0)
                                        (+ x 64) y 32 32 intro_dest_image)
                          (create-layer src_image '(0)
                                        (+ x 96) y 32 32 intro_dest_image)

                          (create-layer src_image '(0)
                                        x (+ y 32) 32 32 intro_dest_image)
                          (create-layer src_image '(0)
                                        (+ x 32) (+ y 32) 32 32
                                        intro_dest_image)
                          (create-layer src_image '(0)
                                        (+ x 64) (+ y 32) 32 32
                                        intro_dest_image)
                          (create-layer src_image '(0)
                                        (+ x 96) (+ y 32) 32 32
                                        intro_dest_image)

                          (create-layer src_image '(0)
                                        x (+ y 64) 32 32 intro_dest_image)
                          (create-layer src_image '(0)
                                        (+ x 32) (+ y 64) 32 32
                                        intro_dest_image)
                          (create-layer src_image '(0)
                                        (+ x 64) (+ y 64) 32 32
                                        intro_dest_image)
                          (create-layer src_image '(0)
                                        (+ x 96) (+ y 64) 32 32
                                        intro_dest_image)

                          (create-layer src_image '(0)
                                        x (+ y 96) 32 32 intro_dest_image)
                          (create-layer src_image '(0)
                                        (+ x 32) (+ y 96) 32 32
                                        intro_dest_image)
                          (create-layer src_image '(0)
                                        (+ x 64) (+ y 96) 32 32
                                        intro_dest_image)
                          (create-layer src_image '(0)
                                        (+ x 96) (+ y 96) 32 32
                                        intro_dest_image)

                          (shift-layers src_image '(0) -8 8)
                          ) ; begin
                        (loop_x (+ x 128))
                        ) ; unless
                ) ; let
              (loop_y (+ y 128))
              ) ; unless
      ) ; let

    (let loop_y ((y 0))
      (unless (= y 512)
              (let loop_x ((x 0))
                (unless (= x 512)
                        (begin
                          (create-layer src_image '(2) x y 64 64
                                        medium_dest_image)
                          (create-layer src_image '(2)
                                        (+ x 64) y 64 64 medium_dest_image)
                          (create-layer src_image '(2)
                                        x (+ y 64) 64 64 medium_dest_image)
                          (create-layer src_image '(2)
                                        (+ x 64) (+ y 64) 64 64
                                        medium_dest_image)

                          (shift-layers src_image '(2) -8 8)
                          ) ; begin
                        (loop_x (+ x 128))
                        ) ; unless
                ) ; let
              (loop_y (+ y 128))
              ) ; unless
      ) ; let

    (save-frames dest_name dest_image)
    (save-frames medium_dest_name medium_dest_image)
    (save-frames-and-exit intro_dest_name intro_dest_image)
    ) ; let
  ) ; let

