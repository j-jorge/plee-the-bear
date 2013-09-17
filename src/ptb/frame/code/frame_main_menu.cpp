/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_main_menu class.
 * \author Julien Jorge
 */
#include "ptb/frame/frame_main_menu.hpp"

#include "engine/game.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/frame/frame_configure.hpp"
#include "ptb/frame/frame_profiles.hpp"
#include "ptb/frame/frame_start_menu.hpp"
#include "ptb/frame/frame_play_mini_game.hpp"

#include "ptb/defines.hpp"

#include "gui/callback_function.hpp"
#include "input/keyboard.hpp"

#include <boost/bind.hpp>
#include <libintl.h>

/*----------------------------------------------------------------------------*/
const bear::input::key_code ptb::frame_main_menu::s_keyboard_cheat[] =
  {
    bear::input::keyboard::kc_up, bear::input::keyboard::kc_up,
    bear::input::keyboard::kc_down, bear::input::keyboard::kc_left,
    bear::input::keyboard::kc_right, bear::input::keyboard::kc_down,
    bear::input::keyboard::kc_not_a_key
  };

const bear::input::joystick::joy_code ptb::frame_main_menu::s_joystick_cheat[] =
  {
    bear::input::joystick::jc_axis_up, bear::input::joystick::jc_axis_up,
    bear::input::joystick::jc_axis_down, bear::input::joystick::jc_axis_left,
    bear::input::joystick::jc_axis_right, bear::input::joystick::jc_axis_down,
    bear::input::joystick::jc_invalid
  };

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer onwing the window.
 */
ptb::frame_main_menu::frame_main_menu( windows_layer* owning_layer )
  : menu_frame(owning_layer, gettext("Main menu")), m_cheat_index(0)
{
  create_controls();
  set_input_priority(true);
} // frame_main_menu::frame_main_menu()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that a key has been pressed.
 * \param key The code of the key.
 */
bool ptb::frame_main_menu::on_key_press( const bear::input::key_info& key )
{
  if (key.get_code() == s_keyboard_cheat[m_cheat_index])
    {
      ++m_cheat_index;

      if ( s_keyboard_cheat[m_cheat_index]
           == bear::input::keyboard::kc_not_a_key )
        game_variables::set_password_menu_visibility(true);
    }
  else
    m_cheat_index = 0;

  return menu_frame::on_key_press(key);
} // frame_main_menu::on_key_press()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that a joystick button has been pressed.
 * \param button The code of the button.
 * \param joy_index The index of the joytick.
 */
bool ptb::frame_main_menu::on_button_press
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  if (button == s_joystick_cheat[m_cheat_index])
    {
      ++m_cheat_index;

      if ( s_joystick_cheat[m_cheat_index]
           == bear::input::joystick::jc_invalid )
        game_variables::set_password_menu_visibility(true);
    }
  else
    m_cheat_index = 0;

  return menu_frame::on_button_press(button, joy_index);
} // frame_main_menu::on_button_press()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_main_menu::create_controls()
{
  push
    ( gettext("Quit"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_main_menu::on_quit, this ) ) );

  push
    ( gettext("Configuration"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_main_menu::on_configuration, this ) ) );

  push
    ( gettext("Mini-game"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_main_menu::on_mini_game, this ) ) );

  push
    ( gettext("Story mode"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_main_menu::on_game, this ) ) );

  fit( get_margin() );
} // frame_main_menu::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called before closing the window.
 * \return True if the window can be closed.
 */
bool ptb::frame_main_menu::on_close()
{
  return false;
} // frame_main_menu::on_close()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when the frame is displayed.
 */
void ptb::frame_main_menu::on_focus()
{
  if ( game_variables::mini_game_is_on() )
    on_mini_game();
} // frame_main_menu::on_focus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Action done when clicking on the "Configuration" entry.
 */
void ptb::frame_main_menu::on_configuration()
{
  show_window( new frame_configure(&get_layer()) );
} // frame_main_menu::on_configuration()

/*----------------------------------------------------------------------------*/
/**
 * \brief Action done when clicking on the "Start game" entry.
 */
void ptb::frame_main_menu::on_game()
{
  show_window( new frame_profiles(&get_layer()) );
} // frame_main_menu::on_game()

/*----------------------------------------------------------------------------*/
/**
 * \brief Action done when clicking on the "Play_Menu mini-game" entry.
 */
void ptb::frame_main_menu::on_mini_game()
{
  game_variables::set_mini_game( true );
  show_window( new frame_play_mini_game
               (&get_layer(), PTB_MINI_GAME_INFORMATIONS) );
} // frame_main_menu::on_mini_game()

/*----------------------------------------------------------------------------*/
/**
 * \brief Action done when clicking on the "Quit" entry.
 */
void ptb::frame_main_menu::on_quit()
{
  bear::engine::game::get_instance().end();
} // frame_main_menu::on_quit()
