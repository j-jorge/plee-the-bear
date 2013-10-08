/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A class that contains informations about differed action.
 * \author Sebastien angibaud
 */

#ifndef __PTB_PLAYER_PENDING_ACTION_HPP__
#define __PTB_PLAYER_PENDING_ACTION_HPP__

#include "ptb/player_action.hpp"
#include "universe/types.hpp"

namespace ptb
{
  /**
   * \brief A class that contains informations about differed action.
   * \author Sebastien angibaud
   */
  class player_pending_action
  {
  public:
    enum player_pending_action_type
      {
        start_action = 0,
        stop_action,
	do_action
      }; // enum player_pending_action_type
    
  public:
    player_pending_action();
    player_pending_action
    ( player_pending_action_type t, bear::universe::time_type d, 
      unsigned int index, player_action::value_type a, 
      bear::universe::time_type dur );
    player_pending_action( const std::string & str );

    std::string to_string() const;

  public:
    /** \brief The type of pending. */
    player_pending_action_type pending_type;
    
    /** \brief date of the action. */
    bear::universe::time_type date;
    
    /** \brief Index of player. */
    unsigned int player_index;

    /** \brief The action. */
    player_action::value_type action;
    
    /** \brief The duration of the action. */
    bear::universe::time_type duration;
  }; // class player_pending_action
} // namespace ptb

#endif // __PTB_PLAYER_PENDING_ACTION_HPP__
