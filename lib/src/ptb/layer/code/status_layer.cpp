/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::status_layer class.
 * \author Julien Jorge
 */
#include "ptb/layer/status_layer.hpp"

#include "ptb/layer/status/accelerated_time_component.hpp"
#include "ptb/layer/status/boss_component.hpp"
#include "ptb/layer/status/cold_gauge_component.hpp"
#include "ptb/layer/status/corrupting_bonus_component.hpp"
#include "ptb/layer/status/energy_component.hpp"
#include "ptb/layer/status/hazelnut_component.hpp"
#include "ptb/layer/status/heat_gauge_component.hpp"
#include "ptb/layer/status/honeypots_component.hpp"
#include "ptb/layer/status/lives_component.hpp"
#include "ptb/layer/status/oxygen_gauge_component.hpp"
#include "ptb/layer/status/score_component.hpp"
#include "ptb/layer/status/throwable_item_component.hpp"
#include "ptb/util/player_util.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/level_variables.hpp"

#include "visual/bitmap_writing.hpp"

#include <boost/bind.hpp>

#include <claw/tween/tweener_sequence.hpp>
#include <claw/tween/easing/easing_back.hpp>
#include <claw/tween/easing/easing_linear.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param glob Level globals in which we take the resources.
 * \param f The font to use to display the texts.
 * \param p The player from which we take the data.
 * \param pos_ref The reference position.
 * \param x_p The x-coordinate placement.
 */
ptb::status_layer::player_status::player_status
( bear::engine::level_globals& glob, const bear::visual::font& f,
  const player_proxy& p, const bear::visual::position_type& pos_ref,
  status_component::x_placement x_p, 
  const bear::universe::size_box_type& layer_size)
  : m_level_globals(glob), notification_offset_y(0), m_player(p)
{
  if ( m_player != NULL )
    {
      bool auto_disappear =  
        ! level_variables::get_player_status_fixed(p.get_level());

      bear::visual::position_type pos(pos_ref);
      bear::universe::zone::position z = 
	bear::universe::zone::middle_left_zone;
      if ( x_p == status_component::right_placement ) 
	z = bear::universe::zone::middle_right_zone;

      status_component * c = new energy_component
	(glob, p, pos, bear::universe::zone::top_zone,
	 x_p,status_component::top_placement,layer_size, auto_disappear); 
      c->build();
      m_components.push_back(c);

      pos.y -= c->height() + s_margin;
      c = new score_component
	(glob, p, pos, z, x_p, status_component::top_placement,
         layer_size, auto_disappear); 
      c->build();
      m_components.push_back(c);

      pos.y -= c->height() + s_margin;
      c = new throwable_item_component
	(glob, p, pos, z, x_p, status_component::top_placement, 
         layer_size, auto_disappear); 
      c->build();
      m_components.push_back(c);

      pos.y -= c->height() + s_margin;
      c = new oxygen_gauge_component
	(glob, p, pos, z, x_p, status_component::top_placement, 
         layer_size, true); 
      c->build();
      m_components.push_back(c);

      pos.y -= c->height() + s_margin;
      c = new heat_gauge_component
	(glob, p, pos, z, x_p, status_component::top_placement,
         layer_size, true); 
      c->build();
      m_components.push_back(c);

      pos.y -= c->height() + s_margin;
      c = new cold_gauge_component
	(glob, p, pos, z, x_p, status_component::top_placement,
         layer_size, true); 
      c->build();
      m_components.push_back(c);

      pos.y = s_margin;
      c = new lives_component
	(glob, p, pos, z, x_p, status_component::bottom_placement,
         layer_size, auto_disappear); 
      c->build();
      m_components.push_back(c);
    }
} // status_layer::player_status::player_status()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::status_layer::player_status::~player_status()
{
  component_list::iterator it;
  for ( it = m_components.begin(); it != m_components.end(); ++it)
    delete *it;
} // status_layer::player_status::~player_status()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the player concerned by this instance.
 */
const ptb::player_proxy& ptb::status_layer::player_status::get_player() const
{
  return m_player;
} // status_layer::player_status::get_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the values.
 * \param glob The level globals in which we load the media.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::status_layer::player_status::progress
