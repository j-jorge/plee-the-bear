/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A message that adds a notification in the status layer.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATUS_LAYER_NOTIFICATION_MESSAGE_HPP__
#define __PTB_STATUS_LAYER_NOTIFICATION_MESSAGE_HPP__

#include "ptb/layer/status_layer.hpp"

#include "communication/typed_message.hpp"
#include "visual/sprite.hpp"

namespace ptb
{
  class monster;
  class status_layer;

  /**
   * \brief A message that adds a notification in the status layer.
   * \author Sebastien Angibaud
   */
  class status_layer_notification_message:
    public bear::communication::typed_message<status_layer>
  {
  public:
    status_layer_notification_message();

    void set_notification
    ( unsigned int index, const bear::visual::sprite& picture, 
      const std::string& m_text );
    bool apply_to( status_layer& that );

  private:
    /** \brief The index of player that sends notification. */
    unsigned int m_index;

    /** \brief The notification. */
    std::string m_text;

    /** \brief The picture to display. */
    bear::visual::sprite m_picture;
  }; // class status_layer_notification_message
} // namespace ptb

#endif // __PTB_STATUS_LAYER_NOTIFICATION_MESSAGE_HPP__
