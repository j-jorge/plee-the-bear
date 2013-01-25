/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_slap class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_slap.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_slap::state_slap( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_slap::state_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_slap::get_name() const
{
  return "slap";
} // state_slap::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start the action.
 */
void ptb::state_slap::start()
{
  m_initial_normal_defensive_power =
    m_player_instance.get_defensive_power( monster::normal_attack );
} // state_slap::stop()

/*----------------------------------------------------------------------------*/
/**
 * \brief The end of the action.
 */
void ptb::state_slap::stop()
{
  m_player_instance.set_offensive_phase(false);
  m_player_instance.set_defensive_power
    (monster::normal_attack, m_initial_normal_defensive_power);
} // state_slap::stop()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void ptb::state_slap::do_slap()
{
  // Player can't do a new slap.
} // state_slap::do_slap()
