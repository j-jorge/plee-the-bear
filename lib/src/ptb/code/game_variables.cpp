/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::game_variables class.
 * \author Julien Jorge
 */
#include "ptb/game_variables.hpp"
#include "ptb/defines.hpp"

#include "engine/game.hpp"
#include "engine/variable/variable.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief A function that gets a game variable.
 * \param n The name of the variable.
 * \param def The default value to return if the variable is not set.
 */
template<typename T>
static T ptb_game_variables_get_value( const std::string& n, const T& def )
{
  bear::engine::variable<T> var(n);

  if ( bear::engine::game::get_instance().game_variable_exists(var) )
    {
      bear::engine::game::get_instance().get_game_variable(var);
      return var.get_value();
    }
  else
    return def;
} // ptb_game_variables_get_value()


/*----------------------------------------------------------------------------*/
/**
 * \brief Get port of a given player.
 */
unsigned int ptb::game_variables::get_port()
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name( "network/port" ), (unsigned int)2424 );
} // game_variables::get_port()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set port of a given player.
 * \param port The port.
 */
void ptb::game_variables::set_port(unsigned int port)
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( make_persistent_variable_name( "network/port" ), port ) );
} // game_variables::set_port()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if a player is local.
 * \param p The index of the player.*/
bool ptb::game_variables::is_local_player(unsigned int p)
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      ( "network/" + make_player_specific_variable_name
        ( p, "local_player" ) ), true );
} // game_variables::get_local_player_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a player is local.
 * \param p The index of the player.
 * \param value The new value.
 */
void ptb::game_variables::set_local_player(unsigned int p, bool value)
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( make_persistent_variable_name
	( "network/" + make_player_specific_variable_name
	  ( p, "local_player" ) ), value ) );
} // game_variables::set_local_player_index()
    
/*----------------------------------------------------------------------------*/
/**
 * \brief Get ip adddress of a given player.
 * \param p The index of the player.
 */
std::string ptb::game_variables::get_ip(unsigned int p)
{
  std::string s("127.0.0.1");
  
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      ( "network/" + make_player_specific_variable_name
        ( p, "network/ip" ) ), s );
} // game_variables::get_ip()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set ip address of a given player.
 * \param p The index of the player.
 * \param ip The ip adress.
 */
void  ptb::game_variables::set_ip(unsigned int p, const std::string& ip)
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<std::string>
      ( make_persistent_variable_name
        ( "network/" +
          make_player_specific_variable_name( p, "network/ip" )), ip ) );
} // game_variables::set_ip()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the number of players as selected at the beginning of the game.
 */
unsigned int ptb::game_variables::get_players_count()
{
  return ptb_game_variables_get_value
    ( "scenario/players_count", (unsigned int)0 );
} // game_variables::get_players_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the number of players.
 * \param c The number of players.
 */
void ptb::game_variables::set_players_count( unsigned int c )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>( "scenario/players_count", c ) );
} // game_variables::set_players_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the name of the last level exit used.
 * \param level The level filename.
 * \param p The index of the player.
 */
std::string ptb::game_variables::get_last_level_exit
( const std::string& level, unsigned int p )
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      ( level + "/" + make_player_specific_variable_name
        ( p, "last_exit" ) ), std::string() );
} // game_variables::get_last_level_exit()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the name of the last level exit used for a given player.
 * \param level The level filename.
 * \param p The index of the player.
 * \param e The name of the exit.
 */
void ptb::game_variables::set_last_level_exit
( const std::string& level, unsigned int p, const std::string& e )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<std::string>
      ( make_persistent_variable_name
        ( level + "/" +
          make_player_specific_variable_name( p, "last_exit" )), e ) );
} // game_variables::set_last_level_exit()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the name of the next level to load.
 */
std::string ptb::game_variables::get_next_level_name()
{
  return ptb_game_variables_get_value( "scenario/next_level", std::string() );
} // game_variables::get_next_level_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the name of the next level to load.
 * \param n The name of the level.
 */
void ptb::game_variables::set_next_level_name( const std::string& n )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<std::string>( "scenario/next_level", n ) );
} // game_variables::set_next_level_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a level precedence.
 * \param prec The filename of the level that preceeds the other.
 * \param next The filename of the level that suceeds the other.
 */
