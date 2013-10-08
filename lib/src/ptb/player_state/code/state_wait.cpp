/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_wait class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_wait.hpp"

#include <stdlib.h>
#include <time.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_wait::state_wait( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_wait::state_wait()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_wait::get_name() const
{
  return "wait";
} // state_wait::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_wait::do_move_left()
{
  super::do_move_left();
  m_player_instance.choose_walk_state();
} // state_wait::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_wait::do_move_right()
{
  super::do_move_right();
  m_player_instance.choose_walk_state();
} // state_wait::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player look up.
 */
void ptb::state_wait::do_look_upward()
{
  m_player_instance.start_action_model("look_upward");
} // state_wait::do_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player crouch.
 */
void ptb::state_wait::do_crouch()
{
  m_player_instance.start_action_model("crouch");
} // state_wait::do_crouch()
