/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class that helps accessing to the game variables.
 * \author Julien Jorge
 */
#ifndef __PTB_LEVEL_VARIABLES_HPP__
#define __PTB_LEVEL_VARIABLES_HPP__

#include "engine/level.hpp"

namespace ptb
{
  /**
   * \brief The class that helps accessing to the game variables.
   * \author Julien Jorge
   */
  class level_variables
  {
  public:
    static unsigned int get_players_on_exit( const bear::engine::level& lvl );
    static void set_players_on_exit
    ( bear::engine::level& lvl, unsigned int c );

    static unsigned int get_object_count
    ( const bear::engine::level& lvl, const std::string& object_type );
    static void set_object_count
    ( bear::engine::level& lvl, const std::string& object_type,
      unsigned int nb );

    static unsigned int get_killed_object_count
    ( const bear::engine::level& lvl, const std::string& object_type );
    static void set_killed_object_count
    ( bear::engine::level& lvl, const std::string& object_type,
      unsigned int nb );

    static bool get_current_hazelnut( const bear::engine::level& lvl);
    static void set_current_hazelnut( bear::engine::level& lvl, bool v );

    static bool get_hazelnut_found( const bear::engine::level& lvl);
    static void set_hazelnut_found( bear::engine::level& lvl, bool v );

    static bool get_secret_level_found( const bear::engine::level& lvl);
    static void set_secret_level_found( bear::engine::level& lvl, bool v );

    static unsigned int get_honeypots_found( const bear::engine::level& lvl );
    static void set_honeypots_found
    ( bear::engine::level& lvl, unsigned int nb );
    static bool get_honeypot_found
    ( const bear::engine::level& lvl, unsigned int id );
    static void set_honeypot_found
    ( bear::engine::level& lvl, unsigned int id, bool b );

    static bool is_exiting( const bear::engine::level& lvl );
    static void set_exiting( bear::engine::level& lvl );

    static bool owl_is_met( const bear::engine::level& lvl );
    static void meet_the_owl( bear::engine::level& lvl );

    static void all_hideouts_found( bear::engine::level& lvl );

    static bool get_friendly_fire(bear::engine::level& lvl);
    static void set_friendly_fire( bear::engine::level& lvl, bool v );

    static std::string get_game_type(bear::engine::level& lvl);
    static void set_game_type
    ( bear::engine::level& lvl, const std::string& type );

    static bool is_network_game(bear::engine::level& lvl);
    static void set_network_game(bear::engine::level& lvl, bool b);

    static bool get_player_status_fixed(bear::engine::level& lvl);
    static void set_player_status_fixed(bear::engine::level& lvl, bool b);
  }; // class level_variables
} // namespace ptb

#endif // __PTB_LEVEL_VARIABLES_HPP__
