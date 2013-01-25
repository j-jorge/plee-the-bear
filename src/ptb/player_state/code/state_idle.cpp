/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_idle class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_idle.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_idle::state_idle( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_idle::state_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_idle::get_name() const
{
  return "idle";
} // state_idle::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_idle::do_move_left()
{
  super::do_move_left();
  m_player_instance.choose_walk_state();
} // state_idle::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_idle::do_move_right()
{
  super::do_move_right();
  m_player_instance.choose_walk_state();
} // state_idle::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player look up.
 */
void ptb::state_idle::do_look_upward()
{
  m_player_instance.start_action_model("look_upward");
} // state_idle::do_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Continue to look up.
 */
void ptb::state_idle::do_continue_look_upward()
{
  m_player_instance.start_action_model("look_upward");
} // state_idle::do_continue_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player crouch.
 */
void ptb::state_idle::do_crouch()
{
  m_player_instance.start_action_model("crouch");
} // state_idle::do_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Continue to crouch.
 */
void ptb::state_idle::do_continue_crouch()
{
  m_player_instance.start_action_model("crouch");
} // state_idle::do_continue_crouch()
