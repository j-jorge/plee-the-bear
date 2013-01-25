/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::controller_layout class.
 * \author Julien Jorge
 */
#include "ptb/controller_layout.hpp"

#include <libintl.h>
#include <claw/configuration_file.hpp>
#include <claw/logger.hpp>

/*----------------------------------------------------------------------------*/
const std::string
ptb::controller_layout::s_action_keyboard_section = "Action/Keyboard";
const std::string
ptb::controller_layout::s_action_joystick_section = "Action/Joystick";
const std::string
ptb::controller_layout::s_action_mouse_section = "Action/Mouse";
const std::string
ptb::controller_layout::s_command_keyboard_section = "GUI/Keyboard";
const std::string
ptb::controller_layout::s_command_joystick_section = "GUI/Joystick";
const std::string
ptb::controller_layout::s_command_mouse_section = "GUI/Mouse";

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the controller button associated with an action.
 * \param a The action to which the button is associated.
 */
bear::input::controller_button
ptb::controller_layout::get_from_action( player_action::value_type a ) const
{
  return m_action.find(a);
} // controller_layout::get_from_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the controller button associated with a command.
 * \param c The command to which the button is associated.
 */
bear::input::controller_button
ptb::controller_layout::get_from_command( gui_command::value_type c ) const
{
  return m_command.find(c);
} // controller_layout::get_from_command()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the button associated with an action.
 * \param key The button.
 * \param a The action.
 */
void ptb::controller_layout::set_action
( const bear::input::controller_button& key, player_action::value_type a )
{
  m_action.set(key, a);
} // controller_layout::set_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the button associated with a gui command.
 * \param key The button.
 * \param c The command.
 */
void ptb::controller_layout::set_command
( const bear::input::controller_button& key, gui_command::value_type c )
{
  m_command.set(key, c);
} // controller_layout::set_command()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the action associated to a keyboard key.
 * \param key The code of the key.
 * \param a The action done with this key.
 */
void ptb::controller_layout::set_action_key
( bear::input::key_code key, player_action::value_type a )
{
  m_command.remove_key(key);
  m_action.set_key(key, a);
} // controller_layout::set_action_key()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the action associated to a keyboard key.
 * \param key The code of the key.
 */
ptb::player_action::value_type
ptb::controller_layout::get_action_from_key( bear::input::key_code key ) const
{
  return m_action.find_key_value(key, player_action::action_null);
} // controller_layout::get_action_from_key()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the keyboard key associated with an action.
 * \return bear::input::keyboard::kc_not_a_key if no key is associated with the
 *         action.
 */
bear::input::key_code
ptb::controller_layout::get_key_from_action( player_action::value_type a ) const
{
  return m_action.find_key(a);
} // controller_layout::get_key_from_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the action associated to a button of a joystick.
 * \param joy The joystick button.
 * \param a The action done with this key.
 */
void ptb::controller_layout::set_action_joystick
( const bear::input::joystick_button& joy, player_action::value_type a )
{
  set_action_joystick(joy.joystick_index, joy.button, a);
} // controller_layout::set_action_joystick()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the action associated to a key of a joystick.
 * \param joy The index of the joystick.
 * \param key The code of the key.
 * \param a The action done with this key.
 */
void ptb::controller_layout::set_action_joystick
( unsigned int joy, bear::input::joystick::joy_code key,
  player_action::value_type a )
{
  m_command.remove_joy(joy, key);
  m_action.set_joystick(joy, key, a);
} // controller_layout::set_action_joystick()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the action associated to a key of a joystick.
 * \param joy The index of the joystick.
 * \param key The code of the key.
 */
ptb::player_action::value_type
ptb::controller_layout::get_action_from_joystick
  ( unsigned int joy, bear::input::joystick::joy_code key ) const
{
  return m_action.find_joystick_value(joy, key, player_action::action_null);
} // controller_layout::get_action_from_joystick()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the joystick key and index associated with an action.
 * \return result.button == bear::input::joystick::jc_invalid if no key is
 *         associated with the action.
 */
bear::input::joystick_button
ptb::controller_layout::get_joystick_from_action
( ptb::player_action::value_type a ) const
{
  return m_action.find_joystick(a);
} // controller_layout::get_joystick_from_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the action associated to a mouse button.
 * \param button The code of the button.
 * \param a The action to associate with \a button.
 */
