/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::honeypot class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/honeypot.hpp"

#include "ptb/item/bonus_points/bonus_points.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/level_variables.hpp"
#include "ptb/util/player_util.hpp"
#include "ptb/defines.hpp"
#include "ptb/message/status_layer_notification_message.hpp"

#include "generic_items/decorative_item.hpp"
#include "engine/function/bool_level_variable_getter.hpp"
#include "engine/function/linear_level_variable_getter.hpp"

#include <libintl.h>

BASE_ITEM_EXPORT( honeypot, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::honeypot::honeypot()
  : sniffable("honeypot"), m_given(false)
{
  set_phantom(true);
  set_can_move_items(false);
} // honeypot::honeypot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::honeypot::pre_cache()
{
  get_level_globals().load_animation("animation/shiny-honey-jar.canim");
} // honeypot::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::honeypot::build()
{
  super::build();

  level_variables::set_object_count
        ( get_level(), "honeypot",
          level_variables::get_object_count( get_level(), "honeypot" ) + 1);
  m_id = level_variables::get_object_count( get_level(), "honeypot" );

  std::ostringstream s;
  s << "honeypot " << m_id;
  std::string name(s.str());

  create_level_bonus(name);

  level_variables::set_honeypot_found
    ( get_level(), m_id, game_variables::get_level_object_state
      (game_variables::get_main_level_name(), name ));

  game_variables::set_level_object_state
    (name, level_variables::get_honeypot_found(get_level(), m_id));
  game_variables::set_level_object_filename
    (name, "gfx/ui/bonus-icons/bonus-icons.png");
  game_variables::set_level_object_name(name, name);

  set_animation
    ( get_level_globals().get_animation("animation/shiny-honey-jar.canim") );

  if ( level_variables::get_honeypot_found(get_level(), m_id) )
    {
      get_rendering_attributes().set_intensity( 0.25, 0.25, 1 );
      get_rendering_attributes().set_opacity( 0.5 );
    }

  set_size( 64, 64 );
} // honeypot::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the collision is with a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::honeypot::collision_check_and_apply
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if ( p != NULL )
    {
      if ( !m_given )
        {
          create_decoration();
          m_given = true;
          level_variables::set_honeypots_found
            ( get_level(),
              level_variables::get_honeypots_found(get_level()) + 1 );
          level_variables::set_honeypot_found( get_level(), m_id, true);

          if ( level_variables::get_honeypots_found(get_level()) % 5 == 0 )
            {
              give_life(1);
              give_life(2);
            }

	  on_found(p.get_index());
	  send_notification(p.get_index());

          kill();
        }
      else
        default_collision(info);
    }
  else
    default_collision(info);
} // honeypot::collision_check_and_apply()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_apply().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::honeypot::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_and_apply(that, info);
} // honeypot::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give a life at each player.
 * \param index The index of the player that receives a life.
 */
void ptb::honeypot::give_life(unsigned int index) const
{
  if ( util::find_player( get_level_globals(), index ) != NULL )
    game_variables::set_lives_count
      ( index, game_variables::get_lives_count(index) + 1);
} // honeypot::give_life()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a decoration.
 */
void ptb::honeypot::create_decoration()
{
  bear::decorative_item* item = new bear::decorative_item;

  item->set_animation
    (get_level_globals().get_animation
     ("animation/corrupting-bonus-disapearing.canim"));
  item->get_rendering_attributes().set_angle(get_visual_angle());
  item->set_kill_when_finished(true);
  item->set_z_position(get_z_position()-1);

  new_item( *item );

  item->set_center_of_mass(get_center_of_mass());

  CLAW_ASSERT( item->is_valid(),
               "The decoration of corrupting_bonus isn't correctly "
               "initialized" );
} // honeypot::create_decoration()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create level bonus objects.
 */
void ptb::honeypot::create_level_bonus(const std::string& name)
{
  bonus_points* new_bonus = new bonus_points( name, 0 );

  new_bonus->set_picture_filename("gfx/ui/bonus-icons/bonus-icons.png");
  new_bonus->set_picture_name(name);
  new_bonus->set_condition
    ( bear::engine::bool_level_variable_getter(&get_level(), name) );

  new_item( *new_bonus );
  CLAW_ASSERT(new_bonus->is_valid(),
              "The bonus isn't correctly initialized" );
  new_bonus->set_center_of_mass(get_center_of_mass());

  if ( m_id == 1 )
    {
      bonus_points* bonus = new bonus_points( "Honey pots", 5000 );

      bonus->set_points
        ( 5000
          * bear::engine::linear_level_variable_getter<unsigned int>
          (&get_level(), "honeypots_found") );

      new_item( *bonus );
      CLAW_ASSERT(new_bonus->is_valid(),
                  "The bonus isn't correctly initialized" );
      bonus->set_center_of_mass(get_center_of_mass());
    }
} // honeypot::create_level_bonus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Send a notification on status layer when the honeypot is found.
 * \param index Index of player that finds honeypot. 
 */
void ptb::honeypot::send_notification(unsigned int index)
{
  std::ostringstream s;
  s << "honeypot " << m_id;
  std::string name(s.str());

  status_layer_notification_message msg;

  bear::visual::sprite sp = 
    get_level_globals().auto_sprite
    ( "gfx/ui/bonus-icons/bonus-icons.png", name );
  msg.set_notification( index, sp, gettext(name.c_str()));

  get_level_globals().send_message
    ( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
} // honeypot::send_notification()