void ptb::game_variables::set_level_precedence
( const std::string& prec, const std::string& next )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<std::string>
      ( make_persistent_variable_name(prec + "/continues_with"),
        next ) );
} // game_variables::set_level_precedence()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a level has been finished.
 * \param lvl The filename of the level.
 * \param b The new status.
 */
void ptb::game_variables::set_finished_level( const std::string& lvl, bool b)
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( make_persistent_variable_name(lvl + "/is_finished"), b ) );
} // game_variables::set_finished_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return if a given level has been finished.
 * \param lvl The filename of the level.
 */
bool ptb::game_variables::level_is_finished(const std::string& lvl)
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name(lvl + "/is_finished"), false);
} // game_variables::level_is_finished()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the state of a level object.
 * \param object The name of the object.
 * \param b The status of the object.
 */
void ptb::game_variables::set_level_object_state
( const std::string& object, bool b )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( make_persistent_level_variable_name
        ( "level_object/" + object + "/state"), b ) );
} // game_variables::set_level_object_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the state of a level object.
 * \param object The name of the object.
 */
bool ptb::game_variables::get_level_object_state( const std::string& object )
{
  return get_level_object_state( get_main_level_name(), object );
} // game_variables::get_level_object_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the state of a level object.
 * \param level The level to consider.
 * \param object The name of the object.
 */
bool ptb::game_variables::get_level_object_state
( const std::string& level, const std::string& object)
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      (level + "/level_object/" + object + "/state"), false);
} // game_variables::get_level_object_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the filename of a level object picture.
 * \param object The name of the object.
 * \param filename The filename of the level object picture.
 */
void ptb::game_variables::set_level_object_filename
( const std::string& object, const std::string& filename )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<std::string>
      ( make_persistent_level_variable_name
        ( "level_object/" +  object + "/picture_filename"), filename ) );
} // game_variables::set_level_object_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the filename of a level object picture.
 * \param object The name of the object.
 */
std::string ptb::game_variables::get_level_object_filename
( const std::string& object )
{
  return get_level_object_filename( get_main_level_name(), object );
} // game_variables::get_level_object_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the filename of a level object picture.
 * \param level The level to consider.
 * \param object The name of the object.
 */
std::string ptb::game_variables::get_level_object_filename
( const std::string& level, const std::string& object )
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      ( level + "/level_object/" + object +
        "/picture_filename"), std::string());
} // game_variables::get_level_object_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the name of a level object picture.
 * \param object The name of the object.
 * \param name The name of the level object picture.
 */
void ptb::game_variables::set_level_object_name
( const std::string& object, const std::string& name )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<std::string>
      ( make_persistent_level_variable_name
        ( "level_object/" + object + "/picture_name"), name ) );
} // game_variables::set_level_object_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the name of a level object picture.
 * \param object The name of the object.
 */
std::string ptb::game_variables::get_level_object_name
( const std::string& object )
{
  return get_level_object_name( get_main_level_name(), object );
} // game_variables::get_level_object_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the name of a level object picture.
 * \param level The level to consider.
 * \param object The name of the object.
 */
std::string ptb::game_variables::get_level_object_name
( const std::string& level, const std::string& object )
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      (level + "/level_object/" + object + "/picture_name"), std::string());
} // game_variables::get_level_object_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the state of a hideout in the current main level.
 * \param id The identifier of the hideout.
 * \param b The new state.
 */
void ptb::game_variables::set_hideout_state( const std::string& id, bool b )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( make_persistent_level_variable_name
        ( "hideout/" + id), b ) );
} // game_variables::set_hideout_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the state of a given hideout in the current main level.
 * \param id The identifier of the hideout.
 */
bool ptb::game_variables::get_hideout_state( const std::string& id )
{
  return ptb_game_variables_get_value
    ( make_persistent_level_variable_name("hideout/" + id), false);
} // game_variables::get_hideout_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the name of a level according its filename.
 * \param filename The filename of the level.
 */
std::string ptb::game_variables::get_level_name(const std::string& filename)
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name(filename + "/name"), std::string() );
} // game_variables::get_level_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the name of a level.
 * \param filename The filename of the level.
 * \param name The name of the level.
 */
