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

(let ( (src_name "level_name-42x50.xcf.bz2")
       (dest_name "level_name-42x50.png") )
  (let ( (src_image (car (gimp-file-load 1 src_name src_name)))
         (dest_image (new-image 512 256)) )

    (create-layer src_image   '(0)   0   0 42 50 dest_image) ; A
    (create-layer src_image   '(1)  42   0 42 50 dest_image) ; B
    (create-layer src_image   '(2)  84   0 42 50 dest_image) ; C
    (create-layer src_image   '(3) 126   0 42 50 dest_image) ; D
    (create-layer src_image   '(4) 168   0 42 50 dest_image) ; E
    (create-layer src_image   '(5) 210   0 42 50 dest_image) ; F
    (create-layer src_image   '(6) 252   0 42 50 dest_image) ; G
    (create-layer src_image   '(7) 294   0 42 50 dest_image) ; H
    (create-layer src_image   '(8) 336   0 42 50 dest_image) ; I
    (create-layer src_image   '(9) 378   0 42 50 dest_image) ; J
    (create-layer src_image  '(10) 420   0 42 50 dest_image) ; K
    (create-layer src_image  '(11) 462   0 42 50 dest_image) ; L
    (create-layer src_image  '(12)   0  50 42 50 dest_image) ; M
    (create-layer src_image  '(13)  42  50 42 50 dest_image) ; N
    (create-layer src_image  '(14)  84  50 42 50 dest_image) ; O
    (create-layer src_image  '(15) 126  50 42 50 dest_image) ; P
    (create-layer src_image  '(16) 168  50 42 50 dest_image) ; Q
    (create-layer src_image  '(17) 210  50 42 50 dest_image) ; R
    (create-layer src_image  '(18) 252  50 42 50 dest_image) ; S
    (create-layer src_image  '(19) 294  50 42 50 dest_image) ; T
    (create-layer src_image  '(20) 336  50 42 50 dest_image) ; U
    (create-layer src_image  '(21) 378  50 42 50 dest_image) ; V
    (create-layer src_image  '(22) 420  50 42 50 dest_image) ; W
    (create-layer src_image  '(23) 462  50 42 50 dest_image) ; X
    (create-layer src_image  '(24)   0 100 42 50 dest_image) ; Y
    (create-layer src_image  '(25)  42 100 42 50 dest_image) ; Z
    (create-layer src_image  '(26)  84 100 42 50 dest_image) ; Ê
    (create-layer src_image  '(27) 126 100 42 50 dest_image) ; Æ
    (create-layer src_image  '(28) 168 100 42 50 dest_image) ; 1
    (create-layer src_image  '(29) 210 100 42 50 dest_image) ; 2
    (create-layer src_image  '(30) 252 100 42 50 dest_image) ; 3
    (create-layer src_image  '(31) 294 100 42 50 dest_image) ; 4
    (create-layer src_image  '(32) 336 100 42 50 dest_image) ; 5
    (create-layer src_image  '(33) 378 100 42 50 dest_image) ; 6
    (create-layer src_image  '(34) 420 100 42 50 dest_image) ; 7
    (create-layer src_image  '(35) 462 100 42 50 dest_image) ; 8
    (create-layer src_image  '(36)   0 150 42 50 dest_image) ; 9
    (create-layer src_image  '(37)  42 150 42 50 dest_image) ; 0
    (create-layer src_image  '(38) 126 150 42 50 dest_image) ; È
    (create-layer src_image  '(39) 168 150 42 50 dest_image) ; É
    (create-layer src_image  '(40) 210 150 42 50 dest_image) ; -
    (create-layer src_image  '(41) 252 150 42 50 dest_image) ; Å
    (create-layer src_image  '(42) 294 150 42 50 dest_image) ; Ø
    (create-layer src_image  '(43) 336 150 42 50 dest_image) ; Î
    
    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
