/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Code values of the player's actions.
 * \author Julien Jorge
 */
#ifndef __PTB_PLAYER_ACTION_HPP__
#define __PTB_PLAYER_ACTION_HPP__

#include <string>

namespace ptb
{
  /**
   * \brief Code values of the player's actions.
   * \author Julien Jorge
   */
  struct player_action
  {
  public:
    /** \brief The type of the codes for the actions. */
    typedef unsigned int value_type;

  public:
    static std::string to_string( value_type a );
    static value_type from_string( const std::string& s );

  public:
    /** \brief Bad action code. */
    static const value_type action_null = 0;

    /** \brief Action code dying. */
    static const value_type die = action_null + 1;

    /** \brief Minimal value of the valid actions. */
    static const value_type min_value = die;

    /** \brief Action code: Idle. */
    static const value_type idle = die + 1;

    /** \brief Action code: Move to the left. */
    static const value_type move_left = idle + 1;

    /** \brief Action code: Move to the right. */
    static const value_type move_right = move_left + 1;

    /** \brief Action code: Jump. */
    static const value_type jump = move_right + 1;

    /** \brief Action code: Look up. */
    static const value_type look_upward = jump + 1;

    /** \brief Action code: Crouch. */
    static const value_type crouch = look_upward + 1;

    /** \brief Action code: Slap. */
    static const value_type slap = crouch + 1;

    /** \brief Action code: Throw a stone. */
    static const value_type throw_stone = slap + 1;

    /** \brief Action code: Change the current object. */
    static const value_type change_object = throw_stone + 1;

    /** \brief Action code: Say something. */
    static const value_type say = change_object + 1;

    /** \brief Action code: Set the camera on the player. */
    static const value_type get_camera = say + 1;

    /** \brief Action code: captive the player. */
    static const value_type captive = get_camera + 1;

    /** \brief Action code: Release player. */
    static const value_type release = captive + 1;

    /** \brief Action code: The player roar. */
    static const value_type roar = release + 1;

    /** \brief Action code: The player disappear. */
    static const value_type disappear = roar + 1;

    /** \brief Action code: The player wait. */
    static const value_type wait = disappear + 1;

    /** \brief Maximal value of the valid actions. */
    static const value_type max_value = wait;

  }; // struct player_action
} // namespace ptb

#endif // __PTB_PLAYER_ACTION_HPP__
