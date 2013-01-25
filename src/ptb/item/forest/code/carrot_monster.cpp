/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::carrot_monster class.
 * \author S�bastien Angibaud
 */
#include "ptb/item/forest/carrot_monster.hpp"

#include "engine/game.hpp"
#include "engine/world.hpp"
#include "generic_items/decorative_item.hpp"

BASE_ITEM_IMPLEMENT( carrot_monster, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::carrot_monster::carrot_monster()
: m_progress(NULL)
{
  m_monster_type = monster::enemy_monster;
  set_energy(1);
  m_offensive_force = 5;
  m_offensive_phase = false;
  m_defensive_powers[normal_attack] = true;
  m_defensive_powers[air_attack] = true;
  m_defensive_powers[fire_attack] = true;
  m_defensive_powers[water_attack] = true;

  set_mass(std::numeric_limits<double>::infinity());
  set_global(true);
  set_friction(1);

  set_system_angle_as_visual_angle(true);
} // carrot_monster::carrot_monster()

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::carrot_monster::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor
    ( get_level_globals().get_model("model/forest/carrot_monster.cm") );
  start_model_action("appear");
} // carrot_monster::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::carrot_monster::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  if ( m_progress != NULL )
    (this->*m_progress)(elapsed_time);
} // carrot_monster::progress()

/*---------------------------------------------------------------------------*/
/**
 * \brief Inform the item that he leaves the active region.
 */
void ptb::carrot_monster::leaves_active_region()
{
  super::leaves_active_region();

  kill();
} // carrot_monster::leaves_active_region()

/*----------------------------------------------------------------------------*/
/**
 * Tell if the value returned by get_attack_point() is meaningful.
 */
bool ptb::carrot_monster::has_attack_point() const
{
  return false;
} // carrot_monster::has_attack_point()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to attack.
 */
void ptb::carrot_monster::start_attack()
{
  set_mass(1);
  m_offensive_coefficients[indefensible_attack] = 1;
  m_offensive_phase = true;

  m_progress = &carrot_monster::progress_attack;
} // carrot_monster::start_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to crush.
 */
void ptb::carrot_monster::start_crush()
{
  set_mass( std::numeric_limits<double>::infinity() );
  add_position_constraint_x();
  add_position_constraint_y();
  m_offensive_phase = false;

  m_progress = NULL;
} // carrot_monster::start_crush()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the attack.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::carrot_monster::progress_attack
( bear::universe::time_type elapsed_time )
{
  if ( has_side_contact() )
    {
      start_model_action("crush");
      m_progress = NULL;
    }
  else
    {
      add_internal_force( bear::universe::force_type(5000, 0) );

      if ( has_owner() )
        add_external_force( -get_owner().get_gravity() );
    }
} // carrot_monster::progress_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::carrot_monster::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( carrot_monster, start_attack, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( carrot_monster, start_crush, void );
} // carrot_monster::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::carrot_monster )
