/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::level_popper class.
 * \author Julien Jorge
 */
#include "ptb/item/level_popper.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/player_proxy.hpp"

#include "engine/message/transition_effect_message.hpp"
#include "engine/message/transition_effect_erase_message.hpp"
#include "engine/transition_effect/fade_effect.hpp"
#include "engine/variable/variable.hpp"
#include "engine/game.hpp"

BASE_ITEM_EXPORT( level_popper, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::level_popper::level_popper()
  : m_players_count(0), m_applied(false), m_fade_duration(1), m_time(0),
    m_effect_id(bear::engine::transition_layer::not_an_id)
{
  set_phantom(true);
  set_can_move_items(false);
} // level_popper::level_popper()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destroy the item.
 */
void ptb::level_popper::destroy()
{
  bear::engine::transition_effect_erase_message msg(m_effect_id);
  get_level_globals().send_message( m_transition_layer_name, msg );
} // level_popper::destroy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 */
void ptb::level_popper::progress
( bear::universe::time_type elapsed_time )
{
  if ( m_players_count == game_variables::get_players_count() )
    {
      m_applied = true;
      start_fading();
    }

  if ( m_applied )
    m_time += elapsed_time;

  if ( m_time >= m_fade_duration )
    bear::engine::game::get_instance().pop_level();

  m_players_count = 0;
} // level_popper::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type string.
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::level_popper::set_string_field
( const std::string& name, const std::string& value )
{
  bool result = true;

  if ( name == "level_popper.transition_layer_name" )
    m_transition_layer_name = get_string_from_vars(value);
  else
    result = super::set_string_field( name, value );

  return result;
} // level_popper::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "real".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::level_popper::set_real_field
( const std::string& name, double value )
{
  bool result(true);

  if ( name == "level_popper.fade_duration" )
    m_fade_duration = value;
  else
    result = super::set_real_field( name, value );

  return result;
} // level_popper::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the collision is with a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::level_popper::collision_check_and_apply
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if ( p != NULL )
    ++m_players_count;
} // level_popper::collision_check_and_apply()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_apply().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::level_popper::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  if ( !m_applied )
    collision_check_and_apply(that, info);
} // level_popper::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start fading before loading the level.
 */
void ptb::level_popper::start_fading()
{
  if ( (m_fade_duration > 0) && !m_transition_layer_name.empty() )
    {
      bear::engine::transition_effect_message<bear::engine::fade_effect> msg;
      msg.get_effect().set_duration(m_fade_duration, 1, 0);
      msg.get_effect().set_color( 0, 0, 0 );
      get_level_globals().send_message( m_transition_layer_name, msg );

      m_effect_id = msg.get_id();
    }
} // level_popper::start_fading()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a string from the game variable.
 * \param name The name of the game variable.
 * \return \a name if there is such a variable.
 */
std::string ptb::level_popper::get_string_from_vars
( const std::string& name ) const
{
  // The parameter is the default result.
  std::string result(name);

  bear::engine::variable<std::string> var(name, name);

  if ( bear::engine::game::get_instance().game_variable_exists(var) )
    {
      bear::engine::game::get_instance().get_game_variable(var);

      if ( !var.get_value().empty() )
        result = var.get_value();
    }

  return result;
} // level_popper::get_string_from_vars()
