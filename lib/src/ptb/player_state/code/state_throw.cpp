/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_throw class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_throw.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_throw::state_throw( const player_proxy& player_instance  )
  : state_player(player_instance)
{

} // state_throw::state_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_throw::get_name() const
{
  return "throw";
} // state_throw::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of this state.
 */
void ptb::state_throw::start()
{
  m_player_instance.update_throw_time_ratio();
} // state_throw::start()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player want start throw.
 */
void ptb::state_throw::do_start_throw()
{
  // Player can't throw an other stone.
} // state_throw::do_start_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player look upward.
 */
void ptb::state_throw::do_look_upward()
{
  m_player_instance.set_throw_up(true);
} // state_throw::do_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player continue to look upward.
 */
void ptb::state_throw::do_continue_look_upward()
{
  m_player_instance.set_throw_up(true);
} // state_throw::do_continue_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player crouch.
 */
void ptb::state_throw::do_crouch()
{
  m_player_instance.set_throw_down(true);
} // state_throw::do_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player continue to crouch.
 */
void ptb::state_throw::do_continue_crouch()
{
  m_player_instance.set_throw_down(true);
} // state_throw::do_continue_crouch()

