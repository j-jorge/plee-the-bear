/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Codes for user's requests requiring something from the GUI.
 * \author Julien Jorge
 */
#ifndef __PTB_GUI_COMMAND_HPP__
#define __PTB_GUI_COMMAND_HPP__

#include <string>

namespace ptb
{
  /**
   * \brief Codes for user's requests requiring something from the GUI.
   * \author Julien Jorge
   */
  struct gui_command
  {
  public:
    /** \brief The type of the codes. */
    typedef unsigned int value_type;

  public:
    static std::string to_string( value_type a );
    static value_type from_string( const std::string& s );

  public:
    /** \brief Bad action code. */
    static const value_type null_command = 0;

    /** \brief Request to pause the game. */
    static const value_type pause = null_command + 1;

    /** \brief Minimal value of the valid actions. */
    static const value_type min_value = pause;

    /** \brief Make the player to say something. */
    static const value_type talk = pause + 1;

    /** \brief Minimal value of the valid actions. */
    static const value_type max_value = talk;

  }; // struct gui_command
} // namespace ptb

#endif // __PTB_GUI_COMMAND_HPP__
