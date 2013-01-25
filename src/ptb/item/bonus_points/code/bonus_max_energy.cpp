/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::bonus_max_energy class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/bonus_points/bonus_max_energy.hpp"

#include "ptb/game_variables.hpp"

#include "expr/boolean_function.hpp"

#include <libintl.h>

BASE_ITEM_EXPORT( bonus_max_energy, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::bonus_max_energy::bonus_max_energy()
  : super("Energy bonus found", 10000)
{

} // bonus_max_energy::bonus_max_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::bonus_max_energy::build()
{
  set_picture_filename("gfx/ui/bonus-icons/bonus-icons.png");
  set_picture_name("energy box");

  super::build();

  m_already_found = 
    game_variables::get_persistent_current_level_max_energy_state();

  set_condition
    ( bear::expr::boolean_function_maker
      ( this, std::mem_fun_ref( &ptb::bonus_max_energy::check ) ) );
} // bonus_max_energy::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the bonus must be given.
 */
bool ptb::bonus_max_energy::check() const
{
  return ( !m_already_found ) &&
    game_variables::get_current_level_max_energy_state();
} // bonus_max_energy::check()