void ptb::game_variables::set_level_name
( const std::string& filename, const std::string& name )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<std::string>
      ( make_persistent_variable_name(filename + "/name"), name ) );
} // game_variables::set_level_precedence()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the name of current main level.
 */
std::string ptb::game_variables::get_main_level_name()
{
  return ptb_game_variables_get_value
    ( "scenario/main_level_name", std::string() );
} // game_variables::get_main_level_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the name of current main level.
 * \param n The name of the current main level.
 */
void ptb::game_variables::set_main_level_name
( const std::string& n )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<std::string>
      ( "scenario/main_level_name", n ) );
} // game_variables::set_main_level_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the current profile name.
 */
std::string ptb::game_variables::get_profile_name()
{
  return ptb_game_variables_get_value
    ( "scenario/profile_name", std::string() );
} // game_variables::get_profile_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the profile name.
 * \param n The name of the profile.
 */
void ptb::game_variables::set_profile_name( const std::string& n )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<std::string>
      ( "scenario/profile_name", n ) );
} // game_variables::set_profile_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the state of a mini-game (true if unlock).
 * \param name The name of the mini-game.
 */
bool ptb::game_variables::get_mini_game_status( const std::string& name )
{
  return ptb_game_variables_get_value( "mini-game/"+name, false );
} // game_variables::get_mini_game_status()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the state of a mini-game (true if unlock).
 * \param name The name of the mini-game.
 * \param v The new value of the mini-game state.
 */
void ptb::game_variables::set_mini_game_status
( const std::string& name, bool v )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>( "mini-game/"+name, v ) );
} // game_variables::set_mini_game_status()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if all mini-game are unlocked.
 */
bool ptb::game_variables::get_all_mini_game_unlocked_status()
{
  return ptb_game_variables_get_value( "cheat/mini-game_unlocked", false );
} // game_variables::get_all_mini_game_unlocked_status()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if all mini-game are unlocked.
 * \param v The new value of the mini-game status.
 */
void ptb::game_variables::set_all_mini_game_unlocked_status( bool v )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>( "cheat/mini-game_unlocked", v ) );
} // game_variables::set_all_mini_game_unlocked_status()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the menu "password" is visible.
 */
bool ptb::game_variables::get_password_menu_visibility()
{
#ifndef NDEBUG
  return ptb_game_variables_get_value( "cheat/password", true );
#else
  return ptb_game_variables_get_value( "cheat/password", false );
#endif
} // game_variables::get_password_menu_visibility()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the visibility of the menu "password".
 * \param v Visible or not.
 */
void ptb::game_variables::set_password_menu_visibility( bool v )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>( "cheat/password", v ) );
} // game_variables::set_password_menu_visibility()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the players can harm each other.
 */
bool ptb::game_variables::get_friendly_fire()
{
  return ptb_game_variables_get_value( "gameplay/friendly_fire", true );
} // game_variables::get_friendly_fire()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the players can harm each other.
 * \param v Harm or don't.
 */
void ptb::game_variables::set_friendly_fire( bool v )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>( "gameplay/friendly_fire", v ) );
} // game_variables::set_friendly_fire()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable of lives number of a given player.
 * \param p The index of the player.
 */
std::string ptb::game_variables::get_lives_count_variable_name
(unsigned int p )
{
  return make_player_specific_variable_name( p, "lives" );
} // game_variables::get_lives_count_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the number of lives of a given player.
 * \param p The index of the player.
 */
unsigned int ptb::game_variables::get_lives_count( unsigned int p)
{
  return ptb_game_variables_get_value
    ( get_lives_count_variable_name(p), (unsigned int)0 );
} // game_variables::get_lives_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the number of lives of a given player.
 * \param p The index of the player.
 * \param c The number of lives.
 */
void ptb::game_variables::set_lives_count( unsigned int p, unsigned int c )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( get_lives_count_variable_name(p), c ) );
} // game_variables::set_lives_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the persistent number of lives of a given player.
 * \param p The index of the player.
 */
unsigned int ptb::game_variables::get_persistent_lives_count( unsigned int p)
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name( get_lives_count_variable_name(p)), 
      (unsigned int)0 );
} // game_variables::get_persistent_lives_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the persistent number of lives of a given player.
 * \param p The index of the player.
 * \param c The number of lives.
 */
