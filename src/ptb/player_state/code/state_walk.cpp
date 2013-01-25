/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_walk class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_walk.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_walk::state_walk( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_walk::state_walk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_walk::get_name() const
{
  return "walk";
} // state_walk::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void ptb::state_walk::do_slap()
{
  m_player_instance.start_action_model("slap_and_walk");
} // state_walk::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player throw.
 */
void ptb::state_walk::do_start_throw()
{
  m_player_instance.start_action_model("maintain_and_walk");
} // state_walk::do_start_throw()