void ptb::controller_layout::set_action_mouse
( bear::input::mouse::mouse_code button, player_action::value_type a )
{
  m_command.remove_mouse(button);
  m_action.set_mouse(button, a);
} // controller_layout::set_action_mouse()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the action associated to a mouse button.
 * \param button The code of the button.
 */
ptb::player_action::value_type
ptb::controller_layout::get_action_from_mouse
  ( bear::input::mouse::mouse_code button ) const
{
  return m_action.find_mouse_value(button, player_action::action_null);
} // controller_layout::get_action_from_mouse()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the mouse key and index associated with an action.
 * \return result == bear::input::mouse::mc_invalid if no button is associated
 *         with the action.
 */
bear::input::mouse::mouse_code
ptb::controller_layout::get_mouse_from_action
( player_action::value_type a ) const
{
  return m_action.find_mouse(a);
} // controller_layout::get_mouse_from_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the command associated to a keyboard key.
 * \param key The code of the key.
 * \param a The command done with this key.
 */
void ptb::controller_layout::set_command_key
( bear::input::key_code key, gui_command::value_type a )
{
  m_action.remove_key(key);
  m_command.set_key(key, a);
} // controller_layout::set_command_key()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the command associated to a keyboard key.
 * \param key The code of the key.
 */
ptb::gui_command::value_type
ptb::controller_layout::get_command_from_key( bear::input::key_code key ) const
{
  return m_command.find_key_value(key, gui_command::null_command);
} // controller_layout::get_command_from_key()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the keyboard key associated with an command.
 * \return bear::input::keyboard::kc_not_a_key if no key is associated with the
 *         command.
 */
bear::input::key_code
ptb::controller_layout::get_key_from_command( gui_command::value_type a ) const
{
  return m_command.find_key(a);
} // controller_layout::get_key_from_command()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the command associated to a button of a joystick.
 * \param joy The joystick button.
 * \param a The command done with this key.
 */
void ptb::controller_layout::set_command_joystick
( const bear::input::joystick_button& joy, gui_command::value_type a )
{
  set_command_joystick(joy.joystick_index, joy.button, a);
} // controller_layout::set_command_joystick()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the command associated to a key of a joystick.
 * \param joy The index of the joystick.
 * \param key The code of the key.
 * \param a The command done with this key.
 */
void ptb::controller_layout::set_command_joystick
( unsigned int joy, bear::input::joystick::joy_code key,
  gui_command::value_type a )
{
  m_action.remove_joy(joy, key);
  m_command.set_joystick(joy, key, a);
} // controller_layout::set_command_joystick()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the command associated to a key of a joystick.
 * \param joy The index of the joystick.
 * \param key The code of the key.
 */
ptb::gui_command::value_type
ptb::controller_layout::get_command_from_joystick
  ( unsigned int joy, bear::input::joystick::joy_code key ) const
{
  return m_command.find_joystick_value(joy, key, gui_command::null_command);
} // controller_layout::get_command_from_joystick()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the joystick key and index associated with an command.
 * \return result.button == bear::input::joystick::jc_invalid if no key is
 *         associated with the command.
 */
bear::input::joystick_button
ptb::controller_layout::get_joystick_from_command
( ptb::gui_command::value_type a ) const
{
  return m_command.find_joystick(a);
} // controller_layout::get_joystick_from_command()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the command associated to a mouse button.
 * \param button The code of the button.
 * \param a The command to associate with \a button.
 */
void ptb::controller_layout::set_command_mouse
( bear::input::mouse::mouse_code button, gui_command::value_type a )
{
  m_action.remove_mouse(button);
  m_command.set_mouse(button, a);
} // controller_layout::set_command_mouse()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the command associated to a mouse button.
 * \param button The code of the button.
 */
ptb::gui_command::value_type
ptb::controller_layout::get_command_from_mouse
  ( bear::input::mouse::mouse_code button ) const
{
  return m_command.find_mouse_value(button, gui_command::null_command);
} // controller_layout::get_command_from_mouse()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the mouse key and index associated with an command.
 * \return result == bear::input::mouse::mc_invalid if no button is associated
 *         with the command.
 */
bear::input::mouse::mouse_code
ptb::controller_layout::get_mouse_from_command
( gui_command::value_type a ) const
{
  return m_command.find_mouse(a);
} // controller_layout::get_mouse_from_command()

/*----------------------------------------------------------------------------*/
/**
 * \brief Convert the escaped action sequence of a string.
 * \param str The string to convert.
 * \param result The resulting string.
 */
