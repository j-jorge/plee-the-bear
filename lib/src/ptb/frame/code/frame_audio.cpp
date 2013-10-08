/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_audio class.
 * \author Julien Jorge
 */
#include "ptb/frame/frame_audio.hpp"

#include "ptb/config_file.hpp"

#include "engine/game.hpp"
#include "gui/button.hpp"
#include "gui/callback_function.hpp"
#include "gui/checkbox.hpp"

#include <libintl.h>
#include <boost/bind.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer owning the window.
 */
ptb::frame_audio::frame_audio( windows_layer* owning_layer )
  : frame(owning_layer, gettext("Audio")),
    m_saved_sound_muted(bear::engine::game::get_instance().get_sound_muted()),
    m_saved_music_muted(bear::engine::game::get_instance().get_music_muted()),
    m_saved_sound_volume
  (bear::engine::game::get_instance().get_sound_volume()),
    m_saved_music_volume
  (bear::engine::game::get_instance().get_music_volume()),
    m_ok_is_pressed(false)
{
  create_controls();
} // frame_audio::frame_audio()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the value of the sliders to the volume.
 */
void ptb::frame_audio::set_volume()
{
  bear::engine::game::get_instance().set_sound_volume
    ( m_sound_volume->get_value() );

  bear::engine::game::get_instance().set_music_volume
    ( m_music_volume->get_value() );
} // frame_audio::set_volume()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_audio::create_controls()
{
  bear::visual::font font = get_font();

  bear::gui::visual_component* music_cb = create_music_checkbox( font );
  bear::gui::visual_component* sound_cb = create_sound_checkbox( font );
  bear::gui::visual_component* music_s = create_music_slider();
  bear::gui::visual_component* sound_s = create_sound_slider();
  bear::gui::visual_component* ok_button = create_ok_button( font );
  bear::gui::visual_component* cancel_button = create_cancel_button( font );

  music_cb->set_bottom( ok_button->top() + get_margin() );
  sound_cb->set_bottom( music_cb->top() + get_margin() );

  const bear::gui::size_type x =
    std::max( music_cb->width(), sound_cb->width() ) + get_margin();

  music_s->set_bottom_left( x, music_cb->bottom() );
  sound_s->set_bottom_left( x, sound_cb->bottom() );

  cancel_button->set_right( music_s->right() );

  fit( get_margin() );
} // frame_audio::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the checkbox for the music.
 * \param f The font to use for the text.
 */
bear::gui::visual_component*
ptb::frame_audio::create_music_checkbox( bear::visual::font f )
{
  bear::gui::checkbox* box =
    new bear::gui::checkbox( get_checkbox_off(), get_checkbox_on(), f );

  box->add_checked_callback
    ( bear::gui::callback_function_maker
      ( boost::bind
        ( &bear::engine::game::set_music_muted,
          &bear::engine::game::get_instance(), false ) ) );
  box->add_unchecked_callback
    ( bear::gui::callback_function_maker
      ( boost::bind
        ( &bear::engine::game::set_music_muted,
          &bear::engine::game::get_instance(), true ) ) );

  box->set_text( gettext("Music") );
  box->check( !bear::engine::game::get_instance().get_music_muted() );

  insert_control(*box);
  return box;
} // frame_audio::create_music_checkbox()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the checkbox for the music.
 * \param f The font to use for the text.
 */
bear::gui::visual_component*
ptb::frame_audio::create_sound_checkbox( bear::visual::font f )
{
  bear::gui::checkbox* box =
    new bear::gui::checkbox( get_checkbox_off(), get_checkbox_on(), f );

  box->add_checked_callback
    ( bear::gui::callback_function_maker
      ( boost::bind
        ( &bear::engine::game::set_sound_muted,
          &bear::engine::game::get_instance(), false ) ) );
  box->add_unchecked_callback
    ( bear::gui::callback_function_maker
      ( boost::bind
        ( &bear::engine::game::set_sound_muted,
          &bear::engine::game::get_instance(), true ) ) );

  box->set_text( gettext("Sound") );
  box->check( !bear::engine::game::get_instance().get_sound_muted() );

  insert_control(*box);

  return box;
} // frame_audio::create_sound_checkbox()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the slider for the music.
 */
