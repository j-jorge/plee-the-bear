/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::honeypots_component class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/status/honeypots_component.hpp"

#include "ptb/level_variables.hpp"

#include "visual/scene_sprite.hpp"

#include <boost/bind.hpp>
#include <claw/tween/tweener_sequence.hpp>
#include <claw/tween/easing/easing_elastic.hpp>
#include <claw/tween/easing/easing_back.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param glob Level globals in which we take the resources.
 * \param p The player from which we take the data.
 * \param active_position the position in active state.
 * \param side Indicates the side on which the component appears.
 * \param x_p The placement on x-coordinate.
 * \param y_p The placement on y-coordinate.
 * \param lvl The level containing the honey pots.
 * \param layer_size The size of the layer in which the component is displayed.
 */
ptb::honeypots_component::honeypots_component
( bear::engine::level_globals& glob, const player_proxy& p,
  const bear::visual::position_type& active_position, 
  bear::universe::zone::position side,
  x_placement x_p, y_placement y_p,
  const bear::engine::level& lvl,
  const bear::universe::size_box_type& layer_size)
  : super(glob,p,active_position,side, x_p, y_p, layer_size), m_level(lvl)
{
} // honeypots_component::honeypots_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the component.
 */
void ptb::honeypots_component::build()
{
  m_honeypot = 
    get_level_globals().auto_sprite("gfx/ui/status/status.png", "shiny jar");
   
  super::build();
} // honeypots_component::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do an iteration.
 */
void ptb::honeypots_component::progress
( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time ); 
  
  unsigned int nb = level_variables::get_honeypots_found(m_level);
 
  if ( m_last_count != nb )
    on_count_change();

  m_last_count = nb;
} // honeypots_component::progress

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players oxygen.
 * \param e (out) The scene elements.
 */
void ptb::honeypots_component::render( scene_element_list& e ) const
{
  for ( unsigned int i = 0; i != m_last_count; ++i )
    e.push_back
      ( bear::visual::scene_sprite
	( get_render_position().x + i * (s_margin + m_honeypot.width()), 
	  get_render_position().y, m_honeypot) );
} // honeypots_component::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int ptb::honeypots_component::width() const
{
  unsigned int nb = level_variables::get_honeypots_found(m_level);
  
  if ( nb > 0 )
    return nb * m_honeypot.width() + (nb-1)*s_margin;
  else
    return 0;
} // honeypots_component::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int ptb::honeypots_component::height() const
{
  return m_honeypot.height();
} // honeypots_component::height()

/*----------------------------------------------------------------------------*/
/**
 * \brief Function called when the count change.
 */
void ptb::honeypots_component::on_count_change()
{
  claw::tween::tweener_sequence tween;

  tween.insert
    ( claw::tween::single_tweener
      (get_position().y, get_active_position().y, 0.5,
       boost::bind
       ( &ptb::status_component::on_y_position_update,
         this, _1 ), &claw::tween::easing_back::ease_out ) );

  tween.insert
    ( claw::tween::single_tweener
      (get_active_position().y, get_active_position().y, 2,
       boost::bind
       ( &ptb::status_component::on_y_position_update,
	 this, _1 ), &claw::tween::easing_back::ease_in ) );
  
  tween.insert
    ( claw::tween::single_tweener
      (get_active_position().y, get_inactive_position().y, 0.5,
       boost::bind
       ( &ptb::status_component::on_y_position_update,
	 this, _1 ), &claw::tween::easing_back::ease_in ) );
  
  add_tweener( tween );
} // honeypots_component::on_count_change()
