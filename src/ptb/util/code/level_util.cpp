/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the level utility functions.
 * \author Julien Jorge
 */
#include "ptb/util/level_util.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the default thumbnail path for a given level path.
 * \param level_path The path to the .cl level file.
 */
std::string ptb::util::get_thumbnail( const std::string& level_path )
{
  std::string::size_type first = level_path.find_last_of('/');

  if ( first == std::string::npos )
    first = 0;
  else
    ++first;

  std::string::size_type dot = level_path.find_last_of('.');

  if ( (dot == std::string::npos) || (dot < first) )
    dot = level_path.length();

  std::string::size_type last =
    level_path.find_last_not_of("0123456789", dot-1);

  if ( (last == std::string::npos) || (last < first) )
    last = dot;
  else if ( level_path[last] == '-' )
    --last;

  return "gfx/thumb/" + level_path.substr(first, last - first + 1) + ".png";
} // get_thumbnail()
