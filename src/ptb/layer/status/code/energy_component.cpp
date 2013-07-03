/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::energy_component class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/status/energy_component.hpp"

#include "ptb/player_signals.hpp"
#include "ptb/gauge.hpp"
#include "ptb/game_variables.hpp"

#include "engine/game.hpp"

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
 * \param layer_size The size of the layer in which the component is displayed.
 */
ptb::energy_component::energy_component
( bear::engine::level_globals& glob, const player_proxy& p,
  const bear::visual::position_type& active_position, 
  bear::universe::zone::position side,
  x_placement x_p, y_placement y_p,
  const bear::universe::size_box_type& layer_size )
  : super(glob,p,active_position,side, x_p, y_p, layer_size),
    m_energy( glob, s_bar_length, "bar (green)", "bar (red)", "heart", true )
{
} // energy_component::energy_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the component.
 */
void ptb::energy_component::build()
{
  super::build();

  if ( get_player() != NULL )
    {
      if ( get_player().get_index() == 2 )
	m_energy.set_level_sprite( get_level_globals(), "bar (light blue)" );
      
      m_energy.set_length
	(game_variables::get_max_energy(get_player().get_index()));
      m_energy.set_max_level
	(game_variables::get_max_energy(get_player().get_index()));
      m_energy.set_level(get_player().get_energy());
    }
} // energy_component::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the players status and update local values.
 */
void ptb::energy_component::progress
( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time ); 

  m_energy.progress(elapsed_time);
} // energy_component::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players oxygen.
 * \param e (out) The scene elements.
 */
void ptb::energy_component::render( scene_element_list& e ) const
{
  m_energy.render(e, get_render_position());
} // energy_component::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int ptb::energy_component::width() const
{
  return m_energy.width();
} // energy_component::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int ptb::energy_component::height() const
{
  return m_energy.height();
} // energy_component::height()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set all signals to listen.
 */
void ptb::energy_component::init_signals()
{
  add_signal
    ( get_player().get_signals().energy_added.connect
      ( boost::bind
        (&ptb::energy_component::on_energy_added, this, _1) ) );
  
  add_signal
    ( get_player().get_signals().energy_removed.connect
      ( boost::bind
        (&ptb::energy_component::on_energy_removed, this, _1) ) );

  add_signal
    ( bear::engine::game::get_instance().listen_double_variable_change
      ( game_variables::get_max_energy_variable_name(get_player().get_index()),
        boost::bind
        (&ptb::energy_component::on_max_energy_added,
         this, _1) ) );
} // energy_component::init_signals()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when some energy is added or removed.
 */
void ptb::energy_component::on_energy_changed()
{
  claw::tween::tweener_sequence tween;

  tween.insert
    ( claw::tween::single_tweener
      (get_position().y, get_active_position().y, 0.3,
       boost::bind
       ( &ptb::status_component::on_y_position_update,
         this, _1 ), &claw::tween::easing_back::ease_out ) );

  if ( ! m_energy.is_critical() )
    {
      tween.insert
	( claw::tween::single_tweener
	  (get_active_position().y, get_active_position().y, 1,
	   boost::bind
	   ( &ptb::status_component::on_y_position_update,
	     this, _1 ), &claw::tween::easing_back::ease_in ) );
      
      tween.insert
	( claw::tween::single_tweener
	  (get_active_position().y, get_inactive_position().y, 0.5,
	   boost::bind
	   ( &ptb::status_component::on_y_position_update,
	     this, _1 ), &claw::tween::easing_back::ease_in ) );
    }

  add_tweener( tween );
} // energy_component::on_energy_changed()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when some energy is added.
 * \param e The new level of energy.
 */
void ptb::energy_component::on_energy_added(double e)
{
  m_energy.set_level( e );
  on_energy_changed();
} // energy_component::on_energy_added()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when some energy is removed.
 * \param e The new level of energy.
 */
void ptb::energy_component::on_energy_removed(double e)
{
  m_energy.set_level( e );
  on_energy_changed();
} // energy_component::on_energy_removed()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when the maximum energy increases.
 * \param e The new maximum of energy.
 */
void ptb::energy_component::on_max_energy_added(double e)
{
  on_energy_changed();
  add_tweener
    ( claw::tween::single_tweener
      (m_energy.length(), e, 1,
       boost::bind
       ( &ptb::energy_component::on_max_energy_length_update,
         this, _1 ), &claw::tween::easing_elastic::ease_out ) );
} // energy_component::on_max_energy_added()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when the length of max energy length changes.
 * \param length The new length of max energy bar.
 */
void ptb::energy_component::on_max_energy_length_update
(double length)
{
  if ( get_player() != NULL )
    {
      m_energy.set_length(length);
      m_energy.set_max_level(length);
      m_energy.set_level(length);
    }
} // energy_component::on_max_energy_length_update
