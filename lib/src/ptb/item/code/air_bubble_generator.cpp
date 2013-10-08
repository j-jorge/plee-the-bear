/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::air_bubble_generator class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/air_bubble_generator.hpp"
#include "engine/export.hpp"

#include "universe/forced_movement/forced_translation.hpp"
#include "universe/physical_item_state.hpp"
#include "universe/world.hpp"
#include "ptb/player_proxy.hpp"
#include "ptb/item/air_bubble.hpp"

BASE_ITEM_EXPORT( air_bubble_generator, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::air_bubble_generator::air_bubble_generator()
  : m_last_bubble(0), m_last_decorative_bubble(0),
    m_index_oxygen(0), m_index_duration(0),
    m_index_decorative_duration(0), m_activated(true)
{
  set_can_move_items(false);
  m_duration_decorative_sequence.clear();
} // air_bubble_generator::air_bubble_generator()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::air_bubble_generator::progress
( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);

  if ( m_activated )
    {
      m_last_bubble += elapsed_time;
      if ( m_last_bubble >= m_duration_sequence[m_index_duration] )
        create_bubble();

      if (  m_duration_decorative_sequence.size() != 0 )
        {
          m_last_decorative_bubble += elapsed_time;
          if ( m_last_decorative_bubble >=
               m_duration_decorative_sequence[m_index_decorative_duration] )
            create_decorative_bubble();
        }
    }
  else
    m_activated = true;
} // air_bubble_generator::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::air_bubble_generator::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy other(&that);

  if (other != NULL)
    m_activated = false;
} // air_bubble_generator::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c list of real.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool
ptb::air_bubble_generator::set_real_list_field
( const std::string& name, const std::vector<double>& value )
{
   bool ok = true;

  if (name == "air_bubble_generator.oxygen_sequence")
    m_oxygen_sequence = value;
  else if (name == "air_bubble_generator.duration_sequence")
    m_duration_sequence = value;
  else if (name == "air_bubble_generator.duration_decorative_sequence")
    m_duration_decorative_sequence = value;
  else
    ok = super::set_real_list_field(name, value);

  return ok;
} // air_bubble_generator::set_real_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::air_bubble_generator::is_valid() const
{
  return ( m_oxygen_sequence.size() != 0) &&
    ( m_duration_sequence.size() != 0) && super::is_valid();
} // air_bubble_generator::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a bubble.
 */
void ptb::air_bubble_generator::create_bubble()
{
  air_bubble* new_bubble;

  new_bubble= new air_bubble();
  new_bubble->set_bottom_middle(get_center_of_mass());
  new_bubble->set_oxygen(m_oxygen_sequence[m_index_oxygen]);
  new_bubble->set_z_position(get_z_position() + 1);
  new_item( *new_bubble );

  m_index_duration = ( m_index_duration + 1 ) % m_duration_sequence.size();
  m_index_oxygen = ( m_index_oxygen + 1 ) % m_oxygen_sequence.size();
  m_last_bubble = 0;

  if ( m_oxygen_sequence[m_index_oxygen] < 0 )
    get_animation().set_intensity(0.8, 0.9, 0.4);
  else
    get_animation().set_intensity(1, 1, 1);
} // air_bubble_generator::create_bubble()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a decorative bubble.
 */
void ptb::air_bubble_generator::create_decorative_bubble()
{
  air_bubble* new_bubble;

  new_bubble= new air_bubble();
  bear::universe::position_type pos = get_bottom_left();

  double a = (double)(get_width() * rand() / RAND_MAX);
  pos.x += a;

  new_bubble->set_bottom_middle(pos);
  new_bubble->set_oxygen(0);
  new_bubble->set_z_position(get_z_position() + 1);
  new_item( *new_bubble );

  m_index_decorative_duration = ( m_index_decorative_duration + 1 ) %
    m_duration_decorative_sequence.size();
  m_last_decorative_bubble = 0;
} // air_bubble_generator::create_bubble()
