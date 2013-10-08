/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This class makes the correspondence between the controllers keys and
 *        custom values.
 * \author Julien Jorge
 */
#ifndef __PTB_CONTROLLER_MAP_HPP__
#define __PTB_CONTROLLER_MAP_HPP__

#include <map>

#include "input/controller_button.hpp"
#include "input/keyboard.hpp"
#include "input/joystick_button.hpp"
#include "input/mouse.hpp"

namespace ptb
{
  /**
   * \brief This class makes the correspondence between the controllers keys
   *        and custom values.
   * \author Julien Jorge
   */
  template<typename T>
  class controller_map
  {
  public:
    /** \brief The type of the data. */
    typedef T value_type;

  private:
    /** \brief The type of the map to store the values associated with the
        keyboard. */
    typedef std::map<bear::input::key_code, value_type> keyboard_map;

    /** \brief The type of the map to store the values associated with the
        joysticks. */
    typedef std::map<bear::input::joystick_button, value_type> joystick_map;

    /** \brief The type of the map to store the values associated with the
        mouse. */
    typedef std::map<bear::input::mouse::mouse_code, value_type> mouse_map;

  public:
    void set( const bear::input::controller_button& b, value_type a );
    bear::input::controller_button find( value_type a ) const;

    void set_key( bear::input::key_code key, value_type a );
    value_type
    find_key_value( bear::input::key_code key, value_type d ) const;
    bear::input::key_code find_key( value_type a ) const;

    void set_joystick
    ( unsigned int joy, bear::input::joystick::joy_code key, value_type a );
    value_type find_joystick_value
    ( unsigned int joy, bear::input::joystick::joy_code key,
      value_type d ) const;
    bear::input::joystick_button find_joystick( value_type a ) const;

    void set_mouse
    ( bear::input::mouse::mouse_code button, value_type a );
    value_type find_mouse_value
    ( bear::input::mouse::mouse_code button, value_type d ) const;
    bear::input::mouse::mouse_code find_mouse( value_type a ) const;

    void remove( const bear::input::controller_button& b );
    void remove_key( bear::input::key_code key );
    void remove_joy( unsigned int joy, bear::input::joystick::joy_code key );
    void remove_mouse( bear::input::mouse::mouse_code button );

    void clear();
    bool empty() const;

  private:
    void remove_value( value_type a );

  private:
    /** \brief Values associated with the keyboard. */
    keyboard_map m_keyboard;

    /** \brief Values associated with the joysticks. */
    joystick_map m_joystick;

    /** \brief Values associated with the mouse. */
    mouse_map m_mouse;

  }; // class controller_map
} // namespace ptb

#include "ptb/impl/controller_map.tpp"

#endif // __PTB_CONTROLLER_MAP_HPP__
