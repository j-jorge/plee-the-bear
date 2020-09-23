/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::invincibility_effect class.
 * \author Julien Jorge
 */
#include "ptb/item/invincibility_effect.hpp"

#include "generic_items/star.hpp"
#include "generic_items/tweener_item.hpp"

#include "universe/forced_movement/forced_tracking.hpp"

#include <boost/bind.hpp>
#include <claw/tween/easing/easing_linear.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param p The player for which the effect is created.
 */
ptb::invincibility_effect::invincibility_effect( player_proxy p )
  : m_player(p), m_music_id(0)
{
  
} // invincibility_effect::invincibility_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::invincibility_effect::build()
{
  super::build();
  m_music_id = get_level_globals().play_music("music/invincibility.ogg", 1);
} // invincibility_effect::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a star over the player.
 */
void ptb::invincibility_effect::create_star()
{
  bear::star* s =
    new bear::star
    ( 5, 0.5, bear::visual::color(145, 145, 145), 1,
      bear::visual::color(200, 200, 20) );

  const unsigned int width = 10 + 20 * (double)rand() / RAND_MAX;

  s->set_size(width, width);
  s->set_z_position( m_player.get_z_position() + 1 );
  s->set_system_angle( rand() );
  s->set_system_angle_as_visual_angle(true);
  s->set_center_of_mass
    ( m_player.get_left() + m_player.get_width() * (double)rand() / RAND_MAX,
      m_player.get_bottom()
      + m_player.get_height() * (double)rand() / RAND_MAX );

  new_item(*s);

  bear::universe::forced_tracking m;
  m.set_reference_point_on_center(*this);
  s->set_forced_movement(m);
  
  const claw::tween::single_tweener tweener
    ( 1, 0, 0.4,
      boost::bind
      ( &bear::visual::bitmap_rendering_attributes::set_opacity,
        &(s->get_rendering_attributes()), boost::placeholders::_1 ),
      &claw::tween::easing_linear::ease_in );

  bear::tweener_item* t = new bear::tweener_item(tweener, s, true);
  new_item( *t );
} // invincibility_effect::create_star()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a remanent trace of the player.
 */
void ptb::invincibility_effect::create_remanent_traces() const
{

} // invincibility_effect::create_remanent_traces()
