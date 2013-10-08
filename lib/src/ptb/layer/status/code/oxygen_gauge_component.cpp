/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::oxygen_gauge_component class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/status/oxygen_gauge_component.hpp"

#include "ptb/player_signals.hpp"
#include "ptb/gauge.hpp"
#include <boost/bind.hpp>

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
ptb::oxygen_gauge_component::oxygen_gauge_component
( bear::engine::level_globals& glob, const player_proxy& p,
  const bear::visual::position_type& active_position,
  bear::universe::zone::position side,
  x_placement x_p, y_placement y_p,
  const bear::universe::size_box_type& layer_size,
  bool auto_disappear )
  : super(glob, p, active_position, side, x_p, y_p, 
	  "bar (blue)", "bubble", layer_size, auto_disappear )
{

} // oxygen_gauge_component::oxygen_gauge_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set all signals to listen.
 */
void ptb::oxygen_gauge_component::init_signals()
{
  add_signal
    ( get_player().get_signals().enters_water_zone.connect
      ( boost::bind
	(&ptb::gauge_component::on_enters_zone, this) ) );
  
  add_signal
    ( get_player().get_signals().leaves_water_zone.connect
      ( boost::bind
	(&ptb::gauge_component::on_leaves_zone, this) ) );

  add_signal
    ( get_player().get_signals().oxygen_gauge_changed.connect
      ( boost::bind
        (&ptb::oxygen_gauge_component::on_oxygen_gauge_changed, this,_1) ) );  
} // oxygen_gauge_component::init_signals()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when the the oxygen gauge changes.
 * \param level The level of the gauge.
 */
void ptb::oxygen_gauge_component::on_oxygen_gauge_changed(double level)
{
  if ( get_player() != NULL )
    get_gauge().set_level
      ( s_bar_length * level / 
	get_player().get_oxygen_gauge().get_max_value() );
} // oxygen_gauge_component::on_oxygen_gauge_changed()

