/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::level_variables class.
 * \author Julien Jorge
 */
#include "ptb/level_variables.hpp"

#include "engine/variable/variable.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief A function that gets a level variable.
 * \param lvl The level.
 * \param n The name of the variable.
 * \param def The default value to return if the variable is not set.
 */
template<typename T>
static T ptb_level_variables_get_value
( const bear::engine::level& lvl, const std::string& n, const T& def )
{
  bear::engine::variable<T> var(n);

  if ( lvl.level_variable_exists(var) )
    {
      lvl.get_level_variable(var);
      return var.get_value();
    }
  else
    return def;
} // ptb_level_variables_get_value()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the number of players on an exit.
 * \param lvl The level in which we take the variable.
 */
unsigned int
ptb::level_variables::get_players_on_exit( const bear::engine::level& lvl )
{
  return ptb_level_variables_get_value
    ( lvl, "players_on_exit", (unsigned int)0 );
} // level_variables::get_players_on_exit()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the number of players on an exit.
 * \param lvl The level in which we take the variable.
 * \param c The number of players.
 */
void ptb::level_variables::set_players_on_exit
( bear::engine::level& lvl, unsigned int c )
{
  lvl.set_level_variable
    ( bear::engine::variable<unsigned int>( "players_on_exit", c ) );
} // level_variables::set_players_on_exit()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the number of a given object in the level.
 * \param lvl The level in which we take the variable.
 * \param object_type The type of the object.
 */
unsigned int
ptb::level_variables::get_object_count
( const bear::engine::level& lvl, const std::string& object_type )
{
  return ptb_level_variables_get_value
    ( lvl, "object_count/" + object_type, (unsigned int)0 );
} // level_variables::get_object_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the number of a given object in the level.
 * \param lvl The level in which we take the variable.
 * \param object_type The type of the object.
 * \param nb The number of killed enemies.
 */
void ptb::level_variables::set_object_count
( bear::engine::level& lvl, const std::string& object_type, unsigned int nb )
{
  lvl.set_level_variable
    ( bear::engine::variable<unsigned int>
      ( "object_count/" + object_type, nb ) );
} // level_variables::set_object_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the number of killed items of a given type in the level.
 * \param lvl The level in which we take the variable.
 * \param object_type The type of the object.
 */
unsigned int
ptb::level_variables::get_killed_object_count
( const bear::engine::level& lvl, const std::string& object_type )
{
  return ptb_level_variables_get_value
    ( lvl, "killed_object_count/" + object_type, (unsigned int)0 );
} // level_variables::get_killed_object_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the number of killed items a given type in the level.
 * \param lvl The level in which we take the variable.
 * \param object_type The type of the object.
 * \param nb The number of killed enemies.
 */
void ptb::level_variables::set_killed_object_count
( bear::engine::level& lvl, const std::string& object_type, unsigned int nb )
{
  lvl.set_level_variable
    ( bear::engine::variable<unsigned int>
      ( "killed_object_count/" + object_type, nb ) );
} // level_variables::set_killed_object_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the hazelnut is currently found.
 * \param lvl The level in which we take the variable.
 */
bool ptb::level_variables::get_current_hazelnut
( const bear::engine::level& lvl )
{
  return ptb_level_variables_get_value
    ( lvl, "current_hazelnut", false );
} // level_variables::get_current_hazelnut()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if the hazelnut is currently found.
 * \param lvl The level in which we take the variable.
 * \param v Found or not.
 */
void ptb::level_variables::set_current_hazelnut
( bear::engine::level& lvl, bool v )
{
  lvl.set_level_variable
    ( bear::engine::variable<bool>( "current_hazelnut", v ) );
} // level_variables::set_current_hazelnut()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the hazelnut has been found.
 * \param lvl The level in which we take the variable.
 */
bool ptb::level_variables::get_hazelnut_found
( const bear::engine::level& lvl )
{
  return ptb_level_variables_get_value
    ( lvl, "hazelnut_found", false );
} // level_variables::get_found_hazelnut()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if the hazelnut has been found.
 * \param lvl The level in which we take the variable.
 * \param v Found or not.
 */
void ptb::level_variables::set_hazelnut_found
( bear::engine::level& lvl, bool v )
{
  lvl.set_level_variable
    ( bear::engine::variable<bool>( "hazelnut_found", v ) );
} // level_variables::set_hazelnut_found()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the secret_level has been found.
 * \param lvl The level in which we take the variable.
 */
bool ptb::level_variables::get_secret_level_found
( const bear::engine::level& lvl )
{
  return ptb_level_variables_get_value
    ( lvl, "secret_level_found", false );
} // level_variables::get_found_secret_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if the secret level has been found.
 * \param lvl The level in which we take the variable.
 * \param v Found or not.
 */
void ptb::level_variables::set_secret_level_found
( bear::engine::level& lvl, bool v )
{
  lvl.set_level_variable
    ( bear::engine::variable<bool>( "secret_level_found", v ) );
} // level_variables::set_secret_level_found()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the number of honeypot found.
 * \param lvl The level in which we take the variable.
 */
