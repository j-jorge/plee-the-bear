/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_start_hang class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_start_hang.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_start_hang::state_start_hang( const player_proxy& player_instance)
  : state_player(player_instance)
{
} // state_start_hang::state_start_hang()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_start_hang::get_name() const
{
  return "start_hang";
} // state_start_hang::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void ptb::state_start_hang::do_slap()
{
} // state_start_hang::do_slap()
