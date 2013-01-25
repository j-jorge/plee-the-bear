/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::script_actor_player class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/script_actor_player.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/player.hpp"
#include "ptb/util/player_util.hpp"

#include "ptb/controller_config.hpp"

BASE_ITEM_EXPORT( script_actor_player, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::script_actor_player::script_actor_player()
  : m_date(0), m_player_index(1)
{
  set_phantom(true);
  set_can_move_items(false);
  set_artificial(true);
} // script_actor_player::script_actor_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c unsigned \c integer.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::script_actor_player::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result = true;

  if ( name == "script_actor_player.player_index" )
    m_player_index = value;
  else
    result = super::set_u_integer_field(name, value);

  return result;
} // script_actor_player:set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c item.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::script_actor_player::set_item_field
( const std::string& name, bear::engine::base_item* value )
{
  bool result = true;

  if ( name == "script_actor_player.player" )
    {
      player_proxy p(value);

      if ( p != NULL )
        {
          m_player_index = p.get_index();
          m_player = p.get_player_instance();
        }
      else
        result = false;
    }
  else
    result = super::set_item_field(name, value);

  return result;
} // script_actor_player::set_item_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is well initialized.
 */
bool ptb::script_actor_player::is_valid() const
{
  return (m_player_index != 0) && super::is_valid();
} // script_actor_player::is_valid()


/*----------------------------------------------------------------------------*/
/**
 * \brief Progress the item.
 * \param elapsed_time The duration of the activity.
 */
void ptb::script_actor_player::progress
( bear::universe::time_type elapsed_time )
{
  progress_actions(elapsed_time);

  if ( m_player != (player*)NULL )
    set_center_of_mass( m_player->get_center_of_mass() );
} // script_actor_player::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the current actions.
 * \param elapsed_time The duration of the progression.
 */
void ptb::script_actor_player::progress_actions
( bear::universe::time_type elapsed_time )
{
  m_date += elapsed_time;

  if ( m_player != (player*)NULL )
    {
      current_actions_map::iterator it;
      std::list<player_action::value_type> finished_actions;
      std::list<player_action::value_type>::iterator it2;

      // continue actions
      for ( it=m_current_actions.begin();  it!=m_current_actions.end(); ++it )
        if ( m_new_actions.find(it->first) == m_new_actions.end())
          {
            if ( it->second <= elapsed_time )
              {
                it->second = 0;
                finished_actions.push_back(it->first);
              }
            else
              {
                m_player->do_action(elapsed_time, it->first);
                it->second -= elapsed_time;
              }
          }

      // stop actions
      for ( it2=finished_actions.begin(); it2!=finished_actions.end(); ++it2 )
        {
          m_player->stop_action(*it2);
          m_current_actions.erase(*it2);
        }

      m_new_actions.clear();
    }
} // script_actor_player::progress_action_file()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a new action.
 * \param action_name The name of the new action.
 * \param duration The duration of the new action.
 */
void ptb::script_actor_player::do_action
( const std::string& action_name, bear::universe::time_type duration )
{
  if ( m_player != (player*)NULL )
    {
      player_action::value_type action
        ( player_action::from_string(action_name) );

      m_player->start_action(action);
      m_current_actions[action] = duration;
      m_new_actions.insert(action);
    }
} // script_actor_player::do_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief The player say a sentence.
 * \param speech The speech.
 */
void ptb::script_actor_player::talk(const std::vector<std::string>& speech)
{
   if ( m_player != (player*)NULL )
    {
      std::vector<std::string> speeches;

      controller_config cfg;

      unsigned int index(m_player->get_index());
      const controller_layout* layout(NULL);

      if ( index <= 2 )
        layout = &(cfg.get_layout( index ));

      std::vector<std::string>::const_iterator it;
      for ( it=speech.begin(); it!=speech.end(); ++it)
        {
          std::string text;
          if ( layout != NULL )
            layout->escape_action_sequence(*it, text);
          else
            text = *it;

          speeches.push_back(text);
        }

      m_player->speak(speeches);
    }
} // script_actor_player::talk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give some stones.
 * \param stock The number of given stones.
 */
void ptb::script_actor_player::give_stone(unsigned int stock)
{
  if ( m_player != (player*)NULL )
    game_variables::set_stones_count
      ( m_player->get_index(),
        game_variables::get_stones_count(m_player->get_index()) + stock);
} // script_actor_player::give_stone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set some stonesa given power.
 * \param power The consider power.
 * \param status The new status of the power.
 */
