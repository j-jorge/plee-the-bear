/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_fall class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_fall.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_fall::state_fall( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_fall::state_fall()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_fall::get_name() const
{
  return "fall";
} // state_fall::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player throw.
 */
void ptb::state_fall::do_start_throw()
{
  m_player_instance.start_action_model("maintain_and_fall");
} // state_fall::do_start_throw()