void ptb::game_variables::set_persistent_lives_count
( unsigned int p, unsigned int c )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( make_persistent_variable_name(get_lives_count_variable_name(p)), c ) );
} // game_variables::set_persistent_lives_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable of stones number of a given player.
 * \param p The index of the player.
 */
std::string ptb::game_variables::get_stones_count_variable_name
(unsigned int p )
{
  return make_player_specific_variable_name( p, "stones" );
} // game_variables::get_stones_count_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the number of stones of a given player.
 * \param p The index of the player.
 */
unsigned int ptb::game_variables::get_stones_count( unsigned int p)
{
  return ptb_game_variables_get_value
    ( get_stones_count_variable_name(p), (unsigned int)0 );
} // game_variables::get_stones_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the number of stones of a given player.
 * \param p The index of the player.
 * \param c The number of stones.
 */
void ptb::game_variables::set_stones_count( unsigned int p, unsigned int c )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( get_stones_count_variable_name(p), c ) );
} // game_variables::set_stones_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the persistent number of stones of a given player.
 * \param p The index of the player.
 */
unsigned int ptb::game_variables::get_persistent_stones_count( unsigned int p)
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name(get_stones_count_variable_name(p)),
      (unsigned int)0 );
} // game_variables::get_persistent_stones_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the persistent number of stones of a given player.
 * \param p The index of the player.
 * \param c The number of stones.
 */
void ptb::game_variables::set_persistent_stones_count
( unsigned int p, unsigned int c )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( make_persistent_variable_name(get_stones_count_variable_name(p)), c) );
} // game_variables::set_persistent_stones_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable of max energy level of a given player.
 * \param p The index of the player.
 */
std::string ptb::game_variables::get_max_energy_variable_name
(unsigned int p )
{
  return make_player_specific_variable_name( p, "max_energy" );
} // game_variables::get_max_energy_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the maximum energy of a given player.
 * \param p The index of the player.
 */
double ptb::game_variables::get_max_energy( unsigned int p )
{
  return ptb_game_variables_get_value
    ( get_max_energy_variable_name(p), (double)100 );
} // game_variables::get_max_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the maximum of energy of a given player.
 * \param p The index of the player.
 * \param v The maximum energy.
 */
void ptb::game_variables::set_max_energy( unsigned int p, double v )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<double>
      ( get_max_energy_variable_name(p), v ) );
} // game_variables::set_max_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the persistent maximum energy of a given player.
 * \param p The index of the player.
 */
double ptb::game_variables::get_persistent_max_energy( unsigned int p )
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      ( get_max_energy_variable_name(p)), (double)100 );
} // game_variables::get_persistent_max_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the persistent maximum of energy of a given player.
 * \param p The index of the player.
 * \param v The maximum energy.
 */
void ptb::game_variables::set_persistent_max_energy( unsigned int p, double v )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<double>
      ( make_persistent_variable_name
	( get_max_energy_variable_name(p)), v ) );
} // game_variables::set_persistent_max_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable of max energy in current level.
 */
std::string ptb::game_variables::get_current_level_max_energy_variable_name()
{
  return get_main_level_name() + "/max_energy_state";
} // game_variables::get_current_level_max_energy_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return if bonus of max_energy has been found in the current level.
 */
bool ptb::game_variables::get_current_level_max_energy_state()
{
  return ptb_game_variables_get_value
    ( get_current_level_max_energy_variable_name(), false);
} // game_variables::get_current_level_max_energy_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if bonus of max_energy has been found in the current level.
 * \param b The new state.
 */
void ptb::game_variables::set_current_level_max_energy_state( bool b )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( get_current_level_max_energy_variable_name(), b ) );
} // game_variables::set_current_level_max_energy_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return if bonus of persistent max_energy has been found 
 * in the current level.
 */
bool ptb::game_variables::get_persistent_current_level_max_energy_state()
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      ( get_current_level_max_energy_variable_name() ), false);
} // game_variables::get_persistent_current_level_max_energy_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if bonus of max_energy has been found in the current level.
 * \param b The new state.
 */
