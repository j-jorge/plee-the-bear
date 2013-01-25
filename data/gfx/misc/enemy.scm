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

(define create-spike-ball
  (lambda (dest_image x y)

    (let ( (src_name "spike-ball.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )

        (let ( (top_spike 0)
               (three_quarter_spike 1)
               (middle_spike 2)
               (shadows 3)
               (black_cracks 4)
               (white_cracks 5)
               (ball 6) )

          (create-layer src_image 
                        (list top_spike three_quarter_spike middle_spike shadows
                              black_cracks white_cracks ball)
                        x y 117 117 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define

(define create-spike-ball-alt
  (lambda (dest_image x y)

    (let ( (src_name "spike-ball-front.xcf.bz2") )
      (let ( (src_image (car (gimp-file-load 1 src_name src_name))) )
        
        (let ( (top_spike 0)
               (three_quarter_spike 1)
               (middle_spike 2)
               (shadows 3)
               (black_cracks 4)
               (white_cracks 5)
               (ball 6) )

          (create-layer src_image 
                        (list top_spike three_quarter_spike middle_spike shadows
                              black_cracks white_cracks ball)
                        x y 117 117 dest_image)
          ) ; let
        ) ; let
      ) ; let
    ) ; lambda
  ) ; define

(let ( (dest_name "enemy.png") )
  (let ( (dest_image (new-image 256 128)) )

    (create-spike-ball dest_image 0 0)
    (create-spike-ball-alt dest_image 118 0 )
    
    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