void ptb::script_actor_player::set_power(const std::string& power, bool status)
{
  if ( m_player != (player*)NULL )
    {
      if ( power == "air" )
        game_variables::set_air_power(m_player->get_index(), status);
      else if ( power == "fire" )
        game_variables::set_fire_power(m_player->get_index(), status);
      else if ( power == "water" )
        game_variables::set_water_power(m_player->get_index(), status);
    }
} // script_actor_player::set_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop a player (speed and force).
 */
void ptb::script_actor_player::stop()
{
  if ( m_player != (player*)NULL )
    m_player->stop();
} // script_actor_player::stop()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a given action is authorized.
 * \param action The action to authorize.
 */
void ptb::script_actor_player::authorize_action
(const std::string& action)
{
  if ( m_player != (player*)NULL )
    {
      player_action::value_type a(player_action::from_string(action));

      if ( a != player_action::action_null )
        m_player->set_authorized_action(a, true);
    }
} // script_actor_player::authorize_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a given action is forbidden.
 * \param action The action to refuse.
 */
void ptb::script_actor_player::refuse_action
(const std::string& action)
{
  if ( m_player != (player*)NULL )
    {
      player_action::value_type a(player_action::from_string(action));

      if ( a != player_action::action_null )
        m_player->set_authorized_action(a, false);
    }
} // script_actor_player::refuse_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Search player.
 */
void ptb::script_actor_player::search_player()
{
  if ( m_player == (player*)NULL )
    {
      const player_proxy p =
        util::find_player( get_level_globals(), m_player_index );
      m_player = p.get_player_instance();
    }

  if ( m_player != (player*)NULL )
    {
      m_player->set_status_look_upward(false);
      m_player->set_status_crouch(false);
      m_player->set_marionette(true);
    }
} // script_actor_player::search_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the items concerned by a progress/move of this one.
 * \param d (out) A list to which are added such items.
 */
void ptb::script_actor_player::get_dependent_items
( std::list<physical_item*>& d ) const
{
  super::get_dependent_items(d);

  if ( m_player != (player*)NULL )
    d.push_front( m_player.get() );
} // script_actor_player::get_dependent_items()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to control the player.
 */
void ptb::script_actor_player::control_player()
{
  search_player();
} // script_actor_player::control_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Release the player.
 */
void ptb::script_actor_player::release_player()
{
  if ( m_player != (player*)NULL )
    {
      m_player->set_marionette(false);
      m_player = NULL;
    }
} // script_actor_player::release_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add oxygen to the player.
 *
 * \param oxygen Quantity of oxygen to give.
 */
void ptb::script_actor_player::give_oxygen(double oxygen)
{
  if ( m_player != (player*)NULL )
    m_player->receive_oxygen(oxygen);
} // player::give_oxygen()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add the instance of player in the script director.
 * \param script The script context in which we add the player.
 * \param name The name of the player.
 */
void ptb::script_actor_player::add_player_in_script
( bear::engine::script_runner& script, const std::string& name)
{
  if ( m_player != (player*)NULL )
    script.set_actor_item( name, m_player.get() );
} // script_actor_player::add_player_in_script()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::script_actor_player::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_2
    ( ptb::script_actor_player, do_action, void, const std::string&,
      bear::universe::time_type);
  TEXT_INTERFACE_CONNECT_METHOD_1
    ( ptb::script_actor_player, talk, void, const std::vector<std::string>& );
  TEXT_INTERFACE_CONNECT_METHOD_1
    ( ptb::script_actor_player, give_stone, void, unsigned int );
  TEXT_INTERFACE_CONNECT_METHOD_2
    ( ptb::script_actor_player, set_power, void, const std::string&, bool );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::script_actor_player, stop, void );
  TEXT_INTERFACE_CONNECT_METHOD_2( ptb::script_actor_player,
                                   add_player_in_script, void,
                                   bear::engine::script_runner&,
                                   const std::string& );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::script_actor_player, control_player,
                                   void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::script_actor_player, release_player,
                                   void );
  TEXT_INTERFACE_CONNECT_METHOD_1( ptb::script_actor_player, authorize_action,
                                   void, const std::string&);
  TEXT_INTERFACE_CONNECT_METHOD_1( ptb::script_actor_player, refuse_action,
                                   void, const std::string&);
  TEXT_INTERFACE_CONNECT_METHOD_1( ptb::script_actor_player, give_oxygen,
                                   void, double);
} // script_actor_player::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::script_actor_player )
