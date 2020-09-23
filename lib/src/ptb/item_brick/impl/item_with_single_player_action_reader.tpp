/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::item_with_single_player_action_reader
 *        class.
 * \author Julien Jorge
 */

#include "ptb/level_variables.hpp"
#include "ptb/network/message/player_action_message.hpp"

#include "engine/game.hpp"
#include "engine/game_network.hpp"

#include <boost/bind.hpp> 

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
template<class Base>
ptb::item_with_single_player_action_reader<Base>::
item_with_single_player_action_reader()
  : m_player_index(1), m_client_observer(NULL)
{

} // item_with_single_player_action_reader()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do post creation actions.
 */
template<class Base>
void ptb::item_with_single_player_action_reader<Base>::on_enters_layer()
{
  super::on_enters_layer();
  
  if ( level_variables::is_network_game(this->get_level()) )
    {
      m_client_observer =
        bear::engine::game::get_instance().get_network().connect_to_service
	( game_variables::get_ip(m_player_index).c_str(),
	  game_variables::get_port() );
      
      m_client_observer.subscribe<player_action_message>
	( boost::bind
	  ( &item_with_single_player_action_reader<Base>::on_message,
	    this, boost::placeholders::_1 ) );
    }
} // item_with_single_player_action_reader::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c unsigned \c integer.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
template<class Base>
bool ptb::item_with_single_player_action_reader<Base>::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result = true;

  if ( name == "item_with_single_player_action_reader.player_index" )
    m_player_index = value;
  else
    result = super::set_u_integer_field(name, value);

  return result;
} // item_with_single_player_action_reader::set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the index of the player to listen to.
 */
template<class Base>
unsigned int
ptb::item_with_single_player_action_reader<Base>::get_player_index() const
{
  return m_player_index;
} // item_with_single_player_action_reader::get_player_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Switch two actions.
 * \param a One of both switched actions.
 * \param b One of both switched actions.
 */
template<class Base>
void ptb::item_with_single_player_action_reader<Base>::switch_action
(player_action::value_type a, player_action::value_type b)
{
  bool present(false);
  actions_map::const_iterator it;

  for( it = m_switch_actions.begin();
       ( it != m_switch_actions.end() ) && ( !present ); ++it)
    present = ( (it->first == a) || (it->first == b) ||
                (it->second == a) || (it->second == b) );

  if ( !present )
    update_action(a, b, true, a);
} // item_with_single_player_action_reader::switch_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Clear two switched actions.
 * \param a One of both switched actions.
 * \param b One of both switched actions.
 */
template<class Base>
void ptb::item_with_single_player_action_reader<Base>::clear_switched_action
(player_action::value_type a, player_action::value_type b)
{
  bool present(false);
  actions_map::const_iterator it;

  // This initialization turns off the following warning:
  //   "'c' may be used uninitialized in this function"
  // It occurrs on the call to update_action() at the end of the function.
  // Actually the variable 'present' is true if and only if 'c' received a
  // value, so there is no problem.
  player_action::value_type c(player_action::action_null);

  for( it = m_switch_actions.begin();
       ( it != m_switch_actions.end() ) && !present; ++it)
    {
      if ( (it->first == a) && (it->second == b) )
         {
           present = true;
           c = a;
         }
      else if ( (it->first == b) && (it->second == a) )
         {
           present = true;
           c = b;
         }
    }

  if ( present )
    update_action(a, b, false, c);
} // item_with_single_player_action_reader::clear_switched_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start an action asked by the human player.
 * \param a The action.
 */
template<class Base>
void ptb::item_with_single_player_action_reader<Base>::start_action
( player_action::value_type a )
{
  // nothing to do
} // item_with_single_player_action_reader::start_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Continue an action asked by the human player.
 * \param elapsed_time How long the action is done.
 * \param a The action.
 */
template<class Base>
void ptb::item_with_single_player_action_reader<Base>::do_action
( bear::universe::time_type elapsed_time, player_action::value_type a )
{
  // nothing to do
} // item_with_single_player_action_reader::do_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop an action asked by the human player.
 * \param a The action.
 */
