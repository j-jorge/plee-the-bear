/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_maintain class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_maintain.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_maintain::state_maintain( const player_proxy& player_instance  )
  : state_player(player_instance)
{

} // state_maintain::state_maintain()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_maintain::get_name() const
{
  return "maintain";
} // state_maintain::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of this state.
 */
void ptb::state_maintain::start()
{
  m_player_instance.set_throw_up(false);
  m_player_instance.set_throw_down(false);
} // state_maintain::start()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player want start throw.
 */
void ptb::state_maintain::do_start_throw()
{
  // Player can't maintain an other stone.
} // state_maintain::do_start_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player want maintain.
 */
void ptb::state_maintain::do_stop_throw()
{
  if ( m_player_instance.get_current_action_name() == "maintain_and_fall" )
    m_player_instance.start_action_model("throw_and_fall");
  else if ( m_player_instance.get_current_action_name() == "maintain_and_walk" )
    m_player_instance.start_action_model("throw_and_walk");
  else
    m_player_instance.start_action_model("throw");
} // state_maintain::do_stop_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player look upward.
 */
void ptb::state_maintain::do_look_upward()
{
  m_player_instance.set_throw_up(true);
} // state_maintain::do_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player continue to look upward.
 */
void ptb::state_maintain::do_continue_look_upward()
{
  m_player_instance.set_throw_up(true);
} // state_maintain::do_continue_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player crouch.
 */
void ptb::state_maintain::do_crouch()
{
  m_player_instance.set_throw_down(true);
} // state_maintain::do_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player continue to crouch.
 */
void ptb::state_maintain::do_continue_crouch()
{
  m_player_instance.set_throw_down(true);
} // state_maintain::do_continue_crouch()