unsigned int
ptb::level_variables::get_honeypots_found( const bear::engine::level& lvl )
{
  return ptb_level_variables_get_value
    ( lvl, "honeypots_found", (unsigned int)0 );
} // level_variables::get_honeypots_found()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the number of honeypots found.
 * \param lvl The level in which we take the variable.
 * \param nb The number of found honeypots.
 */
void ptb::level_variables::set_honeypots_found
( bear::engine::level& lvl, unsigned int nb )
{
  lvl.set_level_variable
    ( bear::engine::variable<unsigned int>( "honeypots_found", nb ) );
} // level_variables::set_honeypots_found()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get if a given honeypot has been found.
 * \param lvl The level in which we take the variable.
 * \param id The identifier of the honeypot.
 */
bool
ptb::level_variables::get_honeypot_found
( const bear::engine::level& lvl, unsigned int id )
{
  std::ostringstream s;
  s << "honeypot " << id;
  std::string var(s.str());

  return ptb_level_variables_get_value( lvl, var, false );
} // level_variables::get_honeypots_found()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a given honeypot has been found.
 * \param lvl The level in which we take the variable.
 * \param id The identifier of honeypot.
 * \param b The new value.
 */
void ptb::level_variables::set_honeypot_found
( bear::engine::level& lvl, unsigned int id, bool b )
{
  std::ostringstream s;
  s << "honeypot " << id;
  std::string var(s.str());

  lvl.set_level_variable( bear::engine::variable<bool>( var, b ) );
} // level_variables::set_honeypots_found()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if we are leaving the level.
 * \param lvl The level in which we take the variable.
 */
bool ptb::level_variables::is_exiting( const bear::engine::level& lvl )
{
  return ptb_level_variables_get_value( lvl, "exiting", false );
} // level_variables::is_exiting()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set that we are leaving the level.
 * \param lvl The level in which we take the variable.
 */
void ptb::level_variables::set_exiting( bear::engine::level& lvl )
{
  lvl.set_level_variable
    ( bear::engine::variable<bool>( "exiting", true ) );
} // level_variables::set_exiting()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the owl was met.
 * \param lvl The level in which we take the variable.
 */
bool ptb::level_variables::owl_is_met( const bear::engine::level& lvl )
{
  return ptb_level_variables_get_value( lvl, "met_the_owl", false );
} // level_variables::owl_is_met()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set that the owl is met.
 * \param lvl The level in which we take the variable.
 */
void ptb::level_variables::meet_the_owl( bear::engine::level& lvl )
{
  lvl.set_level_variable
    ( bear::engine::variable<bool>( "met_the_owl", true ) );
} // level_variables::meet_the_owl()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set that all hideouts are found.
 * \param lvl The level in which we take the variable.
 */
void ptb::level_variables::all_hideouts_found
( bear::engine::level& lvl )
{
  lvl.set_level_variable
    ( bear::engine::variable<bool>( "all_hideouts_found", true ) );
} // level_variables::all_hideouts_found()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the players can harm each other.
 * \param lvl The level in which we take the variable.
 */
bool ptb::level_variables::get_friendly_fire(bear::engine::level& lvl)
{
  return ptb_level_variables_get_value( lvl, "friendly_fire", false );
} // game_variables::get_friendly_fire()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if the players can harm each other.
 * \param lvl The level in which we take the variable.
 * \param v Harm or don't.
 */
void ptb::level_variables::set_friendly_fire
( bear::engine::level& lvl, bool v )
{
  lvl.set_level_variable
    ( bear::engine::variable<bool>( "friendly_fire", v ) );
} // game_variables::set_friendly_fire()


/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if game over is allowed.
 * \param lvl The level in which we take the variable.
 */
bool ptb::level_variables::game_over_allowed(bear::engine::level& lvl)
{
  return ptb_level_variables_get_value( lvl, "game_over_allowed", true );
} // game_variables::game_over_allowed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if game over is allowed.
 * \param lvl The level in which we take the variable.
 * \param v Harm or don't.
 */
void ptb::level_variables::allow_game_over
( bear::engine::level& lvl, bool v )
{
  lvl.set_level_variable
    ( bear::engine::variable<bool>( "game_over_allowed", v ) );
} // game_variables::allow_game_over()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if game is on network.
 * \param lvl The level in which we take the variable.
 */
bool ptb::level_variables::is_network_game(bear::engine::level& lvl)
{
  return ptb_level_variables_get_value( lvl, "network_game", false );
} // game_variables::is_network_game()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if game is on network.
 * \param lvl The level in which we take the variable.
 * \param v The state.
 */
void ptb::level_variables::set_network_game
( bear::engine::level& lvl, bool v )
{
  lvl.set_level_variable
    ( bear::engine::variable<bool>( "network_game", v ) );
} // game_variables::set_network_game()
