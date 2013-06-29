/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::air_bubble class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/air_bubble.hpp"

#include "ptb/player_proxy.hpp"
#include "engine/level_globals.hpp"

#include "universe/forced_movement/forced_translation.hpp"
#include "universe/physical_item_state.hpp"
#include "universe/world.hpp"

BASE_ITEM_EXPORT( air_bubble, ptb )

const bear::universe::size_type ptb::air_bubble::s_min_size = 16;
const bear::universe::size_type ptb::air_bubble::s_max_size = 32;
const double ptb::air_bubble::s_oxygen_in_max_size = 2000;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::air_bubble::air_bubble()
  : m_oxygen(0)
{
  set_size(8, 8);
  m_max_size = s_max_size;
  set_can_move_items(false);
  set_mass(30);
  set_density(0.8);
} // air_bubble::air_bubble()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::air_bubble::progress( bear::universe::time_type elapsed_time )
{
  if ( has_contact() )
    kill();
  else
    {
      update_size(elapsed_time);

      if ( !is_only_in_environment(bear::universe::water_environment) )
        kill();
      else
        {
          double f = (double)(get_mass() * 2000.0 * rand() / RAND_MAX) -
            get_mass() * 1000;
          add_internal_force(bear::universe::force_type(f, 0));
        }

    }
} // air_bubble::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the sprite representing the item.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void ptb::air_bubble::get_visual
( std::list<bear::engine::scene_visual>& visuals ) const
{
  visuals.push_front
    ( bear::engine::scene_visual
      ( get_bottom_left(), m_sprite, get_z_position() ) );
} // air_bubble::get_visual()

/*----------------------------------------------------------------------------*/
/**
 * \brief Pre-cache the datas used by the item.
 */
void ptb::air_bubble::pre_cache()
{
  get_level_globals().load_image("gfx/bubble.png");
} // air_bubble::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::air_bubble::build()
{
  super::build();

  m_sprite = get_level_globals().auto_sprite("gfx/bubble.png", "bubble");

  if ( m_oxygen < 0 )
    m_sprite.set_intensity(0.8, 0.9, 0.4);
  else
    m_sprite.set_intensity(1, 1, 1);

  m_sprite.set_size( get_size() );
} // air_bubble::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::air_bubble::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  if ( get_width() >= (unsigned int)s_min_size )
    {
      player_proxy other(&that);

      if (other != NULL)
        {
          bear::engine::model_mark_placement m;

          if ( other.get_mark_placement("mouth", m) )
            if ( get_bounding_box().includes( m.get_position()) )
              {
                other.receive_oxygen(m_oxygen);
                m_oxygen = 0;
                kill();
              }
        }
    }
} // air_bubble::collision()

/*---------------------------------------------------------------------------*/
/**
 * \brief Set the oxygen value.
 * \param oxygen The new oxygen value.
 */
void ptb::air_bubble::set_oxygen( double oxygen )
{
  m_oxygen = oxygen;

  if ( m_oxygen == 0 )
    {
      // a decorative bubble;
      m_max_size = s_min_size / 2;
      set_density(0.85);
    }
  else
    {
      if ( std::abs(m_oxygen) >= s_oxygen_in_max_size )
        m_max_size = s_max_size;
      else
        m_max_size = s_min_size +
          std::abs(m_oxygen) *
          ( s_max_size - s_min_size) / s_oxygen_in_max_size;
    }
} // air_bubble::set_oxygen()

/*---------------------------------------------------------------------------*/
/**
 * \brief Set the size with the maximum size.
 */
void ptb::air_bubble::give_max_size()
{
  set_width(m_max_size);
  set_height(m_max_size);
} // air_bubble::give_max_size()

/*---------------------------------------------------------------------------*/
/**
 * \brief Inform the item that he left the active region.
 */
void ptb::air_bubble::leaves_active_region()
{
  super::leaves_active_region();

  kill();
} // ptb::air_bubble::leaves_active_region()

/*---------------------------------------------------------------------------*/
/**
 * \brief Update the size of the bubble according to its oxygen.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::air_bubble::update_size( bear::universe::time_type elapsed_time )
{
  if ( get_width() < m_max_size )
    {
      const bear::universe::position_type center( get_center_of_mass() );
      set_width( get_width() + 13 * elapsed_time );
      set_height(get_height() + 13 * elapsed_time );
      set_density
        ( 0.9 - 0.3 * (get_width() - s_min_size) / (s_max_size - s_min_size) );
      set_center_of_mass(center);
    }

  m_sprite.set_size( get_size() );
} // air_bubble::update_size()
