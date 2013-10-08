/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_game_over class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_game_over.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_game_over::state_game_over( const player_proxy& player_instance )
  : state_player(player_instance)
{
} // state_game_over::state_game_over()


/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_game_over::get_name() const
{
  return "game_over";
} // state_game_over::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_game_over::do_move_left()
{
  // do nothing
} // state_game_over::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_game_over::do_move_right()
{
  // do nothing
} // state_game_over::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void ptb::state_game_over::do_jump()
{
  // do nothing
} // state_game_over::do_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void ptb::state_game_over::do_slap()
{
  // do nothing
} // state_game_over::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player throw.
 */
void ptb::state_game_over::do_start_throw()
{
  // do nothing
} // state_game_over::do_start_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player drop a power.
 */
void ptb::state_game_over::do_start_drop()
{
  // do nothing
} // state_game_over::do_start_drop()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player is injured.
 */
void ptb::state_game_over::do_injured()
{
  // do nothing
} // state_game_over::do_injured()
