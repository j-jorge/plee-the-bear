/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_roar class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_roar.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_roar::state_roar( const player_proxy& player_instance )
  : state_player(player_instance)
{
} // state_roar::state_roar()


/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_roar::get_name() const
{
  return "roar";
} // state_roar::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_roar::do_move_left()
{
  // we can't move in this state
} // state_roar::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_roar::do_move_right()
{
   // we can't move in this state
} // state_roar::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void ptb::state_roar::do_jump()
{
   // we can't jump in this state
} // state_roar::do_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void ptb::state_roar::do_slap()
{
   // we can't slap in this state
} // state_roar::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player throw a stone
 */
void ptb::state_roar::do_start_throw()
{
 // we can't throw in this state
} // state_roar::start_throw

/*----------------------------------------------------------------------------*/
/**
 * \brief Player drop a power.
 */
void ptb::state_roar::do_start_drop()
{
  // we can't drop in this state
} // state_roar::do_start_drop()

