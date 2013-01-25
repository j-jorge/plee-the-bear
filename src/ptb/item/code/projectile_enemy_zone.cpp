/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::projectile_enemy_zone class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/projectile_enemy_zone.hpp"

#include "engine/game.hpp"
#include "ptb/item/projectile_enemy.hpp"

#include "engine/export.hpp"

BASE_ITEM_EXPORT( projectile_enemy_zone, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::projectile_enemy_zone::projectile_enemy_zone()
  : m_projectile_model(""), m_projectile_number(0), m_is_finished(false)
{
  set_can_move_items(false);
} // projectile_enemy_zone::projectile_enemy_zone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 */
void
ptb::projectile_enemy_zone::progress( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);

  if ( !m_is_finished )
    m_animation.next(elapsed_time);
} // projectile_enemy_zone::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c string.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::projectile_enemy_zone::set_string_field
( const std::string& name, const std::string& value )
{
  bool result = true;

  if ( name == "projectile_enemy_zone.projectile_model" )
    m_projectile_model = value;
  else
    result = super::set_string_field(name, value);

  return result;
} // projectile_enemy_zone::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c unsigned int.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::projectile_enemy_zone::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result = true;

  if ( name == "projectile_enemy_zone.projectile_number" )
    m_projectile_number = value;
  else
    result = super::set_u_integer_field(name, value);

  return result;
} // projectile_enemy_zone::set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "animation".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::projectile_enemy_zone::set_animation_field
( const std::string& name, const bear::visual::animation& value )
{
  bool result = true;

  if ( name == "projectile_enemy_zone.animation" )
    m_animation = value;
  else
    result = super::set_animation_field( name, value );

  return result;
} // projectile_enemy_zone::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::projectile_enemy_zone::is_valid() const
{
  return m_animation.is_valid() && !m_projectile_model.empty()
    && super::is_valid();
} // projectile_enemy_zone::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the sprite representing the item.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void
ptb::projectile_enemy_zone::get_visual
( std::list<bear::engine::scene_visual>& visuals ) const
{
  if ( !m_is_finished )
    {
      bear::visual::sprite spr( m_animation.get_sprite() );
      spr.set_angle( spr.get_angle() + get_visual_angle() );

      visuals.push_front
        ( bear::engine::scene_visual
          ( get_top_middle() + get_gap(), spr, get_z_position() ) );
    }
} // projectile_enemy_zone::get_visual()

/*----------------------------------------------------------------------------*/
/**
 * \brief Collision of this item.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::projectile_enemy_zone::collision_check_monster
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  if ( !m_is_finished && m_animation.is_finished() )
    {
      monster* p = dynamic_cast<ptb::monster*>(&that);

      if ( p )
        if ( ( p->get_monster_type() == monster::player_monster ) ||
             ( p->get_monster_type() == monster::stone_monster ) ||
             ( p->get_monster_type() == monster::enemy_monster ) )
          create_projectile();
    }
} // projectile_enemy_zone::collision_check_monster()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a projectile.
 */
void ptb::projectile_enemy_zone::create_projectile()
{
  if ( m_projectile_number != 0 )
    {
      --m_projectile_number;

      if ( m_projectile_number == 0)
        m_is_finished = true;
    }

  projectile_enemy* new_projectile = new projectile_enemy;

  new_projectile->set_top_middle(get_top_middle());
  new_projectile->set_z_position( get_z_position() - 1 );
  new_projectile->set_projectile_model(m_projectile_model);
  new_projectile->get_rendering_attributes().set_angle
    (get_rendering_attributes().get_angle());
  CLAW_ASSERT(new_projectile->is_valid(),
              "The projectile isn't correctly initialized" );

  new_item( *new_projectile );
  m_animation.reset();
} // projectile_enemy_zone::create_projectile()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_monster().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::projectile_enemy_zone::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_monster(that, info);
} // projectile_enemy_zone::collision()
