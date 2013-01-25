/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An item activated by an event comming from the players.
 * \author Julien Jorge
 */
#ifndef __PTB_ACTIVATE_ON_PLAYERS_HPP__
#define __PTB_ACTIVATE_ON_PLAYERS_HPP__

namespace ptb
{
  class player_proxy;

  /**
   * \brief An item activated by an event comming from the players.
   * \author Julien Jorge
   * \sa on_players_activator
   */
  class activate_on_players
  {
  public:
    virtual ~activate_on_players();

    virtual void on_one_player( const player_proxy& p );
    virtual void on_all_players
    ( const player_proxy& p1, const player_proxy& p2 );

  }; // class activate_on_players
} // namespace ptb

#endif // __PTB_ACTIVATE_ON_PLAYERS_HPP__
