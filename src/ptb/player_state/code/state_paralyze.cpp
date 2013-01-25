/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_paralyze class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_paralyze.hpp"

#include <limits>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_paralyze::state_paralyze( const player_proxy& player_instance )
  : state_player(player_instance)
{

} // state_paralyze::state_paralyze()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_paralyze::get_name() const
{
  return "paralyze";
} // state_paralyze::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of this state.
 */
void ptb::state_paralyze::start()
{
 m_player_instance.set_marionette(true);
} // state_paralyze::start()

/*----------------------------------------------------------------------------*/
/**
 * \brief The end of the action.
 */
void ptb::state_paralyze::stop()
{
  m_player_instance.set_marionette(false);
} // state_paralyze::stop()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_paralyze::do_move_left()
{
  // we can't move in this state
} // state_paralyze::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_paralyze::do_move_right()
{
   // we can't move in this state
} // state_paralyze::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void ptb::state_paralyze::do_jump()
{
   // we can't jump in this state
} // state_paralyze::do_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void ptb::state_paralyze::do_slap()
{
   // we can't slap in this state
} // state_paralyze::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player throw a stone
 */
void ptb::state_paralyze::do_start_throw()
{
 // we can't throw in this state
} // state_paralyze::start_throw

/*----------------------------------------------------------------------------*/
/**
 * \brief Player drop a power.
 */
void ptb::state_paralyze::do_start_drop()
{
 // we can't drop in this state
} // state_paralyze::do_start_drop()
