/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::small_honeypot class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/small_honeypot.hpp"

#include "universe/collision_info.hpp"
#include "generic_items/decorative_item.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/player_proxy.hpp"
#include "engine/game.hpp"

#include "engine/export.hpp"

BASE_ITEM_EXPORT( small_honeypot, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::small_honeypot::small_honeypot()
{
  set_mass(1);
  set_width(15);
  set_height(15);
  set_elasticity(0.2);
} // small_honeypot::small_honeypot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::small_honeypot::pre_cache()
{
  super::pre_cache();

  get_level_globals().load_animation("animation/powerup/small_air.canim");
  get_level_globals().load_animation("animation/powerup/small_fire.canim");
  get_level_globals().load_animation("animation/powerup/small_water.canim");
} // small_honeypot::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the collision is with a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::small_honeypot::collision_check_and_apply
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if ( p != NULL )
    {
      if ( !get_bonus_given()
           && ( info.get_collision_side() != bear::universe::zone::middle_zone )
           && ( p.get_index() <= 2 )
           && ( ( get_type() != base_bonus::air_power )
                || !game_variables::get_air_power(p.get_index()) )
           && ( ( get_type() != base_bonus::fire_power )
                || !game_variables::get_fire_power(p.get_index()) )
           && ( ( get_type() != base_bonus::water_power )
                || !game_variables::get_water_power(p.get_index()) ) )
        give_bonus(p);
    }
} // small_honeypot::collision_check_and_apply()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_apply().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::small_honeypot::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_and_apply(that, info);
} // small_honeypot::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do the actions related to a change in the bonus type.
 * \param t The new type of the bonus.
 */
void ptb::small_honeypot::do_set_type(base_bonus_type t)
{
  switch(t)
    {
    case fire_power:
      set_animation
        ( get_level_globals().get_animation
          ("animation/powerup/small_fire.canim") );
      break;
    case air_power:
      set_animation
        ( get_level_globals().get_animation
          ("animation/powerup/small_air.canim") );
      break;
    case water_power:
      set_animation
        ( get_level_globals().get_animation
          ("animation/powerup/small_water.canim") );
      break;
    default:
      {
        CLAW_FAIL( "Not a valid power for this class." );
      }
    }
} // small_honeypot::do_set_type()
