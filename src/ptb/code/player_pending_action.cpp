/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::player_pending_action class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_pending_action.hpp"
#include <sstream>
#include <vector>
#include <claw/string_algorithm.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::player_pending_action::player_pending_action()
  : pending_type(start_action), date(0), player_index(0), 
    action(player_action::action_null), duration(0)
{

} // player_pending_action::player_pending_action

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::player_pending_action::player_pending_action
( player_pending_action_type t, bear::universe::time_type d, 
  unsigned int index, player_action::value_type a, 
  bear::universe::time_type dur)
  : pending_type(t), date(d), player_index(index), 
    action(a), duration(dur)
{
  
} // player_pending_action::player_pending_action

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::player_pending_action::player_pending_action( const std::string & str )
{
  std::vector<std::string> params;
  
  claw::text::split(params, str, '|');
  if ( params.size() == 5 ) 
    {
      size_t t;
      std::istringstream iss0(params[0]);
      iss0 >> t;
      if ( t == start_action ) 
	pending_type = start_action;
      else if ( t == stop_action ) 
	pending_type = stop_action;
      else
	pending_type = do_action;
      
      std::istringstream iss1(params[1]);
      iss1 >> date; 
      
      std::istringstream iss2(params[2]);
      iss2 >> player_index; 
      
      std::istringstream iss3(params[3]);
      iss3 >> action; 
      
      std::istringstream iss4(params[4]);
      iss4 >> duration;
    }
} // player_pending_action::player_pending_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
std::string ptb::player_pending_action::to_string() const
{
  std::stringstream out;
  out << pending_type << "|" << date << "|" << player_index 
      << "|" << action << "|" << duration;
  
  return out.str();  
} // player_pending_action::to_string()
