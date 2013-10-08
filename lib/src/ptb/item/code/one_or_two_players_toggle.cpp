/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::one_or_two_players_toggle class.
 * \author Julien Jorge
 */
#include "ptb/item/one_or_two_players_toggle.hpp"

#include "ptb/game_variables.hpp"

BASE_ITEM_EXPORT( one_or_two_players_toggle, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::one_or_two_players_toggle::one_or_two_players_toggle()
  : m_toggle_single(NULL), m_toggle_coop(NULL)
{

} // one_or_two_players_toggle::one_or_two_players_toggle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type item
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::one_or_two_players_toggle::set_item_field
( const std::string& name, base_item* value)
{
  bool result(true);

  if ( name == "one_or_two_players_toggle.single_player_game" )
    {
      m_toggle_single = value;
      result = m_toggle_single != (bear::engine::with_toggle*)NULL;
    }
  else if ( name == "one_or_two_players_toggle.two_players_game" )
    {
      m_toggle_coop = value;
      result = m_toggle_single != (bear::engine::with_toggle*)NULL;
    }
  else
    result = super::set_item_field(name, value);

  return result;
} // one_or_two_players_toggle::set_item_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Actions done when the state of the toggle changes from off to on.
 * \param activator The item that changed the state.
 */
void ptb::one_or_two_players_toggle::on_toggle_on
(bear::engine::base_item *activator)
{
  if ( game_variables::get_players_count() == 1 )
    {
      if ( m_toggle_single != (bear::engine::with_toggle*)NULL )
        m_toggle_single->toggle_on(activator);
    }
  else if ( m_toggle_coop != (bear::engine::with_toggle*)NULL )
    m_toggle_coop->toggle_on(activator);
} // one_or_two_players_toggle::on_toggle_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Actions done when the state of the toggle changes from on to off.
 * \param activator The item that changed the state.
 */
void ptb::one_or_two_players_toggle::on_toggle_off
(bear::engine::base_item *activator)
{
  if ( game_variables::get_players_count() == 1 )
    {
      if ( m_toggle_single != (bear::engine::with_toggle*)NULL )
        m_toggle_single->toggle_off(activator);
    }
  else if ( m_toggle_coop != (bear::engine::with_toggle*)NULL )
    m_toggle_coop->toggle_off(activator);
} // one_or_two_players_toggle::on_toggle_off()
