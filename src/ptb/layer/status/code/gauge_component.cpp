/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::gauge_component class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/status/gauge_component.hpp"

#include "ptb/player_signals.hpp"
#include "ptb/gauge.hpp"

#include <boost/bind.hpp>
#include <claw/tween/tweener_sequence.hpp>
#include <claw/tween/easing/easing_elastic.hpp>
#include <claw/tween/easing/easing_linear.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param glob Level globals in which we take the resources.
 * \param p The player from which we take the data.
 * \param active_position the position in active state.
 * \param side Indicates the side on which the component appears.
 * \param x_p The placement on x-coordinate.
 * \param y_p The placement on y-coordinate.
 * \param level_sprite The name of the sprite in
 *        "gfx/ui/status/tube-vertical.png" of the image to use for the main
 *        level.
 * \param icon_sprite The name of the sprite in
 *        "gfx/ui/status/tube-vertical.png" of the image to use for the icon of
 *        the bar.
 * \param layer_size The size of the layer in which the component is displayed.
 */
ptb::gauge_component::gauge_component
( bear::engine::level_globals& glob, const player_proxy& p,
  const bear::visual::position_type& active_position, 
  bear::universe::zone::position side,
  x_placement x_p, y_placement y_p,
  const std::string& level_sprite, const std::string& icon_sprite,
  const bear::universe::size_box_type& layer_size )
  : super(glob, p, active_position, side, x_p, y_p, layer_size),
    m_gauge( glob, s_bar_length, level_sprite, icon_sprite )
{
} // gauge_component::gauge_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the players status and update local values.
 */
void ptb::gauge_component::progress
( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time ); 

  m_gauge.progress(elapsed_time);
} // gauge_component::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players oxygen.
 * \param e (out) The scene elements.
 */
void ptb::gauge_component::render( scene_element_list& e ) const
{
  m_gauge.render(e, get_render_position());
} // gauge_component::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int ptb::gauge_component::width() const
{
  return m_gauge.width();
} // gauge_component::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int ptb::gauge_component::height() const
{
  return m_gauge.height();
} // gauge_component::height()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when the player enters in the zone.*/
void ptb::gauge_component::on_enters_zone()
{
  add_tweener
    ( claw::tween::single_tweener
      (get_position().x, get_active_position().x, 1,
       boost::bind
       ( &ptb::gauge_component::on_x_position_update,
	 this, _1 ), &claw::tween::easing_elastic::ease_out ) );
} // gauge_component::on_enters_zone()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when the player leaves the zone.*/
void ptb::gauge_component::on_leaves_zone()
{
  claw::tween::tweener_sequence tween;

  tween.insert( claw::tween::single_tweener
      (get_position().x, get_position().x, 0.5,
       boost::bind
       ( &ptb::gauge_component::on_x_position_update,
	 this, _1 ), &claw::tween::easing_linear::ease_in_out ) );

  tween.insert( claw::tween::single_tweener
      (get_position().x, get_inactive_position().x, 1,
       boost::bind
       ( &ptb::gauge_component::on_x_position_update,
	 this, _1 ), &claw::tween::easing_linear::ease_in_out ) );

  add_tweener( tween );
} // gauge_component::on_leaves_zone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the gauge. 
 */
ptb::vertical_gauge& ptb::gauge_component::get_gauge()
{
  return m_gauge;
} // gauge_component::get_gauge()
