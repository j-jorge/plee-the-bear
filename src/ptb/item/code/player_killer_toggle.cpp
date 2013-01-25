/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::player_killer_toggle class.
 * \author Julien Jorge
 */
#include "ptb/item/player_killer_toggle.hpp"

#include "ptb/util/player_util.hpp"

BASE_ITEM_EXPORT( player_killer_toggle, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param player_index The index of the player to kill.
 */
ptb::player_killer_toggle::player_killer_toggle( unsigned int player_index  )
  : m_player_index(player_index)
{

} // player_killer_toggle::player_killer_toggle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type unsigned int.
 * \param name The name of the field to set.
 * \param value The value of the field.
 */
bool ptb::player_killer_toggle::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result(true);

  if ( name == "player_killer_toggle.player_index" )
    m_player_index = value;
  else
    result = super::set_u_integer_field( name, value );

  return result;
} // player_killer_toggle::set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief The toggle is activated, kill the player.
 * \param activator The item who activated this toggle.
 */
void ptb::player_killer_toggle::on_toggle_on
( bear::engine::base_item* activator )
{
  super::on_toggle_on(activator);

  player_proxy p = util::find_player( get_level_globals(), m_player_index );

  if ( p != NULL )
    p.start_action( player_action::die );
} // player_killer_toggle::on_toggle_on()
