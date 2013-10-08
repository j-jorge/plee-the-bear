/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Utility functions about the players.
 * \author Julien Jorge
 */
#include "ptb/util/player_util.hpp"

#include "ptb/message/get_player_instance.hpp"

#include <sstream>

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the name of a player.
 * \param player_index The index of the player for which we want the name.
 */
std::string ptb::util::get_player_name( unsigned int player_index )
{
  std::ostringstream oss;
  oss << "player_" << player_index;

  return oss.str();
} // get_player_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Find a player in a level.
 * \param glob The level_globals of the level in which the player is
 *        searched.
 * \param player_index The index of the player we are searching for.
 */
ptb::player_proxy ptb::util::find_player
( const bear::engine::level_globals& glob, unsigned int player_index )
{
  get_player_instance msg;
  glob.send_message( get_player_name(player_index), msg );
  return player_proxy(msg.get_instance());
} // find_player()
