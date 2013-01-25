/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::notification_toggle class.
 * \author Julien Jorge
 */
#include "ptb/item/notification_toggle.hpp"
#include "ptb/defines.hpp"
#include "ptb/message/status_layer_notification_message.hpp"
#include "ptb/game_variables.hpp"

#include "engine/level_globals.hpp"

#include <libintl.h>

BASE_ITEM_EXPORT( notification_toggle, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::notification_toggle::notification_toggle()
  : m_text(""), m_picture_filename(""), m_picture_name("")
{

} // notification_toggle::notification_toggle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "std::string".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::notification_toggle::set_string_field
( const std::string& name, const std::string& value )
{
  bool result(true);

  if ( name == "notification_toggle.text" )
    m_text = value;
  else if ( name == "notification_toggle.picture_filename" )
    m_picture_filename = value;
  else if ( name == "notification_toggle.picture_name" )
    m_picture_name = value;
  else
    result = super::set_string_field( name, value );

  return result;
} // notification_toggle::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Actions done when the state of the toggle changes from off to on.
 * \param activator The item that changed the state.
 */
void ptb::notification_toggle::on_toggle_on
(bear::engine::base_item *activator)
{
  status_layer_notification_message msg;

  bear::visual::sprite sp;

  if ( ( ! m_picture_filename.empty() ) && ( ! m_picture_name.empty() ) ) 
    sp = get_level_globals().auto_sprite
      ( m_picture_filename, m_picture_name );
  msg.set_notification( 0, sp, gettext(m_text.c_str()));

  get_level_globals().send_message
    ( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
} // notification_toggle::on_toggle_on()
