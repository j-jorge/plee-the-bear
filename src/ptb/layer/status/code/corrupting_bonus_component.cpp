/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::corrupting_bonus_component class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/status/corrupting_bonus_component.hpp"

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
 * \param layer_size The size of the layer.
 * \param layer_size The size of the layer in which the component is displayed.
 */
ptb::corrupting_bonus_component::corrupting_bonus_component
( bear::engine::level_globals& glob, const player_proxy& p,
  const bear::visual::position_type& active_position, 
  bear::universe::zone::position side,
  x_placement x_p, y_placement y_p,
  const bear::universe::size_box_type& layer_size )
  : super(glob,p,active_position,side, x_p, y_p, layer_size),
    m_font(glob.get_font("font/bouncy.fnt", 30)),
    m_corrupting_bonus_scale(1)
{
} // corrupting_bonus_component::corrupting_bonus_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the component.
 */
void ptb::corrupting_bonus_component::build()
{
  std::ostringstream oss;
  oss << game_variables::get_corrupting_bonus_count();
  m_text_corrupting_bonus.create(m_font, oss.str());
  m_text_corrupting_bonus->set_intensity(1, 0.8, 0);
  m_last_corrupting_bonus_count = game_variables::get_corrupting_bonus_count();

  m_corrupting_bonus =
    get_level_globals().get_animation("animation/corrupting-bonus.canim");
  m_corrupting_bonus.set_size( m_corrupting_bonus.get_size() / 2 );

  super::build();
} // corrupting_bonus_component::build()
      
/*----------------------------------------------------------------------------*/
/**
 * \brief Do an iteration.
 */
void ptb::corrupting_bonus_component::progress
( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time ); 
  
  m_corrupting_bonus.next(elapsed_time);

  floating_corrupting_bonus_list::iterator it =
    m_floating_corrupting_bonus.begin();

  while ( it != m_floating_corrupting_bonus.end() )
    {
      it->progress(elapsed_time);

      if ( it->is_finished() )
	{
          floating_corrupting_bonus_list::iterator tmp(it);
          ++it;
          m_floating_corrupting_bonus.erase(tmp);

	  on_corrupting_bonus_added();
	}
      else
        ++it;
    }
} // corrupting_bonus_component::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players oxygen.
 * \param e (out) The scene elements.
 */
void ptb::corrupting_bonus_component::render( scene_element_list& e ) const
{
  if ( m_corrupting_bonus.empty() )
    return;

  bear::universe::position_type pos(get_render_position());
  bear::visual::scene_sprite sp( 0, 0, m_corrupting_bonus.get_sprite() );

  //sp.set_scale_factor(m_corrupting_bonus_scale, m_corrupting_bonus_scale);
  sp.set_position
    ( pos.x + (m_corrupting_bonus.width() - sp.get_bounding_box().width()) / 2,
      pos.y + (height() - sp.get_bounding_box().height()) / 2 );
  e.push_back( sp );

  pos.x += m_corrupting_bonus.width() + s_margin;

  bear::visual::scene_writing s( 0, 0, m_text_corrupting_bonus );
  //s.set_scale_factor(m_corrupting_bonus_scale, m_corrupting_bonus_scale);
  s.set_position
    ( pos.x
      + ( m_text_corrupting_bonus.get_width()
          - s.get_bounding_box().width() ) / 2,
      pos.y + (height() - s.get_bounding_box().height()) / 2 );

  e.push_back( s );
  
  floating_corrupting_bonus_list::const_iterator it;
  for ( it = m_floating_corrupting_bonus.begin(); 
	it != m_floating_corrupting_bonus.end(); ++it )
    {
      bear::visual::scene_sprite sp2
	( it->get_position().x, it->get_position().y, 
	  m_corrupting_bonus.get_sprite() );
      e.push_back( sp2 );
    } 
} // corrupting_bonus_component::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int ptb::corrupting_bonus_component::width() const
{
  return m_corrupting_bonus.width() +
    m_text_corrupting_bonus.get_width() + s_margin;
} // corrupting_bonus_component::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int ptb::corrupting_bonus_component::height() const
{
  return std::max
    (m_corrupting_bonus.height(), m_text_corrupting_bonus.get_height());
} // corrupting_bonus_component::height()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set all signals to listen.
 */
