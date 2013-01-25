/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::get_player_instance class.
 * \author Julien Jorge
 */
#include "ptb/message/get_player_instance.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::get_player_instance::get_player_instance()
  : m_player(NULL)
{

} // get_player_instance::get_player_instance()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the message to a player.
 * \param that The player to which the message is applied.
 */
bool ptb::get_player_instance::apply_to( player& that )
{
  m_player = &that;
  return true;
} // get_player_instance::apply_to()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the instance of the player.
 */
ptb::player* ptb::get_player_instance::get_instance() const
{
  return m_player;
} // get_player_instance::get_instance()
