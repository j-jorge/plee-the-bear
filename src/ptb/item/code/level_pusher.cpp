/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::level_pusher class.
 * \author Julien Jorge
 */
#include "ptb/item/level_pusher.hpp"

#include "ptb/defines.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/player_proxy.hpp"

#include "engine/game.hpp"

BASE_ITEM_EXPORT( level_pusher, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::level_pusher::level_pusher()
  : m_pushed(false), m_players_count(0)
{
  set_phantom(true);
  set_can_move_items(false);
} // level_pusher::level_pusher()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 */
void ptb::level_pusher::progress
( bear::universe::time_type elapsed_time )
{
  if ( m_players_count == 0 )
    m_pushed = false;
  else if ( (m_players_count == game_variables::get_players_count())
            && !m_pushed )
    {
      m_pushed = true;

      game_variables::set_next_level_name(m_level_name);
      bear::engine::game::get_instance().push_level( PTB_LOADING_LEVEL_NAME );
    }

  m_players_count = 0;
} // level_pusher::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "std::string".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::level_pusher::set_string_field
( const std::string& name, const std::string& value )
{
  bool result;

  if ( name == "level_pusher.level" )
    {
      m_level_name = value;
      result = true;
    }
  else
    result = super::set_string_field( name, value );

  return result;
} // level_pusher::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::level_pusher::is_valid() const
{
  return !m_level_name.empty() && super::is_valid();
} // level_pusher::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the collision is with a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::level_pusher::collision_check_and_apply
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if ( p != NULL )
    ++m_players_count;
} // level_pusher::collision_check_and_apply()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_apply().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::level_pusher::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_and_apply(that, info);
} // level_pusher::collision()
