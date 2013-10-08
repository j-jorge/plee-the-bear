/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::hideout_bonus_item class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/hideout_bonus_item.hpp"

#include "ptb/defines.hpp"
#include "ptb/level_variables.hpp"
#include "ptb/message/status_layer_notification_message.hpp"
#include "ptb/item/bonus_points/bonus_points.hpp"
#include "engine/function/bool_level_variable_getter.hpp"
#include "engine/game.hpp"
#include <libintl.h>
#include <sstream>

BASE_ITEM_EXPORT( hideout_bonus_item, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::hideout_bonus_item::hideout_bonus_item()
{
  set_weak_collisions(true);
} // hideout_bonus_item::hideout_bonus_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::hideout_bonus_item::build()
{
  super::build();

  level_variables::set_object_count
    ( this->get_level(), "hideout",
      level_variables::get_object_count
      ( this->get_level(), "hideout" ) + 1);

  std::ostringstream s;
  s << "hideout "
    << level_variables::get_object_count( this->get_level(), "hideout" );;
  m_id = s.str();

  game_variables::set_hideout_state
    ( m_id, game_variables::get_hideout_state( m_id ) );

  if ( level_variables::get_object_count( this->get_level(), "hideout" ) == 1 )
    create_level_bonus();
} // hideout_bonus_item::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Activation by one player among the two players.
 * \param p The player.
 */
void ptb::hideout_bonus_item::on_one_player( const player_proxy& p )
{
  discover(p.get_index());
} // hideout_bonus_item::on_one_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Activation by all players.
 * \param p1 The first player.
 * \param p2 The second player. NULL in a single player game.
 */
void ptb::hideout_bonus_item::on_all_players
( const player_proxy& p1, const player_proxy& p2 )
{
  if (p2 == NULL)
    discover(p1.get_index());
  else
    discover(0);
} // hideout_bonus_item::on_all_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief The hideout is discovered.
 * \param index Index of player that discovers hideout. 
 */
void ptb::hideout_bonus_item::discover(unsigned int index)
{
  bool bonus(false);

  if ( !game_variables::get_hideout_state(m_id) )
    {
      game_variables::set_hideout_state( m_id, true);
      bonus = true;
    }

  bear::engine::var_map vars;
  bear::engine::game::get_instance().get_game_variables
    ( vars, PTB_PERSISTENT_PREFIX +
      game_variables::get_main_level_name() + "/hideout/.*");
  
  bear::engine::var_map::iterator<bool>::type it;
  std::string prefix
    (PTB_PERSISTENT_PREFIX + game_variables::get_main_level_name()
     + "/hideout/");
  
  unsigned int found = 0;
  for ( it=vars.begin<bool>();
	(it!=vars.end<bool>()); ++it )
    {
      std::string var(it->first);
      std::string c1;
      c1 = var.erase(0, prefix.size());
      
      if ( game_variables::get_hideout_state(c1) )
	found++;
      else
	bonus = false;
    }

  if ( bonus )
    level_variables::all_hideouts_found(get_level());

  send_notification(index,found,vars.size());

  kill();
} // hideout_bonus_item::discover()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create level bonus object.
 */
void ptb::hideout_bonus_item::create_level_bonus()
{
  bonus_points* new_bonus = new bonus_points( "Great explorer", 10000 );

  new_bonus->set_picture_filename("gfx/ui/bonus-icons/bonus-icons.png");
  new_bonus->set_picture_name("hideouts");
  new_bonus->set_condition
   ( bear::engine::bool_level_variable_getter
     (&get_level(), "all_hideouts_found"));

  new_item( *new_bonus );
  CLAW_ASSERT(new_bonus->is_valid(),
              "The bonus isn't correctly initialized" );
  new_bonus->set_center_of_mass(get_center_of_mass());
} // hideout_bonus_item::create_level_bonus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Send a notification on status layer.
 * \param index Index of player that discovers hideout. 
 * \param found Number of found hideout.
 * \param total Number of hideout.
 */
void ptb::hideout_bonus_item::send_notification
(unsigned int index, unsigned int found, unsigned int total)
{
  status_layer_notification_message msg;
  
  std::ostringstream oss;
  oss << gettext("Great explorer") << " " 
      << found << "/" << total;

  bear::visual::sprite sp = 
    get_level_globals().auto_sprite
    ( "gfx/ui/bonus-icons/bonus-icons.png", "hideouts" );
  msg.set_notification( index, sp, oss.str());

  get_level_globals().send_message
    ( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
} // hideout_bonus_item::send_notification()