( bear::engine::level_globals& glob, bear::universe::time_type elapsed_time )
{
  if (m_player != NULL)
    {
      m_tweeners.update(elapsed_time);
      progress_notification(elapsed_time);
    
      component_list::iterator it;
      for ( it = m_components.begin(); it != m_components.end(); ++it)
	(*it)->progress(elapsed_time);
    }  
} // status_layer::player_status::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the player status.
 * \param e (out) The scene elements.
 */
void ptb::status_layer::player_status::render( scene_element_list& e ) const
{
  if ( m_player != NULL )
    {
      component_list::const_iterator it;
      for ( it = m_components.begin(); it != m_components.end(); ++it)
	(*it)->render(e);
    }
} // status_layer::player_status::::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when the there is a new notification.
 * \param text The text of notification.
 * \param sp The sprite of the notification.
 */
void ptb::status_layer::player_status::add_notification
( const std::string& text, const bear::visual::sprite& sp )
{       
   m_notifications.push_back
      (std::pair<std::string,bear::visual::sprite>(text,sp));
} // player_status::add_notification()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do an iteration for notification.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::status_layer::player_status::progress_notification
( bear::universe::time_type elapsed_time)
{
  if (m_player != NULL)
    {
      m_notification_tweener.update(elapsed_time);
      
      if ( ( ! m_notifications.empty() ) && 
           ( ( notification_offset_y <= 0 ) || 
             ( notification_offset_y == notification.height()+s_margin ) ) ) 
      {
         m_notification_tweener.clear();

         if ( notification_offset_y <= 0 )
            create_notification();
      
         m_notification_tweener.insert
            (claw::tween::single_tweener
             (notification.height()+s_margin, -1, 0.5,
              boost::bind
              ( &player_status::on_notification_position_update,
                this, _1 ), &claw::tween::easing_back::ease_in ) );
      }
    }
} // player_status::progress_notification

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a notification.
 */
void ptb::status_layer::player_status::create_notification()
{
   notification.get_text()->set_intensity(1, 0.8, 0);
   notification.set_background
     (m_level_globals.auto_sprite("gfx/ui/status/notification.png", "frame"));
   notification.set_text
     (m_level_globals.get_font("font/AndikaBasic.ttf", 14),
      m_notifications.front().first);
   notification.set_picture(m_notifications.front().second);
   m_notifications.pop_front();
   
   m_notification_tweener.insert
      (claw::tween::single_tweener
       (0, notification.height()+s_margin, 0.5,
        boost::bind
        (&player_status::on_notification_position_update,
         this, _1 ), &claw::tween::easing_back::ease_out ) );
      
   m_notification_tweener.insert
      (claw::tween::single_tweener
       (notification.height()+s_margin, notification.height()+s_margin,1,
        boost::bind
        (&player_status::on_notification_position_update,
         this, _1 ), &claw::tween::easing_linear::ease_out ) );     
} // player_status::create_notification()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when the position of notification changes.
 * \param position The new y position of the notification.
 */
void ptb::status_layer::player_status::on_notification_position_update
(double position)
{
  notification_offset_y = position;
} // status_layer::player_status::on_notification_position_update()

/*----------------------------------------------------------------------------*/
const unsigned int ptb::status_layer::s_margin = 10;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param name The name of the layer.
 */
ptb::status_layer::status_layer( const std::string& name )
  : bear::communication::messageable(name), m_data_1(NULL), m_data_2(NULL),
    m_timer(NULL)
{

} // status_layer::status_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::status_layer::~status_layer()
{
  component_list::iterator it;
  for ( it = m_components.begin(); it != m_components.end(); ++it)
    delete *it;

  component_map::iterator it2;
  for ( it2 = m_persistent_components.begin(); 
	it2 != m_persistent_components.end(); ++it2)
    delete it2->second;

  delete m_data_1;
  delete m_data_2;
} // status_layer::~status_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::status_layer::pre_cache()
{
  super::pre_cache();

  get_level_globals().load_image("gfx/ui/status/tube.png");
  get_level_globals().load_image("gfx/ui/status/tube-vertical.png");
  get_level_globals().load_image("gfx/ui/status/notification.png");
} // status_layer::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the layer.
 */
