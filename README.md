What is this?
====

Plee the Bear is a platform game in which you play an angry bear whose
son has been kidnapped by god. Here is a guy hard to brave! Jump in
this amazing journey to find and rescue your son. Because you want to
rescue him, don't you? Or to slap him? Maybe both….

How to build the project?
====

The game relies upon the Bear engine. I would suggest that you prepare
a workspace as follows:

    mkdir plee-the-bear-build
    cd plee-the-bear-build
    git clone https://github.com/j-jorge/bear.git
    git clone https://github.com/j-jorge/plee-the-bear.git

You should now have two subdirectories named `bear` and
`plee-the-bear` in the current directory. Create a file name
`CMakeLists.txt` beside them, with the following content:

    cmake_minimum_required(VERSION 2.6)
    
    if( NOT DEFINED BEAR_ROOT_DIRECTORY )
      set( BEAR_ROOT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bear" )
    endif()
    
    set( CMAKE_MODULE_PATH "${BEAR_ROOT_DIRECTORY}/cmake-helper" )
    
    include( uninstall )
    
    subdirs( bear plee-the-bear )
  
We use CMake as the build system (http://www.cmake.org/). You will
also need a C++ compiler and the following libraries in order to build
the game:

- Boost: http://www.boost.org,
- SDL: http://www.libsdl.org,
- Claw: http://libclaw.sourceforge.net,
- Gettext: http://www.gnu.org/software/gettext/,
- FreeType: http://www.freetype.org/,
- wxWidgets (for the editors): http://www.wxwidgets.org/.

Once everything is installed, build the game by typing the following
commands:

    cmake . -DCMAKE_BUILD_TYPE=release -DCMAKE_INSTALL_PREFIX=/usr
    make
    sudo make install
    
The default installation prefix is `/usr/local`. You can set another
prefix by defining `CMAKE_INSTALL_PREFIX` as shown above.

If you want to hack or debug the game, I would suggest to define
`CMAKE_BUILD_TYPE=debug`, not to `make install` and to run the game
using the `plee-the-bear` script from `plee-the-bear` folder.

Where to get help?
====

Issues should be reported on the projects page on GitHub:
https://github.com/j-jorge/plee-the-bear

For general questions, send an email to julien.jorge@stuff-o-matic.com. 

Legal information
====

The software is licensed under the version 3 of the GNU GPL. All
multimedia resources are provided under the terms of the version 3 of
the Creative Commons license, with attribution and share-alike clauses
(CC-by-sa).

See the accompanying LICENSE file for details.
