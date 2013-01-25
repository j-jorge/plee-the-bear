/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This class makes the correspondence between the controllers keys and
 *        the actions of the player.
 * \author Julien Jorge
 */
#ifndef __PTB_CONTROLLER_LAYOUT_HPP__
#define __PTB_CONTROLLER_LAYOUT_HPP__

#include <map>

#include "ptb/controller_map.hpp"
#include "ptb/gui_command.hpp"
#include "ptb/player_action.hpp"

namespace ptb
{
  /**
   * \brief This class makes the correspondence between the controllers keys
   *        and the actions of the player.
   * \author Julien Jorge
   */
  class controller_layout
  {
  private:
    /** \brief The type of the map to store the actions associated with the
        controllers. */
    typedef controller_map<player_action::value_type> action_map;

    /** \brief The type of the map to store the GUI commands associated with the
        controllers. */
    typedef controller_map<gui_command::value_type> command_map;

  public:
    bear::input::controller_button
    get_from_action( player_action::value_type a ) const;
    bear::input::controller_button
    get_from_command( gui_command::value_type c ) const;

    void set_action
    ( const bear::input::controller_button& key, player_action::value_type a );
    void set_command
    ( const bear::input::controller_button& key, gui_command::value_type c );

    void
    set_action_key( bear::input::key_code key, player_action::value_type a );
    player_action::value_type
    get_action_from_key( bear::input::key_code key ) const;
    bear::input::key_code
    get_key_from_action( player_action::value_type a ) const;

    void set_action_joystick
    ( const bear::input::joystick_button& joy, player_action::value_type a );
    void set_action_joystick
    ( unsigned int joy, bear::input::joystick::joy_code key,
      player_action::value_type a );
    player_action::value_type get_action_from_joystick
      ( unsigned int joy, bear::input::joystick::joy_code key ) const;
    bear::input::joystick_button
    get_joystick_from_action( player_action::value_type a ) const;

    void set_action_mouse
    ( bear::input::mouse::mouse_code button, player_action::value_type a );
    player_action::value_type
    get_action_from_mouse( bear::input::mouse::mouse_code button ) const;
    bear::input::mouse::mouse_code
    get_mouse_from_action( player_action::value_type a ) const;

    void
    set_command_key ( bear::input::key_code key, gui_command::value_type a );
    gui_command::value_type
    get_command_from_key( bear::input::key_code key ) const;
    bear::input::key_code
    get_key_from_command( gui_command::value_type a ) const;

    void set_command_joystick
    ( const bear::input::joystick_button& joy, gui_command::value_type a );
    void set_command_joystick
    ( unsigned int joy, bear::input::joystick::joy_code key,
      gui_command::value_type a );
    gui_command::value_type get_command_from_joystick
      ( unsigned int joy, bear::input::joystick::joy_code key ) const;
    bear::input::joystick_button
    get_joystick_from_command( gui_command::value_type a ) const;

    void set_command_mouse
    ( bear::input::mouse::mouse_code button, gui_command::value_type a );
    gui_command::value_type
    get_command_from_mouse( bear::input::mouse::mouse_code button ) const;
    bear::input::mouse::mouse_code
    get_mouse_from_command( gui_command::value_type a ) const;

    void escape_action_sequence
    ( const std::string& str, std::string& result ) const;

    void load( std::istream& f );
    void save( std::ostream& f ) const;

    void remove( const bear::input::controller_button& b );
    void remove_key( bear::input::key_code key );
    void remove_joy( unsigned int joy, bear::input::joystick::joy_code key );
    void remove_mouse( bear::input::mouse::mouse_code button );

    bool empty() const;

  private:
    unsigned int append_action_string
    ( std::string& result, const std::string& str, unsigned int current ) const;
    bool append_action_string( std::string& str, unsigned int action ) const;

    void remove_action( player_action::value_type a );

    void save_actions( std::ostream& f ) const;
    void save_commands( std::ostream& f ) const;

  private:
    /** \brief Actions associated with the controllers. */
    action_map m_action;

    /** \brief Commands associated with the controllers. */
    command_map m_command;

    /** \brief The name of the section containing the action associated to a
        keyboard key in a saved layout. */
    static const std::string s_action_keyboard_section;

    /** \brief The name of the section containing the action associated to a
        joystick key in a saved layout. */
    static const std::string s_action_joystick_section;

    /** \brief The name of the section containing the action associated to a
        mouse button in a saved layout. */
    static const std::string s_action_mouse_section;

    /** \brief The name of the section containing the command associated to a
        keyboard key in a saved layout. */
    static const std::string s_command_keyboard_section;

    /** \brief The name of the section containing the command associated to a
        joystick key in a saved layout. */
    static const std::string s_command_joystick_section;

    /** \brief The name of the section containing the command associated to a
        mouse key in a saved layout. */
    static const std::string s_command_mouse_section;

  }; // class controller_layout
} // namespace ptb

#endif // __PTB_CONTROLLER_LAYOUT_HPP__
