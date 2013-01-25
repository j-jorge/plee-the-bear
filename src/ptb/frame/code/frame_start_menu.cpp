/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_start_menu class.
 * \author Julien Jorge
 */
#include "ptb/frame/frame_start_menu.hpp"

#include "ptb/defines.hpp"
#include "ptb/game_variables.hpp"
#include "engine/game.hpp"

#include "gui/callback_function.hpp"

#include <boost/bind.hpp>
#include <libintl.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer onwing the window.
 * \param use_loading Tell if we use the "loading" level.
 * \param playability Indicates the number of required players.
 */
ptb::frame_start_menu::frame_start_menu
( windows_layer* owning_layer, bool use_loading,
  playability_type::value_type playability )
  : menu_frame(owning_layer, gettext("Start game")),
    m_use_loading(use_loading), m_playability(playability)
{
  create_controls();
} // frame_start_menu::frame_start_menu()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_start_menu::create_controls()
{
  push
    ( gettext("Back"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_start_menu::close_window, this ) ) );

  if ( ( m_playability != playability_type::one_player_only )
       && ( m_playability != playability_type::no_player ) )
    push
      ( gettext("Two players (local)"),
        bear::gui::callback_function_maker
        ( boost::bind( &frame_start_menu::start_game, this, 2 ) ) );

  if ( ( m_playability != playability_type::two_players_only )
       && ( m_playability != playability_type::no_player ) )
    push
      ( gettext("One player"),
        bear::gui::callback_function_maker
        ( boost::bind( &frame_start_menu::start_game, this, 1 ) ) );

  fit();
} // frame_start_menu::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start the game.
 * \param p The number of players.
 */
void ptb::frame_start_menu::start_game( unsigned int p ) const
{
  game_variables::set_players_count(p);

  if ( m_use_loading )
    bear::engine::game::get_instance().set_waiting_level
      ( PTB_LOADING_LEVEL_NAME );
  else
    bear::engine::game::get_instance().set_waiting_level
      ( game_variables::get_next_level_name() );
} // frame_start_menu::start_game()