void ptb::controller_layout::escape_action_sequence
( const std::string& str, std::string& result ) const
{
  unsigned int ref = 0;
  unsigned int prev = 0;
  unsigned int current = 1;

  while ( current < str.size() )
    if ( str[prev] == '%' )
      {
        if ( str[current] == 'a' )
          {
            result += str.substr(ref, prev - ref);
            current = append_action_string(result, str, current);
          }
        else
          result += str.substr(ref, current - ref + 1);

        ref = current + 1;
        prev = ref;
        current = prev + 1;
      }
    else
      {
        ++prev;
        ++current;
      }

  if ( ref < str.size() )
    result += str.substr(ref);
} // controller_layout::escape_action_sequence()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the layout from a stream.
 * \param f The stream from which we read.
 */
void ptb::controller_layout::load( std::istream& f )
{
  claw::configuration_file config(f);
  claw::configuration_file::const_section_iterator it;

  m_action.clear();
  m_command.clear();

  for ( it=config.section_begin(s_action_keyboard_section);
        it!=config.section_end(s_action_keyboard_section); ++it )
    set_action_key
      ( bear::input::keyboard::get_key_named
        (config(s_action_keyboard_section, *it)),
        player_action::from_string(*it) );

  for ( it=config.section_begin(s_action_joystick_section);
        it!=config.section_end(s_action_joystick_section); ++it )
    set_action_joystick
      ( bear::input::joystick_button::get_button_named
        (config(s_action_joystick_section, *it)),
        player_action::from_string(*it) );

  for ( it=config.section_begin(s_action_mouse_section);
        it!=config.section_end(s_action_mouse_section); ++it )
    set_action_mouse
      ( bear::input::mouse::get_button_named
        (config(s_action_mouse_section, *it)),
        player_action::from_string(*it) );

  for ( it=config.section_begin(s_command_keyboard_section);
        it!=config.section_end(s_command_keyboard_section); ++it )
    set_command_key
      ( bear::input::keyboard::get_key_named
        (config(s_command_keyboard_section, *it)),
        gui_command::from_string(*it) );

  for ( it=config.section_begin(s_command_joystick_section);
        it!=config.section_end(s_command_joystick_section); ++it )
    set_command_joystick
      ( bear::input::joystick_button::get_button_named
        (config(s_command_joystick_section, *it)),
        gui_command::from_string(*it) );

  for ( it=config.section_begin(s_command_mouse_section);
        it!=config.section_end(s_command_mouse_section); ++it )
    set_command_mouse
      ( bear::input::mouse::get_button_named
        (config(s_command_mouse_section, *it)),
        gui_command::from_string(*it) );
} // controller_layout::load()

/*----------------------------------------------------------------------------*/
/**
 * \brief save the layout in a stream.
 * \param f The stream in which we write.
 */
void ptb::controller_layout::save( std::ostream& f ) const
{
  save_actions(f);
  save_commands(f);
} // controller_layout::save()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove a button from the controller.
 * \param b The button to remove.
 */
void ptb::controller_layout::remove( const bear::input::controller_button& b )
{
  m_action.remove(b);
  m_command.remove(b);
} // controller_layout::remove()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove an action from the controller.
 * \param key The keyboard key of the action to remove.
 */
void ptb::controller_layout::remove_key( bear::input::key_code key )
{
  m_action.remove_key(key);
  m_command.remove_key(key);
} // controller_layout::remove_key()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove an action from the controller.
 * \param joy The joystick index of the action to remove.
 * \param key The button of the action to remove.
 */
void ptb::controller_layout::remove_joy
( unsigned int joy, bear::input::joystick::joy_code key )
{
  m_action.remove_joy( joy, key );
  m_command.remove_joy( joy, key );
} // controller_layout::remove_joy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove an action from the controller.
 * \param button The mouse button of the action to remove.
 */
void
ptb::controller_layout::remove_mouse( bear::input::mouse::mouse_code button )
{
  m_action.remove_mouse(button);
  m_command.remove_mouse(button);
} // controller_layout::remove_mouse()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if no keys are configured.
 */
bool ptb::controller_layout::empty() const
{
  return m_action.empty() && m_command.empty();
} // controller_layout::empty()

/*----------------------------------------------------------------------------*/
/**
 * \brief Convert the "\\ai" escape sequence.
 * \param result (in/out) The string to which we append the action.
 * \param str The string to convert.
 * \param current The position of the parameters of the 'a' in the \\a
 *        sequence.
 * \return The position of the last character read.
 */