void ptb::game_variables::set_persistent_current_level_max_energy_state
( bool b )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( make_persistent_variable_name
        ( get_current_level_max_energy_variable_name() ), b ) );
} // game_variables::set_persistent_current_level_max_energy_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable of max energy in current level for a given player.
 * \param index Index of considered player.
 */
std::string ptb::game_variables::get_player_max_energy_variable_name
(unsigned int index)
{
  return get_main_level_name() + "/" + 
    make_player_specific_variable_name(index, "max_energy_state");
} // game_variables::get_player_max_energy_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return if bonus of max_energy has been found in the current level by
 * a specific player.
 * \param index Index of considered player.
 */
bool ptb::game_variables::get_current_level_max_energy_state
( unsigned int index )
{
  return ptb_game_variables_get_value
    ( get_player_max_energy_variable_name(index), false);
} // game_variables::get_current_level_max_energy_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if bonus of max_energy has been found in the current level.
 * \param index Index of considered player.
 * \param b The new state.
 */
void ptb::game_variables::set_current_level_max_energy_state
( unsigned int index, bool b )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      (get_player_max_energy_variable_name(index), b ) );
} // game_variables::set_current_level_max_energy_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return if bonus of persistent max_energy has been found 
 * in the current level by a specific player.
 * \param index Index of considered player.
 */
bool ptb::game_variables::get_persistent_current_level_max_energy_state
( unsigned int index )
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      ( get_player_max_energy_variable_name(index) ), false);
} // game_variables::get_persistent_current_level_max_energy_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if bonus of persistent max_energy has been found 
 * in the current level.
 * \param index Index of considered player.
 * \param b The new state.
 */
void ptb::game_variables::set_persistent_current_level_max_energy_state
( unsigned int index, bool b )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( make_persistent_variable_name
        ( get_player_max_energy_variable_name(index) ), b ) );
} // game_variables::set_persistent_current_level_max_energy_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return if boss has been killed in the current level.
 */
bool ptb::game_variables::get_current_level_boss_killed()
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      ( get_main_level_name() + "/boss_killed"), false);
} // game_variables::get_current_level_boss_killed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if boss has been killed in the current level.
 * \param b The new state.
 */
void ptb::game_variables::set_current_level_boss_killed( bool b )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( make_persistent_variable_name
        ( get_main_level_name() + "/boss_killed"), b ) );
} // game_variables::set_current_level_boss_killed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return if the mini_game has been unlocked in the current level.
 */
bool ptb::game_variables::get_current_level_mini_game_state()
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      ( get_main_level_name() + "/mini_game_state"), false);
} // game_variables::get_current_level_mini_game_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if the mini_game has been unlocked in the current level.
 * \param b The new state.
 */
void ptb::game_variables::set_current_level_mini_game_state( bool b )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( make_persistent_variable_name
        ( get_main_level_name() + "/mini_game_state"), b ) );
} // game_variables::set_current_level_mini_game_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable name for score of a given player.
  * \param p The index of the player.
 */
std::string ptb::game_variables::get_score_variable_name(unsigned int p)
{
  return make_player_specific_variable_name( p, "score" );
} // game_variables::make_score_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the score of a given player.
 * \param p The index of the player.
 */
unsigned int ptb::game_variables::get_score(unsigned int p)
{
  return ptb_game_variables_get_value
    ( get_score_variable_name( p ) , (unsigned int)0 );
} // game_variables::get_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the persistent score of a given player.
 * \param p The index of the player.
 */
unsigned int ptb::game_variables::get_persistent_score(unsigned int p)
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name(get_score_variable_name( p )) ,
      (unsigned int)0 );
} // game_variables::get_persistent_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the score of a given player.
 * \param p The index of the player.
 * \param c The number of score.
 */
void ptb::game_variables::set_score( unsigned int p, unsigned int c )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( get_score_variable_name( p ) , c ) );
} // game_variables::set_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the persistent score of a given player.
 * \param p The index of the player.
 * \param c The number of score.
 */
void ptb::game_variables::set_persistent_score
( unsigned int p, unsigned int c )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( make_persistent_variable_name(get_score_variable_name( p )) , c ) );
} // game_variables::set_persistent_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add some points to the score of a given player.
 * \param p The index of the player.
 * \param c The number of points.
 */
