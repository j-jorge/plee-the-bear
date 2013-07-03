/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::hazelnut_component class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/status/hazelnut_component.hpp"

#include "ptb/level_variables.hpp"

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
 * \param lvl The level containing the hazelnut.
 * \param layer_size The size of the layer in which the component is displayed.
 */
ptb::hazelnut_component::hazelnut_component
( bear::engine::level_globals& glob, const player_proxy& p,
  const bear::visual::position_type& active_position, 
  bear::universe::zone::position side,
  x_placement x_p, y_placement y_p,
  const bear::engine::level& lvl,
  const bear::universe::size_box_type& layer_size )
  : super(glob, p,active_position, side, x_p, y_p, layer_size), m_level(lvl)
{

} // hazelnut_component::hazelnut_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the component.
 */
void ptb::hazelnut_component::build()
{
  m_hazelnut = 
    get_level_globals().get_animation("animation/owl/hazelnut.canim");

  super::build();
} // hazelnut_component::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players oxygen.
 * \param e (out) The scene elements.
 */
void ptb::hazelnut_component::render( scene_element_list& e ) const
{
  if ( level_variables::get_current_hazelnut(m_level) )
    {
      e.push_back
        ( bear::visual::scene_sprite
	  ( get_render_position().x, get_render_position().y,
	    m_hazelnut.get_sprite() ) );
    }
} // hazelnut_component::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int ptb::hazelnut_component::width() const
{
  return m_hazelnut.get_max_size().x;
} // hazelnut_component::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int ptb::hazelnut_component::height() const
{
  return m_hazelnut.get_max_size().x;
} // hazelnut_component::height()
