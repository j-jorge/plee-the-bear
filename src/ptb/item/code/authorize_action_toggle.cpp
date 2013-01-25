/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::authorize_action_toggle class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/authorize_action_toggle.hpp"

#include "universe/derived_item_handle.hpp"
#include "ptb/util/player_util.hpp"

BASE_ITEM_EXPORT( authorize_action_toggle, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::authorize_action_toggle::authorize_action_toggle()
  : m_value(0), m_action(player_action::action_null)
{

} // authorize_action_toggle::authorize_action_toggle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type string
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::authorize_action_toggle::set_string_field
( const std::string& name, const std::string& value)
{
  bool result(true);

  if ( name == "authorize_action_toggle.action" )
    {
      m_action = player_action::from_string(value);
      result = ( m_action != player_action::action_null );
    }
  else
    result = super::set_string_field(name, value);

  return result;
} // authorize_action_toggle::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type bool
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::authorize_action_toggle::set_bool_field
( const std::string& name, bool value)
{
  bool result(true);

  if ( name == "authorize_action_toggle.value" )
    m_value = value;
  else
    result = super::set_bool_field(name, value);

  return result;
} // authorize_action_toggle::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Actions done when the state of the toggle changes from off to on.
 * \param activator The item that changed the state.
 */
void ptb::authorize_action_toggle::on_toggle_on
(bear::engine::base_item *activator)
{
  if ( m_action != player_action::action_null )
    {
      player_proxy p = util::find_player( get_level_globals(), 1 );

      if ( p != NULL )
        p.set_authorized_action(m_action, m_value);

      p = util::find_player( get_level_globals(), 2 );

      if ( p != NULL )
        p.set_authorized_action(m_action, m_value);
    }
} // authorize_action_toggle::on_toggle_on()

