/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::controller_map class.
 * \author Julien Jorge
 */

#include <claw/logger.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the key associated with a value.
 * \param b The button associated with the value.
 * \param a The value to which is associated the key.
 */
template<typename T>
void ptb::controller_map<T>::set
( const bear::input::controller_button& b, value_type a )
{
  switch( b.get_type() )
    {
    case bear::input::controller_button::controller_keyboard:
      set_key(b.get_key_info().get_code(), a);
      break;
    case bear::input::controller_button::controller_joystick:
      set_joystick
        ( b.get_joystick_button().joystick_index,
          b.get_joystick_button().button, a );
      break;
    case bear::input::controller_button::controller_mouse:
      set_mouse( b.get_mouse_code(), a );
      break;
    default:
      {
        CLAW_FAIL("Invalid button type.");
      }
    }
} // controller_map::set()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the key associated with a value.
 * \param a The value to which is associated the key.
 */
template<typename T>
bear::input::controller_button
ptb::controller_map<T>::find( value_type a ) const
{
  bear::input::key_code k = find_key(a);
  bear::input::joystick_button j = find_joystick(a);
  bear::input::mouse::mouse_code m = find_mouse(a);

  if ( k != bear::input::keyboard::kc_not_a_key )
    return bear::input::controller_button( bear::input::key_info(k) );
  else if ( j.button != bear::input::joystick::jc_invalid )
    return bear::input::controller_button(j);
  else if ( m != bear::input::mouse::mc_invalid )
    return bear::input::controller_button(m);
  else
    return bear::input::controller_button();
} // controller_map::find()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value associated to a keyboard key.
 * \param key The code of the key.
 * \param a The value done with this key.
 */
template<typename T>
void ptb::controller_map<T>::set_key( bear::input::key_code key, value_type a )
{
  remove_key(key);
  remove_value(a);
  m_keyboard[key] = a;
} // controller_map::set_key()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the value associated to a keyboard key.
 * \param key The code of the key.
 * \param d Default value returned if the key is not found.
 */
template<typename T>
typename ptb::controller_map<T>::value_type
ptb::controller_map<T>::find_key_value
( bear::input::key_code key, value_type d ) const
{
  typename keyboard_map::const_iterator it = m_keyboard.find(key);

  if ( it != m_keyboard.end() )
    return it->second;
  else
    return d;
} // controller_map::find_key_value() [const]

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the keyboard key associated with a value.
 * \param a The value to which is associated the key.
 * \return bear::input::keyboard::kc_not_a_key if no key is associated with the
 *         value.
 */
template<typename T>
bear::input::key_code ptb::controller_map<T>::find_key( value_type a ) const
{
  bear::input::key_code result = bear::input::keyboard::kc_not_a_key;

  typename keyboard_map::const_iterator it;

  for ( it=m_keyboard.begin();
        (it!=m_keyboard.end())
          && (result == bear::input::keyboard::kc_not_a_key);
        ++it )
    if ( it->second == a )
      result = it->first;

  return result;
} // controller_map::find_key()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value associated to a key of a joystick.
 * \param joy The index of the joystick.
 * \param key The code of the key.
 * \param a The value done with this key.
 */
template<typename T>
void ptb::controller_map<T>::set_joystick
( unsigned int joy, bear::input::joystick::joy_code key, value_type a )
{
  remove_joy(joy, key);
  remove_value(a);
  m_joystick[ bear::input::joystick_button(joy, key) ] = a;
} // controller_map::set_joystick()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the value associated to a key of a joystick.
 * \param joy The index of the joystick.
 * \param key The code of the key.
 * \param d Default value returned if the key is not found.
 */
template<typename T>
typename ptb::controller_map<T>::value_type
ptb::controller_map<T>::find_joystick_value
( unsigned int joy, bear::input::joystick::joy_code key, value_type d ) const
{
  typename joystick_map::const_iterator it =
    m_joystick.find( bear::input::joystick_button(joy, key) );

  if ( it != m_joystick.end() )
    return it->second;
  else
    return d;
} // controller_map::find_joystick_value()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the joystick key and index associated with a value.
 * \return result.button == bear::input::joystick::jc_invalid if no key is
 *         associated with the value.
 */
