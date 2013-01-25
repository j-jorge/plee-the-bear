/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_crouch class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_crouch.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_crouch::state_crouch( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_crouch::state_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_crouch::get_name() const
{
  return "crouch";
} // state_crouch::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_crouch::do_move_left()
{
  super::do_move_left();
  m_player_instance.choose_walk_state();
} // state_crouch::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_crouch::do_move_right()
{
  super::do_move_right();
  m_player_instance.choose_walk_state();
} // state_crouch::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop to look up.
 */
void ptb::state_crouch::do_stop_crouch()
{
  if ( m_player_instance.get_status_look_upward() )
    m_player_instance.start_action_model("look_upward");
  else
    m_player_instance.choose_idle_state();
} // state_crouch::do_stop_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player look up.
 */
void ptb::state_crouch::do_look_upward()
{
  m_player_instance.start_action_model("look_upward");
} // state_crouch::do_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void ptb::state_crouch::do_slap()
{
  // The player roars
  m_player_instance.set_status_crouch(false);
  m_player_instance.start_action_model("roar");
} // state_crouch::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player continue to crouch.
 */
void ptb::state_crouch::do_continue_crouch()
{
  m_player_instance.set_status_crouch(true);
} // state_crouch::do_continue_crouch()