template<class Base>
void ptb::item_with_single_player_action_reader<Base>::stop_action
( player_action::value_type a )
{
  // nothing to do
} // item_with_single_player_action_reader::stop_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the index of the player to listen to.
 * \param i The index of the player.
 */
template<class Base>
void ptb::item_with_single_player_action_reader<Base>::set_player_index
( unsigned int i )
{
  m_player_index = i;
} // item_with_single_player_action_reader::set_player_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the action by which a given action is replaced.
 * \param a The replaced action.
 */
template<class Base>
ptb::player_action::value_type
ptb::item_with_single_player_action_reader<Base>::get_switched_action
(player_action::value_type a) const
{
  player_action::value_type result(a);
  actions_map::const_iterator it;

  for( it = m_switch_actions.begin();
       ( it != m_switch_actions.end() ) && ( result == a ); ++it)
    {
      if ( it->first == a )
       result = it->second;
      else if ( it->second == a )
       result = it->first;
    }

  return result;
} // item_with_single_player_action_reader::get_switched_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start an action asked by the human player.
 * \param player_index The index of the player asking the action.
 * \param a The action.
 */
template<class Base>
void ptb::item_with_single_player_action_reader<Base>::start_action
( unsigned int player_index, player_action::value_type a )
{
  if ( player_index == m_player_index )
    {
      start_action(get_switched_action(a));
      m_current_actions.insert(a);
    }
} // item_with_single_player_action_reader::start_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Continue an action asked by the human player.
 * \param elapsed_time How long the action is done.
 * \param player_index The index of the player asking the action.
 * \param a The action.
 */
template<class Base>
void ptb::item_with_single_player_action_reader<Base>::do_action
( bear::universe::time_type elapsed_time, unsigned int player_index,
  player_action::value_type a )
{
  if ( player_index == m_player_index )
    do_action(elapsed_time, get_switched_action(a));
} // item_with_single_player_action_reader::do_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop an action asked by the human player.
 * \param player_index The index of the player asking the action.
 * \param a The action.
 */
template<class Base>
void ptb::item_with_single_player_action_reader<Base>::stop_action
( unsigned int player_index, player_action::value_type a )
{
  if ( player_index == m_player_index )
    {
      stop_action(get_switched_action(a));

      if ( m_current_actions.find(a) != m_current_actions.end() )
        m_current_actions.erase(a);
    }
} // item_with_single_player_action_reader::stop_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop an action asked by the human player.
 * \param a One of both switched actions.
 * \param b One of both switched actions.
 * \param insertion Indicates if we insert the switch (or clear).
 * \param clear_action The action to clear.
 */
template<class Base>
void ptb::item_with_single_player_action_reader<Base>::update_action
(player_action::value_type a, player_action::value_type b,
 bool insertion, player_action::value_type clear_action)
{
  bool change_a(m_current_actions.find(a) != m_current_actions.end());
  bool change_b(m_current_actions.find(b) != m_current_actions.end());

  if ( change_a )
    this->stop_action(m_player_index, a);
  if ( change_b )
    this->stop_action(m_player_index, b);

  if ( insertion )
    m_switch_actions[a] = b;
  else
    m_switch_actions.erase(clear_action);

  if ( change_a )
    this->start_action(m_player_index, a);
  if ( change_b )
    this->start_action(m_player_index, b);
} // item_with_single_player_action_reader::update_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Read input actions without send actions.
 * \param elapsed_time Elapsed time since the last call.
 */
template<class Base>
void ptb::item_with_single_player_action_reader<Base>::read_input_action
(bear::universe::time_type elapsed_time)
{
  if ( level_variables::is_network_game(this->get_level()) )
    m_client_observer.process_message();
  else
    this->progress_input_reader(elapsed_time);
} // item_with_single_player_action_reader::read_input_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief The item receive a new message.
 * \param m The message.
 */
template<class Base>
void ptb::item_with_single_player_action_reader<Base>::on_message
(const player_action_message& m)
{
  if ( m.get_action().player_index == m_player_index )
    this->add_pending_action(m.get_action());  
} // item_with_single_player_action_reader::on_message()
