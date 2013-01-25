/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::boss_component class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/status/boss_component.hpp"

#include "ptb/item_brick/monster.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param glob Level globals in which we take the resources.
 * \param p The player from which we take the data.
 * \param active_position the position in active state.
 * \param side Indicates the side on which the component appears.
 * \param x_p The placement on x-coordinate.
 * \param y_p The placement on y-coordinate.
 * \param m The boss.
 * \param layer_size The size of the layer in which the component is displayed.
 */
ptb::boss_component::boss_component
( bear::engine::level_globals& glob, const player_proxy& p,
  const bear::visual::position_type& active_position, 
  bear::universe::zone::position side, x_placement x_p, 
  y_placement y_p, const monster_handle& m, 
  const bear::universe::size_box_type& layer_size )
  : super(glob, p, active_position, side, x_p, y_p, layer_size), m_boss(m),
    m_boss_energy(glob,m_boss->get_max_energy(),"bar (god yellow)")
{
} // boss_component::boss_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do an iteration.
 */
void ptb::boss_component::progress
( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time ); 

  m_boss_energy.set_length
    ( std::min(m_boss->get_max_energy(), get_layer_size().x*0.9 ) );
  m_boss_energy.set_max_level( m_boss->get_max_energy() );
  m_boss_energy.set_level( m_boss->get_energy() );
  on_x_position_update(get_position().x);
  on_y_position_update(get_position().y);

  m_boss_energy.progress( elapsed_time );
} // boss_component::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players oxygen.
 * \param e (out) The scene elements.
 */
void ptb::boss_component::render( scene_element_list& e ) const
{
  if (m_boss_energy.get_level() != 0)
    m_boss_energy.render( e, get_render_position() );
} // boss_component::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int ptb::boss_component::width() const
{
  return m_boss_energy.width();
} // boss_component::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int ptb::boss_component::height() const
{
  return m_boss_energy.height();
} // boss_component::height()