unsigned int ptb::controller_layout::append_action_string
( std::string& result, const std::string& str, unsigned int current ) const
{
  std::string::size_type pos = str.find_first_of(';', current);
  bool ok = false;

  if ( pos != std::string::npos )
    {
      std::istringstream iss( str.substr(current+1, pos - current - 1) );
      unsigned int action;

      if ( iss >> action)
        if ( iss.rdbuf()->in_avail() == 0 )
          if ( append_action_string(result, action) )
            {
              current = pos;
              ok = true;
            }
    }

  if (!ok)
    result += "%a";

  return current;
} // controller_layout::append_action_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief Append to a string the string corresponding to the action of a given
 *        player.
 * \param str (in/out) The string to which we append the action.
 * \param action The action from which we want the string.
 * \return The position of the next character to read.
 */
bool ptb::controller_layout::append_action_string
( std::string& str, unsigned int action ) const
{
  bool result = true;

  bear::input::key_code key = get_key_from_action( action );
  bear::input::joystick_button joy = get_joystick_from_action( action );
  bear::input::mouse::mouse_code mouse = get_mouse_from_action( action );

  if ( key != bear::input::keyboard::kc_not_a_key )
    str += bear::input::keyboard::get_name_of(key);
  else if ( joy.button != bear::input::joystick::jc_invalid )
    {
      std::ostringstream oss;
      oss << joy.joystick_index << ' ';

      str += gettext("joystick ") + oss.str()
        + gettext(bear::input::joystick::get_name_of(joy.button).c_str());
    }
  else if ( mouse != bear::input::mouse::mc_invalid )
    str += bear::input::mouse::get_name_of(mouse);
  else
    result = false;

  return result;
} // controller_layout::append_action_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the actions in a stream.
 * \param f The stream in which we write.
 */
void ptb::controller_layout::save_actions( std::ostream& f ) const
{
  claw::configuration_file config;

  player_action::value_type a;

  for (a = player_action::min_value; a!=player_action::max_value; ++a)
    {
      bear::input::key_code key = get_key_from_action( a );

      if ( key != bear::input::keyboard::kc_not_a_key )
        config.set_value
          ( s_action_keyboard_section, player_action::to_string(a),
            bear::input::keyboard::get_name_of(key) );
    }

  for (a = player_action::min_value; a!=player_action::max_value; ++a)
    {
      bear::input::joystick_button joy = get_joystick_from_action( a );

      if ( joy.button != bear::input::joystick::jc_invalid )
        config.set_value
          ( s_action_joystick_section, player_action::to_string(a),
            bear::input::joystick_button::get_name_of(joy) );
    }

  for (a = player_action::min_value; a!=player_action::max_value; ++a)
    {
      bear::input::mouse::mouse_code mouse = get_mouse_from_action( a );

      if ( mouse != bear::input::mouse::mc_invalid )
        config.set_value
          ( s_action_mouse_section, player_action::to_string(a),
            bear::input::mouse::get_name_of(mouse) );
    }

  config.save(f);
} // controller_layout::save_actions()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the commands in a stream.
 * \param f The stream in which we write.
 */
void ptb::controller_layout::save_commands( std::ostream& f ) const
{
  claw::configuration_file config;

  gui_command::value_type a;

  for (a = gui_command::min_value; a<=gui_command::max_value; ++a)
    {
      bear::input::key_code key = get_key_from_command( a );

      if ( key != bear::input::keyboard::kc_not_a_key )
        config.set_value
          ( s_command_keyboard_section, gui_command::to_string(a),
            bear::input::keyboard::get_name_of(key) );
    }

  for (a = gui_command::min_value; a<=gui_command::max_value; ++a)
    {
      bear::input::joystick_button joy = get_joystick_from_command( a );

      if ( joy.button != bear::input::joystick::jc_invalid )
        config.set_value
          ( s_command_joystick_section, gui_command::to_string(a),
            bear::input::joystick_button::get_name_of(joy) );
    }

  for (a = gui_command::min_value; a<=gui_command::max_value; ++a)
    {
      bear::input::mouse::mouse_code mouse = get_mouse_from_command( a );

      if ( mouse != bear::input::mouse::mc_invalid )
        config.set_value
          ( s_command_mouse_section, gui_command::to_string(a),
            bear::input::mouse::get_name_of(mouse) );
    }

  config.save(f);
} // controller_layout::save_commands()
