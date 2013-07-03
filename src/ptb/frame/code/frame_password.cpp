/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_password class.
 * \author Julien Jorge
 */
#include "ptb/frame/frame_password.hpp"

#include "ptb/frame/frame_start_menu.hpp"
#include "ptb/frame/theme_colors.hpp"
#include "ptb/layer/windows_layer.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/gauge.hpp"
#include "ptb/util/player_util.hpp"

#include "engine/game.hpp"
#include "engine/resource_pool.hpp"
#include "engine/variable/variable.hpp"
#include "gui/button.hpp"
#include "gui/callback_function.hpp"
#include "gui/static_text.hpp"

#include <boost/bind.hpp>
#include <claw/string_algorithm.hpp>
#include <libintl.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer owning the window.
 */
ptb::frame_password::frame_password( windows_layer* owning_layer )
  : frame(owning_layer, gettext("Password"))
{
  create_controls();
} // frame_password::frame_password()

/*----------------------------------------------------------------------------*/
/**
 * \brief Validate the selected action.
 */
void ptb::frame_password::validate()
{
  std::vector<std::string> command;
  std::string text( m_password->get_text() );

  claw::text::trim(text);
  claw::text::squeeze(text, " ");
  claw::text::split(command, text, ' ');

  if ( !command.empty() )
    execute_command(command);
} // frame_password::validate()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_password::create_controls()
{
  bear::gui::visual_component* text = create_input();
  bear::gui::visual_component* back = create_back();

  back->set_right( text->right() );
  text->set_bottom( back->top() + get_margin() );

  fit( get_margin() );
} // frame_password::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the text input control.
 */
bear::gui::visual_component* ptb::frame_password::create_input()
{
  m_password =
    new bear::gui::text_input( get_font(), claw::graphic::red_pixel );

  m_password->add_enter_callback
    ( bear::gui::callback_function_maker
      ( boost::bind( &frame_password::validate, this ) ) );

  m_password->set_width(300);
  set_borders_down(*m_password);
  insert_control(*m_password);

  return m_password;
} // frame_password::create_input()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "back" button.
 */
bear::gui::visual_component* ptb::frame_password::create_back()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Back"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_password::close_window, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_password::create_back()

/*----------------------------------------------------------------------------*/
/**
 * \brief Execute a command entered by the user.
 * \param command The tokens read on the command line.
 */
void ptb::frame_password::execute_command
( const std::vector<std::string>& command ) const
{
  CLAW_PRECOND( !command.empty() );

  if ( command[0] == "goto" )
    command_load_level(command);
  else if ( command[0] == "give" )
    command_give(command, 1);
  else if ( command[0] == "givetoo" )
    command_give(command, 2);
  else if ( command[0] == "gamevar" )
    command_game_variable(command);
  else if ( command[0] == "unlock" )
    command_unlock(command);
  else
    claw::logger << claw::log_warning << "Unknow command '" << command[0]
                 << "'" << std::endl;
} // frame_password::execute_command()

/*----------------------------------------------------------------------------*/
/**
 * \brief Execute a 'goto' command.
 * \param command The tokens read on the command line.
 */
void ptb::frame_password::command_load_level
( const std::vector<std::string>& command ) const
{
  CLAW_PRECOND( command[0] == "goto" );

  if ( command.size() == 2 )
    {
      if ( bear::engine::resource_pool::get_instance().exists(command[1]) )
        {
          game_variables::set_next_level_name( command[1] );
          show_window
            ( new frame_start_menu
              (&get_layer(), true, playability_type::one_or_two_players) );
        }
      else
        claw::logger << claw::log_warning << "goto: no level named '"
                     << command[1] << "'." << std::endl;
    }
  else
    claw::logger << claw::log_warning << "goto: one parameter required, "
                 << (command.size()-1) << " given." << std::endl;
} // frame_password::command_load_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Execute a 'unlock' command.
 * \param command The tokens read on the command line.
 */
