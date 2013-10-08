/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_dead class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_dead.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_dead::state_dead( const player_proxy& player_instance )
  : state_player(player_instance)
{
} // state_dead::state_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_dead::get_name() const
{
  return "dead";
} // state_dead::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_dead::do_move_left()
{
  // do nothing
} // state_dead::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_dead::do_move_right()
{
  // do nothing
} // state_dead::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void ptb::state_dead::do_jump()
{
  // do nothing
} // state_dead::do_jump()


/*----------------------------------------------------------------------------*/
/**
 * \brief Stop a vertical jump.
 */
void ptb::state_dead::do_stop_vertical_jump()
{
  // do nothing
} // state_dead::do_stop_vertical_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void ptb::state_dead::do_slap()
{
  // do nothing
} // state_dead::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player look upward.
 */
void ptb::state_dead::do_look_upward()
{
  // do nothing
} // state_dead::do_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop to look up.
 */
void ptb::state_dead::do_stop_look_upward()
{
  // do nothing
} // state_dead::do_stop_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Continue to look up.
 */
void ptb::state_dead::do_continue_look_upward()
{
  // do nothing
} // state_dead::do_continue_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player crouch.
 */
void ptb::state_dead::do_crouch()
{
  // do nothing
} // state_dead::do_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player continue to crouch.
 */
void ptb::state_dead::do_continue_crouch()
{
  // do nothing
} // state_dead::do_continue_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop to crouch.
 */
void ptb::state_dead::do_stop_crouch()
{
  // do nothing
} // state_dead::do_stop_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief To unchain Player.
 */
void ptb::state_dead::unchain()
{
  // do nothing
} // state_dead::unchain()

/*----------------------------------------------------------------------------*/
/**
 * \brief To chain Player.
 */
void ptb::state_dead::chain()
{
  // do nothing
} // state_dead::chain()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player throw.
 */
void ptb::state_dead::do_start_throw()
{
  // do nothing
} // state_dead::do_start_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Change the current object.
 */
void ptb::state_dead::do_start_change_object()
{
  // do nothing
} // state_dead::do_start_change_object()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player want throw.
 */
void ptb::state_dead::do_stop_throw()
{

} // state_dead::do_stop_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player is injured.
 */
void ptb::state_dead::do_injured()
{
  // do nothing
} // state_dead::do_injured()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player is not injured now.
 */
void ptb::state_dead::do_finish_injured()
{
  // do nothing
} // state_dead::do_finish_injured()
