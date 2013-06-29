/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_look_upward class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_look_upward.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_look_upward::state_look_upward( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_look_upward::state_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_look_upward::get_name() const
{
  return "look_upward";
} // state_look_upward::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_look_upward::do_move_left()
{
  super::do_move_left();
  m_player_instance.choose_walk_state();
} // state_look_upward::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_look_upward::do_move_right()
{
  super::do_move_right();
  m_player_instance.choose_walk_state();
} // state_look_upward::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void ptb::state_look_upward::do_jump()
{
  if ( m_player_instance.has_bottom_contact() )
    m_player_instance.start_action_model("start_jump");
} // state_look_upward::do_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop to look up.
 */
void ptb::state_look_upward::do_stop_look_upward()
{
   if ( m_player_instance.get_status_crouch() )
     m_player_instance.start_action_model("crouch");
   else
     m_player_instance.choose_idle_state();
} // state_look_upward::do_stop_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player crouch.
 */
void ptb::state_look_upward::do_crouch()
{
  m_player_instance.start_action_model("crouch");
} // state_look_upward::do_crouch()
