cmake_minimum_required(VERSION 2.6)
project(plee-the-bear)

set( GAME_ROOT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" )

#-------------------------------------------------------------------------------
if( NOT DEFINED BEAR_ROOT_DIRECTORY )

  #The path to the directory containing the source code of the Bear engine.
  set(
    BEAR_ROOT_DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/../bear"
    )
endif()

set( CMAKE_MODULE_PATH "${BEAR_ROOT_DIRECTORY}/cmake-helper" )

include( bear-config )
include( gettext )
include( compiler-defaults )
include( docbook-to-man )

#-------------------------------------------------------------------------------
# where the game resources are installed
if( NOT PTB_INSTALL_DATA_DIR )
  set( PTB_INSTALL_DATA_DIR share/plee-the-bear )
endif( NOT PTB_INSTALL_DATA_DIR )

# where the game executables are installed
if( NOT PTB_INSTALL_EXECUTABLE_DIR )
  set( PTB_INSTALL_EXECUTABLE_DIR bin )
endif( NOT PTB_INSTALL_EXECUTABLE_DIR )

# where the game libraries (the items) are installed
if( NOT PTB_INSTALL_CUSTOM_LIBRARY_DIR )
  if( WIN32 )
    set( PTB_INSTALL_CUSTOM_LIBRARY_DIR
      "${PTB_INSTALL_EXECUTABLE_DIR}"
      )
  else( WIN32 )
    set( PTB_INSTALL_CUSTOM_LIBRARY_DIR lib )
  endif( WIN32 )
endif( NOT PTB_INSTALL_CUSTOM_LIBRARY_DIR )

# Directories where the executable and libraries are built
set( PTB_EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin" )
set( PTB_LIBRARY_OUTPUT_PATH "${PTB_EXECUTABLE_OUTPUT_PATH}" )

set( EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin" )
set( LIBRARY_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}" )

# common flags
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )

#-------------------------------------------------------------------------------
# check SDL
include( FindSDL )

if( NOT SDL_FOUND )
  message( FATAL_ERROR "SDL lbrary must be installed." )
else( NOT SDL_FOUND )
  #-----------------------------------------------------------------------------
  # Include directories for SDL
  include_directories(
    ${SDL_INCLUDE_DIR}
    )
endif( NOT SDL_FOUND )

#-------------------------------------------------------------------------------
# check SDL::mixer
include( FindSDL_mixer )

if( NOT SDLMIXER_FOUND )
  message( FATAL_ERROR "SDL_mixer lbrary must be installed." )
else( NOT SDLMIXER_FOUND )
  #-----------------------------------------------------------------------------
  # Include directories for all these libraries
  include_directories(
    ${SDLMIXER_INCLUDE_DIR}
    )
endif( NOT SDLMIXER_FOUND )

#-------------------------------------------------------------------------------
# various libraries

#-------------------------------------------------------------------------------
# Claw
find_package( libclaw 1.7.4 )

#-------------------------------------------------------------------------------
# Include directories for Claw
include_directories(
  ${CLAW_INCLUDE_DIRECTORY}
  ${CLAW_GRAPHIC_INCLUDE_DIRECTORY}
  )

#-------------------------------------------------------------------------------
# Link directories for Claw
link_directories(
  ${CLAW_LINK_DIRECTORY}
  ${CLAW_GRAPHIC_LINK_DIRECTORY}
  )

#-------------------------------------------------------------------------------
# Boost
include(FindBoost)

find_package( Boost 1.46 REQUIRED COMPONENTS signals)

if( NOT Boost_FOUND )
  message( FATAL_ERROR 
    "You must have boost::signals library installed (at least 1.46)" )
endif( NOT Boost_FOUND )

#-------------------------------------------------------------------------------
# Include directories for Boost
include_directories(
  ${Boost_INCLUDE_DIR}
  )

#-------------------------------------------------------------------------------
# Link directories for Boost
link_directories(
  ${Boost_LIBRARY_DIRS}
  )

#-------------------------------------------------------------------------------
# Link directories for the game
link_directories(
  ${LIBRARY_OUTPUT_PATH}
  )

#-------------------------------------------------------------------------------
include_directories( "${BEAR_ENGINE_INCLUDE_DIRECTORY}" )
include_directories( "${BEAR_ITEMS_INCLUDE_DIRECTORY}" )

# Link directories for the Bear engine
link_directories(
  ${BEAR_ENGINE_LIBRARY_DIRECTORY}
  )

#-------------------------------------------------------------------------------
if( RP_TAG )
  add_definitions( "-DRP_TAG=${RP_TAG}" )
endif()

#-------------------------------------------------------------------------------
subdirs(
  launcher
  lib
  data
  desktop
  )

install(
  DIRECTORY "lib/item-description"
  DESTINATION "share/bear-factory/plee-the-bear"
  FILE_PERMISSIONS OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ
  DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE
  PATTERN "*~" EXCLUDE
)

if(UNIX)

  IF(APPLE)
    SET(DYLIB_EXTENSION "dylib")
  ELSE(APPLE)
    SET(DYLIB_EXTENSION "so")
  ENDIF(APPLE)
  
endif(UNIX)
