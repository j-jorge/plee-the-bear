/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::catapult class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/castle/catapult.hpp"
#include "ptb/player_proxy.hpp"
#include "ptb/message/status_layer_notification_message.hpp"
#include "ptb/defines.hpp"

#include "engine/export.hpp"
#include "expr/linear_function.hpp"
#include "universe/collision_info.hpp"
#include "universe/forced_movement/forced_tracking.hpp"

#include <claw/tween/easing/easing_cubic.hpp>
#include <claw/tween/easing/easing_elastic.hpp>
#include <claw/tween/easing/easing_linear.hpp>

BASE_ITEM_EXPORT( catapult, ptb )

const double ptb::catapult::s_initial_stop_angle = -0.175;
const double ptb::catapult::s_initial_arm_angle = -0.30; //-0.35;
const double ptb::catapult::s_minimal_arm_angle = -0.04;
const double ptb::catapult::s_maximal_arm_angle = -0.30;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::catapult::catapult()
  : m_state(idle_state), m_progress(NULL), 
    m_stop_angle(s_initial_stop_angle), m_arm_angle(s_initial_arm_angle),
    m_minimal_force(0), m_maximal_force(50000000)
{
  set_mass(2000);
  set_height(80);
  set_width(665);

  m_player = player_proxy();
} // catapult::catapult()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::catapult::pre_cache()
{
  get_level_globals().load_model("model/castle/catapult.cm");
} // catapult::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::catapult::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor( get_level_globals().get_model("model/castle/catapult.cm") );
  start_model_action("idle");
  start_idle();
} // catapult::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::catapult::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  if ( m_state != end_state )
    {
      m_stop_angle_tweener.update(elapsed_time);
      m_arm_angle_tweener.update(elapsed_time);
    }

  if ( m_progress != NULL )
    (this->*m_progress)(elapsed_time);
} // catapult::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the current state.
 */
unsigned int ptb::catapult::get_state() const
{
  return m_state;
} // catapult::get_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the items concerned by a progress/move of this one.
 * \param d (out) A list to which are added such items.
 */
void ptb::catapult::get_dependent_items( std::list<physical_item*>& d ) const
{
  super::get_dependent_items(d);
  
  if ( m_player != NULL ) 
    d.push_front
      ((bear::universe::physical_item*)m_player.get_player_instance());
} // catapult::get_dependent_items()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state idle.
 */
void ptb::catapult::progress_idle( bear::universe::time_type elapsed_time )
{

} // catapult::progress_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state angle_selection.
 */
void ptb::catapult::progress_angle_selection
( bear::universe::time_type elapsed_time )
{
  if ( m_stop_angle_tweener.is_finished() )
    create_stop_angle_tweener();

  progress_input_actions(elapsed_time);
} //  catapult::progress_angle_selection()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state force_selection.
 */
void ptb::catapult::progress_force_selection
( bear::universe::time_type elapsed_time )
{
  if ( m_arm_angle_tweener.is_finished() )
    create_arm_angle_tweener();
  
  progress_input_actions(elapsed_time);
} // progress_force_selection()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state throw.
 */
void ptb::catapult::progress_throw
( bear::universe::time_type elapsed_time )
{

} // progress_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state end.
 */
