/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::player_start_position class.
 * \author Julien Jorge
 */
#include "ptb/item/player_start_position.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/player.hpp"
#include "ptb/item/player/plee.hpp"
#include "ptb/item/player/ray.hpp"
#include "engine/level.hpp"

BASE_ITEM_EXPORT( player_start_position, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::player_start_position::player_start_position()
  : m_player_index(0), m_exit_name(PTB_DEFAULT_EXIT_NAME), m_character("plee")
{

} // player_start_position::player_start_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "unsigned integer".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::player_start_position::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result;

  if ( name == "player_start_position.player_index" )
    {
      m_player_index = value;
      result = true;
    }
  else
    result = super::set_u_integer_field( name, value );

  return result;
} // player_start_position::set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "std::string".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::player_start_position::set_string_field
( const std::string& name, const std::string& value )
{
  bool result(true);

  if ( name == "player_start_position.exit_name" )
    m_exit_name = value;
  else if ( name == "player_start_position.character" )
    m_character = value;
  else
    result = super::set_string_field( name, value );

  return result;
} // player_start_position::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::player_start_position::is_valid() const
{
  return (m_player_index != 0)
    && ( ( m_character == "plee" ) || ( m_character == "ray" ) )
    && super::is_valid();
} // player_start_position::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the player and die.
 */
void ptb::player_start_position::build()
{
  if ( game_variables::get_players_count() >= m_player_index)
    if ( (game_variables::get_last_level_exit
          (get_level().get_filename(), m_player_index) == m_exit_name)
         || m_exit_name.empty() )
      {
        player* p(NULL);

        if ( m_character == "plee" )
          p = new plee;
        else if ( m_character == "ray" )
          p = new ray;
        else
          claw::logger << claw::log_error << "Unknown character '"
                       << m_character
                       << "' in function build of player_start_position "
                       << std::endl;

        if ( p != NULL )
          {
            p->set_index( m_player_index );
            p->set_center_of_mass( get_center_of_mass() );

            new_item( *p );
          }
      }

  kill();
} // player_start_position::build()