bear::gui::visual_component* ptb::frame_audio::create_music_slider()
{
  m_music_volume =
    new bear::gui::slider<double>
    ( get_slider_bar(), get_slider(), 0, 1,
      bear::engine::game::get_instance().get_music_volume(),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_audio::set_volume, this ) ) );

  m_music_volume->set_size( 150, 20 );
  m_music_volume->set_delta(0.1);

  insert_control(*m_music_volume);

  return m_music_volume;
} // frame_audio::create_music_slider()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the slider for the sound.
 */
bear::gui::visual_component* ptb::frame_audio::create_sound_slider()
{
  m_sound_volume =
    new bear::gui::slider<double>
    ( get_slider_bar(), get_slider(), 0, 1,
      bear::engine::game::get_instance().get_sound_volume(),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_audio::set_volume, this ) ) );

  m_sound_volume->set_size( 150, 20 );
  m_sound_volume->set_delta(0.1);

  insert_control(*m_sound_volume);

  return m_sound_volume;
} // frame_audio::create_sound_slider()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "ok" button.
 * \param f The font to use for the texts.
 * \return The top position of the controls.
 */
bear::gui::visual_component*
ptb::frame_audio::create_ok_button( bear::visual::font f )
{
  bear::gui::button* result =
    new bear::gui::button
    ( f, gettext("OK"),
      bear::gui::callback_function_maker
      ( boost::bind(&frame_audio::on_ok, this) ) );

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
ptb::frame_audio::create_cancel_button( bear::visual::font f )
{
  bear::gui::button* result =
    new bear::gui::button
    ( f, gettext("Cancel"),
      bear::gui::callback_function_maker
      ( boost::bind(&frame_audio::on_cancel, this) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_language::create_cancel_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the audio configuration.
 */
void ptb::frame_audio::save()
{
  config_file config;
  config.set_sound_on( !bear::engine::game::get_instance().get_sound_muted() );
  config.set_music_on( !bear::engine::game::get_instance().get_music_muted() );
  config.set_sound_volume
    ( bear::engine::game::get_instance().get_sound_volume() );
  config.set_music_volume
    ( bear::engine::game::get_instance().get_music_volume() );
  config.save();
} // frame_audio::save()

/*----------------------------------------------------------------------------*/
/**
 * \brief Cancel audio configuration.
 */
void ptb::frame_audio::cancel() const
{
 if ( m_saved_sound_muted
       != bear::engine::game::get_instance().get_sound_muted() )
    bear::engine::game::get_instance().set_sound_muted( m_saved_sound_muted );

  if ( m_saved_music_muted
       != bear::engine::game::get_instance().get_music_muted() )
    bear::engine::game::get_instance().set_music_muted( m_saved_music_muted );

  if ( m_saved_sound_volume
       != bear::engine::game::get_instance().get_sound_volume() )
    bear::engine::game::get_instance().set_sound_volume(m_saved_sound_volume);

  if ( m_saved_music_volume
       != bear::engine::game::get_instance().get_music_volume() )
    bear::engine::game::get_instance().set_music_volume(m_saved_music_volume);
} // frame_audio::cancel()


/*----------------------------------------------------------------------------*/
/**
 * \brief Save the configuration.
 */
bool ptb::frame_audio::on_ok()
{
  m_ok_is_pressed = true;
  save();
  close_window();

  return true;
} // frame_audio::on_ok()

/*----------------------------------------------------------------------------*/
/**
 * \brief Exit without saving.
 */
bool ptb::frame_audio::on_cancel()
{
  close_window();
  return true;
} // frame_audio::on_cancel()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called before closing the frame.
 * \return True if the frame can be closed.
 */
bool ptb::frame_audio::on_close()
{
  if ( !m_ok_is_pressed )
    cancel();

  return super::on_close();
} // frame_audio::on_close()
