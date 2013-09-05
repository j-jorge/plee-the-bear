/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::accelerated_time_component class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/status/accelerated_time_component.hpp"

#include "engine/game.hpp"

#include "visual/scene_sprite.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param glob Level globals in which we take the resources.
 * \param p The player from which we take the data.
 * \param active_position the position in active state.
 * \param side Indicates the side on which the component appears.
 * \param x_p The placement on x-coordinate.
 * \param y_p The placement on y-coordinate.
 * \param layer_size The size of the layer in which the component is displayed.
 * \param auto_disappear Indicates that the component disappears automatically.
 */
ptb::accelerated_time_component::accelerated_time_component
( bear::engine::level_globals& glob, const player_proxy& p,
  const bear::visual::position_type& active_position, 
  bear::universe::zone::position side,
  x_placement x_p, y_placement y_p,
  const bear::universe::size_box_type& layer_size,
  bool auto_disappear )
  : super(glob, p, active_position, side, x_p, y_p, layer_size, auto_disappear)
{
} // accelerated_time_component::accelerated_time_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the component.
 */
void ptb::accelerated_time_component::build()
{
  m_accelerated_time =
    get_level_globals().auto_sprite
    ("gfx/ui/status/status.png", "fast forward");

  super::build();
} // accelerated_time_component::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players oxygen.
 * \param e (out) The scene elements.
 */
void ptb::accelerated_time_component::render( scene_element_list& e ) const
{
  if ( bear::engine::game::get_instance().get_time_scale() > 1 )
    e.push_back
      ( bear::visual::scene_sprite
	( get_render_position().x,get_render_position().y,
	  m_accelerated_time) );
} // accelerated_time_component::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int ptb::accelerated_time_component::width() const
{
  return m_accelerated_time.width();
} // accelerated_time_component::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int ptb::accelerated_time_component::height() const
{
  return m_accelerated_time.height();
} // accelerated_time_component::height()