void ptb::corrupting_bonus_component::init_signals()
{  
  add_signal
    ( bear::engine::game::get_instance().listen_uint_variable_change
      ( game_variables::get_corrupting_bonus_count_variable_name(),
        boost::bind
        (&ptb::corrupting_bonus_component::on_corrupting_bonus_updated,
         this, _1) ) );
} // corrupting_bonus_component::init_signals()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when a corrupting_bonus is updated.
 * \param value The new number of corrupting_bonus.
 */
void ptb::corrupting_bonus_component::on_corrupting_bonus_updated
(unsigned int value)
{
  if ( value < m_last_corrupting_bonus_count )
    change_scale();
  else
    create_floating_corrupting_bonus();
  
  move();
} // corrupting_bonus_component::on_corrupting_bonus_updated()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when a corrupting_bonus is added.
 * \param value The new number of corrupting_bonus.
 */
void ptb::corrupting_bonus_component::on_corrupting_bonus_added()
{
  m_last_corrupting_bonus_count++;

  std::ostringstream oss;
  oss << m_last_corrupting_bonus_count;
  m_text_corrupting_bonus.create(m_font, oss.str());
  m_text_corrupting_bonus->set_intensity(1, 0.8, 0);
} // corrupting_bonus_component::on_corrupting_bonus_added()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when the scale of corrupting bonus
 * writing changes.
 * \param scale The new scale.
 */
void ptb::corrupting_bonus_component::on_corrupting_bonus_scale_update
(double scale)
{
  m_corrupting_bonus_scale = scale;

  double red(1/m_corrupting_bonus_scale);
  double green(red-0.5);
  green = green * 8 / 5;
  m_text_corrupting_bonus->set_intensity(red, green, 0);
} // corrupting_bonus_component::on_corrupting_bonus_scale_update()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add tweener for moving corrupting bonus.
 */
void ptb::corrupting_bonus_component::move()
{
  claw::tween::tweener_sequence tween;

  tween.insert
    ( claw::tween::single_tweener
      (get_position().y, get_active_position().y, 0.3,
       boost::bind
       ( &ptb::status_component::on_y_position_update,
         this, _1 ), &claw::tween::easing_back::ease_out ) );
  
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

  add_tweener( tween );
} // corrupting_bonus_component::move()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add tweener for changing corrupting bonus scale.
 */
void ptb::corrupting_bonus_component::change_scale()
{
  claw::tween::tweener_sequence tween;
  
  tween.insert
    ( claw::tween::single_tweener
      (1, 1, 0.3,
       boost::bind
       (&ptb::corrupting_bonus_component::on_corrupting_bonus_scale_update,
	this, _1 ), &claw::tween::easing_back::ease_out ) );
  
  tween.insert
    ( claw::tween::single_tweener
      (1, 1.5, 0.3,
       boost::bind
       (&ptb::corrupting_bonus_component::on_corrupting_bonus_scale_update,
	this, _1 ), &claw::tween::easing_back::ease_out ) );
  
  tween.insert
    ( claw::tween::single_tweener
      (1.5, 1, 0.3,
       boost::bind
       (&ptb::corrupting_bonus_component::on_corrupting_bonus_scale_update,
	this, _1 ), &claw::tween::easing_back::ease_in ) );
  
  add_tweener( tween );
} // corrupting_bonus_component::change_scale()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a floating corrupting_bonus.
 */
void ptb::corrupting_bonus_component::create_floating_corrupting_bonus()
{
  bear::visual::position_type pos(get_layer_size()/2);
  pos.x += 
    ( game_variables::get_corrupting_bonus_rate_x() * get_layer_size().x);
  pos.y += 
    ( game_variables::get_corrupting_bonus_rate_y() * get_layer_size().y);
  
  if ( ( pos.x <= get_layer_size().x ) && ( pos.y <= get_layer_size().y ) && 
       ( pos.x + m_corrupting_bonus.width() >= 0 ) && 
       ( pos.y + m_corrupting_bonus.height() >= 0 ) )
    {
      floating_corrupting_bonus f;

      m_floating_corrupting_bonus.push_back(f);
      m_floating_corrupting_bonus.back().set_position
        (pos, get_render_position());
    }
  else
    on_corrupting_bonus_added();
} // corrupting_bonus_component::create_floating_corrupting_bonus()
