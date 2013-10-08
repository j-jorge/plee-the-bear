/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_game_options class.
 * \author Julien Jorge
 */
#include "ptb/frame/frame_game_options.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/config_file.hpp"

#include "gui/button.hpp"
#include "gui/callback_function.hpp"
#include "gui/checkbox.hpp"

#include <boost/bind.hpp>
#include <libintl.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer owning the window.
 */
ptb::frame_game_options::frame_game_options( windows_layer* owning_layer )
  : frame(owning_layer, gettext("Options"))
{
  create_controls();
} // frame_game_options::frame_game_options()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_game_options::create_controls()
{
  bear::visual::font font = frame::get_font();

  bear::gui::visual_component* cb = create_checkbox( font );
  bear::gui::visual_component* ok = create_ok_button( font );
  bear::gui::visual_component* cancel = create_cancel_button( font );

  cb->set_bottom( ok->top() + get_margin() );
  cancel->set_left
    ( std::max( ok->right() + get_margin(), cb->right() - cancel->width() ) );

  fit( get_margin() );
} // frame_game_options::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "friendly_fire" checkbox.
 * \param f The font to use for the text.
 */
bear::gui::visual_component*
ptb::frame_game_options::create_checkbox( bear::visual::font f )
{
  bear::gui::checkbox* result =
    new bear::gui::checkbox( get_checkbox_off(), get_checkbox_on(), f );

  result->set_text( gettext("Friendly fire") );
  result->check( game_variables::get_friendly_fire() );

  result->add_checked_callback
    ( bear::gui::callback_function_maker
      ( boost::bind( &frame_game_options::on_friendly_fire_check, this ) ) );
  result->add_unchecked_callback
    ( bear::gui::callback_function_maker
      ( boost::bind( &frame_game_options::on_friendly_fire_uncheck, this ) ) );

  insert_control(*result);
  return result;
} // frame_game_options::create_checkbox()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "ok" button.
 * \param f The font to use for the texts.
 */
bear::gui::visual_component*
ptb::frame_game_options::create_ok_button( bear::visual::font f )
{
  bear::gui::button* result =
    new bear::gui::button
    ( f, gettext("OK"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_game_options::on_ok, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_language::create_ok_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "cancel" button.
 * \param f The font to use for the texts.
 */
bear::gui::visual_component*
ptb::frame_game_options::create_cancel_button( bear::visual::font f )
{
  bear::gui::button* result =
    new bear::gui::button
    ( f, "Cancel",
      bear::gui::callback_function_maker
      ( boost::bind( &frame_game_options::on_cancel, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_language::create_cancel_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the game_options configuration.
 */
void ptb::frame_game_options::save()
{
  config_file config;
  config.set_friendly_fire( game_variables::get_friendly_fire() );
  config.save();
} // frame_game_options::save()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the configuration.
 */
void ptb::frame_game_options::on_ok()
{
  save();
  close_window();
} // frame_game_options::on_ok()

/*----------------------------------------------------------------------------*/
/**
 * \brief Exit without saving.
 */
void ptb::frame_game_options::on_cancel()
{
  close_window();
} // frame_game_options::on_cancel()

/*----------------------------------------------------------------------------*/
/**
 * \brief The friendly fire checkbox has been checked.
 */
void ptb::frame_game_options::on_friendly_fire_check()
{
  game_variables::set_friendly_fire( true );
} // frame_game_options::on_friendly_fire_check()

/*----------------------------------------------------------------------------*/
/**
 * \brief The friendly fire checkbox has been unchecked.
 */
void ptb::frame_game_options::on_friendly_fire_uncheck()
{
  game_variables::set_friendly_fire( false );
} // frame_game_options::on_friendly_fire_uncheck()
