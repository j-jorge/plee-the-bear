/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Type of level playability : number of required players.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_PLAYABILITY_TYPE_HPP__
#define __PTB_PLAYABILITY_TYPE_HPP__

#include <string>

namespace ptb
{
  /**
   * \brief Type of level playability : number of required players.
   * \author Sébastien Angibaud
   */
  struct playability_type
  {
  public:
    /** \brief The type of playability_type. */
    typedef unsigned int value_type;

  public:
    static std::string to_string( value_type a );
    static value_type from_string( const std::string& s );

  public:
    /** \brief Playable with one or two players. */
    static const value_type one_or_two_players = 0;

    /** \brief Playable with one player only. */
    static const value_type one_player_only = one_or_two_players + 1;

    /** \brief Playable with two players only. */
    static const value_type two_players_only = one_player_only + 1;

    /** \brief Playable without player. */
    static const value_type no_player = two_players_only + 1;
  }; // struct playability_type
} // namespace ptb

#endif // __PTB_PLAYABILITY_TYPE_HPP__
