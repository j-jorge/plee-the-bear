install( DIRECTORY "appdata" "applications" "icons" "pixmaps"
  DESTINATION "${CMAKE_INSTALL_PREFIX}/share/"
  FILE_PERMISSIONS
  OWNER_READ OWNER_WRITE
  GROUP_READ
  WORLD_READ 
  DIRECTORY_PERMISSIONS  OWNER_READ OWNER_WRITE OWNER_EXECUTE
  GROUP_READ GROUP_EXECUTE
  WORLD_READ WORLD_EXECUTE )

subdirs(locale man)

