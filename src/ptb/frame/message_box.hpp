/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This frame displays a message.
 * \author Julien Jorge
 */
#ifndef __PTB_MESSAGE_BOX_HPP__
#define __PTB_MESSAGE_BOX_HPP__

#include "ptb/frame/frame.hpp"

namespace ptb
{
  /**
   * \brief This frame displays a message.
   * \author Julien Jorge
   */
  class message_box:
    public frame
  {
  public:
    typedef unsigned int flags;

  public:
    message_box( windows_layer* in_layer, const std::string& msg,
                 flags* buttons = NULL );

  private:
    void on_ok();
    void on_cancel();

    void create_controls( const std::string& msg );
    bear::gui::visual_component* create_text( const std::string& msg );
    bear::gui::visual_component* create_ok_button();
    bear::gui::visual_component* create_cancel_button();

  public:
    /** \brief Flag of the 'ok' button. */
    static const flags s_ok;

    /** \brief Flag of the 'cancel' button. */
    static const flags s_cancel;

  private:
    /** \brief The flags of the selected buttons. Serves also as result. */
    flags* m_flags;

  }; // class message_box
} // namespace ptb

#endif // __PTB_MESSAGE_BOX_HPP__
