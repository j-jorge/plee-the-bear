/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This frame is shown to choose the screen parameters.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_FRAME_SCREEN_HPP__
#define __PTB_FRAME_SCREEN_HPP__

#include "ptb/frame/frame.hpp"

namespace ptb
{
  /**
   * \brief This frame is shown to choose the screen parameters.
   * \author Sebastien Angibaud
   */
  class frame_screen:
    public frame
  {
  public:
    typedef frame super;

  public:
    frame_screen( windows_layer* in_layer );

  private:
    void create_controls();
    bear::gui::visual_component* create_checkbox();
    bear::gui::visual_component* create_ok_button();
    bear::gui::visual_component* create_cancel_button();

    bool on_ok();
    bool on_cancel();
    bool on_close();

  private:
    /* \brief The full screen mode when the frame is shown. */
    const bool m_saved_mode;

    /** \brief Indicates if ok button has been pressed. */
    bool m_ok_is_pressed;
  }; // class frame_screen
} // namespace ptb

#endif // __PTB_FRAME_SCREEN_HPP__
