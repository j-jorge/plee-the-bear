/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::ingame_menu_layer class.
 * \author Julien Jorge
 */
#include "ptb/layer/ingame_menu_layer.hpp"

#include "ptb/controller_config.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/frame/frame_level_score.hpp"
#include "ptb/frame/frame_pause.hpp"
#include "ptb/frame/frame_talk.hpp"

#include "ptb/message/score_message.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param name The name of the layer.
 */
ptb::ingame_menu_layer::ingame_menu_layer( const std::string& name )
  : windows_layer(name)
{

} // ingame_menu_layer::ingame_menu_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the layer that a key had been pressed.
 * \param key The value of the pressed key.
 */
bool ptb::ingame_menu_layer::key_pressed( const bear::input::key_info& key )
{
  if ( super::key_pressed( key ) || !empty() )
    return true;

  if ( key.is_escape() )
    return pause(1);
  else
    {
      const controller_config cfg;
      const bear::input::key_code k(key.get_code());

      for ( unsigned int i=1; i<=game_variables::get_players_count(); ++i )
        {
          const controller_layout& layout = cfg.get_layout(i);

          if ( k == layout.get_key_from_command(gui_command::pause) )
            return pause(i);
          else if ( k == layout.get_key_from_command(gui_command::talk) )
            return talk(i);
        }
    }

  return false;
} // ingame_menu_layer::key_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the layer that a joystick button had been pressed.
 * \param button The code of the button.
 * \param joy_index The index of the joystick.
 */
bool ptb::ingame_menu_layer::button_pressed
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  if ( super::button_pressed( button, joy_index ) )
    return true;

  const controller_config cfg;
  const bear::input::joystick_button btn(joy_index, button);

  for ( unsigned int i=1; i<=game_variables::get_players_count(); ++i )
    {
      const controller_layout& layout = cfg.get_layout(i);

      if ( btn == layout.get_joystick_from_command(gui_command::pause) )
        return pause(i);
      else if ( btn == layout.get_joystick_from_command(gui_command::talk) )
        return talk(i);
    }

  return false;
} // ingame_menu_layer::button_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the layer that a mouse button had been pressed.
 * \param button The code of the button.
 * \param pos The position of the cursor on the screen.
 */
bool ptb::ingame_menu_layer::mouse_pressed
( bear::input::mouse::mouse_code button,
  const claw::math::coordinate_2d<unsigned int>& pos )
{
  if ( super::mouse_pressed( button, pos ) )
    return true;

  const controller_config cfg;

  for ( unsigned int i=1; i<=game_variables::get_players_count(); ++i )
    {
      const controller_layout& layout = cfg.get_layout(i);

      if ( button == layout.get_mouse_from_command(gui_command::pause) )
        return pause(i);
      else if ( button == layout.get_mouse_from_command(gui_command::talk) )
        return talk(i);
    }

  return false;
} // ingame_menu_layer::mouse_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Pause the game.
 * \param player_index The index of the player asking to pause the game.
 */
bool ptb::ingame_menu_layer::pause( unsigned int player_index )
{
  if ( game_variables::demo_is_on() )
    return false;
  else
    {
      show_centered_window( new frame_pause(this) );
      return true;
    }
} // ingame_menu_layer::pause()

/*----------------------------------------------------------------------------*/
/**
 * \brief Show the frame to make a player talking.
 * \param player_index The index of the player to make talking.
 */
bool ptb::ingame_menu_layer::talk( unsigned int player_index )
{
  if ( !empty() )
    return false;

  frame* f = new frame_talk(this, player_index);
  bear::visual::coordinate_type p = (get_size().x - f->width()) / 2;

  f->set_bottom_left(p, p / 2);

  show_window(f);
  return true;
} // ingame_menu_layer::talk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do the stuff related to a score message.
 * \param msg The message to process.
 */
bool ptb::ingame_menu_layer::process_score_message( const score_message& msg )
{
  show_centered_window
    ( new frame_level_score
      ( this, msg.get_score_table(), msg.get_value(), msg.get_medal(),
        msg.get_format(), msg.get_next_level() ) );

  return true;
} // ingame_menu_layer::process_score_message()
