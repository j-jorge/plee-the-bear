/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This frame is shown to choose a profile name.
 * \author Sebastien Angibaud.
 */
#ifndef __PTB_FRAME_PROFILE_NAME_HPP__
#define __PTB_FRAME_PROFILE_NAME_HPP__

#include "ptb/frame/frame.hpp"
#include "gui/text_input.hpp"

namespace ptb
{
  /**
   * \brief This frame is shown to choose a profile name.
   * \author Sebastien Angibaud.
   */
  class frame_profile_name:
    public frame
  {
  public:
    frame_profile_name( windows_layer* in_layer );

  private:
    void validate();

    void create_controls();
    bear::gui::visual_component* create_input();
    bear::gui::visual_component* create_back();
    bear::gui::visual_component* create_create();

  private:
    /** \brief The text control receiving the profile name. */
    bear::gui::text_input* m_profile_name;

  }; // class frame_profile_name
} // namespace ptb

#endif // __PTB_FRAME_PROFILE_NAME_HPP__
