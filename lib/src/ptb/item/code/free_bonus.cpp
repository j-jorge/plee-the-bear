/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::free_bonus class.
 * \author Julien Jorge
 */
#include "ptb/item/free_bonus.hpp"

#include "ptb/level_variables.hpp"
#include "ptb/player_proxy.hpp"

#include "universe/collision_info.hpp"

BASE_ITEM_EXPORT( free_bonus, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::free_bonus::free_bonus()
{
  set_can_move_items(false);
} // free_bonus::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::free_bonus::pre_cache()
{
  super::pre_cache();

  get_level_globals().load_animation( "animation/stones/stone.canim" );
} // free_bonus::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the collision is with a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::free_bonus::collision_check_and_apply
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if ( p != NULL && !get_bonus_given() )
    give_bonus(p);
  else
    default_collision(info);
} // free_bonus::collision_check_and_apply()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_apply().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::free_bonus::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_and_apply(that, info);
} // free_bonus::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do the actions related to a change in the bonus type.
 * \param t The new type of the bonus.
 */
void ptb::free_bonus::do_set_type(base_bonus_type t)
{
  switch(t)
    {
    case stones_stock:
      set_animation
      ( get_level_globals().get_animation("animation/stones/stone.canim") );
      set_stock(1);
      break;
    case stones_big_stock:
      set_animation
      ( get_level_globals().get_animation("animation/stones/stone.canim") );
      set_stock(5);
      break;
    case fire_power:
    case air_power:
    case water_power:
    case invincibility_power:
    case one_more_life:
    case increase_max_energy:
    case switch_players:
    default:
      {
        CLAW_FAIL( "Not a valid power." );
      }
    }

  const bear::universe::position_type pos = get_center_of_mass();
  set_size( get_animation().get_size() );
  set_center_of_mass(pos);
} // free_bonus::do_set_type()