void ptb::catapult::progress_end_state
( bear::universe::time_type elapsed_time )
{
  if ( m_player != NULL )
    {
      bear::universe::coordinate_type height = 
	m_player.get_bottom() - get_vertical_middle();
      if ( height > m_maximal_height )
	m_maximal_height = height;

      if ( m_player.has_bottom_contact() )
	{
	  if ( ! m_cancel )
	    {
	      status_layer_notification_message msg;
	      bear::visual::sprite sp;
	      bear::universe::coordinate_type dist = 
		m_player.get_center_of_mass().distance
		(get_center_of_mass()) / 50;
	      
	      std::ostringstream oss;
	      oss << dist << "m\n" << m_maximal_height/50 << "m" ;
	      
	      msg.set_notification( m_player.get_index(), sp, oss.str());	
	      get_level_globals().send_message
		( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
	    }

	  m_player = player_proxy();
	  
	  m_state = idle_state;
	  init_angle();
	}
    }
} // progress_end_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start idle state.
 */
void ptb::catapult::start_idle()
{
  m_state = idle_state;
  m_progress = &catapult::progress_idle;
  on_stop_angle_update(0);
  on_arm_angle_update(s_initial_arm_angle);
} // catapult::start_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start angle selection state.
 */
void ptb::catapult::start_angle_selection()
{
  m_state = angle_selection_state;
  m_progress = &catapult::progress_angle_selection;
  
  create_stop_angle_tweener();
} // catapult::start_angle_selection()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start force selection state.
 */
void ptb::catapult::start_force_selection()
{
  m_state = force_selection_state;
  m_progress = &catapult::progress_force_selection;
  
  m_stop_angle_tweener.clear();
} // catapult::start_force_selection()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start throw state.
 */
void ptb::catapult::start_throw()
{
  m_state = throw_state;
  m_progress = &catapult::progress_throw;

  compute_force();
  m_cancel = false;

  m_stop_angle_tweener.clear();
  m_arm_angle_tweener.clear();
  m_arm_angle_tweener.insert
    (claw::tween::single_tweener
     (m_arm_angle, -1.57+m_stop_angle, 0.1,
       boost::bind
       ( &catapult::on_arm_angle_update,
	 this, _1 ), &claw::tween::easing_linear::ease_out ) );
  m_arm_angle_tweener.insert
    (claw::tween::single_tweener
     (m_arm_angle, 0, 0.5,
       boost::bind
       ( &catapult::start_end_state,
	 this ), &claw::tween::easing_elastic::ease_out ) );
} // catapult::start_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Cancel.
 */
void ptb::catapult::cancel()
{
  m_state = throw_state;
  m_progress = &catapult::progress_throw;

  m_force.x = 0;
  m_force.y = 0;
  m_cancel = true;

  m_stop_angle_tweener.clear();
  m_arm_angle_tweener.clear();
  m_arm_angle_tweener.insert
    (claw::tween::single_tweener
     (m_arm_angle, m_arm_angle-0.2, 0.05,
       boost::bind
       ( &catapult::on_arm_angle_update,
	 this, _1 ), &claw::tween::easing_linear::ease_out ) );
  m_arm_angle_tweener.insert
    (claw::tween::single_tweener
     (m_arm_angle, 0, 0.5,
       boost::bind
       ( &catapult::start_end_state,
	 this ), &claw::tween::easing_elastic::ease_out ) );
} // catapult::cancel

/*----------------------------------------------------------------------------*/
/**
 * \brief Start end state.
 */
void ptb::catapult::start_end_state()
{
  m_state = end_state;
  m_progress = &catapult::progress_end_state;
  m_maximal_height = 0;

  if ( m_player != NULL )
    {
      m_player.do_action(0,player_action::release);
      if ( m_player.has_forced_movement() )
	m_player.clear_forced_movement();
      m_player.set_marionette(false);
      m_player.add_internal_force(m_force);
    }
} // catapult::start_end_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start an action asked by the human player.
 * \param a The action to start.
 */
void ptb::catapult::start_action(player_action::value_type a)
{
  if ( a == player_action::jump )
    {
      if ( ( m_state == angle_selection_state ) ||
	   ( m_state == force_selection_state ) )
	cancel();
    }
  else if ( m_state == angle_selection_state )
    start_force_selection();
} // catapult::start_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop an action asked by the human player.
 * \param a The action to start.
 */
void ptb::catapult::stop_action(player_action::value_type a)
{
  if ( m_state == force_selection_state )
   start_throw();
} // catapult::stop_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create tweener for stop angle.
 */
void ptb::catapult::create_stop_angle_tweener()
{
  m_stop_angle_tweener.clear();
  m_stop_angle_tweener.insert
    (claw::tween::single_tweener
     (0, -s_initial_stop_angle, 0.3,
       boost::bind
       ( &catapult::on_stop_angle_update,
	 this, _1 ), &claw::tween::easing_cubic::ease_in ) );
  m_stop_angle_tweener.insert
    (claw::tween::single_tweener
     (-s_initial_stop_angle, 0, 0.3,
       boost::bind
       ( &catapult::on_stop_angle_update,
	 this, _1 ), &claw::tween::easing_cubic::ease_out ) );
  m_stop_angle_tweener.insert
    (claw::tween::single_tweener
     (0, s_initial_stop_angle, 0.3,
       boost::bind
       ( &catapult::on_stop_angle_update,
	 this, _1 ), &claw::tween::easing_cubic::ease_in ) );
  m_stop_angle_tweener.insert
    (claw::tween::single_tweener
     (s_initial_stop_angle, 0, 0.3,
       boost::bind
       ( &catapult::on_stop_angle_update,
	 this, _1 ), &claw::tween::easing_cubic::ease_out ) ); 
} // catapult::create_stop_angle_tweener()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create tweener for arm angle.
 */
void ptb::catapult::create_arm_angle_tweener()
{
  m_arm_angle_tweener.clear();
  m_arm_angle_tweener.insert
    (claw::tween::single_tweener
     (m_arm_angle, s_minimal_arm_angle, 1,
       boost::bind
       ( &catapult::on_arm_angle_update,
	 this, _1 ), &claw::tween::easing_cubic::ease_in ) );
  m_arm_angle_tweener.insert
    (claw::tween::single_tweener
     (s_minimal_arm_angle, s_maximal_arm_angle, 1,
       boost::bind
       ( &catapult::on_arm_angle_update,
	 this, _1 ), &claw::tween::easing_cubic::ease_out ) );
} // catapult::create_arm_angle_tweener()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create tweener for arm and stop angle to set in initial state.
 */
void ptb::catapult::init_angle()
{
  m_arm_angle_tweener.clear();
  m_arm_angle_tweener.insert
    (claw::tween::single_tweener
     (m_arm_angle, s_maximal_arm_angle, 0.5,
       boost::bind
       ( &catapult::on_arm_angle_update,
	 this, _1 ), &claw::tween::easing_linear::ease_in ) );
   m_arm_angle_tweener.insert
    (claw::tween::single_tweener
     (m_arm_angle, s_initial_arm_angle, 1,
       boost::bind
       ( &catapult::start_idle,
	 this ), &claw::tween::easing_linear::ease_in ) );

  m_stop_angle_tweener.clear();
  m_stop_angle_tweener.insert
    (claw::tween::single_tweener
     (m_stop_angle, 0, 0.5,
       boost::bind
       ( &catapult::on_stop_angle_update,
	 this, _1 ), &claw::tween::easing_linear::ease_in ) );
} // catapult::init_angle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Compute the force to give. 
 */
void ptb::catapult::compute_force()
{
  bear::universe::coordinate_type coeff = 
    ( s_minimal_arm_angle - m_arm_angle ) / 
    ( s_maximal_arm_angle - s_minimal_arm_angle) + 1;
 
  std::cout << "coef = "<< coeff << " cos=" << cos(4*m_stop_angle) 
	    << " sin=" << sin(4*m_stop_angle) << std::endl;
  
  bear::universe::coordinate_type f = 
    m_minimal_force + coeff * (m_maximal_force - m_minimal_force); 
  
  m_force.x = f * cos(4*m_stop_angle);
  m_force.y = f * sin(4*m_stop_angle);
} // catapult::compute_force()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when the angle of stop component changes. 
 * \param angle The new angle. 
 */
void ptb::catapult::on_stop_angle_update(double angle)
{
  m_stop_angle = angle;

  bear::engine::model_mark_placement m;

  if ( get_mark_placement("front_wheel", m) )
    {
      bear::universe::position_type center = 
	m.get_position() - get_bottom_left();
      
      bear::universe::position_type pos(center);
      pos.y += 140;
      pos.rotate(center,m_stop_angle);      
      set_mark_position_in_action("stop",pos);
      set_mark_angle_in_action("stop",m_stop_angle);
    }
} // catapult::on_stop_angle_update()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when the angle of arm component changes. 
 * \param angle The new angle. 
 */
void ptb::catapult::on_arm_angle_update(double angle)
{
  m_arm_angle = angle;
  
  bear::engine::model_mark_placement m;

  if ( get_mark_placement("front_wheel", m) )
    {
      bear::universe::position_type center = 
	m.get_position() - get_bottom_left();
      center.x -= 42;
      
      bear::universe::position_type pos(center);
      pos.x -= 250;
      pos.rotate(center,m_arm_angle);      
      set_mark_position_in_action("arm",pos);
      set_mark_angle_in_action("arm",m_arm_angle);

      pos = center;
      pos.x -= 408;
      pos.rotate(center,m_arm_angle);           
      set_mark_position_in_action("placement",pos);
      set_mark_angle_in_action("placement",m_arm_angle);
    }
} //  catapult::on_arm_angle_update()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision on placement.
 * \param mark The mark on which the collision occurred.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::catapult::on_placement_collision
( bear::engine::base_item& mark, bear::engine::base_item& that,
  bear::universe::collision_info& info )
{
  if ( info.get_collision_side() != bear::universe::zone::top_zone )
    return;

  player_proxy p(&that);
  if ( (p != NULL) && ( m_state == idle_state ) )
    {
      start_angle_selection();

      m_player_position = p.get_center_of_mass() - mark.get_center_of_mass();
      m_player = p;
      set_player_index( p.get_index() );
      p.set_z_position(get_z_position() - 10);
      p.do_action(0,player_action::captive);
      p.set_marionette(true);
      p.stop();

      bear::engine::base_item* mark = get_model_mark_item("placement");
      
      bear::universe::forced_tracking mvt;
      mvt.set_ratio_reference_point
	    ( *mark, bear::universe::position_type(0.5,1), 
	      bear::universe::position_type(0,0));
      mvt.set_distance( bear::universe::position_type(m_player_position.x,0) );
      mvt.set_moving_item_ratio(bear::universe::position_type(0.5,0));
      m_player.set_forced_movement( mvt );
      
      m_arm_angle_tweener.clear();
    }
} // catapult::on_placement_collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a linear expression returning the performance of the player.
 */
bear::expr::linear_expression ptb::catapult::do_get_expression() const
{
  return bear::expr::linear_function_maker
    ( bear::universe::const_derived_item_handle<catapult>(this),
      std::mem_fun_ref(&catapult::get_state) );
} // catapult::do_get_expression();

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::catapult::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_3
    ( catapult, on_placement_collision, void, bear::engine::base_item&,
      bear::engine::base_item&, bear::universe::collision_info& );
} // catapult::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::catapult )
