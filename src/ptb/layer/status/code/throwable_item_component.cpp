/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::throwable_item_component class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/status/throwable_item_component.hpp"

#include "ptb/throwable_item/throwable_items_container.hpp"
#include "ptb/player_signals.hpp"

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
 * \param auto_disappear Indicates that the component disappears automatically.
 */
ptb::throwable_item_component::throwable_item_component
( bear::engine::level_globals& glob, const player_proxy& p,
  const bear::visual::position_type& active_position, 
  bear::universe::zone::position side,
  x_placement x_p, y_placement y_p,
  const bear::universe::size_box_type& layer_size,
  bool auto_disappear )
  : super(glob,p,active_position,side, x_p, y_p, layer_size, auto_disappear),
    m_font(glob.get_font("font/bouncy.fnt", 30))
{

} // throwable_item_component::throwable_item_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the component.
 */
void ptb::throwable_item_component::build()
{
  if ( get_player() != NULL )
    {
        std::ostringstream oss;
	oss << get_player().get_throwable_items()
	  .get_current_throwable_item()->get_stock();
	m_throwable_item.create(m_font, oss.str());
	m_throwable_item->set_intensity(1, 0.8, 0);

	m_throwable_item_animation =
	  get_level_globals().get_animation
	  ( get_player().get_throwable_items().get_current_throwable_item()
	    ->get_animation() );
    }

  super::build();
} // throwable_item_component::build()
      
/*----------------------------------------------------------------------------*/
/**
 * \brief Get the players status and update local values.
 */
void ptb::throwable_item_component::progress
( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time ); 

  m_throwable_item_animation.next(elapsed_time);
} // throwable_item_component::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players oxygen.
 * \param e (out) The scene elements.
 */
void ptb::throwable_item_component::render( scene_element_list& e ) const
{
  bear::visual::scene_sprite s1
    ( get_render_position().x, get_render_position().y, 
      m_throwable_item_animation.get_sprite());

  bear::visual::scene_writing s2
    ( get_render_position().x + 
      m_throwable_item_animation.get_max_size().x + s_margin, 
      get_render_position().y, m_throwable_item );

  e.push_back( s1 );
  e.push_back( s2 );
} // throwable_item_component::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int ptb::throwable_item_component::width() const
{
  return m_throwable_item.get_width() + s_margin +
    m_throwable_item_animation.get_max_size().x;
} // throwable_item_component::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int ptb::throwable_item_component::height() const
{
  return std::max
    ( m_throwable_item.get_height(), 
      m_throwable_item_animation.get_max_size().y);
} // throwable_item_component::height()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set all signals to listen.
 */
void ptb::throwable_item_component::init_signals()
{
  add_signal
    ( get_player().get_throwable_items().throwable_item_changed.connect
      ( boost::bind
        (&ptb::throwable_item_component::on_throwable_item_changed,
         this, _1) ) );
  
  add_signal
    ( get_player().get_throwable_items().throwable_item_stock_changed.connect
      ( boost::bind
        (&ptb::throwable_item_component::on_throwable_item_stock_changed,
         this, _1) ) );

  add_signal
    ( get_player().get_throwable_items().throwable_item_no_stock.connect
      ( boost::bind
        (&ptb::throwable_item_component::on_throwable_item_changed, this)));
} // throwable_item_component::init_signals()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when .
 * \param animation The new animation */
void ptb::throwable_item_component::on_throwable_item_changed
( const std::string& animation )
{
  m_throwable_item_animation = get_level_globals().get_animation( animation );
  update_inactive_position();
  on_throwable_item_changed();
} // throwable_item_component::on_throwable_item_changed()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when .
 * \param stock The new stock.
 */
void ptb::throwable_item_component::on_throwable_item_stock_changed
( unsigned int stock)
{
  std::ostringstream oss;
  oss << stock;
  m_throwable_item.create(m_font, oss.str());
  m_throwable_item->set_intensity(1, 0.8, 0);
  
  update_inactive_position();

  on_throwable_item_changed();
} // throwable_item_component::on_throwable_item_stock_changed()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when some throwable_item is added or removed.
 */
void ptb::throwable_item_component::on_throwable_item_changed()
{
  claw::tween::tweener_sequence tween;

  tween.insert
    ( claw::tween::single_tweener
      (get_position().x, get_active_position().x, 0.3,
       boost::bind
       ( &ptb::status_component::on_x_position_update,
         this, _1 ), &claw::tween::easing_back::ease_out ) );

  tween.insert
    ( claw::tween::single_tweener
      (get_active_position().x, get_active_position().x, 1,
       boost::bind
       ( &ptb::status_component::on_x_position_update,
	 this, _1 ), &claw::tween::easing_back::ease_in ) );
  
  tween.insert
    ( claw::tween::single_tweener
      (get_active_position().x, get_inactive_position().x, 0.5,
       boost::bind
       ( &ptb::status_component::on_x_position_update,
	 this, _1 ), &claw::tween::easing_back::ease_in ) );

  add_tweener( tween );
} // throwable_item_component::on_throwable_item_changed()
