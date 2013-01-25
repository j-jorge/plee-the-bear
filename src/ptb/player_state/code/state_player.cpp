/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_plee class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_player.hpp"

#include "ptb/game_variables.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_player::state_player( const player_proxy& player_instance )
  : m_player_instance(player_instance)
{

} // state_player::state_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_player::do_move_left()
{
  m_player_instance.apply_move_left();
} // state_player::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_player::do_move_right()
{
  m_player_instance.apply_move_right();
} // state_player::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void ptb::state_player::do_jump()
{
  if ( m_player_instance.has_bottom_contact() )
    {
      m_player_instance.apply_impulse_jump();
      if ( game_variables::get_air_power(m_player_instance.get_index() ) )
        m_player_instance.set_air_float(true);
      m_player_instance.start_action_model("jump");
    }
} // state_player::do_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Continue to jump.
 */
void ptb::state_player::do_continue_jump()
{
  // do nothing
} // state_player::do_continue_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop a vertical jump.
 */
void ptb::state_player::do_stop_vertical_jump()
{
  m_player_instance.set_air_float(false);
} // state_player::do_stop_vertical_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void ptb::state_player::do_slap()
{
  if (m_player_instance.has_bottom_contact() )
    m_player_instance.start_action_model("slap");
  else
    m_player_instance.start_action_model("start_cling");
} // state_player::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player look upward.
 */
void ptb::state_player::do_look_upward()
{

} // state_player::do_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop to look up.
 */
void ptb::state_player::do_stop_look_upward()
{

} // state_player::do_stop_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Continue to look up.
 */
void ptb::state_player::do_continue_look_upward()
{

} // state_player::do_continue_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player crouch.
 */
void ptb::state_player::do_crouch()
{

} // state_player::do_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player continue to crouch.
 */
void ptb::state_player::do_continue_crouch()
{

} // state_player::do_continue_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop to crouch.
 */
void ptb::state_player::do_stop_crouch()
{

} // state_player::do_stop_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief To captive Player.
 */
void ptb::state_player::captive()
{
  m_player_instance.start_action_model("captive");
} // state_player::captive()

/*----------------------------------------------------------------------------*/
/**
 * \brief To release player.
 */
void ptb::state_player::release()
{
  m_player_instance.start_action_model("idle");
} // state_player::release()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player throw.
 */
void ptb::state_player::do_start_throw()
{
  m_player_instance.start_action_model("maintain");
} // state_player::do_start_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Change the current object.
 */
void ptb::state_player::do_start_change_object()
{
  m_player_instance.apply_change_object();
} // state_player::do_start_change_object()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player want throw.
 */
void ptb::state_player::do_stop_throw()
{

} // state_player::do_stop_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player is injured.
 */
void ptb::state_player::do_injured()
{
  m_player_instance.start_action_model("injured");
} // state_player::do_injured()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player is not injured now.
 */
void ptb::state_player::do_finish_injured()
{
  // do nothing
} // state_player::do_finish_injured()
