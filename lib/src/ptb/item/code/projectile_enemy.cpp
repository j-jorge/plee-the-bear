/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::projectile_enemy class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/projectile_enemy.hpp"
#include "engine/world.hpp"
#include "generic_items/decorative_item.hpp"
#include "engine/export.hpp"

BASE_ITEM_EXPORT( projectile_enemy, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::projectile_enemy::projectile_enemy()
  : m_projectile_model(""), m_is_dead(false)
{
  m_monster_type = monster::enemy_monster;
  set_size(26, 26);
  set_mass(10);

  m_offensive_force = 10;
  m_defensive_powers[normal_attack] = true;
  m_offensive_coefficients[indefensible_attack] = 1;
} // projectile_enemy::projectile_enemy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::projectile_enemy::on_enters_layer()
{
  set_model_actor
    (get_level_globals().get_model("model/"+ m_projectile_model + ".cm"));
  start_model_action("default");
} // projectile_enemy::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c string.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::projectile_enemy::set_string_field
( const std::string& name, const std::string& value )
{
  bool result = true;

  if ( name == "projectile_enemy.projectile_model" )
    m_projectile_model = value;
  else
    result = super::set_string_field(name, value);

  return result;
} // projectile_enemy::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the projectile model.
 */
void ptb::projectile_enemy::set_projectile_model(const std::string& value)
{
  m_projectile_model = value;
} // projectile_enemy::set_projectile_model()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::projectile_enemy::is_valid() const
{
  return (!m_projectile_model.empty() ) && super::is_valid();
} // projectile_enemy::is_valid()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::projectile_enemy::progress( bear::universe::time_type elapsed_time )
{
  if ( m_is_dead )
    {
      bear::decorative_item* item = new bear::decorative_item;

      /*
      bear::visual::animation anim( get_action("explosion").get_animation() );
      anim.set_loops(1);
      item->set_animation(anim);
      */

      item->set_bottom_left(get_bottom_left());
      item->get_rendering_attributes().set_angle(get_visual_angle());
      item->set_kill_when_finished(true);
      new_item( *item );

      CLAW_ASSERT( item->is_valid(),
                   "The explosion of sting isn't correctly initialized" );

      kill();
    }
  else if ( has_contact() )
    m_is_dead = true;
  else
    super::progress( elapsed_time );
} // projectile_enemy::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief The item has attacked.
 * \param other The monster that is attacked.
 */
void ptb::projectile_enemy::has_attacked(const monster& other)
{
  m_is_dead = true;
} // projectile_enemy::has_attacked()

/*---------------------------------------------------------------------------*/
/**
 * \brief Inform the item tat he left the active region.
 */
void ptb::projectile_enemy::leaves_active_region()
{
  super::leaves_active_region();

  kill();
} // projectile_enemy::leaves_active_region()
