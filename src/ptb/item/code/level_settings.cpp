/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::level_settings class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/level_settings.hpp"
#include "ptb/level_variables.hpp"
#include "ptb/game_variables.hpp"

BASE_ITEM_EXPORT( level_settings, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::level_settings::level_settings()
: m_is_main_level(true), m_player_status_fixed(false)
{
} // level_settings::level_settings()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::level_settings::build()
{
  super::build();

  if ( m_is_main_level )
    game_variables::set_main_level_name(get_level().get_filename());

  game_variables::load_player_variables();

  kill();
} // level_settings::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c bool.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool
ptb::level_settings::set_bool_field( const std::string& name, bool value )
{
  bool result = true;

  if (name == "level_settings.friendly_fire")
    level_variables::set_friendly_fire(get_level(), value);
  else if (name == "level_settings.game_over_allowed")
    level_variables::allow_game_over(get_level(), value);
  else if (name == "level_settings.player_status_fixed")
    level_variables::set_player_status_fixed(get_level(), value);
  else if (name == "level_settings.is_main_level")
    m_is_main_level  = value;
  else
    result = super::set_bool_field(name, value);

  return result;
} // level_settings::set_bool_field()

