/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::player_action class.
 * \author Julien Jorge
 */
#include "ptb/player_action.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Convert an action into its string representation.
 * \param a The action to convert.
 */
std::string ptb::player_action::to_string( value_type a )
{
  std::string result;

  switch(a)
    {
    case action_null:   result = "action_null" ; break;
    case die:           result = "die" ; break;
    case idle:          result = "idle" ; break;
    case move_left:     result = "move_left" ; break;
    case move_right:    result = "move_right" ; break;
    case jump:          result = "jump" ; break;
    case look_upward:   result = "look_upward" ; break;
    case crouch:        result = "crouch" ; break;
    case slap:          result = "slap" ; break;
    case throw_stone:   result = "throw_stone" ; break;
    case change_object: result = "change_object" ; break;
    case say:           result = "say" ; break;
    case get_camera:    result = "get_camera" ; break;
    case captive:       result = "captive" ; break;
    case release:       result = "release" ; break;
    case roar:          result = "roar" ; break;
    case disappear:     result = "disappear" ; break;
    case wait:          result = "wait" ; break;

    default:
      result = "not_an_action";
    }

  return result;
} // player_action::to_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief Convert a string into an action.
 * \param s The action to convert.
 */
ptb::player_action::value_type
ptb::player_action::from_string( const std::string& s )
{
  value_type a(action_null);

  if ( s == "die" )
    a = die;
  else if ( s == "idle" )
    a = idle;
  else if ( s == "move_left" )
    a = move_left;
  else if ( s == "move_right" )
    a = move_right;
  else if ( s == "jump" )
    a = jump;
  else if ( s == "look_upward" )
    a = look_upward;
  else if ( s == "crouch" )
    a = crouch;
  else if ( s == "slap" )
    a = slap;
  else if ( s == "throw_stone" )
    a = throw_stone;
  else if ( s == "change_object" )
    a = change_object;
  else if ( s == "say" )
    a = say;
  else if ( s == "get_camera" )
    a = get_camera;
  else if ( s == "captive" )
    a = captive;
  else if ( s == "release" )
    a = release;
  else if ( s == "roar" )
    a = roar;
  else if ( s == "disappear" )
    a = disappear;
  else if ( s == "wait" )
    a = wait;

  return a;
} // player_action::from_string()
