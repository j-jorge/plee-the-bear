/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_screen class.
 * \author Sebastien Angibaud
 */
#include "ptb/frame/frame_screen.hpp"

#include "ptb/config_file.hpp"

#include "engine/game.hpp"
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
ptb::frame_screen::frame_screen( windows_layer* owning_layer )
  : frame(owning_layer, gettext("Screen")),
    m_saved_mode(bear::engine::game::get_instance().get_fullscreen()),
    m_ok_is_pressed(false)
{
  create_controls();
} // frame_screen::frame_screen()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_screen::create_controls()
{
  bear::gui::visual_component* cb = create_checkbox();
  bear::gui::visual_component* ok = create_ok_button();
  bear::gui::visual_component* cancel = create_cancel_button();

  cb->set_bottom( ok->top() + get_margin() );
  cancel->set_left
    ( std::max(ok->right() + get_margin(), cb->right() - cancel->width()) );

  fit( get_margin() );
} // frame_screen::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "Fullscreen" checkbox.
 */
bear::gui::visual_component* ptb::frame_screen::create_checkbox()
{
  bear::gui::checkbox* result =
    new bear::gui::checkbox
    ( get_checkbox_off(), get_checkbox_on(), get_font() );

  result->set_text( gettext("Fullscreen") );
  result->check( bear::engine::game::get_instance().get_fullscreen() );

  result->add_checked_callback
    ( bear::gui::callback_function_maker
      ( boost::bind
        ( &bear::engine::game::set_fullscreen,
          &bear::engine::game::get_instance(), true ) ) );
  result->add_unchecked_callback
    ( bear::gui::callback_function_maker
      ( boost::bind
        ( &bear::engine::game::set_fullscreen,
          &bear::engine::game::get_instance(), false ) ) );

  insert_control(*result);

  return result;
} // frame_screen::create_checkbox()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "ok" button.
 */
bear::gui::visual_component* ptb::frame_screen::create_ok_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("OK"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_screen::on_ok, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_screen::create_ok_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "cancel" button.
 */
bear::gui::visual_component* ptb::frame_screen::create_cancel_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Cancel"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_screen::on_cancel, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_screen::create_cancel_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the configuration.
 */
bool ptb::frame_screen::on_ok()
{
  m_ok_is_pressed = true;

  config_file config;
  config.set_fullscreen( bear::engine::game::get_instance().get_fullscreen() );
  config.save();

  close_window();

  return true;
} // frame_screen::on_ok()

/*----------------------------------------------------------------------------*/
/**
 * \brief Exit without saving.
 */
bool ptb::frame_screen::on_cancel()
{
  close_window();
  return true;
} // frame_screen::on_cancel()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called before closing the frame.
 * \return True if the frame can be closed.
 */
bool ptb::frame_screen::on_close()
{
  if ( !m_ok_is_pressed )
    if ( m_saved_mode != bear::engine::game::get_instance().get_fullscreen() )
      bear::engine::game::get_instance().set_fullscreen( m_saved_mode );

  return super::on_close();
} // frame_screen::on_close()