void ptb::status_layer::build()
{
  super::build();

  bear::engine::level_globals& glob = get_level_globals();
  glob.register_item(*this);

  create_components();
  create_persistent_components();
} // status_layer::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the players status and update local values.
 */
void ptb::status_layer::progress( bear::universe::time_type elapsed_time )
{
  search_players();

  component_list::iterator it;
  for ( it = m_components.begin(); it != m_components.end(); ++it)
    (*it)->progress(elapsed_time);
  
  component_map::iterator it2;
  for ( it2 = m_persistent_components.begin(); 
	it2 != m_persistent_components.end(); ++it2)
    it2->second->progress(elapsed_time);

  if ( m_data_1 != NULL )
    m_data_1->progress(get_level_globals(), elapsed_time);

  if ( m_data_2 != NULL )
    m_data_2->progress(get_level_globals(), elapsed_time);
} // status_layer::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players status.
 * \param e (out) The scene elements.
 */
void ptb::status_layer::render( scene_element_list& e ) const
{
  bool player_on(false);

  // render first player status
  if ( m_data_1 != NULL) 
    {
      render_notification(e, m_data_1, 0, 1);
  
      if ( !m_data_1->get_player().is_a_marionette() )
	{
          scene_element_list visuals;
	  m_data_1->render(visuals);
          set_visual_shadows( visuals, 3, -3 );
          e.insert( e.end(), visuals.begin(), visuals.end() );
      	  player_on = true;
	}
    }

  // render second player status (if any)
  if ( m_data_2 != NULL )
    {
      render_notification(e, m_data_2, 1, -1);
      
      if ( ! m_data_2->get_player().is_a_marionette() )
	{
          scene_element_list visuals;
	  m_data_2->render(visuals);
          set_visual_shadows( visuals, 3, -3 );
          e.insert( e.end(), visuals.begin(), visuals.end() );
      	  player_on = true;
	}
    }
  
  if ( player_on )
    {
      component_list::const_iterator it;
      for ( it = m_components.begin(); it != m_components.end(); ++it)
	(*it)->render( e ); 
    }
  
  component_map::const_iterator it;
  for ( it = m_persistent_components.begin(); 
	it != m_persistent_components.end(); ++it)
    it->second->render( e );
} // status_layer::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the timer to use for the time.
 */
void ptb::status_layer::set_timer( const time_component::timer_handle& t )
{
  m_timer = t;
} // status_layer::set_timer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the boss for which we display the energy.
 * \param b The boss.
 */
void ptb::status_layer::set_boss( const monster* b )
{
  boss_component::monster_handle the_boss = 
    dynamic_cast<const bear::universe::physical_item*>(b);

  if ( the_boss != (monster*)NULL )
    {
      component_map::iterator it = m_persistent_components.find("boss");
      
      if ( it != m_persistent_components.end() ) 
	m_persistent_components.erase(it);
      
      bear::visual::position_type pos(get_size().x/2, 80);
      
      status_component* c = new
	boss_component
	(get_level_globals(), player_proxy(), pos,
	 bear::universe::zone::middle_zone, 
	 status_component::middle_x_placement,
	 status_component::bottom_placement, the_boss, get_size(), true);
      
      c->build();
      
      m_persistent_components["boss"] = c;
    }
} // status_layer::set_boss()

/*----------------------------------------------------------------------------*/
/**
 * \brief The fonction called when the there is a new notification.
 */
void ptb::status_layer::add_notification
( unsigned int index, const std::string& text, const bear::visual::sprite& sp )
{
  if ( ( index != 1 ) && ( m_data_2 != NULL ) )
     m_data_2->add_notification(text,sp);
   
  if ( ( index != 2 ) && ( m_data_1 != NULL ) )
     m_data_1->add_notification(text,sp);
} // status_layer::add_notification()

/*----------------------------------------------------------------------------*/
/**
 * \brief Draw notification.
 * \param e (out) The scene elements.
 * \param data The player status to render.
 * \param take_width Indicates if we take into account object's width.
 * \param orientation The orientation of objects.
 */
