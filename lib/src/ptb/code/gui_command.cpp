/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::gui_command class.
 * \author Julien Jorge
 */
#include "ptb/gui_command.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Convert an action into its string representation.
 * \param a The action to convert.
 */
std::string ptb::gui_command::to_string( value_type a )
{
  std::string result;

  switch(a)
    {
    case null_command: result = "null_command" ; break;
    case pause:        result = "pause" ; break;
    case talk:         result = "talk" ; break;
    default:
      result = "not_a_command";
    }

  return result;
} // gui_command::to_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief Convert a string into an action.
 * \param s The action to convert.
 */
ptb::gui_command::value_type
ptb::gui_command::from_string( const std::string& s )
{
  value_type a(null_command);

  if ( s == "pause" )
    a = pause;
  else if ( s == "talk" )
    a = talk;

  return a;
} // gui_command::from_string()
