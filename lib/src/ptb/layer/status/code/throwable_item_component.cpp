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

#include "ptb/game_variables.hpp"
#include "ptb/throwable_item/throwable_items_container.hpp"
#include "ptb/player_signals.hpp"

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
    m_font(glob.get_font("font/Fava-black.ttf", 30))
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
        m_bonus_signals.clear();

        std::ostringstream oss;
	oss << get_player().get_throwable_items()
	  .get_current_throwable_item()->get_stock();
	m_throwable_item.create(m_font, oss.str());
	m_throwable_item->set_intensity(1, 0.8, 0);

	m_throwable_item_animation =
	  get_level_globals().get_animation
	  ( get_player().get_throwable_items().get_current_throwable_item()
	    ->get_animation() );

        m_stones_count = 
          game_variables::get_stones_count( get_player().get_index() );
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

  floating_bonus_list::iterator it = m_floating_bonus.begin();

  while ( it != m_floating_bonus.end() )
    {
      it->progress(elapsed_time);

      if ( it->is_finished() )
	{
          floating_bonus_list::iterator tmp(it);
          ++it;
          m_floating_bonus.erase(tmp);
        }
      else
        ++it;
    }
} // throwable_item_component::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players oxygen.
 * \param e (out) The scene elements.
 */
void ptb::throwable_item_component::render( scene_element_list& e ) const
{
  bear::visual::coordinate_type pos_y = height() / 2;

  bear::visual::scene_sprite s1
    ( get_render_position().x, 
      ( pos_y - m_throwable_item_animation.get_sprite().height() ) / 2 + 
      get_render_position().y, 
      m_throwable_item_animation.get_sprite());

  bear::visual::scene_writing s2
    ( get_render_position().x + 
      m_throwable_item_animation.get_max_size().x + s_margin, 
      ( pos_y - m_throwable_item.get_height() ) / 2 + 
      get_render_position().y , m_throwable_item );

  e.push_back( s1 );
  e.push_back( s2 );

  floating_bonus_list::const_iterator it;
  for ( it = m_floating_bonus.begin(); 
	it != m_floating_bonus.end(); ++it )
    {
      bear::visual::scene_sprite sp2
	( it->get_position().x, it->get_position().y, 
          get_level_globals().auto_sprite( "gfx/ui/ui-1.png", it->get_name() ));
      e.push_back( sp2 );
    } 
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
         this, boost::placeholders::_1) ) );
  
  add_signal
    ( get_player().get_throwable_items().throwable_item_stock_changed.connect
      ( boost::bind
        (&ptb::throwable_item_component::on_throwable_item_stock_changed,
         this, boost::placeholders::_1) ) );

  add_signal
    ( get_player().get_throwable_items().throwable_item_no_stock.connect
      ( boost::bind
        (&ptb::throwable_item_component::on_throwable_item_changed, this)));

  add_signal
    ( bear::engine::game::get_instance().listen_bool_variable_change
      ( game_variables::get_air_power_variable_name(get_player().get_index()),
        boost::bind
        ( &throwable_item_component::on_power_changed, this,
          boost::placeholders::_1, "air") ) );

  add_signal
    ( bear::engine::game::get_instance().listen_bool_variable_change
      ( game_variables::get_fire_power_variable_name(get_player().get_index()),
        boost::bind
        ( &throwable_item_component::on_power_changed, this,
          boost::placeholders::_1, "fire") ) );

  add_signal
    ( bear::engine::game::get_instance().listen_bool_variable_change
      ( game_variables::get_water_power_variable_name(get_player().get_index()),
        boost::bind
        ( &throwable_item_component::on_power_changed, this,
          boost::placeholders::_1, "water") ) );

  add_signal
    ( bear::engine::game::get_instance().listen_uint_variable_change
      ( game_variables::get_stones_count_variable_name
        (get_player().get_index()),
        boost::bind
        ( &throwable_item_component::on_stones_stock_changed, this,
          boost::placeholders::_1) ) );
} // throwable_item_component::init_signals()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when there is a new bonus.
 * \param animation The name of the new bonus. */
void ptb::throwable_item_component::create_floating_bonus
( const std::string& name )
{
  bear::visual::animation anim =
    get_level_globals().auto_sprite( "gfx/ui/ui-1.png", name );

  bear::visual::position_type rate(0,0);
  if ( get_player() != NULL )
    {
      rate.x = 
        ( get_player().get_left() - 
          get_player().get_level().get_camera_center().x) /
        get_player().get_level().get_camera()->get_width();
      rate.y = 
        ( get_player().get_bottom() - 
          get_player().get_level().get_camera_center().y) /
        get_player().get_level().get_camera()->get_height();
    }

  bear::visual::position_type pos(get_layer_size()/2);
  pos.x += ( rate.x * get_layer_size().x);
  pos.y += ( rate.y * get_layer_size().y);
  
  if ( ( pos.x <= get_layer_size().x ) && ( pos.y <= get_layer_size().y ) && 
       ( pos.x + anim.width() >= 0 ) && 
       ( pos.y + anim.height() >= 0 ) )
    {
      floating_bonus f(name);

      m_floating_bonus.push_back(f);
      m_floating_bonus.back().set_position
        ( pos - anim.get_size()/2, 
          get_render_position() - anim.get_size()/2);
    }
} // throwable_item_component::create_floating_bonus
/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when the stone's stock changes.
 * \param stock The new stock. */
void ptb::throwable_item_component::on_stones_stock_changed
( unsigned int stock )
{
  if ( m_stones_count + 20 < stock )
    create_floating_bonus("stones");
  else if ( m_stones_count < stock )
    create_floating_bonus("stone");

  m_stones_count = stock;
} // throwable_item_component::on_stones_stock_changed()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when the throwable item changes.
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
 * \brief The fonction called when a power changes.
 * \param status Indicates if the power's status. 
 * \param name The name of the bonus.
 */
void ptb::throwable_item_component::on_power_changed
( bool status, const std::string& name )
{
  if ( status )
    create_floating_bonus(name);
} // throwable_item_component::on_power_changed()

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
} // throwable_item_component::on_throwable_item_changed()