template<typename T>
bear::input::joystick_button
ptb::controller_map<T>::find_joystick( value_type a ) const
{
  bear::input::joystick_button result( 0, bear::input::joystick::jc_invalid );

  typename joystick_map::const_iterator it;

  for ( it=m_joystick.begin();
        (it!=m_joystick.end())
          && (result.button == bear::input::joystick::jc_invalid);
        ++it )
    if ( it->second == a )
      result = it->first;

  return result;
} // controller_map::find_joystick()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value associated to a mouse button.
 * \param button The code of the button.
 * \param a action to associate with \a button.
 */
template<typename T>
void ptb::controller_map<T>::set_mouse
( bear::input::mouse::mouse_code button, value_type a )
{
  remove_mouse(button);
  remove_value(a);
  m_mouse[button] = a;
} // controller_map::set_mouse()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the value associated to a mouse button.
 * \param button The code of the button.
 * \param d Default value returned if the button is not found.
 */
template<typename T>
typename ptb::controller_map<T>::value_type
ptb::controller_map<T>::find_mouse_value
( bear::input::mouse::mouse_code button, value_type d ) const
{
  typename mouse_map::const_iterator it = m_mouse.find(button);

  if ( it != m_mouse.end() )
    return it->second;
  else
    return d;
} // controller_map::find_mouse_value()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the mouse key and index associated with a value.
 * \return result == bear::input::mouse::mc_invalid if no button is associated
 *         with the value.
 */
template<typename T>
bear::input::mouse::mouse_code
ptb::controller_map<T>::find_mouse( value_type a ) const
{
  bear::input::mouse::mouse_code result( bear::input::mouse::mc_invalid );

  typename mouse_map::const_iterator it;

  for ( it=m_mouse.begin();
        (it!=m_mouse.end()) && (result == bear::input::mouse::mc_invalid);
        ++it )
    if ( it->second == a )
      result = it->first;

  return result;
} // controller_map::find_mouse()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove a value from the controller.
 * \param b The button of the value to remove.
 */
template<typename T>
void ptb::controller_map<T>::remove( const bear::input::controller_button& b )
{
  switch( b.get_type() )
    {
    case bear::input::controller_button::controller_keyboard:
      m_keyboard.erase(b.get_key_info().get_code());
      break;
    case bear::input::controller_button::controller_joystick:
      m_joystick.erase(b.get_joystick_button());
      break;
    case bear::input::controller_button::controller_mouse:
      m_mouse.erase(b.get_mouse_code());
      break;
    default:
      {
        CLAW_FAIL("Invalid button type.");
      }
    }
} // controller_map::remove()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove a value from the controller.
 * \param key The keyboard key of the value to remove.
 */
template<typename T>
void ptb::controller_map<T>::remove_key( bear::input::key_code key )
{
  m_keyboard.erase(key);
} // controller_map::remove_key()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove a value from the controller.
 * \param joy The joystick index of the value to remove.
 * \param key The button of the value to remove.
 */
template<typename T>
void ptb::controller_map<T>::remove_joy
( unsigned int joy, bear::input::joystick::joy_code key )
{
  m_joystick.erase( bear::input::joystick_button(joy, key) );
} // controller_map::remove_joy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove a value from the controller.
 * \param button The mouse button of the value to remove.
 */
template<typename T>
void
ptb::controller_map<T>::remove_mouse( bear::input::mouse::mouse_code button )
{
  m_mouse.erase(button);
} // controller_map::remove_mouse()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove all values.
 */
template<typename T>
void ptb::controller_map<T>::clear()
{
  m_joystick.clear();
  m_keyboard.clear();
  m_mouse.clear();
} // controller_map::clear()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if no keys are configured.
 */
template<typename T>
bool ptb::controller_map<T>::empty() const
{
  return m_joystick.empty() && m_keyboard.empty() && m_mouse.empty();
} // controller_map::empty()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove a value from all controllers.
 * \param a The value to remove.
 */
template<typename T>
void ptb::controller_map<T>::remove_value( value_type a )
{
  bear::input::key_code key = find_key( a );

  while ( key != bear::input::keyboard::kc_not_a_key )
    {
      remove_key(key);
      key = find_key( a );
    }

  bear::input::joystick_button joy = find_joystick( a );

  while ( joy.button != bear::input::joystick::jc_invalid )
    {
      remove_joy(joy.joystick_index, joy.button);
      joy = find_joystick( a );
    }

  bear::input::mouse::mouse_code mouse = find_mouse( a );

  while ( mouse != bear::input::mouse::mc_invalid )
    {
      remove_mouse(mouse);
      mouse = find_mouse( a );
    }
} // controller_map::remove_value()
