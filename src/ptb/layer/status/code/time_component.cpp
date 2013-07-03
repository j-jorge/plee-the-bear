/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::time_component class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/status/time_component.hpp"

#include "ptb/player_signals.hpp"
#include "ptb/game_variables.hpp"

#include "engine/game.hpp"

#include "visual/bitmap_writing.hpp"
#include "visual/scene_writing.hpp"

#include <libintl.h>
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
 * \param t The timer to use.
 * \param layer_size The size of the layer in which the component is displayed.
 */
ptb::time_component::time_component
( bear::engine::level_globals& glob, const player_proxy& p,
  const bear::visual::position_type& active_position, 
  bear::universe::zone::position side,
  x_placement x_p, y_placement y_p, const timer_handle& t,
  const bear::universe::size_box_type& layer_size )
  : super(glob,p,active_position,side, x_p, y_p, layer_size),
    m_font(glob.get_font("font/bouncy.fnt", 30)),
    m_time_on(true), m_timer(t)
{
} // time_component::time_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the component.
 */
void ptb::time_component::build()
{
  m_text_time.create(m_font, "00:00");
  
  super::build();
} // time_component::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the players status and update local values.
 */
void ptb::time_component::progress
( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time ); 

  if ( m_timer != (bear::timer*)NULL )
    {
      m_time_on = true;

      const bear::universe::time_type time = m_timer->get_time();
      const std::string t
        ( bear::systime::format_time_s( time,  gettext("%M:%S") ) );

      if ( m_timer->is_countdown() && (time <= 30) &&
           ((time - (int)time) < 0.5) )
        m_text_time->set_intensity(1, 0, 0);
      else
        m_text_time->set_intensity(1, 0.8, 0);

      m_text_time.create
        ( get_level_globals().get_font("font/bouncy.fnt", 30), t );
    }
  else
    m_time_on = false;
}// time_component::progress

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players oxygen.
 * \param e (out) The scene elements.
 */
void ptb::time_component::render( scene_element_list& e ) const
{
  if ( m_time_on )
    e.push_back
      ( bear::visual::scene_writing
	(get_render_position().x,
	 get_render_position().y, m_text_time));
} // time_component::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int ptb::time_component::width() const
{
  return m_text_time.get_width();
} // time_component::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int ptb::time_component::height() const
{
  return m_text_time.get_height();
} // time_component::height()
