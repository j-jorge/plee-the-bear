/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This frame allow the user to make its player to say something.
 * \author Julien Jorge.
 */
#ifndef __PTB_FRAME_TALK_HPP__
#define __PTB_FRAME_TALK_HPP__

#include "ptb/frame/frame.hpp"
#include "gui/text_input.hpp"

namespace ptb
{
  /**
   * \brief This frame allow the user to make its player to say something.
   * \author Julien Jorge.
   */
  class frame_talk:
    public frame
  {
  public:
    frame_talk( windows_layer* in_layer, unsigned int player_index );

  private:
    bool on_key_press( const bear::input::key_info& key );
    void validate();

    void create_controls();
    bear::gui::visual_component* create_input();
    bear::gui::visual_component* create_close_button();

    virtual bool on_close();

  private:
    /** \brief The index of the talking player. */
    const unsigned int m_player_index;

    /** \brief The text control receiving the text. */
    bear::gui::text_input* m_text;

  }; // class frame_talk
} // namespace ptb

#endif // __PTB_FRAME_TALK_HPP__