void ptb::game_variables::add_score( unsigned int p, unsigned int c )
{
  set_score( p, get_score(p) + c );
} // game_variables::add_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Subtract some points to the score of a given player.
 * \param p The index of the player.
 * \param c The number of points.
 */
void ptb::game_variables::sub_score( unsigned int p, unsigned int c )
{
  if ( get_score(p) >= c )
    set_score( p, get_score(p) - c );
  else
    set_score( p, 0 );
} // game_variables::sub_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable name containing the state of the power of air for a
 *        given player.
 * \param p The index of the player.
 */
std::string ptb::game_variables::get_air_power_variable_name(unsigned int p)
{
  return make_player_specific_variable_name( p, "air" );
} // game_variables::get_air_power_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if a given player has the air power.
 * \param p The index of the player.
 */
bool ptb::game_variables::get_air_power( unsigned int p )
{
  return ptb_game_variables_get_value( get_air_power_variable_name(p), false );
} // game_variables::get_air_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a given player has the air power.
 * \param p The index of the player.
 * \param v The new status.
 */
void ptb::game_variables::set_air_power( unsigned int p, bool v )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>( get_air_power_variable_name(p), v ) );
} // game_variables::set_air_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if a given player has the persistent air power.
 * \param p The index of the player.
 */
bool ptb::game_variables::get_persistent_air_power( unsigned int p )
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      ( get_air_power_variable_name(p)), false );
} // game_variables::get_persistent_air_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a given player has the persistent air power.
 * \param p The index of the player.
 * \param v The new status.
 */
void ptb::game_variables::set_persistent_air_power( unsigned int p, bool v )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( make_persistent_variable_name
	( get_air_power_variable_name(p)), v ) );
} // game_variables::set_persistent_air_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable name containing the state of the power of fire for a
 *        given player.
 * \param p The index of the player.
 */
std::string ptb::game_variables::get_fire_power_variable_name(unsigned int p)
{
  return make_player_specific_variable_name( p, "fire" );
} // game_variables::get_fire_power_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if a given player has the fire power.
 * \param p The index of the player.
 */
bool ptb::game_variables::get_fire_power( unsigned int p )
{
  return ptb_game_variables_get_value
    ( get_fire_power_variable_name(p), false );
} // game_variables::get_fire_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a given player has the fire power.
 * \param p The index of the player.
 * \param v The new status.
 */
void ptb::game_variables::set_fire_power( unsigned int p, bool v )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>( get_fire_power_variable_name(p), v ) );
} // game_variables::set_fire_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if a given player has the persistent fire power.
 * \param p The index of the player.
 */
bool ptb::game_variables::get_persistent_fire_power( unsigned int p )
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      ( get_fire_power_variable_name(p)), false );
} // game_variables::get_persistent_fire_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a given player has the persistent fire power.
 * \param p The index of the player.
 * \param v The new status.
 */
void ptb::game_variables::set_persistent_fire_power( unsigned int p, bool v )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( make_persistent_variable_name
	( get_fire_power_variable_name(p)), v ) );
} // game_variables::set_persistent_fire_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable name containing the state of the power of 
 * water for a given player.
 * \param p The index of the player.
 */
std::string ptb::game_variables::get_water_power_variable_name(unsigned int p)
{
  return make_player_specific_variable_name( p, "water" );
} // game_variables::get_water_power_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if a given player has the water power.
 * \param p The index of the player.
 */
bool ptb::game_variables::get_water_power( unsigned int p )
{
  return ptb_game_variables_get_value
    ( get_water_power_variable_name(p), false );
} // game_variables::get_water_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a given player has a power.
 * \param p The index of the player.
 * \param v The new status.
 */
void ptb::game_variables::set_water_power( unsigned int p, bool v )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>( get_water_power_variable_name(p), v ) );
} // game_variables::set_water_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if a given player has the persistent water power.
 * \param p The index of the player.
 */
bool ptb::game_variables::get_persistent_water_power( unsigned int p )
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      ( get_water_power_variable_name(p) ), false );
} // game_variables::get_persistent_water_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a given player has the persistent water power.
 * \param p The index of the player.
 * \param v The new status.
 */
