/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The ingame_menu_layer is a layer containing the windows shown during
 *        the game (levels).
 * \author Julien Jorge
 */
#ifndef __PTB_INGAME_MENU_LAYER_HPP__
#define __PTB_INGAME_MENU_LAYER_HPP__

#include "ptb/layer/windows_layer.hpp"

namespace ptb
{
  /**
   * \brief The ingame_menu_layer is a layer containing the windows shown during
   *        the game (levels).
   * \author Julien Jorge
   */
  class ingame_menu_layer:
    public windows_layer
  {
  public:
    /** \brief The type of the parent class. */
    typedef windows_layer super;

  public:
    ingame_menu_layer( const std::string& name );

    bool key_pressed( const bear::input::key_info& key );
    bool button_pressed
    ( bear::input::joystick::joy_code button, unsigned int joy_index );
    bool mouse_pressed
    ( bear::input::mouse::mouse_code button,
      const claw::math::coordinate_2d<unsigned int>& pos );

    virtual bool process_score_message( const score_message& msg );

  private:
    bool pause( unsigned int player_index );
    bool talk( unsigned int player_index );

  }; // class ingame_menu_layer
} // namespace ptb

#endif // __PTB_INGAME_MENU_LAYER_HPP__
