/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This frame is shown to choose a profile.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_FRAME_PROFILES_HPP__
#define __PTB_FRAME_PROFILES_HPP__

#include "ptb/frame/frame.hpp"
#include "gui/radio_group.hpp"
#include "ptb/frame/message_box.hpp"

namespace ptb
{
  /**
   * \brief This frame is shown to choose a profile.
   * \author Sebastien Angibaud
   */
  class frame_profiles:
    public frame
  {
  public:
    frame_profiles( windows_layer* in_layer );
    void on_focus();

  private:
    void create_controls();
    bear::gui::radio_group*
    create_profiles_radio_buttons( bear::visual::font f );
    bear::gui::visual_component* create_ok_button( bear::visual::font f );
    bear::gui::visual_component* create_back_button( bear::visual::font f );
    bear::gui::visual_component* create_remove_button( bear::visual::font f );

    bool on_ok();
    bool on_back();
    bool on_remove();

    void update_controls();
    void select_current_profile();

  private:
    /** \brief Radio group to select a uniq profile. */
    bear::gui::radio_group* m_profiles;

    /** \brief Radio buttons to select a profile. */
    std::vector<bear::gui::radio_button*> m_profile_radio_buttons;

    /** \brief The resulting value of a displayed message box. */
    message_box::flags m_msg_result;
  }; // class frame_profiles
} // namespace ptb

#endif // __PTB_FRAME_PROFILES_HPP__
