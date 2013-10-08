/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::player_settings class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/player_settings.hpp"
#include "ptb/game_variables.hpp"

BASE_ITEM_EXPORT( player_settings, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::player_settings::player_settings()
  : m_player_index(1), m_global_settings(false)
{
} // player_settings::player_settings()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::player_settings::build()
{
  super::build();

  kill();
} // player_settings::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c unsigned \c integer.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::player_settings::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result(true);

  if ( name == "player_settings.player_index" )
    m_player_index = value;
  else if ( name == "player_settings.stones" )
    {
      game_variables::set_stones_count(m_player_index, value);
      if ( m_global_settings )
	game_variables::set_persistent_stones_count(m_player_index, value);
    }
  else if ( name == "player_settings.lives" )
    {
      game_variables::set_lives_count(m_player_index, value);
      if ( m_global_settings )
	game_variables::set_persistent_lives_count(m_player_index, value);
    }
  else if ( name == "player_settings.score" )
    {
      game_variables::set_score(m_player_index, value);
      if ( m_global_settings )
	game_variables::set_persistent_score(m_player_index, value);
    }
  else
    result = super::set_u_integer_field(name, value);
  
  return result;
} // player_settings::set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c bool.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool
ptb::player_settings::set_bool_field( const std::string& name, bool value )
{
  bool result = true;

  if (name == "player_settings.power.air")
    {
      game_variables::set_air_power(m_player_index, value);
      if ( m_global_settings )
	game_variables::set_persistent_air_power(m_player_index, value);
    }
  else if (name == "player_settings.power.fire")
    {
      game_variables::set_fire_power(m_player_index, value);
      if ( m_global_settings )
	game_variables::set_persistent_fire_power(m_player_index, value);
    }
  else if (name == "player_settings.power.water")
    {
      game_variables::set_water_power(m_player_index, value);
      if ( m_global_settings )
	game_variables::set_persistent_water_power(m_player_index, value);
    }
  else if (name == "player_settings.global_settings")
    m_global_settings = value;
  else 
    result = super::set_bool_field(name, value);

  return result;
} // player_settings::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c real.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool
ptb::player_settings::set_real_field( const std::string& name, double value )
{
  bool result = true;

  if (name == "player_settings.max_energy")
    {
      game_variables::set_max_energy(m_player_index, value);
      if ( m_global_settings )
	game_variables::set_persistent_max_energy(m_player_index, value);
    }
  else
    result = super::set_real_field(name, value);

  return result;
} // player_settings::set_real_field()
