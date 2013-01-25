/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::level_exit class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/level_exit.hpp"

#include "ptb/defines.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/level_variables.hpp"
#include "ptb/util/player_util.hpp"

#include "ptb/transition_effect/level_ending_effect.hpp"
#include "engine/message/transition_effect_message.hpp"

BASE_ITEM_EXPORT( level_exit, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::level_exit::level_exit()
  : m_exit_name(PTB_DEFAULT_EXIT_NAME)
{
  set_phantom(true);
  set_can_move_items(false);
} // level_exit::level_exit()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::level_exit::build()
{
  super::build();

  game_variables::set_level_name
    (get_level().get_filename(), get_level().get_name());
  game_variables::set_level_precedence
    (get_level().get_filename(), m_level_name);
  game_variables::load_player_variables();
} // level_exit::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 */
void ptb::level_exit::progress
( bear::universe::time_type elapsed_time )
{
  if ( !level_variables::is_exiting( get_level() )
       && ( level_variables::get_players_on_exit( get_level() )
            == game_variables::get_players_count() ) )
    {
      level_variables::set_exiting( get_level() );
      game_variables::set_next_level_name(m_level_name);
      game_variables::set_finished_level(get_level().get_filename(), true);

      for (unsigned int i=1; i<=game_variables::get_players_count(); ++i)
        {
          player_proxy p = util::find_player( get_level_globals(), i );
          if ( p != NULL )
            p.set_marionette(true);
        }

      bear::engine::transition_effect_message<level_ending_effect> msg;

      if ( has_world() )
        msg.get_effect().set_world( &get_world() );

      get_level_globals().send_message
        ( PTB_TRANSITION_EFFECT_DEFAULT_TARGET_NAME, msg );
    }

  level_variables::set_players_on_exit( get_level(), 0 );
} // level_exit::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::level_exit::is_valid() const
{
  return !m_level_name.empty() && super::is_valid();
} // level_exit::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "std::string".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::level_exit::set_string_field
( const std::string& name, const std::string& value )
{
  bool result(true);

  if ( name == "level_exit.level" )
    m_level_name = value;
  else if ( name == "level_exit.exit_name" )
    m_exit_name = value;
  else
    result = super::set_string_field( name, value );

  return result;
} // level_exit::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the collision is with a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::level_exit::collision_check_and_apply
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if ( p != NULL )
    {
      game_variables::set_last_corrupting_bonus_count
        ( m_level_name, game_variables::get_corrupting_bonus_count() );
      game_variables::set_last_level_exit
        ( m_level_name, p.get_index(), m_exit_name );
      level_variables::set_players_on_exit
        ( get_level(), level_variables::get_players_on_exit(get_level()) + 1 );
      game_variables::save_player_variables();
    }
} // level_exit::collision_check_and_apply()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_apply().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::level_exit::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_and_apply(that, info);
} // level_exit::collision()
