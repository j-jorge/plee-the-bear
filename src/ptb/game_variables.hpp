/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class that helps accessing to the game variables.
 * \author Julien Jorge
 */
#ifndef __PTB_GAME_VARIABLES_HPP__
#define __PTB_GAME_VARIABLES_HPP__

#include <string>

namespace ptb
{
  /**
   * \brief The class that helps accessing to the game variables.
   * \author Julien Jorge
   */
  class game_variables
  {
  public:
    static unsigned int get_port();
    static void set_port(unsigned int port);
    
    static std::string get_ip(unsigned int p);
    static void set_ip(unsigned int p, const std::string& ip);

    static bool is_local_player(unsigned int p);
    static void set_local_player(unsigned int p, bool value);

    static unsigned int get_players_count();
    static void set_players_count( unsigned int c );

    static std::string get_last_level_exit
    ( const std::string& level, unsigned int p );
    static void set_last_level_exit
    ( const std::string& level, unsigned int p, const std::string& e );

    static std::string get_next_level_name();
    static void set_next_level_name( const std::string& n );

    static std::string get_level_name( const std::string& filename);
    static void set_level_name
    ( const std::string& filename, const std::string& name );

    static void set_level_precedence
    ( const std::string& prec, const std::string& next );
    static void set_finished_level( const std::string& lvl, bool b);
    static bool level_is_finished(const std::string& lvl);

    static void set_level_object_state( const std::string& object, bool b );
    static bool get_level_object_state( const std::string& object);
    static bool get_level_object_state
    ( const std::string& level, const std::string& object);

    static void set_level_object_filename
    ( const std::string& object, const std::string& filename );
    static std::string get_level_object_filename( const std::string& object );
    static std::string get_level_object_filename
    ( const std::string& level, const std::string& object );

    static void set_level_object_name
    ( const std::string& object, const std::string& name );
    static std::string get_level_object_name( const std::string& object );
    static std::string get_level_object_name
    ( const std::string& level, const std::string& object );

    static void set_hideout_state( const std::string& id, bool b );
    static bool get_hideout_state( const std::string& id );

    static std::string get_main_level_name();
    static void set_main_level_name( const std::string& n );

    static std::string get_profile_name();
    static void set_profile_name( const std::string& n );

    static bool get_mini_game_status( const std::string& name);
    static void set_mini_game_status( const std::string& n, bool v );

    static bool get_all_mini_game_unlocked_status();
    static void set_all_mini_game_unlocked_status( bool v );

    static bool get_password_menu_visibility();
    static void set_password_menu_visibility( bool v );

    static bool get_friendly_fire();
    static void set_friendly_fire( bool v );

    static std::string get_lives_count_variable_name(unsigned int p );
    static unsigned int get_lives_count( unsigned int p);
    static void set_lives_count( unsigned int p, unsigned int c );
    static unsigned int get_persistent_lives_count( unsigned int p);
    static void set_persistent_lives_count( unsigned int p, unsigned int c );

    static std::string get_stones_count_variable_name(unsigned int p );
    static unsigned int get_stones_count( unsigned int p);
    static void set_stones_count( unsigned int p, unsigned int c );
    static unsigned int get_persistent_stones_count( unsigned int p);
    static void set_persistent_stones_count( unsigned int p, unsigned int c );

    static std::string get_max_energy_variable_name(unsigned int p );
    static double get_max_energy( unsigned int p);
    static void set_max_energy( unsigned int p, double b );
    static double get_persistent_max_energy( unsigned int p);
    static void set_persistent_max_energy( unsigned int p, double b );

    static std::string get_current_level_max_energy_variable_name();
    static bool get_current_level_max_energy_state();
    static void set_current_level_max_energy_state( bool v );
    static bool get_persistent_current_level_max_energy_state();
    static void set_persistent_current_level_max_energy_state( bool v );

    static std::string get_player_max_energy_variable_name(unsigned int index);
    static bool get_current_level_max_energy_state(unsigned int index);
    static void set_current_level_max_energy_state
    ( unsigned int index, bool v );
    static bool get_persistent_current_level_max_energy_state
    (unsigned int index);
    static void set_persistent_current_level_max_energy_state
    ( unsigned int index, bool v );

    static bool get_current_level_boss_killed();
    static void set_current_level_boss_killed( bool v );

    static bool get_current_level_mini_game_state();
    static void set_current_level_mini_game_state( bool v );

    static std::string get_score_variable_name(unsigned int p );
    static unsigned int get_score( unsigned int p );
    static unsigned int get_persistent_score( unsigned int p );
    static void set_score( unsigned int p, unsigned int c );
    static void set_persistent_score( unsigned int p, unsigned int c );
    static void add_score( unsigned int p, unsigned int c );
    static void sub_score( unsigned int p, unsigned int c );

    static std::string get_air_power_variable_name(unsigned int p );
    static bool get_air_power( unsigned int p );
    static void set_air_power( unsigned int p, bool v );
    static bool get_persistent_air_power( unsigned int p );
    static void set_persistent_air_power( unsigned int p, bool v );

    static std::string get_fire_power_variable_name(unsigned int p );
    static bool get_fire_power( unsigned int p );
    static void set_fire_power( unsigned int p, bool v );
    static bool get_persistent_fire_power( unsigned int p );
    static void set_persistent_fire_power( unsigned int p, bool v );

    static std::string get_water_power_variable_name(unsigned int p );
    static bool get_water_power( unsigned int p );
    static void set_water_power( unsigned int p, bool v );
    static bool get_persistent_water_power( unsigned int p );
    static void set_persistent_water_power( unsigned int p, bool v );

    static std::string get_sniffable_variable_name
    (unsigned int p, const std::string& category);
    static bool get_persistent_sniffable
    ( unsigned int p, const std::string& category);
    static void set_persistent_sniffable
    ( unsigned int p, const std::string& category);
    
    static std::string get_corrupting_bonus_count_variable_name();
    static unsigned int get_corrupting_bonus_count();
    static void set_corrupting_bonus_count( unsigned int c );

    static unsigned int get_last_corrupting_bonus_count
    (const std::string& lvl);
    static void set_last_corrupting_bonus_count
    ( const std::string& lvl, unsigned int c );

    static double get_corrupting_bonus_rate_x();
    static void set_corrupting_bonus_rate_x(double x);
    static double get_corrupting_bonus_rate_y();
    static void set_corrupting_bonus_rate_y(double y);

    static bool demo_is_on();
    static void set_demo(bool v);

    static bool mini_game_is_on();
    static void set_mini_game(bool v);

    static unsigned int get_last_mini_game();
    static void set_last_mini_game(unsigned int index);

    static bool record_game();

    static std::string get_string_default( const std::string& n );

    static std::string
    make_player_specific_variable_name( unsigned int p, const std::string& n );

    static std::string make_persistent_variable_name( const std::string& n );
    static std::string make_persistent_level_variable_name
    ( const std::string& n );

    static void load_player_variables();
    static void load_player_variables(unsigned int p);
    static void save_player_variables();
    static void save_player_variables(unsigned int p);
  }; // class game_variables
} // namespace ptb

#endif // __PTB_GAME_VARIABLES_HPP__
