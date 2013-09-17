/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This frame is the main menu of the game.
 * \author Julien Jorge
 */
#ifndef __PTB_FRAME_MAIN_MENU_HPP__
#define __PTB_FRAME_MAIN_MENU_HPP__

#include "ptb/frame/menu_frame.hpp"

#include "input/key_info.hpp"

namespace ptb
{
  /**
   * \brief This frame is the main menu of the game.
   * \author Julien Jorge
   */
  class frame_main_menu:
    public menu_frame
  {
  public:
    frame_main_menu( windows_layer* in_layer );

  private:
    bool on_key_press( const bear::input::key_info& key );
    bool on_button_press( bear::input::joystick::joy_code button,
                          unsigned int joy_index );

    void create_controls();

    bool on_close();
    void on_focus();
    void on_configuration();
    void on_game();
    void on_mini_game();
    void on_quit();

  private:
    /** \brief The index of the next key to read in the cheat code sequence. */
    unsigned int m_cheat_index;

    /** \brief The sequence to type on the keyboard to turn on the passwords. */
    static const bear::input::key_code s_keyboard_cheat[];

    /** \brief The sequence to type on the joystick to turn on the passwords. */
    static const bear::input::joystick::joy_code s_joystick_cheat[];

  }; // class frame_main_menu
} // namespace ptb

#endif // __PTB_FRAME_MAIN_MENU_HPP__
