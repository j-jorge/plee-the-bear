/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::ghost class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/castle/ghost.hpp"
#include "ptb/util/player_util.hpp"
#include "ptb/player.hpp"

#include "universe/forced_movement/forced_join.hpp"
#include "universe/forced_movement/forced_stay_around.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
*/
ptb::ghost::ghost()
  : m_progress(NULL), m_max_distance(600), m_fly_distance(400),
    m_scan_distance(200), m_scan(false)
{
  set_phantom(true);
  set_auto_mirror(true);
} // ghost::ghost()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
*/
ptb::ghost::~ghost()
{
} // ghost::~ghost()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
*/
void ptb::ghost::build()
{
  super::build();

  m_player = player_proxy();
  m_progress = &ghost::progress_wait;
} // ghost::build()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
*/
void ptb::ghost::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  if ( m_progress != NULL )
    (this->*m_progress)(elapsed_time);
} // ghost::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "real".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
*/
bool ptb::ghost::set_real_field
( const std::string& name, double value )
{
  bool ok = true;

  if (name == "ghost.max_distance")
    m_max_distance = value;
  else if (name == "ghost.fly_distance")
    m_fly_distance = value;
  else if (name == "ghost.scan_distance")
    m_scan_distance = value;
  else
    ok = super::set_real_field(name, value);

  return ok;
} // ghost::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_as_train().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
*/
void ptb::ghost::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
   player_proxy p(&that);

   if ( p != NULL )
     {
       if ( p.get_z_position() >= get_z_position() ) 
	 set_z_position(p.get_z_position() + 1);
       
       if ( ( m_player == NULL ) && 
	    ( (get_current_action_name() == "fly") || 
	      (get_current_action_name() == "appear")
	      || ( (get_current_action_name() == "come_back") && m_scan ) ) )
	 {
	   m_player = p;
	   start_model_action("control");
	 }
     }
}// ghost::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the ghost is in control state.
*/
bool ptb::ghost::possess() const
{
  return (get_current_action_name() == "control" );
} // ghost::possess()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the player.
*/
ptb::player_proxy ptb::ghost::get_player()
{
  return m_player;
} // ghost::get_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state fly.
*/
void ptb::ghost::progress_fly( bear::universe::time_type elapsed_time )
{
  if ( get_center_of_mass().distance
       (m_origin.get_center_of_mass()) > m_fly_distance )
    start_model_action("come_back");
} // ghost::progress_fly()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state appear.
*/
void ptb::ghost::progress_appear( bear::universe::time_type elapsed_time )
{
  // do nothing
} // ghost::progress_appear()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state come_back.
*/
void ptb::ghost::progress_come_back
( bear::universe::time_type elapsed_time )
{
  if ( get_center_of_mass().distance(m_origin.get_center_of_mass()) < 1 )
    {
      if ( has_forced_movement() )
        {
          clear_forced_movement();
          set_speed(bear::universe::speed_type(0, 0));
        }

      start_model_action("wait");
    }
  else if ( m_scan )
    scan_players();
} // ghost::progress_come_back()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state control.
*/
void ptb::ghost::progress_control
( bear::universe::time_type elapsed_time )
{
  if ( get_center_of_mass().distance
       (m_origin.get_center_of_mass()) > m_max_distance )
    start_model_action("come_back");
} // ghost::progress_control()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state wait.
*/
void ptb::ghost::progress_wait( bear::universe::time_type elapsed_time )
{
  scan_players();
} // ghost::progress_wait()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start fly state.
*/
void ptb::ghost::start_fly()
{ 
  player_proxy p = util::find_player( get_level_globals(), 1 );

  if( p != NULL )
    create_fly_movement(p);
  else
    {
      p = util::find_player( get_level_globals(), 2 );
      
      if( p != NULL )
	create_fly_movement(p);
    }
  
  m_progress = &ghost::progress_fly;
} // ghost::start_fly()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start appear state.
*/
void ptb::ghost::start_appear()
{
  m_progress = &ghost::progress_appear;
} // ghost::start_appear()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start come_back state.
*/
void ptb::ghost::start_come_back()
{
  m_scan = false;
  m_progress = &ghost::progress_come_back;
  if ( m_player != NULL )
    release_player();
  m_player = player_proxy();

  create_come_back_movement();
} // ghost::start_come_back()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start control state.
*/
void ptb::ghost::start_control()
{
  m_progress = &ghost::progress_control;

  if ( has_forced_movement() )
    clear_forced_movement();

  control_player();
} // ghost::start_control()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start wait state.
*/
void ptb::ghost::start_wait()
{
  m_progress = &ghost::progress_wait;
} // ghost::start_wait()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to scan.
*/
void ptb::ghost::start_scan()
{
  m_scan = true;
} // ghost::start_scan()

/*----------------------------------------------------------------------------*/
/**
 * \brief Scan players.
*/
bool ptb::ghost::scan_players()
{
  bool result(true);

  const double r = (double)rand() / RAND_MAX;
  if ( r < 0.5 )
    {
      if ( !scan_player(1) )
        result = scan_player(2);
    }
  else if ( !scan_player(2) )
    result = scan_player(1);
  else
    result = false;

  return result;
} // ghost::scan_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Scan a player.
 * \param index Player index to scan.
*/
bool ptb::ghost::scan_player(unsigned int index)
{
  bool found(false);
  player_proxy p = util::find_player( get_level_globals(), index );

  if( p != NULL )
    if ( ( get_center_of_mass().distance( p.get_center_of_mass() ) <=
           m_scan_distance ) &&
         ( p.get_center_of_mass().distance(m_origin.get_center_of_mass()) <
           m_fly_distance ) )
      {
       	if ( get_current_action_name() == "wait" )
	  start_model_action("appear");
        else
	  start_model_action("fly");
	found = true;
      }

  return found;
} // ghost::scan_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the origin reference.
*/
void ptb::ghost::set_origin()
{
  m_origin.set_center_of_mass(get_center_of_mass());
} // ghost::set_origin()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give a string representation of the item.
 * \param str (out) The result of the convertion.
*/
void ptb::ghost::to_string( std::string& str ) const
{
  std::ostringstream oss;

  super::to_string(str);

  oss << "state: " << get_current_action_name() << "\n";
  oss << "origin_position: " << m_origin.get_center_of_mass().x << " " <<
    m_origin.get_center_of_mass().y << "\n";
  oss << "scan: " << m_scan << "\n";

  str += oss.str();
} // ghost::to_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief Control the current player.
*/
void ptb::ghost::control_player()
{
  // do nothing
} // ghost::control_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Release the current player.
*/
void ptb::ghost::release_player()
{
  // do nothing
} // ghost::release_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the movement in fly state.
 * \param p The founded player.
*/
void ptb::ghost::create_fly_movement(player_proxy& p)
{
  bear::universe::forced_stay_around mvt;

  mvt.set_reference_point_on_center(*(p.get_player_instance()));
  mvt.set_max_angle( 0.2 );
  mvt.set_speed( 300 );
  mvt.set_max_distance(50);

  set_forced_movement( mvt );
} // ghost::create_fly_movement()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the movement in come_back state.
*/
void ptb::ghost::create_come_back_movement()
{
  bear::universe::forced_join mvt;

  mvt.set_reference_point_on_center(m_origin);
  mvt.set_total_time(3);

  set_forced_movement( mvt );
} // ghost::create_come_back_movement()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
*/
void ptb::ghost::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::ghost, start_fly, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::ghost, start_appear, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::ghost, start_come_back, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::ghost, start_control, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::ghost, start_wait, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::ghost, start_scan, void );
} // ghost::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::ghost )
