/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::lives_component class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/status/lives_component.hpp"

#include "ptb/player_signals.hpp"
#include "ptb/game_variables.hpp"

#include "engine/game.hpp"

#include "visual/scene_sprite.hpp"
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
 */
ptb::lives_component::lives_component
( bear::engine::level_globals& glob, const player_proxy& p,
  const bear::visual::position_type& active_position, 
  bear::universe::zone::position side,
  x_placement x_p, y_placement y_p,
  const bear::universe::size_box_type& layer_size )
  : super(glob,p,active_position,side, x_p, y_p, layer_size),
    m_font(glob.get_font("font/bouncy.fnt", 30)), m_lives_scale(1) 
{

} // lives_component::lives_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the component.
 */
void ptb::lives_component::build()
{
  if ( get_player() != NULL )
    {
      std::ostringstream oss;
      oss << game_variables::get_lives_count(get_player().get_index());
      m_lives.create(m_font, oss.str());
      m_lives->set_intensity(1, 0.8, 0);
    }
  
  m_small_player =
    bear::visual::sprite
    ( get_level_globals().auto_sprite("gfx/ui/status/status.png", "plee"));

  super::build();
} // lives_component::build()
      
/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players oxygen.
 * \param e (out) The scene elements.
 */
void ptb::lives_component::render( scene_element_list& e ) const
{
  bear::visual::scene_sprite s1
    ( get_render_position().x, get_render_position().y, m_small_player);

  bear::visual::scene_writing s2
    ( get_render_position().x + m_small_player.width() + s_margin, 
      get_render_position().y, m_lives );

  e.push_back( s1 );
  e.push_back( s2 );
} // lives_component::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int ptb::lives_component::width() const
{
  return m_lives.get_width() + s_margin + m_small_player.width();
} // lives_component::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int ptb::lives_component::height() const
{
  return std::max( m_lives.get_height(), m_small_player.height());
} // lives_component::height()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set all signals to listen.
 */
void ptb::lives_component::init_signals()
{  
  add_signal
    ( bear::engine::game::get_instance().listen_uint_variable_change
      ( game_variables::get_lives_count_variable_name
	(get_player().get_index()),
        boost::bind
        (&ptb::lives_component::on_lives_changed,this, _1) ) );
} // lives_component::init_signals()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when the scale of lives writing changes.
 * \param scale The new scale.
 */
void ptb::lives_component::on_lives_scale_update
(double scale)
{
  m_lives_scale = scale;

  double red(1/m_lives_scale);
  double green(red-0.5);
  green = green * 8 / 5;
  m_lives->set_intensity(red, green, 0);
} // lives_component::on_lives_scale_update()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when lives count changes.
 * \param s The new lives count.
 */
void ptb::lives_component::on_lives_changed(unsigned int s)
{
  std::ostringstream oss;
  oss << s;
  m_lives.create(m_font, oss.str());
  m_lives->set_intensity(1, 0.8, 0);

  update_inactive_position();

  claw::tween::tweener_sequence tween;
  tween.insert
    ( claw::tween::single_tweener
      (1, 1, 0.5,
       boost::bind
       ( &ptb::lives_component::on_lives_scale_update,
         this, _1 ), &claw::tween::easing_back::ease_out ) );
  tween.insert
    ( claw::tween::single_tweener
      (1, 1.5, 0.5,
       boost::bind
       ( &ptb::lives_component::on_lives_scale_update,
         this, _1 ), &claw::tween::easing_back::ease_out ) );
  tween.insert
    ( claw::tween::single_tweener
      (1.5, 1, 0.5,
       boost::bind
       ( &ptb::lives_component::on_lives_scale_update,
         this, _1 ), &claw::tween::easing_back::ease_in ) );

  add_tweener( tween );

  claw::tween::tweener_sequence tween2;

  tween2.insert
    ( claw::tween::single_tweener
      (get_position().x, get_active_position().x, 0.3,
       boost::bind
       ( &ptb::status_component::on_x_position_update,
         this, _1 ), &claw::tween::easing_back::ease_out ) );

  tween2.insert
    ( claw::tween::single_tweener
      (get_active_position().x, get_active_position().x, 2,
       boost::bind
       ( &ptb::status_component::on_x_position_update,
	 this, _1 ), &claw::tween::easing_back::ease_in ) );
  
  tween2.insert
    ( claw::tween::single_tweener
      (get_active_position().x, get_inactive_position().x, 0.5,
       boost::bind
       ( &ptb::status_component::on_x_position_update,
	 this, _1 ), &claw::tween::easing_back::ease_in ) );
  
  add_tweener( tween2 );
} // lives_component::on_lives_changed()
