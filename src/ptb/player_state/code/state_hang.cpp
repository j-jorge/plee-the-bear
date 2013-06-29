/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_hang class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_hang.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_hang::state_hang( const player_proxy& player_instance)
  : state_player(player_instance)
{
} // state_hang::state_hang()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_hang::get_name() const
{
  return "hang";
} // state_hang::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void ptb::state_hang::do_slap()
{
} // state_hang::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_hang::do_move_left()
{
} // state_hang::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_hang::do_move_right()
{
} // state_hang::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player want start throw.
 */
void ptb::state_hang::do_start_throw()
{
} // state_hang::do_start_throw()
