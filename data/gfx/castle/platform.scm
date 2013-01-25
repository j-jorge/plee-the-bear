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

(load "platform-sprites.scm")

(let ( (dest_name "platform.png") )
  (let ( (dest_image (new-image-max 256 512)) )

    (platform-sprite 0 0 0 256 104 dest_image ".")
    (platform-sprite 1 0 105 256 104 dest_image ".")
    (platform-sprite 2 0 210 256 104 dest_image ".")
    (platform-sprite 3 0 315 256 104 dest_image ".")

    (save-frames-and-exit dest_name dest_image)
    ) ; let
  ) ; let
