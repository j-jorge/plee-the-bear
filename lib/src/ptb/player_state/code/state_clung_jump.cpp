/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_clung_jump class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_clung_jump.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_clung_jump::state_clung_jump( const player_proxy& player_instance  )
  : state_player(player_instance)
{

} // state_clung_jump::state_clung_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_clung_jump::get_name() const
{
  return "clung_jump";
} // state_clung_jump::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a clung_jump.
 */
void ptb::state_clung_jump::do_jump()
{
  // we can't jump in this state.
} // state_clung_jump::do_jump()
