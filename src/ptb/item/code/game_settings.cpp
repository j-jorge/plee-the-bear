/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::game_settings class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/game_settings.hpp"
#include "ptb/game_variables.hpp"

BASE_ITEM_EXPORT( game_settings, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::game_settings::game_settings()
{
} // game_settings::game_settings()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::game_settings::build()
{
  super::build();

  kill();
} // game_settings::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c unsigned \c integer.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::game_settings::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result(true);

  if ( name == "game_settings.corrupting_bonus_count" )
    game_variables::set_corrupting_bonus_count(value);
  else
    result = super::set_u_integer_field(name, value);

  return result;
} // game_settings::set_u_integer_field()
