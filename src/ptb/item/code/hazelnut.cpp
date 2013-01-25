/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::hazelnut class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/hazelnut.hpp"

#include "ptb/player_proxy.hpp"
#include "ptb/level_variables.hpp"
#include "ptb/item/bonus_points/bonus_points.hpp"
#include "ptb/defines.hpp"
#include "ptb/message/status_layer_notification_message.hpp"

#include "engine/level_globals.hpp"
#include "engine/function/bool_level_variable_getter.hpp"

#include <libintl.h>

BASE_ITEM_EXPORT( hazelnut, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::hazelnut::hazelnut()
  : sniffable("hazelnut")
{
  set_can_move_items(false);
  set_elasticity(1);
  set_friction(0.98);
  set_mass(20);
  set_density(2);
} // hazelnut::hazelnut()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::hazelnut::pre_cache()
{
  super::pre_cache();

  get_level_globals().load_animation("animation/owl/hazelnut.canim");
} // hazelnut::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::hazelnut::build()
{
  super::build();

  level_variables::set_object_count
    ( this->get_level(), "hazelnut",
      level_variables::get_object_count( this->get_level(), "hazelnut" ) + 1);

  if ( level_variables::get_object_count( this->get_level(), "hazelnut" ) == 1 )
    create_level_bonus();

  set_animation
    ( get_level_globals().get_animation("animation/owl/hazelnut.canim") );

  set_size( get_animation().get_size() );
} // hazelnut::build()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::hazelnut::progress( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);

  if ( has_bottom_contact() )
    add_internal_force( bear::universe::force_type(0, 200000) );
} // hazelnut::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the collision is with a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::hazelnut::collision_check_and_apply
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  const player_proxy p(&that);

  if ( p != NULL )
    {
      if ( !level_variables::get_current_hazelnut(get_level()) )
        {
          if ( info.get_collision_side() != bear::universe::zone::middle_zone)
            {
              level_variables::set_current_hazelnut(get_level(), true);
              level_variables::set_hazelnut_found(get_level(), true);
	      send_notification(p.get_index());
	      on_found(p.get_index());
              kill();
            }
          else
            default_collision(info);
        }
      else
        default_collision(info);
    }
  else
    default_collision(info);
} // hazelnut::collision_check_and_apply()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_apply().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::hazelnut::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_and_apply(that, info);
} // hazelnut::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create level bonus objects.
 */
void ptb::hazelnut::create_level_bonus()
{
  bonus_points* new_bonus_hazelnut = new bonus_points( "Hazelnut", 5000 );

  new_bonus_hazelnut->set_picture_filename
    ("gfx/ui/bonus-icons/bonus-icons.png");
  new_bonus_hazelnut->set_picture_name("hazelnut");
  new_bonus_hazelnut->set_condition
    ( bear::engine::bool_level_variable_getter
      ( &get_level(), "hazelnut_found" ) );

  new_item( *new_bonus_hazelnut );
  CLAW_ASSERT(new_bonus_hazelnut->is_valid(),
              "The bonus_points isn't correctly initialized" );
  new_bonus_hazelnut->set_center_of_mass(get_center_of_mass());
} // hazelnut::create_level_bonus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Send a notification on status layer.
 * \param index Index of player that finds hazelnut. 
 */
void ptb::hazelnut::send_notification(unsigned int index)
{
  status_layer_notification_message msg;

  bear::visual::sprite sp = 
    get_level_globals().auto_sprite
    ( "gfx/ui/bonus-icons/bonus-icons.png", "hazelnut" );
  msg.set_notification( index, sp, gettext("Hazelnut"));

  get_level_globals().send_message
    ( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
} // hazelnut::send_notification()
