/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::bonus_boss class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/bonus_points/bonus_boss.hpp"

#include "ptb/game_variables.hpp"

#include "expr/boolean_function.hpp"

#include <libintl.h>

BASE_ITEM_EXPORT( bonus_boss, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::bonus_boss::bonus_boss()
  : super("Boss killed", 10000)
{

} // bonus_boss::bonus_boss()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::bonus_boss::build()
{
  super::build();

  m_already_killed = game_variables::get_current_level_boss_killed();

  set_condition
    ( bear::expr::boolean_function_maker
      ( this, std::mem_fun_ref( &ptb::bonus_boss::check ) ) );
} // bonus_boss::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the bonus must be given.
 */
bool ptb::bonus_boss::check() const
{
  return ( !m_already_killed ) &&
    game_variables::get_current_level_boss_killed();
} // bonus_boss::check()
