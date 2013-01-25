/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::player_action_sender class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/player_action_sender.hpp"

#include "ptb/level_variables.hpp"
#include "ptb/controller_config.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/defines.hpp"
#include "ptb/network/message/player_action_message.hpp"

#include "engine/game.hpp"
#include "engine/game_network.hpp"

BASE_ITEM_EXPORT( player_action_sender, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::player_action_sender::player_action_sender()
  : m_date(0)
{
  set_global(true);

  bear::engine::game::get_instance().get_network().create_service
    ( PTB_PLAYER_ACTIONS_SERVICE, game_variables::get_port() );
} // player_action_sender::player_action_sender()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do post creation actions.
 */
void ptb::player_action_sender::on_enters_layer()
{
  super::on_enters_layer();
  
  level_variables::set_network_game(get_level(), true);
} // player_action_sender::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::player_action_sender::progress
( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);

  m_date += elapsed_time;

  progress_input_reader(elapsed_time);
} // player_action_sender::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "unsigned integer".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::player_action_sender::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result(true);
  
  if ( name == "player_action_sender.local_player_index" )
    {
      game_variables::set_local_player(value,true);
      game_variables::set_local_player(3-value,false);
    }
  else
    result = super::set_u_integer_field( name, value );

  return result;
} // player_action_sender::set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "std::string".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::player_action_sender::set_string_field
( const std::string& name, const std::string& value )
{
  bool result(true);

  if ( name == "player_action_sender.other_ip" )
    {
      if ( game_variables::is_local_player(1) )
	game_variables::set_ip(1,"127.0.0.1");
      else
	game_variables::set_ip(1,value);

      if ( game_variables::is_local_player(2) )
	game_variables::set_ip(2,"127.0.0.1");
      else
	game_variables::set_ip(2,value);
    }
  else
    result = super::set_string_field( name, value );

  return result;
} // player_action_sender::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to start the action associated with a keyboard key.
 * \param key The code of the key.
 */
bool ptb::player_action_sender::key_pressed
( const bear::input::key_info& key )
{
  bool result = false;
  const unsigned int m( game_variables::get_players_count() );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_key(key.get_code());

      if ( action != player_action::action_null )
        {
          result = true;
	  send
	    ( player_pending_action
	      ( player_pending_action::start_action,m_date,i,action,0 ));
        }
    }

  return result;
} // player_action_sender::key_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to stop the action associated with a keyboard key.
 * \param key The code of the key.
 */
bool ptb::player_action_sender::key_released
( const bear::input::key_info& key )
{
  bool result = false;
  const unsigned int m( game_variables::get_players_count() );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_key(key.get_code());

      if ( action != player_action::action_null )
        {
          result = true;
         send
	    ( player_pending_action
	      ( player_pending_action::stop_action,m_date,i,action,0 ));
        }
    }

  return result;
} // player_action_sender::key_released()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to continue the action associated with a keyboard key.
 * \param elapsed_time How long the action is done.
 * \param key The code of the key.
 */
bool ptb::player_action_sender::key_maintained
( bear::universe::time_type elapsed_time,
  const bear::input::key_info& key )
{
  bool result = false;
  const unsigned int m( game_variables::get_players_count() );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_key(key.get_code());

      if ( action != player_action::action_null )
        {
          result = true;
          send
	    ( player_pending_action
	      (player_pending_action::do_action,m_date,i,action,elapsed_time));
        }
    }

  return result;
} // player_action_sender::key_maintained()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to start the action associated with a joystick button.
 * \param button The code of the button.
 * \param joy_index The index of the joystick.
 */
bool ptb::player_action_sender::button_pressed
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  bool result = false;
  const unsigned int m( game_variables::get_players_count() );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_joystick(joy_index, button);

      if ( action != player_action::action_null )
        {
          result = true;
           send
	    ( player_pending_action
	      (player_pending_action::start_action,m_date,i,action,0));
        }
    }

  return result;
} // player_action_sender::button_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to stop the action associated with a joystick button.
 * \param button The code of the button.
 * \param joy_index The index of the joystick.
 */
bool ptb::player_action_sender::button_released
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  bool result = false;
  const unsigned int m( game_variables::get_players_count() );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_joystick(joy_index, button);

      if ( action != player_action::action_null )
        {
          result = true;
          send
	    ( player_pending_action
	      (player_pending_action::stop_action,m_date,i,action,0));
        }
    }

  return result;
} // player_action_sender::button_released()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to continue the action associated with a joystick
 *        button.
 * \param elapsed_time How long the action is done.
 * \param button The code of the button.
 * \param joy_index The index of the joystick.
 */
bool ptb::player_action_sender::button_maintained
( bear::universe::time_type elapsed_time,
 bear::input::joystick::joy_code button, unsigned int joy_index )
{
  bool result = false;
  const unsigned int m( game_variables::get_players_count() );
  controller_config cfg;
 
  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_joystick(joy_index, button);

      if ( action != player_action::action_null )
        {
          result = true;
	  send
	    ( player_pending_action
	      (player_pending_action::do_action,m_date,i,action,elapsed_time));
        }
    }

  return result;
} // player_action_sender::button_maintained()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to start the action associated with a mouse button.
 * \param button The code of the button.
 * \param pos The position of the cursor on the screen.
 */
bool ptb::player_action_sender::mouse_pressed
( bear::input::mouse::mouse_code button,
  const claw::math::coordinate_2d<unsigned int>& pos )
{
  bool result = false;
  const unsigned int m( game_variables::get_players_count() );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_mouse(button);

      if ( action != player_action::action_null )
        {
          result = true;
           send
	    ( player_pending_action
	      (player_pending_action::start_action,m_date,i,action,0));
        }
    }

  return result;
} // player_action_sender::mouse_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to stop the action associated with a mouse button.
 * \param button The code of the button.
 * \param pos The position of the cursor on the screen.
 */
bool ptb::player_action_sender::mouse_released
( bear::input::mouse::mouse_code button,
  const claw::math::coordinate_2d<unsigned int>& pos )
{
  bool result = false;
  const unsigned int m( game_variables::get_players_count() );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_mouse(button);

      if ( action != player_action::action_null )
        {
          result = true;
          send
	    ( player_pending_action
	      (player_pending_action::stop_action,m_date,i,action,0));
        }
    }

  return result;
} // player_action_sender::mouse_released()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to continue the action associated with a mouse 
 * button.
 * \param elapsed_time How long the action is done.
 * \param button The code of the button.
 * \param pos The position of the cursor on the screen.
 */
bool ptb::player_action_sender::mouse_maintained
( bear::universe::time_type elapsed_time,
  bear::input::mouse::mouse_code button,
  const claw::math::coordinate_2d<unsigned int>& pos )
{
  bool result = false;
  const unsigned int m( game_variables::get_players_count() );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_mouse(button);

      if ( action != player_action::action_null )
        {
          result = true;
	  send
	    ( player_pending_action
	      (player_pending_action::do_action,m_date,i,action,elapsed_time));
        }
    }

  return result;
} // player_action_sender::mouse_maintained()

/*----------------------------------------------------------------------------*/
/**
 * \brief Send an action.
 * \param a The action to send.
 */
void ptb::player_action_sender::send( const player_pending_action& a )
{
  if ( game_variables::is_local_player(a.player_index) )
    {
      player_action_message message(a);

      bear::engine::game::get_instance().get_network().send_message
        ( PTB_PLAYER_ACTIONS_SERVICE, message );
    }
} // player_action_sender::send()
