/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This frame is the configuration menu.
 * \author Julien Jorge
 */
#ifndef __PTB_FRAME_CONFIGURE_HPP__
#define __PTB_FRAME_CONFIGURE_HPP__

#include "ptb/frame/menu_frame.hpp"

namespace ptb
{
  /**
   * \brief This frame is the configuration menu.
   * \author Julien Jorge
   */
  class frame_configure:
    public menu_frame
  {
  public:
    frame_configure( windows_layer* in_layer );

  private:
    void create_controls();

    void on_first_player_controls();
    void on_second_player_controls();
    void on_game_options();
    void on_screen();
    void on_audio();
    void on_password();
    void on_back();

  }; // class frame_configure
} // namespace ptb

#endif // __PTB_FRAME_CONFIGURE_HPP__