void ptb::frame_password::command_unlock
( const std::vector<std::string>& command ) const
{
  CLAW_PRECOND( command[0] == "unlock" );

  if ( command.size() == 2 )
    {
      if ( command[1] == "mini-game" )
        game_variables::set_all_mini_game_unlocked_status(true);
      else
        claw::logger << claw::log_warning << "'"
                     << command[1] << "' cannot be unlocked." << std::endl;
    }
  else
    claw::logger << claw::log_warning << "unlock: one parameter required, "
                 << (command.size()-1) << " given." << std::endl;
} // frame_password::command_unlock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Execute a 'give' command.
 * \param command The tokens read on the command line.
 * \param index The index of the player to which we give something.
 */
void ptb::frame_password::command_give
( const std::vector<std::string>& command, unsigned int index ) const
{
  CLAW_PRECOND( (command[0] == "give") || (command[0] == "givetoo") );

  if ( command.size() == 2 )
    {
      player_proxy p =
        util::find_player( get_layer().get_level_globals(), index );

      if ( p != NULL )
        {
          const bool all = (command[1] == "all");

          if ( all || (command[1] == "stones") )
            game_variables::set_stones_count
              (index, game_variables::get_stones_count(index) + 50);

          if ( all || (command[1] == "air") )
            game_variables::set_air_power(index, true);

          if ( all || (command[1] == "fire") )
            game_variables::set_fire_power(index, true);

          if ( all || (command[1] == "water") )
            game_variables::set_water_power(index, true);

          if ( all || (command[1] == "energy") )
            p.receive_energy( game_variables::get_max_energy(index) );

          if ( all || (command[1] == "oxygen") )
            p.receive_oxygen( p.get_oxygen_gauge().get_max_value() );

          if ( all || (command[1] == "life") )
            game_variables::set_lives_count
              (index, game_variables::get_lives_count(index) + 1);
        }
      else
        claw::logger << claw::log_warning << "give: can't find player #"
                     << index << '.' << std::endl;
    }
  else
    claw::logger << claw::log_warning << "give: one parameter required, "
                 << (command.size()-1) << " given." << std::endl;
} // frame_password::command_give()

/*----------------------------------------------------------------------------*/
/**
 * \brief Execute a 'gamevar' command.
 * \param command The tokens read on the command line.
 */
void ptb::frame_password::command_game_variable
( const std::vector<std::string>& command ) const
{
  CLAW_PRECOND( command[0] == "gamevar" );

  if ( command.size() == 3 )
    {
      if ( command[1] == "int" )
        command_game_variable<int>( command[2] );
      else if ( command[1] == "u_int" )
        command_game_variable<unsigned int>( command[2] );
      else if ( command[1] == "real" )
        command_game_variable<double>( command[2] );
      else if ( command[1] == "string" )
        command_game_variable<std::string>( command[2] );
      else if ( command[1] == "bool" )
        command_game_variable<bool>( command[2] );
      else
        claw::logger << claw::log_warning << "gamevar: '" << command[1]
                     << "' is not a valid type." << std::endl;
    }
  else
    claw::logger << claw::log_warning
                 << "gamevar: incorrect parameters."
                 << " Must be 'gamevar type name=value'."
                 << std::endl;
} // frame_password::command_game_variable()

/*----------------------------------------------------------------------------*/
/**
 * \brief Execute a 'gamevar' command.
 * \param var_value The assignement of the value to the variable.
 */
template<typename T>
void ptb::frame_password::command_game_variable
( const std::string& var_value ) const
{
  const std::size_t equal( var_value.find_first_of('=') );

  if ( equal == std::string::npos )
    claw::logger << claw::log_warning
                 << "gamevar: bad format."
                 << " Must be 'gamevar type name=value'."
                 << std::endl;
  else
    {
      std::string name( var_value.substr(0, equal) );
      std::string value( var_value.substr(equal+1) );

      if ( !claw::text::is_of_type<T>(value) )
        claw::logger << claw::log_warning << "gamevar: incorrect value."
                     << std::endl;
      else
        {
          std::istringstream iss(value);
          T v;

          iss >> v;
          bear::engine::game::get_instance().set_game_variable
            ( bear::engine::variable<T>(name, v) );
        }
    }
} // frame_password::command_game_variable()
