cmake_minimum_required(VERSION 2.6)
project(rp-launcher)

set( PTB_LAUNCHER_TARGET_NAME plee-the-bear )

include_directories( . ${BEAR_ENGINE_INCLUDE_DIRECTORY} )

#-------------------------------------------------------------------------------
# This sets up the exe icon for windows under mingw.

set( PTB_RESOURCES "" )

if(MINGW)
  set( PTB_RESOURCES "resources.rc")
  set(CMAKE_RC_COMPILER_INIT windres)
  ENABLE_LANGUAGE(RC)
  SET(
    CMAKE_RC_COMPILE_OBJECT
    "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>"
  )
endif()

#-------------------------------------------------------------------------------
set( PTB_LAUNCHER_SOURCE_FILES
  code/launcher.cpp
  code/main.cpp
  )

add_executable(
  ${PTB_LAUNCHER_TARGET_NAME}
  ${PTB_LAUNCHER_SOURCE_FILES}
  ${PTB_RESOURCES} )

set_target_properties(
  ${PTB_LAUNCHER_TARGET_NAME}
  PROPERTIES
  INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${PTB_INSTALL_CUSTOM_LIBRARY_DIR}"
  )

#-------------------------------------------------------------------------------
# Get the name of a given library on the system
macro( make_library_system_name ROOT_NAME RESULT )

  if( WIN32 )
    set( ${RESULT} "lib${ROOT_NAME}.dll" )
  else()
    set( ${RESULT} "lib${ROOT_NAME}.so" )
  endif()

endmacro()

#-------------------------------------------------------------------------------

make_library_system_name(
  "bear_generic_items" GENERIC_ITEM_LIBRARY_SYSTEM_NAME
)

make_library_system_name(
  "plee_the_bear" PTB_LIBRARY_SYSTEM_NAME
  )

if( NOT CMAKE_BUILD_TYPE STREQUAL "release" )
  set(
    PTB_COMPILE_DEFINITIONS
    "GENERIC_ITEMS_LIBRARY_DEBUG_PATH=${BEAR_ENGINE_LIBRARY_DIRECTORY}/${GENERIC_ITEM_LIBRARY_SYSTEM_NAME}"
    "PTB_LIBRARY_DEBUG_PATH=${PTB_EXECUTABLE_OUTPUT_PATH}/${PTB_LIBRARY_SYSTEM_NAME}"
    "PTB_DATA_DEBUG_DIRECTORY=${CMAKE_CURRENT_SOURCE_DIR}/../../data"
    )
endif()

if( PTB_TEXT_DOMAIN_PATH )
  set( PTB_TEXT_DOMAIN_PATH_DEF "PTB_TEXT_DOMAIN_PATH=${PTB_TEXT_DOMAIN_PATH}" )
endif()

if( BEAR_TEXT_DOMAIN_PATH )
  set(
    BEAR_TEXT_DOMAIN_PATH_DEF
    "BEAR_TEXT_DOMAIN_PATH=${BEAR_TEXT_DOMAIN_PATH}"
    )
endif()

if( WIN32 )
  set(
    PTB_COMPILE_DEFINITIONS
    "${PTB_COMPILE_DEFINITIONS}"
    "GENERIC_ITEMS_LIBRARY_PATH=${GENERIC_ITEM_LIBRARY_SYSTEM_NAME}"
    "PTB_LIBRARY_PATH=${PTB_LIBRARY_SYSTEM_NAME}"
    "PTB_DATA_DIRECTORY=../${PTB_INSTALL_DATA_DIR}"
    
    "BEAR_TEXT_DOMAIN_PATH=${CMAKE_INSTALL_PREFIX}/${TRANSLATIONS_INSTALL_DIR}"
    )
else()
  set(
    PTB_COMPILE_DEFINITIONS
    "${PTB_COMPILE_DEFINITIONS}"
    "GENERIC_ITEMS_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/${BEAR_ENGINE_INSTALL_LIBRARY_DIR}/${GENERIC_ITEM_LIBRARY_SYSTEM_NAME}"
    "PTB_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/${BEAR_ENGINE_INSTALL_LIBRARY_DIR}/${PTB_LIBRARY_SYSTEM_NAME}"
    "PTB_DATA_DIRECTORY=${CMAKE_INSTALL_PREFIX}/${PTB_INSTALL_DATA_DIR}"

    ${BEAR_TEXT_DOMAIN_PATH_DEF}
    ${PTB_TEXT_DOMAIN_PATH_DEF}
    )
endif()

set_target_properties(
  ${PTB_LAUNCHER_TARGET_NAME}
  PROPERTIES
  COMPILE_DEFINITIONS
  "${PTB_COMPILE_DEFINITIONS}"
  )

#-------------------------------------------------------------------------------
install(
  TARGETS ${PTB_LAUNCHER_TARGET_NAME}
  DESTINATION ${PTB_INSTALL_EXECUTABLE_DIR}
  )

set(
  PTB_LAUNCHER_LINK_LIBRARIES
  bear_engine
  ${CLAW_APPLICATION_LIBRARIES}
  )

if(WIN32)
  set(
    PTB_LAUNCHER_LINK_LIBRARIES
    ${PTB_LAUNCHER_LINK_LIBRARIES}
    ${SDL_LIBRARY}
    intl )
endif(WIN32)

# FIXME: it would be even better to use "sdl-config"
if(APPLE)
  set(
    PTB_LAUNCHER_LINK_LIBRARIES
    ${PTB_LAUNCHER_LINK_LIBRARIES}
    ${SDL_LIBRARY}
    SDLmain
    intl )
endif(APPLE)

target_link_libraries(
  ${PTB_LAUNCHER_TARGET_NAME}
  ${PTB_LAUNCHER_LINK_LIBRARIES}
  )
