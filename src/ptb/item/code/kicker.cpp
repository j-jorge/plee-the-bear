/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::kicker class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/kicker.hpp"

#include "universe/collision_info.hpp"
#include "engine/layer/layer.hpp"
#include "engine/world.hpp"

#include "generic_items/decorative_item.hpp"

BASE_ITEM_EXPORT( kicker, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::kicker::kicker()
  : m_applied_force(0, 0), m_left_fixed(false), m_decorative_item(NULL),
    m_decorative_instances(0)
{

} // kicker::kicker()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "unsigned integer".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::kicker::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result = true;

  if ( name == "kicker.decorative_instances" )
    m_decorative_instances = value;
  else
    result = super::set_u_integer_field( name, value );

  return result;
} // kicker::set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "real".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::kicker::set_real_field( const std::string& name, double value )
{
  bool result = true;

  if ( name == "kicker.applied_force" )
    m_applied_force.y = value;
  else
    result = super::set_real_field( name, value );

  return result;
} // kicker::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "bool".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::kicker::set_bool_field( const std::string& name, bool value )
{
  bool result = true;

  if ( name == "kicker.left_fixed" )
    m_left_fixed = value;
  else
    result = super::set_bool_field( name, value );

  return result;
} // kicker::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "item".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::kicker::set_item_field
( const std::string& name, bear::engine::base_item* value )
{
  bool result = true;

  if ( (name == "kicker.decorative_item") && (value != NULL) )
    m_decorative_item = value;
  else
    result = super::set_item_field( name, value );

  return result;
} // kicker::set_item_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::kicker::build()
{
  if ( get_layer().has_world() )
    {
      m_applied_force.x =
        get_layer().get_world().to_world_unit( m_applied_force.x );
      m_applied_force.y =
        get_layer().get_world().to_world_unit( m_applied_force.y );
    }

  if ( m_decorative_item != NULL )
    {
      m_decorative_item->add_position_constraints();

      if ( m_decorative_instances == 0 )
        m_decorative_instances = 1;
    }
} // kicker::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the collision is on an active side and bounce the other item.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::kicker::collision_check_and_bounce
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  if ( info.get_collision_side() == bear::universe::zone::top_zone )
    {
      bear::universe::coordinate_type speed_y = that.get_speed().y;
      if ( default_collision(info) )
        {
          double rate = 0;

          if ( m_left_fixed )
            rate = (info.other_item().get_left() - get_left()) / get_width();
          else
            rate = (get_right() - info.other_item().get_right()) / get_width();

          if (rate < 0.1)
            rate = 0;

          bear::universe::force_type force = m_applied_force * rate;

          if ( force.y != 0 && ( speed_y < -600 ) )
            {
              that.add_external_force(force);
              that.set_bottom_contact(false);
              get_animation().reset();

              if ( m_decorative_item != NULL )
                {
                  m_decorative_item->remove_position_constraints();
                  --m_decorative_instances;

                  if( m_decorative_instances != 0 )
                    {
                      m_decorative_item = m_decorative_item->clone();
                      new_item(*m_decorative_item);
                      m_decorative_item->add_position_constraints();
                    }
                  else
                    m_decorative_item = NULL;
                }
            }
        }
    }
} // kicker::collision_check_and_bounce()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_bounce().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::kicker::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_and_bounce(that, info);
} // kicker::collision()
