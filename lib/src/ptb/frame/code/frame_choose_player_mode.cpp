/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_choose_player_mode class.
 * \author Angibaud Sebastien
 */
#include "ptb/frame/frame_choose_player_mode.hpp"
#include "ptb/frame/frame_play_story.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/defines.hpp"

#include "engine/game.hpp"
#include "engine/system/game_filesystem.hpp"
#include "engine/variable/variable_list_reader.hpp"
#include "engine/variable/var_map.hpp"

#include "gui/callback_function.hpp"

#include <boost/bind.hpp>
#include <libintl.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer onwing the window.
 */
ptb::frame_choose_player_mode::frame_choose_player_mode
( windows_layer* owning_layer )
  : menu_frame(owning_layer, gettext("Start game"))
{
  create_controls();
} // frame_choose_player_mode::frame_choose_player_mode()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_choose_player_mode::create_controls()
{
  push
    ( gettext("Back"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_choose_player_mode::close_window, this ) ) );

  push
    ( gettext("Two players (local)"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_choose_player_mode::start_game, this, 2 ) ) );

  push
    ( gettext("One player"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_choose_player_mode::start_game, this, 1 ) ) );

  fit();
} // frame_choose_player_mode::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start the game.
 * \param p The number of players.
 */
void ptb::frame_choose_player_mode::start_game( unsigned int p ) const
{
  game_variables::set_players_count(p);

  std::string pattern(PTB_PERSISTENT_PREFIX);
  pattern += ".*";
  bear::engine::game::get_instance().erase_game_variables( pattern );

  load_game_variables();
  bear::engine::var_map vars;
  bear::engine::game::get_instance().get_game_variables
    ( vars, ".*continues_with" );

  if ( vars.begin<std::string>() != vars.end<std::string>() )
    show_window( new frame_play_story(&get_layer()) );
  else
    bear::engine::game::get_instance().set_waiting_level
      ( "level/forest-intro.cl" );
} // frame_choose_player_mode::start_game()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load game variables.
 )*/
void ptb::frame_choose_player_mode::load_game_variables() const
{
  const bear::engine::game& g( bear::engine::game::get_instance() );

  std::string filename
    ( g.get_game_filesystem().get_custom_config_file_name
      (PTB_PROFILES_FOLDER) + game_variables::get_profile_name() + "/" );

  if ( game_variables::get_players_count() == 1 )
    filename += PTB_SAVE_ONE_PLAYER_FILENAME;
  else
    filename += PTB_SAVE_TWO_PLAYERS_FILENAME;

  std::ifstream f( filename.c_str() );
  bear::engine::var_map vars;
  bear::engine::variable_list_reader reader;

  reader(f, vars);

  bear::engine::game::get_instance().set_game_variables(vars);
} // frame_choose_player_mode::load_game_variables()
