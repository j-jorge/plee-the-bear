/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_start_cling class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_start_cling.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_start_cling::state_start_cling( const player_proxy& player_instance)
  : state_player(player_instance)
{
} // state_start_cling::state_start_cling()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of this state.
 */
void ptb::state_start_cling::start()
{
  m_player_instance.set_offensive_phase(true);
  m_initial_normal_defensive_power =
    m_player_instance.get_defensive_power(monster::normal_attack);
  m_player_instance.set_defensive_power(monster::normal_attack, true);
} // state_start_cling::start()

/*----------------------------------------------------------------------------*/
/**
 * \brief The end of the action.
 */
void ptb::state_start_cling::stop()
{
  m_player_instance.set_offensive_phase(false);
  m_player_instance.set_defensive_power
    (monster::normal_attack, m_initial_normal_defensive_power);
} // state_start_cling::stop()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_start_cling::get_name() const
{
  return "start_cling";
} // state_start_cling::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void ptb::state_start_cling::do_slap()
{
} // state_start_cling::do_slap()
