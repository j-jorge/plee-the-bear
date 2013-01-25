/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_injured class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_injured.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_injured::state_injured( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_injured::state_injured()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_injured::get_name() const
{
  return "injured";
} // state_injured::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player is not injured now.
 */
void ptb::state_injured::do_finish_injured()
{
  m_player_instance.choose_idle_state();
} // state_injured::do_finish_injured()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void ptb::state_injured::do_slap()
{
  // Player can't slap.
} // state_injured::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player want start throw.
 */
void ptb::state_injured::do_start_throw()
{
} // state_injured::do_start_throw()
