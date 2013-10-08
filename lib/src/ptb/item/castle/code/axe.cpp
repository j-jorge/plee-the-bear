/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::axe class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/castle/axe.hpp"

#include "engine/game.hpp"
#include "engine/world.hpp"
#include "generic_items/decorative_item.hpp"

BASE_ITEM_IMPLEMENT( axe, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::axe::axe()
  : m_progress(NULL)
{
  m_monster_type = monster::enemy_monster;
  set_energy(1);
  m_offensive_phase = true;
  set_stone_vulnerability(false);
  m_offensive_force = 20;
  m_offensive_coefficients[indefensible_attack] = 1;
  m_defensive_powers[normal_attack] = true;
  m_defensive_powers[air_attack] = true;
  m_defensive_powers[fire_attack] = true;
  m_defensive_powers[water_attack] = true;

  set_mass(10);
  set_global(true);
  set_friction(1);

  set_system_angle_as_visual_angle(true);
} // axe::axe()

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::axe::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor
    ( get_level_globals().get_model("model/castle/axe.cm") );
  start_model_action("attack");
} // axe::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::axe::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  if ( m_progress != NULL )
    (this->*m_progress)(elapsed_time);
} // axe::progress()

/*---------------------------------------------------------------------------*/
/**
 * \brief Inform the item that he leaves the active region.
 */
void ptb::axe::leaves_active_region()
{
  super::leaves_active_region();

  kill();
} // axe::leaves_active_region()

/*----------------------------------------------------------------------------*/
/**
 * Tell if the value returned by get_attack_point() is meaningful.
 */
bool ptb::axe::has_attack_point() const
{
  return false;
} // axe::has_attack_point()

/*----------------------------------------------------------------------------*/
/**
 * \brief The item has attacked.
 * \param other The monster that is attacked.
 */
void ptb::axe::has_attacked(const monster& other)
{
  m_offensive_phase = false;
  m_offensive_force = 0;

  super::has_attacked(other);
} // axe::has_attacked()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to attack.
 */
void ptb::axe::start_attack()
{
  m_progress = &axe::progress_attack;
} // axe::start_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to idle.
 */
void ptb::axe::start_idle()
{
  m_progress = &axe::progress_idle;
} // axe::start_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the attack.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::axe::progress_attack
( bear::universe::time_type elapsed_time )
{
  if ( has_bottom_contact() )
    {
      m_offensive_phase = false;
      m_offensive_force = 0;
      set_speed( bear::universe::speed_type(0, 0) );
      set_internal_force(bear::universe::force_type(0, 0));
      set_external_force(bear::universe::force_type(0, 0));
      set_mass(std::numeric_limits<double>::infinity());
      start_model_action("idle");
    }
  else
    {
      if (get_speed().x > 0 )
        get_rendering_attributes().set_angle
          ( get_rendering_attributes().get_angle() - 0.3 );
      else
        get_rendering_attributes().set_angle
          ( get_rendering_attributes().get_angle() + 0.3 );
    }
} // axe::progress_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the idle.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::axe::progress_idle
( bear::universe::time_type elapsed_time )
{
  // do nothing
} // axe::progress_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::axe::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( axe, start_attack, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( axe, start_idle, void );
} // axe::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::axe )
