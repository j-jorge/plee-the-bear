/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the bear::timer_kill_players class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/timer_kill_players.hpp"

#include "ptb/expr/boolean_player_function.hpp"
#include "ptb/item/player_killer_toggle.hpp"
#include "ptb/game_variables.hpp"

#include "generic_items/toggle_group.hpp"
#include "generic_items/trigger.hpp"

BASE_ITEM_EXPORT( timer_kill_players, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Do post creation actions.
 */
void ptb::timer_kill_players::build()
{
  super::build();

  create_trigger();
  create_toggles();
} // timer_kill_players::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the trigger who commands the timer.
 */
void ptb::timer_kill_players::create_trigger()
{
  bear::trigger* t = new bear::trigger( bear::trigger::trigger_condition );
  bear::expr::boolean_expression p1_marionette =
    boolean_player_function_maker
    ( std::mem_fun_ref(&player_proxy::is_a_marionette), 1,
      get_level_globals() );

  if ( game_variables::get_players_count() == 1 )
    t->set_condition( !p1_marionette );
  else
    {
      bear::expr::boolean_expression p2_marionette =
        boolean_player_function_maker
        ( std::mem_fun_ref(&player_proxy::is_a_marionette), 2,
          get_level_globals() );

      t->set_condition( !p1_marionette || !p2_marionette );
    }

  t->set_center_of_mass( get_center_of_mass() );
  t->set_global( is_global() );
  t->set_insert_as_static();

  t->add_toggle(this);

  new_item(*t);
} // ptb::timer_kill_players::create_trigger()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the toggles activated at the end of the countdown.
 */
void ptb::timer_kill_players::create_toggles()
{
  if ( !is_countdown() )
    return;

  bear::toggle_group* toggles = new bear::toggle_group;
  toggles->set_insert_as_static();

  if ( get_toggle() != NULL )
    toggles->insert( get_toggle() );

  const unsigned int n = game_variables::get_players_count();

  for ( unsigned int i=1; i<=n; ++i )
    toggles->insert( create_kill_toggle(i) );

  toggles->set_delay(0);
  new_item( *toggles );
  set_toggle( toggles );
} // timer_kill_players::create_toggles()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a toggle to kill a player.
 * \param i The index of the player to kill.
 */
bear::engine::base_item*
ptb::timer_kill_players::create_kill_toggle( unsigned int i ) const
{
  player_killer_toggle* result = new player_killer_toggle(i);

  result->set_center_of_mass( get_center_of_mass() );
  result->set_insert_as_static();
  result->set_global( is_global() );
  new_item( *result );

  return result;
} // timer_kill_players::create_kill_toggle()
