/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::stone class.
 * \author S�bastien Angibaud
 */
#include "ptb/item/stone/stone.hpp"
#include "ptb/item/air_bubble.hpp"
#include "ptb/message/status_layer_notification_message.hpp"
#include "ptb/defines.hpp"
#include "ptb/level_variables.hpp"

#include "engine/world.hpp"

#include <libintl.h>

BASE_ITEM_EXPORT( stone, ptb )

int ptb::stone::s_lost_stone_count = 0;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::stone::stone()
  : m_lost(true), m_counted(true)
{
  set_friction(0.98);
  set_mass(1);
  set_density(2);
  set_z_fixed(false);
  set_size(16, 16);
  set_weak_collisions(false);

  m_monster_type = monster::stone_monster;
  m_energy = 1;
  m_offensive_force = 10;
  m_offensive_coefficients[normal_attack] = 1;
  
  set_system_angle_as_visual_angle(true);
} // stone::stone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::stone::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor(get_level_globals().get_model("model/stones/stone.cm"));
  start_model_action("attack");
} // stone::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::stone::progress( bear::universe::time_type elapsed_time )
{
  if ( has_contact() )
    kill();
  else
    {
      rotate();
      default_progress(elapsed_time);
    }
} // stone::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief The item has attacked.
 * \param other The monster that is attacked.
 */
void ptb::stone::has_attacked(const monster& other)
{
  if ( m_counted )
    m_lost = false;

  check_traitor(other);  

  kill();
} // stone::has_attacked()

/*----------------------------------------------------------------------------*/
/**
 * \brief The item has attacked a non monster item.
 */
void ptb::stone::has_attacked()
{
  if ( m_counted )
    m_lost = false;

  kill();
} // stone::has_attacked()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item tat he left the active region.
 */
void ptb::stone::leaves_active_region()
{
  super::leaves_active_region();

  kill();
} // stone::leaves_active_region()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item that he have no energy now.
 */
void ptb::stone::inform_no_energy(const monster& attacker)
{
  if ( m_counted )
    m_lost = false;

  kill();
} // stone::inform_no_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Kill the item.
 * \pre m_owner != NULL
 */
void ptb::stone::kill()
{
  if ( is_only_in_environment(bear::universe::water_environment) )
    create_bubble();

  if ( m_counted && 
       ( ( get_monster_index() == 1 ) || ( get_monster_index() == 2 ) ) )
    {
      if ( m_lost )
	s_lost_stone_count++ ;
      else
	s_lost_stone_count--;

      if ( s_lost_stone_count > 4 )
	{
	  send_notification( gettext("Stone's waster") );
	  s_lost_stone_count = 0;
	}
      else if ( s_lost_stone_count < -4 )
	{
	  send_notification( gettext("Marskman") );
	  s_lost_stone_count = 0;
	}
    }

  super::kill();
} // stone::kill()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform that a new stone is create.
 */
void ptb::stone::inform_new_stone()
{

} // stone::inform_new_stone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the stone has the air power.
 */
bool ptb::stone::has_air_power() const
{
  return false;
} // stone::has_air_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the stone has the fire power.
 */
bool ptb::stone::has_fire_power() const
{
  return false;
} // stone::has_fire_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the stone has the water power.
 */
bool ptb::stone::has_water_power() const
{
  return false;
} // stone::has_water_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if the stone must be counted.
 * \param value The new value.
 */
void ptb::stone::set_counted_state(bool value)
{
  m_counted = value;
} // stone::set_counted_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the stone attack the other player.
 * \param other The monster that is attacked.
 */
void ptb::stone::check_traitor(const monster& other)
{
  if ( ( other.get_monster_type() == monster::player_monster ) &&
       ( ! level_variables::get_friendly_fire( get_level() ) ) )
    {
      status_layer_notification_message msg;
      
      bear::visual::sprite sp;
      msg.set_notification
	( get_monster_index(), sp, gettext("snake in the grass"));
      
      get_level_globals().send_message
	( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
    }
} // stone::check_traitor()

/*----------------------------------------------------------------------------*/
/**
 * \brief Rotate the stone.
 */
void ptb::stone::rotate()
{
  double delta = 0.05;

  if ( is_in_environment(bear::universe::water_environment) )
    delta = 0.01;

  if ( get_speed().x >= 0 )
    delta *= -1;

  get_rendering_attributes().set_angle
    ( get_rendering_attributes().get_angle() + delta );
} // stone::rotate()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do the default progress of a stone.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::stone::default_progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );
} // stone::default_progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a star to show a hit.
 * \param that The item being attacked by this.
 */
void ptb::stone::create_hit_star( const bear::engine::base_item& that ) const
{
  super::create_hit_star
    ( get_center_of_mass(), get_rendering_attributes().get_angle() );
} // stone::create_hit_star()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a bubble.
 */
void ptb::stone::create_bubble()
{
  air_bubble* new_bubble;

  new_bubble= new air_bubble();
  new_bubble->set_z_position(get_z_position() + 1);
  new_bubble->set_center_of_mass(get_center_of_mass());
  new_bubble->set_oxygen(2000);
  new_item( *new_bubble );
} // stone::create_bubble()

/*----------------------------------------------------------------------------*/
/**
 * \brief Send a notification.
 */
void ptb::stone::send_notification(const std::string& text) const
{
  status_layer_notification_message msg;

  bear::visual::sprite sp;
  msg.set_notification( get_monster_index(), sp, text);

  get_level_globals().send_message
    ( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
} // stone::send_notification()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::stone::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::stone, kill, void );
} // stone::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::stone )
