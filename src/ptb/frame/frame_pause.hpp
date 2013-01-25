/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This frame is shown when the game is paused.
 * \author Julien Jorge
 */
#ifndef __PTB_FRAME_PAUSE_HPP__
#define __PTB_FRAME_PAUSE_HPP__

#include "ptb/frame/menu_frame.hpp"
#include "ptb/frame/message_box.hpp"

namespace ptb
{
  /**
   * \brief This frame is shown when the game is paused.
   * \author Julien Jorge
   */
  class frame_pause:
    public menu_frame
  {
  public:
    frame_pause( windows_layer* in_layer );

  private:
    bool on_close();
    void on_focus();

    void on_resume() const;
    void on_restart_level();
    void on_title_screen();
    void on_configuration();

    void create_controls();

  private:
    /** \brief The resulting value of a displayed message box. */
    message_box::flags m_msg_result;

  }; // class frame_pause
} // namespace ptb

#endif // __PTB_FRAME_PAUSE_HPP__
