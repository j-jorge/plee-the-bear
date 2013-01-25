/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::key_edit class.
 * \author Julien Jorge
 */
#include "ptb/gui/key_edit.hpp"

#include "ptb/defines.hpp"
#include "ptb/frame/theme_colors.hpp"

#include "input/joystick_button.hpp"
#include "input/keyboard.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param font The font used to display the text.
 * \param b The initial value of the key.
 * \param change_callback The callback executed when the button is changed.
 */
ptb::key_edit::key_edit
( const bear::visual::font& font, const bear::input::controller_button& b,
  const bear::gui::callback& change_callback )
  : bear::gui::static_text(font), m_edit_mode(false), m_button(b),
    m_change_callback(change_callback),
    m_next_background_color( PTB_ORANGE_PIXEL )
{
  set_label();
} // key_edit::key_edit()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the button. Does not execute the callback.
 * \param c The new button.
 */
void ptb::key_edit::set_key( const bear::input::controller_button& c )
{
  m_button = c;
  set_label();
} // key_edit::set_key()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the button.
 */
const bear::input::controller_button& ptb::key_edit::get_key() const
{
  return m_button;
} // key_edit::get_key()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the callback executed when the button is changed.
 * \param c The callback.
 */
void ptb::key_edit::set_change_callback( const bear::gui::callback& c )
{
  m_change_callback = c;
} // key_edit::set_change_callback()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that a key has been pressed.
 * \param key The code of the key.
 */
bool ptb::key_edit::on_key_press( const bear::input::key_info& key )
{
  bool result = true;

  if ( key.is_escape() )
    {
      if ( m_edit_mode )
        edit_mode_off();
      else
        result = false;
    }
  else if ( m_edit_mode )
    {
      edit_mode_off();
      set_key_callback(key);
    }
  else if ( key.is_enter() )
    edit_mode_on();
  else
    result = false;

  return result;
} // key_edit::on_key_press()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that a joystick button has been pressed.
 * \param button The code of the button.
 * \param joy_index The index of the joytick.
 */
bool ptb::key_edit::on_button_press
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  bool result = true;

  if ( m_edit_mode )
    {
      edit_mode_off();
      set_key_callback( bear::input::joystick_button(joy_index, button) );
    }
  else if ( button >= bear::input::joystick::jc_button_1 )
    edit_mode_on();
  else
    result = false;

  return result;
} // key_edit::on_button_press()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that a mouse button has been pressed.
 * \param key The code of the key.
 * \param pos The current position of the cursor.
 */
bool ptb::key_edit::on_mouse_press
( bear::input::mouse::mouse_code key,
  const claw::math::coordinate_2d<unsigned int>& pos )
{
  bool result = true;

  if ( m_edit_mode )
    {
      edit_mode_off();
      set_key_callback( key );
    }
  else switch( key )
    {
    case bear::input::mouse::mc_left_button :
    case bear::input::mouse::mc_middle_button :
    case bear::input::mouse::mc_right_button :
      edit_mode_on();
      break;
    default:
      result = false;
    }

  return result;
} // key_edit::on_key_press()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop reading the inputs.
 * \pre m_edit_mode == true
 */
void ptb::key_edit::edit_mode_off()
{
  CLAW_PRECOND( m_edit_mode );

  m_edit_mode = false;

  const bear::gui::color_type c( m_next_background_color );
  m_next_background_color = get_background_color();
  set_background_color( c );
} // key_edit::edit_mode_off()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start reading the inputs.
 * \pre !m_edit_mode
 */
void ptb::key_edit::edit_mode_on()
{
  CLAW_PRECOND( !m_edit_mode );

  m_edit_mode = true;

  const bear::gui::color_type c( m_next_background_color );
  m_next_background_color = get_background_color();
  set_background_color( c );
} // key_edit::edit_mode_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the stored button and execute the callback.
 * \param key The new value of the key.
 */
void
ptb::key_edit::set_key_callback( const bear::input::controller_button& key )
{
  set_key(key);
  m_change_callback.execute();
} // key_edit::set_key_callback()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the text displayed in the control.
 */
void ptb::key_edit::set_label()
{
  std::string t;

  switch ( m_button.get_type() )
    {
    case bear::input::controller_button::controller_keyboard:
      t = bear::input::keyboard::get_translated_name_of
        (m_button.get_key_info().get_code());
      break;
    case bear::input::controller_button::controller_joystick:
      t = bear::input::joystick_button::get_translated_name_of
        (m_button.get_joystick_button());
      break;
    case bear::input::controller_button::controller_mouse:
      t = bear::input::mouse::get_translated_name_of(m_button.get_mouse_code());
      break;
    default: { }
    }

  set_text(t);
} // key_edit::set_label()
