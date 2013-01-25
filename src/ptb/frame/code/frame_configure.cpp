/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_configure class.
 * \author Julien Jorge
 */
#include "ptb/frame/frame_configure.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/frame/frame_audio.hpp"
#include "ptb/frame/frame_game_options.hpp"
#include "ptb/frame/frame_password.hpp"
#include "ptb/frame/frame_player_controls.hpp"
#include "ptb/frame/frame_screen.hpp"

#include "gui/callback_function.hpp"

#include <boost/bind.hpp>
#include <libintl.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer onwing the window.
 */
ptb::frame_configure::frame_configure( windows_layer* owning_layer )
  : menu_frame(owning_layer, gettext("Configuration"))
{
  create_controls();
} // frame_configure::frame_configure()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_configure::create_controls()
{
  push
    ( gettext("Back"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_configure::on_back, this ) ) );

  if ( game_variables::get_password_menu_visibility() == true )
    push
      ( gettext("Password"),
        bear::gui::callback_function_maker
        ( boost::bind( &frame_configure::on_password, this ) ) );

  push
    ( gettext("Audio"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_configure::on_audio, this ) ) );
  push
    ( gettext("Screen"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_configure::on_screen, this ) ) );
  push
    ( gettext("Game options"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_configure::on_game_options, this ) ) );
  push
    ( gettext("Player two's controls"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_configure::on_second_player_controls, this ) ) );
  push
    ( gettext("Player one's controls"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_configure::on_first_player_controls, this ) ) );

  fit( get_margin() );
} // frame_configure::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Show the frame used to configure the first player's controls.
 */
void ptb::frame_configure::on_first_player_controls()
{
  show_window( new frame_player_controls(&get_layer(), 1) );
} // frame_configure::on_first_player_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Show the frame used to configure the second player's controls.
 */
void ptb::frame_configure::on_second_player_controls()
{
  show_window( new frame_player_controls(&get_layer(), 2) );
} // frame_configure::on_second_player_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Show the frame used to configure the options.
 */
void ptb::frame_configure::on_game_options()
{
  show_window( new frame_game_options(&get_layer()) );
} // frame_configure::on_game_options()

/*----------------------------------------------------------------------------*/
/**
 * \brief Show the frame used to configure the screen.
 */
void ptb::frame_configure::on_screen()
{
  show_window( new frame_screen(&get_layer()) );
} // frame_configure::on_screen()

/*----------------------------------------------------------------------------*/
/**
 * \brief Show the frame used to configure the audio.
 */
void ptb::frame_configure::on_audio()
{
  show_window( new frame_audio(&get_layer()) );
} // frame_configure::on_audio()

/*----------------------------------------------------------------------------*/
/**
 * \brief Show the frame used to enter passwords.
 */
void ptb::frame_configure::on_password()
{
  show_window( new frame_password(&get_layer()) );
} // frame_configure::on_password()

/*----------------------------------------------------------------------------*/
/**
 * \brief Close the frame.
 */
void ptb::frame_configure::on_back()
{
  close_window();
} // frame_configure::on_back()