void ptb::game_variables::set_persistent_water_power( unsigned int p, bool v )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( make_persistent_variable_name
	( get_water_power_variable_name(p)), v ) );
} // game_variables::set_persistent_water_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable name tell that if a obeject is sniffable.
 * \param p The index of the player.
 * \param category The sniffable category.
 */
std::string ptb::game_variables::get_sniffable_variable_name
(unsigned int p, const std::string& category)
{
  return make_player_specific_variable_name( p, "sniffable/"+category );
} // game_variables::get_sniffable_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if a object is sniffable.
 * \param p The index of the player.
 * \param category The sniffable category.
  */
bool ptb::game_variables::get_persistent_sniffable
( unsigned int p, const std::string& category )
{
  return ptb_game_variables_get_value
    ( make_persistent_variable_name
      ( get_sniffable_variable_name(p,category) ), false );
} // game_variables::get_persistent_sniffable()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set that a category is sniffable.
 * \param p The index of the player.
 * \param category The sniffable category.
 */
void ptb::game_variables::set_persistent_sniffable
( unsigned int p, const std::string& category )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>
      ( make_persistent_variable_name
	( get_sniffable_variable_name(p,category)), true ) );
} // game_variables::set_persistent_sniffable()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the variable name for corrupting bonus count.
 */
std::string ptb::game_variables::get_corrupting_bonus_count_variable_name()
{
  return "level/corrupting_bonus_count";
} // game_variables::make_corrupting_bonus_count_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the number of corrupting_bonus found.
 */
unsigned int ptb::game_variables::get_corrupting_bonus_count()
{
  return ptb_game_variables_get_value
    ( get_corrupting_bonus_count_variable_name(), (unsigned int)0 );
} // game_variables::get_corrupting_bonus_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the number of corrupting_bonus found.
 * \param c The new number of corrupting_bonus found.
 */
void ptb::game_variables::set_corrupting_bonus_count( unsigned int c )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( get_corrupting_bonus_count_variable_name(), c ) );
} // game_variables::set_corrupting_bonus_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the number of corrupting_bonus found in the previous level.
 * \param lvl The level in which we start with this count.
 */
unsigned int ptb::game_variables::get_last_corrupting_bonus_count
(const std::string& lvl)
{
  return ptb_game_variables_get_value
    (  make_persistent_variable_name
       (lvl + "/last_corrupting_bonus_count"), (unsigned int)0 );
} // game_variables::get_last_corrupting_bonus_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the number of corrupting_bonus found in the previous level.
 * \param lvl The level in which we start with this count.
 * \param c The number of corrupting_bonus found.
 */
void ptb::game_variables::set_last_corrupting_bonus_count
( const std::string& lvl, unsigned int c )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>
      ( make_persistent_variable_name
        (lvl + "/last_corrupting_bonus_count"), c ) );
} // game_variables::set_last_corrupting_bonus_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the x-position rate of corrupting bonus according camera center.
 */
double ptb::game_variables::get_corrupting_bonus_rate_x()
{
  return ptb_game_variables_get_value( "corrupting_bonus_rate_x", (double)0 );
} // game_variables::get_corrupting_bonus_rate_x()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the x-position rate of corrupting bonus according camera center.
 * \param x The rate on x-coordinate.
 */
void ptb::game_variables::set_corrupting_bonus_rate_x(double x)
{
   bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<double>
      ( "corrupting_bonus_rate_x", x ) );
} // game_variables::set_corrupting_bonus_rate_x()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the y-position rate of corrupting bonus according camera center.
 */
double ptb::game_variables::get_corrupting_bonus_rate_y()
{
  return ptb_game_variables_get_value( "corrupting_bonus_rate_y", (double)0 );
} // game_variables::get_corrupting_bonus_rate_y()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the y-position rate of corrupting bonus according camera center.
 * \param y The rate on y_coordinate.
 */
void ptb::game_variables::set_corrupting_bonus_rate_y(double y)
{
   bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<double>
      ( "corrupting_bonus_rate_y", y ) );
} // game_variables::set_corrupting_bonus_rate_y()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the current level has been started in demo mode.
 */
bool ptb::game_variables::demo_is_on()
{
  return ptb_game_variables_get_value( "demo/is_on", false );
} // game_variables::demo_is_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the current level has been started in demo mode.
 * \param v Mini-game mode or not.
 */
