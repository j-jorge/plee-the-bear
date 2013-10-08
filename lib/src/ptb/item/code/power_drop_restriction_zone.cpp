/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::power_drop_restriction_bonus class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/power_drop_restriction_zone.hpp"

#include "ptb/player_proxy.hpp"

BASE_ITEM_EXPORT( power_drop_restriction_zone, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::power_drop_restriction_zone::power_drop_restriction_zone()
  : m_air(false), m_fire(false), m_water(false)
{
  set_phantom(true);
  set_can_move_items(false);
} // power_drop_restriction_zone::power_drop_restriction_zone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 * \param air Indicates if the player can throw the air power.
 * \param fire Indicates if the player can throw the fire power.
 * \param water Indicates if the player can throw the water power.
 */
void ptb::power_drop_restriction_zone::set_powers_restriction
(bool air, bool fire, bool water)
{
  m_air = air;
  m_fire = fire;
  m_water = water;
} // power_drop_restriction_zone::set_powers_restriction()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "bool".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::power_drop_restriction_zone::set_bool_field
( const std::string& name, bool value )
{
  bool result = true;

  if ( name == "power_drop_restriction_zone.air" )
    m_air = value;
  else if ( name == "power_drop_restriction_zone.fire" )
    m_fire = value;
  else if ( name == "power_drop_restriction_zone.water" )
    m_water = value;
  else
    result = super::set_bool_field( name, value );

  return result;
} // power_drop_restriction_zone::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the collision is with a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::power_drop_restriction_zone::collision_check_and_apply
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if ( p != NULL )
    {
      if ( m_air )
        p.set_can_throw_power(false, monster::air_attack);

      if ( m_fire )
        p.set_can_throw_power(false, monster::fire_attack);

      if ( m_water )
        p.set_can_throw_power(false, monster::water_attack);
    }
} // power_drop_restriction_zone::collision_check_and_apply()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_apply().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::power_drop_restriction_zone::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_and_apply(that, info);
} // power_drop_restriction_zone::collision()
