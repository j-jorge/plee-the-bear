/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::bonus_mini_game class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/bonus_points/bonus_mini_game.hpp"

#include "ptb/game_variables.hpp"

#include "expr/boolean_function.hpp"

#include <libintl.h>

BASE_ITEM_EXPORT( bonus_mini_game, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::bonus_mini_game::bonus_mini_game()
  : super("Mini-game unlocked", 10000)
{

} // bonus_mini_game::bonus_mini_game()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::bonus_mini_game::build()
{
  super::build();

  m_already_unlocked = game_variables::get_level_object_state(get_bonus_id());

  set_condition
    ( bear::expr::boolean_function_maker
      ( this, std::mem_fun_ref( &ptb::bonus_mini_game::check ) ) );
} // bonus_mini_game::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the bonus must be given.
 */
bool ptb::bonus_mini_game::check() const
{
  return ( !m_already_unlocked ) &&
    game_variables::get_current_level_mini_game_state();
} // bonus_mini_game::check()
