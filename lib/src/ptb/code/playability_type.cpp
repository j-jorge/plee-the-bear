/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::playability_type class.
 * \author Sébastien Angibaud
 */
#include "ptb/playability_type.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Convert an playability_type into its string representation.
 * \param a The value to convert.
 */
std::string ptb::playability_type::to_string( value_type a )
{
  std::string result;

  switch(a)
    {
    case one_player_only:   result = "one_player_only" ; break;
    case two_players_only:   result = "two_players_only" ; break;
    default:
      result = "one_or_two_players";
    }

  return result;
} // playability_type::to_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief Convert a string into an playability_type.
 * \param s The value to convert.
 */
ptb::playability_type::value_type
ptb::playability_type::from_string( const std::string& s )
{
  value_type a(one_or_two_players);

  if ( s == "one_player_only" )
    a = one_player_only;
  else if ( s == "two_players_only" )
    a = two_players_only;

  return a;
} // playability_type::from_string()
