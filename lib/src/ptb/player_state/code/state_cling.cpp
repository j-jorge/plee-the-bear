/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::state_cling class.
 * \author Sebastien Angibaud
 */
#include "ptb/player_state/state_cling.hpp"

#include "universe/world.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::state_cling::state_cling( const player_proxy& player_instance)
  : state_player(player_instance)
{
} // state_cling::state_cling()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the state.
 */
std::string ptb::state_cling::get_name() const
{
  return "cling";
} // state_cling::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player doing slap.
 */
void ptb::state_cling::do_slap()
{
  m_player_instance.start_action_model("fall");
} // state_cling::do_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void ptb::state_cling::do_jump()
{
  m_player_instance.apply_clung_jump();
  m_player_instance.start_action_model("fall");
} // state_cling::do_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_cling::do_move_left()
{
  if ( !m_player_instance.get_rendering_attributes().is_mirrored() )
    m_player_instance.set_want_clung_jump(true);
} // state_cling::do_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the player to the left.
 */
void ptb::state_cling::do_move_right()
{
  if ( m_player_instance.get_rendering_attributes().is_mirrored() )
    m_player_instance.set_want_clung_jump(true);
} // state_cling::do_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player want start throw.
 */
void ptb::state_cling::do_start_throw()
{
} // state_cling::do_start_throw()
