/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::status_layer_notification_message class.
 * \author Sebastien Angibaud
 */
#include "ptb/message/status_layer_notification_message.hpp"

#include "ptb/layer/status_layer.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::status_layer_notification_message::status_layer_notification_message()
{

} // status_layer_notification_message::status_layer_notification_message()

/*----------------------------------------------------------------------------*/
/*
 * \brief Set the notification.
 * \param Index of the player.
 * \param picture The picture to display
 * \parama text The notification.
 */
void ptb::status_layer_notification_message::set_notification
( unsigned int index, 
  const bear::visual::sprite& picture, const std::string& text )
{
  m_index = index;
  m_picture = picture;
  m_text = text;
} // status_layer_notification_message::set_notification()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the message to the status layer.
 * \param that The status layer to apply the message to.
 */
bool ptb::status_layer_notification_message::apply_to( status_layer& that )
{
   that.add_notification(m_index, m_text, m_picture);

  return true;
} // status_layer_notification_message::apply_to()