void ptb::game_variables::set_demo( bool v )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>( "demo/is_on", v ) );
} // game_variables::set_demo()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the current level is a mini-game.
 */
bool ptb::game_variables::mini_game_is_on()
{
  return ptb_game_variables_get_value( "mini_game/is_on", false );
} // game_variables::mini_game_is_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the current level has been started in demo mode.
 * \param v Mini-game mode or not.
 */
void ptb::game_variables::set_mini_game( bool v )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<bool>( "mini_game/is_on", v ) );
} // game_variables::set_mini_game()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the last selected mini-game.
 */
unsigned int ptb::game_variables::get_last_mini_game()
{
  return ptb_game_variables_get_value( "mini_game/last", (unsigned int)0 );
} // game_variables::get_last_mini_game()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the last selected level.
 * \param index Mini-game index.
 */
void ptb::game_variables::set_last_mini_game( unsigned int index )
{
  bear::engine::game::get_instance().set_game_variable
    ( bear::engine::variable<unsigned int>( "mini_game/last", index ) );
} // game_variables::set_last_mini_game()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the video recording of the game is on.
 */
bool ptb::game_variables::record_game()
{
  return ptb_game_variables_get_value( "record_game", false );
} // game_variables::record_game()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a variable of type string, return the parameter if the variable
 *        does not exist.
 * \param n The name of the variable.
 */
std::string ptb::game_variables::get_string_default( const std::string& n )
{
  return ptb_game_variables_get_value( n, n );
} // game_variables::get_string_default()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a variable name prefixed with the default variable name of a given
 *        player.
 * \param p The index of the player.
 * \param n The name of the variable.
 */
std::string ptb::game_variables::make_player_specific_variable_name
( unsigned int p, const std::string& n )
{
  std::ostringstream oss;
  oss << "player_" << p << '/' << n;

  return oss.str();
} // game_variables::make_player_specific_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a variable name prefixed with persistent option prefix.
 * \param n The name of the variable.
 */
std::string ptb::game_variables::make_persistent_variable_name
( const std::string& n )
{
  return PTB_PERSISTENT_PREFIX + n;
} // game_variables::make_persistent_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a persistent level variable name for the current main level.
 * \param n The name of the variable.
 */
std::string ptb::game_variables::make_persistent_level_variable_name
( const std::string& n )
{
  return make_persistent_variable_name( get_main_level_name() + "/" + n );
} // game_variables::make_persistent_level_variable_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load player's variables.
 */
void ptb::game_variables::load_player_variables()
{
  load_player_variables(1);
  load_player_variables(2);

  set_current_level_max_energy_state
    ( get_persistent_current_level_max_energy_state() );
} // game_variables::load_player_variables()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load player's variables.
 * \param p The index of the player.
 */
void ptb::game_variables::load_player_variables(unsigned int p)
{
  set_score(p,get_persistent_score(p));
  set_lives_count(p,get_persistent_lives_count(p));
  set_stones_count(p,get_persistent_stones_count(p));
  set_water_power(p,get_persistent_water_power(p));
  set_air_power(p,get_persistent_air_power(p));
  set_fire_power(p,get_persistent_fire_power(p));
  set_max_energy(p,get_persistent_max_energy(p));
  set_current_level_max_energy_state
    (p,get_persistent_current_level_max_energy_state(p));
} // game_variables::load_player_variables()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save player's variables. 
 */
void ptb::game_variables::save_player_variables()
{
  save_player_variables(1);
  save_player_variables(2);

  set_persistent_current_level_max_energy_state
    ( get_current_level_max_energy_state() );
} // game_variables::save_player_variables()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save player's variables. 
 * \param p The index of the player.
 */
void ptb::game_variables::save_player_variables(unsigned int p)
{
  set_persistent_score(p,get_score(p));
  set_persistent_lives_count(p,get_lives_count(p));
  set_persistent_stones_count(p,get_stones_count(p));
  set_persistent_water_power(p,get_water_power(p));
  set_persistent_air_power(p,get_air_power(p));
  set_persistent_fire_power(p,get_fire_power(p));
  set_persistent_max_energy(p,get_max_energy(p));
  set_persistent_current_level_max_energy_state
    (p,get_current_level_max_energy_state(p));
} // game_variables::save_player_variables()