void ptb::status_layer::render_notification
( scene_element_list& e, const player_status* data,
  double take_width, double orientation ) const
{
  bear::visual::position_type pos
    ( (take_width ? get_size().x : 1) + orientation*85 - 
      take_width*data->notification.width(), 
      data->notification_offset_y - data->notification.height());
  
  data->notification.render(e, pos);
} // status_layer::render_notification

/*----------------------------------------------------------------------------*/
/**
 * \brief Adds a shadow to some visuals.
 * \param visuals The visuals.
 * \param x The shadow's distance on the x-axis.
 * \param y The shadow's distance on the y-axis.
 */
void ptb::status_layer::set_visual_shadows
( scene_element_list& visuals, bear::visual::coordinate_type x,
  bear::visual::coordinate_type y ) const
{
  for ( scene_element_list::iterator it( visuals.begin() );
        it != visuals.end(); ++it )
    {
      it->set_shadow( x, y );
      it->set_shadow_opacity( 0.75 );
    }
} // status_layer::set_visual_shadows()

/*----------------------------------------------------------------------------*/
/**
 * \brief Search players.
 */
void ptb::status_layer::search_players( )
{
  if ( m_data_1 == NULL )
    {
      player_proxy p = util::find_player( get_level_globals(), 1 );

      if ( p != NULL )
        m_data_1 = new player_status
          ( get_level_globals(),
            get_level_globals().get_font("font/Fava-black.ttf", 30), p,
	    bear::visual::position_type(s_margin,get_size().y - s_margin),
	    status_component::left_placement, get_size());
    }

  if ( (game_variables::get_players_count() == 2) && (m_data_2 == NULL) )
    {
      player_proxy p = util::find_player( get_level_globals(), 2 );

      if ( p != NULL )
        m_data_2 = new player_status
          ( get_level_globals(),
            get_level_globals().get_font("font/Fava-black.ttf", 30), p,
	    bear::visual::position_type
	    (get_size().x - s_margin,get_size().y - s_margin),
	    status_component::right_placement, get_size() );
    }
} // status_layer::search_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the components.
 */
void ptb::status_layer::create_components()
{
  // honeypots
  bear::visual::position_type pos(get_size().x/2,s_margin);
  
  status_component* c = new
    corrupting_bonus_component
    (get_level_globals(), player_proxy(), pos,
     bear::universe::zone::bottom_zone, status_component::middle_x_placement, 
     status_component::bottom_placement, get_size(), true);
  c->build();
  m_components.push_back(c);

  // corrupting bonus
  pos.y += c->height() + s_margin;

  c = new
   honeypots_component
    (get_level_globals(), player_proxy(), pos,
     bear::universe::zone::bottom_zone, status_component::middle_x_placement, 
     status_component::bottom_placement, get_level(), get_size(), true);
  c->build();
  m_components.push_back(c);

  // time
  pos.y = get_size().y - s_margin;
  
  c = new
  time_component
    (get_level_globals(), player_proxy(), pos,
     bear::universe::zone::middle_zone, status_component::middle_x_placement, 
     status_component::top_placement, m_timer, get_size(), true);
  c->build();
  m_components.push_back(c);
  
  // hazelnut
  pos.y = pos.y - c->height() - s_margin;

  c = new
  hazelnut_component
    (get_level_globals(), player_proxy(), pos,
     bear::universe::zone::middle_zone, status_component::middle_x_placement, 
     status_component::top_placement, get_level(), get_size(), true);
  c->build();
  m_components.push_back(c);
} // status_layer::create_time()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create persistent components.
 */
void ptb::status_layer::create_persistent_components()
{
  // accelerated time
  bear::visual::position_type pos(get_size().x/2, get_size().y/2);
  
  status_component* c = new
    accelerated_time_component
    (get_level_globals(), player_proxy(), pos,
     bear::universe::zone::middle_zone,
     status_component::middle_x_placement,
     status_component::middle_y_placement, get_size(), true);

  c->build();

  m_persistent_components["accelerated_time"] = c;
} // status_layer::create_persistent_components()
