/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::score_component class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/status/score_component.hpp"

#include "ptb/player_signals.hpp"
#include "ptb/game_variables.hpp"

#include "engine/game.hpp"

#include "visual/bitmap_writing.hpp"
#include "visual/scene_writing.hpp"

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
 * \param auto_disappear Indicates that the component disappears automatically.
 */
ptb::score_component::score_component
( bear::engine::level_globals& glob, const player_proxy& p,
  const bear::visual::position_type& active_position, 
  bear::universe::zone::position side,
  x_placement x_p, y_placement y_p,
  const bear::universe::size_box_type& layer_size,
  bool auto_disappear )
  : super(glob,p,active_position,side, x_p, y_p, layer_size, auto_disappear),
    m_font(glob.get_font("font/Fava-black.ttf", 30))
{

} // score_component::score_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the component.
 */
void ptb::score_component::build()
{
  if ( get_player() != NULL )
    {
      std::ostringstream oss;
      oss << game_variables::get_score(get_player().get_index());
      m_score.create(m_font, oss.str());
      m_score->set_intensity(1, 0.8, 0);
    }

  super::build();
} // score_component::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players oxygen.
 * \param e (out) The scene elements.
 */
void ptb::score_component::render( scene_element_list& e ) const
{
  bear::visual::scene_writing s1
    ( get_render_position().x, get_render_position().y, m_score );
  e.push_back( s1 );
} // score_component::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int ptb::score_component::width() const
{
  return m_score.get_width();
} // score_component::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int ptb::score_component::height() const
{
  return m_score.get_height();
} // score_component::height()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set all signals to listen.
 */
void ptb::score_component::init_signals()
{
  add_signal
    ( bear::engine::game::get_instance().listen_uint_variable_change
      ( game_variables::get_score_variable_name(get_player().get_index()),
        boost::bind
        (&ptb::score_component::on_score_changed,
         this, boost::placeholders::_1) ) );
} // score_component::init_signals()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when score changes.
 * \param s The new score.
 */
void ptb::score_component::on_score_changed(unsigned int s)
{
  std::ostringstream oss;
  oss << s;
  m_score.create(m_font, oss.str());
  m_score->set_intensity(1, 0.8, 0);

  update_inactive_position();

  claw::tween::tweener_sequence tween;

  tween.insert
    ( claw::tween::single_tweener
      (get_position().x, get_active_position().x, 0.3,
       boost::bind
       ( &ptb::status_component::on_x_position_update,
         this, boost::placeholders::_1 ),
       &claw::tween::easing_back::ease_out ) );

  tween.insert
    ( claw::tween::single_tweener
      (get_active_position().x, get_active_position().x, 1,
       boost::bind
       ( &ptb::status_component::on_x_position_update,
	 this, boost::placeholders::_1 ), &claw::tween::easing_back::ease_in ) );
  
  tween.insert
    ( claw::tween::single_tweener
      (get_active_position().x, get_inactive_position().x, 0.5,
       boost::bind
       ( &ptb::status_component::on_x_position_update,
	 this, boost::placeholders::_1 ), &claw::tween::easing_back::ease_in ) );
  
  add_tweener( tween );
} // score_component::on_score_changed()
