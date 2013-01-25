/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_sink class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_sink.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_sink::state_sink( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_sink::state_sink()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_sink::get_name() const
{
  return "sink";
} // state_sink::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player look upward.
 */
void ptb::state_sink::do_look_upward()
{
  m_player_instance.apply_swim_up();
} // state_sink::do_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player continue to look_upward.
 */
void ptb::state_sink::do_continue_look_upward()
{
  m_player_instance.apply_swim_up();
} // state_sink::do_continue_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player crouch.
 */
void ptb::state_sink::do_crouch()
{
  m_player_instance.apply_swim_down();
} // state_sink::do_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player continue to crouch.
 */
void ptb::state_sink::do_continue_crouch()
{
  m_player_instance.apply_swim_down();
} // state_sink::do_continue_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void ptb::state_sink::do_jump()
{
  m_player_instance.start_action_model("swimming");
} // state_sink::do_jump()


/*----------------------------------------------------------------------------*/
/**
 * \brief Do continue a jump.
 */
void ptb::state_sink::do_continue_jump()
{
  m_player_instance.start_action_model("swimming");
} // state_sink::do_continuejump()
