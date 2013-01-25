/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::passive_enemy class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/passive_enemy.hpp"
#include "engine/export.hpp"

BASE_ITEM_EXPORT( passive_enemy, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::passive_enemy::passive_enemy()
  : m_right_side_type(inactive_type), m_left_side_type(inactive_type),
    m_top_side_type(inactive_type), m_bottom_side_type(inactive_type)
{
  set_can_move_items(true);
  m_monster_type = monster::nature_monster;
  m_offensive_coefficients[indefensible_attack] = 1;
} // passive_enemy::passive_enemy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_align().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::passive_enemy::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  side_type t = inactive_type;

  switch( info.get_collision_side() )
    {
    case bear::universe::zone::top_zone:
      t = m_top_side_type; break;
    case bear::universe::zone::bottom_zone:
      t = m_bottom_side_type; break;
    case bear::universe::zone::middle_left_zone:
      t = m_left_side_type; break;
    case bear::universe::zone::middle_right_zone:
      t = m_right_side_type; break;
    default:
      { }
    }

  if ( t == attack_type )
    {
      if ( collision_and_attack(that, info) )
        collision_check_and_align(that, info);
    }
  else
    collision_check_and_align(that, info);
} // passive_enemy::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c string.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::passive_enemy::set_string_field
( const std::string& name, const std::string& value )
{
  bool result = true;

  if ( name == "passive_enemy.type_right_side" )
    result = set_side_type(m_right_side_type, value);
  else if ( name == "passive_enemy.type_left_side" )
    result = set_side_type(m_left_side_type, value);
  else if ( name == "passive_enemy.type_top_side" )
    result = set_side_type(m_top_side_type, value);
  else if ( name == "passive_enemy.type_bottom_side" )
    result = set_side_type(m_bottom_side_type, value);
  else
    result = super::set_string_field(name, value);

  return result;
} // passive_enemy::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if all required fields are initialized.
 */
bool ptb::passive_enemy::is_valid() const
{
  return ( !( ( get_monster_type() != monster::nature_monster) &&
               ( is_fixed() ) ) ) &&
    super::is_valid();
} // passive_enemy::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the type of a given side.
 * \param side The considered side.
 * \param value The new type of the side.
 * \return false if the value is unknow, true otherwise.
 */
bool ptb::passive_enemy::set_side_type
(side_type& side, const std::string& value)
{
  bool result = true;

  if ( value == "inactive" )
    side = inactive_type;
  else if ( value == "attack" )
    side = attack_type;
  else
    result = false;

  return result;
} // passive_enemy::set_side()
