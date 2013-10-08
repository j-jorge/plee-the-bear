/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This frame is shown to choose the game_options parameters.
 * \author Julien Jorge
 */
#ifndef __PTB_FRAME_GAME_OPTIONS_HPP__
#define __PTB_FRAME_GAME_OPTIONS_HPP__

#include "ptb/frame/frame.hpp"

namespace ptb
{
  /**
   * \brief This frame is shown to configure miscellaneous game options.
   * \author Julien Jorge
   */
  class frame_game_options:
    public frame
  {
  public:
    frame_game_options( windows_layer* in_layer );

  private:
    void create_controls();

    bear::gui::visual_component* create_checkbox( bear::visual::font f );
    bear::gui::visual_component* create_ok_button( bear::visual::font f );
    bear::gui::visual_component* create_cancel_button( bear::visual::font f );

    void save();

    void on_ok();
    void on_cancel();
    void on_friendly_fire_check();
    void on_friendly_fire_uncheck();

  }; // class frame_game_options
} // namespace ptb

#endif // __PTB_FRAME_GAME_OPTIONS_HPP__
