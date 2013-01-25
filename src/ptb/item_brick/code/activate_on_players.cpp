/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::activate_on_players class.
 * \author Julien Jorge
 */
#include "ptb/item_brick/activate_on_players.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Desctructor.
 */
ptb::activate_on_players::~activate_on_players()
{
  // nothing to do
} // activate_on_players::~activate_on_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Only one of the two players is present in the event.
 * \param p The player.
 * \remark This method is called only in a two players game.
 */
void ptb::activate_on_players::on_one_player( const player_proxy& p )
{
  // nothing to do
} // activate_on_players::on_one_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief All players are present in the event.
 * \param p1 The first player.
 * \param p2 The second player. NULL in a single player game.
 */
void ptb::activate_on_players::on_all_players
( const player_proxy& p1, const player_proxy& p2 )
{
  // nothing to do
} // activate_on_players::on_all_players()
