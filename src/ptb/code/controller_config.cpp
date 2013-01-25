/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \brief Implementation of the ptb::controller_config class.
 * \author Julien Jorge
 */
#include "ptb/controller_config.hpp"

#include "ptb/player_action.hpp"
#include "engine/game.hpp"
#include "engine/system/game_filesystem.hpp"

#include <claw/logger.hpp>
#include <sstream>
#include <fstream>

/*----------------------------------------------------------------------------*/
ptb::controller_layout ptb::controller_config::s_controller_layout[2];

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::controller_config::controller_config()
  : m_base_layout_file_name("controller_layout")
{
  if ( s_controller_layout[0].empty() )
    default_controls_for_player_1();
  if ( s_controller_layout[1].empty() )
    default_controls_for_player_2();
} // controller_config::controller_config

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the configuration.
 */
void ptb::controller_config::load()
{
  load_controller_layout(1);
  load_controller_layout(2);
} // controller_config::save()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the configuration.
 */
void ptb::controller_config::save() const
{
  save_controller_layout(1);
  save_controller_layout(2);
} // controller_config::save()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the layout of the controls for a player.
 * \param i Index of the player.
 * \pre \a i != 0
 */
void ptb::controller_config::save_controller_layout( unsigned int i ) const
{
  CLAW_PRECOND( i!=0 );

  std::ostringstream oss;
  oss << m_base_layout_file_name << "_" << (int)i;

  const bear::engine::game& g( bear::engine::game::get_instance() );

  const std::string file_name
    ( g.get_game_filesystem().get_custom_config_file_name( oss.str() ) );
  std::ofstream f( file_name.c_str() );

  if ( !f )
    claw::logger << claw::log_warning << "Can't open controller's layout file '"
                 << oss.str() << "'." << std::endl;
  else
    {
      s_controller_layout[i-1].save(f);
      f.close();
    }
} // controller_config::save_controller_layout()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the layout of the controls for a player.
 * \param i Index of the player.
 * \pre \a i != 0 *
 */
void ptb::controller_config::load_controller_layout( unsigned int i )
{
  CLAW_PRECOND( i!=0 );

  std::ostringstream oss;
  oss << m_base_layout_file_name << "_" << (int)i;

  const bear::engine::game& g( bear::engine::game::get_instance() );

  const std::string file_name
    ( g.get_game_filesystem().get_custom_config_file_name( oss.str() ) );
  std::ifstream f( file_name.c_str() );

  if ( !f )
    claw::logger << claw::log_warning << "Can't open controller's layout file '"
                 << oss.str() << "'." << std::endl;
  else
    {
      s_controller_layout[i-1].load(f);
      f.close();
    }
} // controller_config::load_controller_layout()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the controller layout of a given player.
 * \param i Index of the player.
 * \param lay The layout.
 * \pre \a i != 0
 */
void ptb::controller_config::set_layout
( unsigned int i, const controller_layout& lay )
{
  CLAW_PRECOND( i!=0 );
  CLAW_PRECOND( i <= 2 );

  s_controller_layout[i-1] = lay;
} // controller_config::set_layout()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the controller layout of a given player.
 * \param i Index of the player.
 * \pre \a i != 0
 */
ptb::controller_layout& ptb::controller_config::get_layout( unsigned int i )
{
  CLAW_PRECOND( i != 0 );
  CLAW_PRECOND( i <= 2 );

  return s_controller_layout[i-1];
} // controller_config::get_layout()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the controller layout of a given player.
 * \param i Index of the player.
 * \pre \a i != 0
 */
const ptb::controller_layout&
ptb::controller_config::get_layout( unsigned int i ) const
{
  CLAW_PRECOND( i!=0 );
  CLAW_PRECOND( i <= 2 );

  return s_controller_layout[i-1];
} // controller_config::get_layout()

/*----------------------------------------------------------------------------*/
/**
 * \brief Define the default controls for the first player.
 */
void ptb::controller_config::default_controls_for_player_1()
{
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_left, player_action::move_left);
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_right, player_action::move_right);
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_up, player_action::look_upward);
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_down, player_action::crouch);
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_f, player_action::slap);
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_d, player_action::throw_stone);
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_s, player_action::change_object);
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_space, player_action::jump);
  s_controller_layout[0].set_action_key
    (bear::input::keyboard::kc_c, player_action::get_camera);
  s_controller_layout[0].set_command_key
    (bear::input::keyboard::kc_t, gui_command::talk);
  s_controller_layout[0].set_command_key
    (bear::input::keyboard::kc_pause, gui_command::pause);
} // controller_config::default_controls_for_player_1()

/*----------------------------------------------------------------------------*/
/**
 * \brief Define the default controls for the second player.
 */
void ptb::controller_config::default_controls_for_player_2()
{
  s_controller_layout[1].set_action_joystick
    (0, bear::input::joystick::jc_axis_left, player_action::move_left);
  s_controller_layout[1].set_action_joystick
    (0, bear::input::joystick::jc_axis_right, player_action::move_right);
  s_controller_layout[1].set_action_joystick
    (0, bear::input::joystick::jc_axis_up,  player_action::look_upward);
  s_controller_layout[1].set_action_joystick
    (0, bear::input::joystick::jc_axis_down, player_action::crouch);
  s_controller_layout[1].set_action_joystick
    (0, bear::input::joystick::jc_button_1, player_action::slap);
  s_controller_layout[1].set_action_joystick
    (0, bear::input::joystick::jc_button_2, player_action::throw_stone);
  s_controller_layout[1].set_action_joystick
    (0, bear::input::joystick::jc_button_3, player_action::change_object);
  s_controller_layout[1].set_action_joystick
    (0, bear::input::joystick::jc_button_4, player_action::jump);
  s_controller_layout[1].set_action_joystick
    (0, bear::input::joystick::jc_button_5, player_action::get_camera);
  s_controller_layout[1].set_command_joystick
    (0, bear::input::joystick::jc_button_6, gui_command::talk);
  s_controller_layout[1].set_command_joystick
    (0, bear::input::joystick::jc_button_7, gui_command::pause);
} // controller_config::default_controls_for_player_2()
