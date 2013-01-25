/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::sting class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/forest/sting.hpp"

#include "engine/game.hpp"
#include "engine/world.hpp"
#include "generic_items/decorative_item.hpp"

BASE_ITEM_IMPLEMENT( sting, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::sting::sting()
  : m_is_dead(false)
{
  set_size( 26, 26 );

  m_monster_type = monster::enemy_monster;
  m_energy = s_sting_energy;
  m_offensive_force = s_sting_offensive_force;
  m_defensive_powers[normal_attack] = true;
  m_offensive_coefficients[indefensible_attack] = 1;
  set_mass(0);

  set_system_angle_as_visual_angle(true);
} // sting::sting()

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::sting::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor(get_level_globals().get_model("model/forest/sting.cm"));
  start_model_action("attack");
} // sting::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::sting::progress( bear::universe::time_type elapsed_time )
{
  if ( m_is_dead )
    {
      bear::decorative_item* item = new bear::decorative_item;

      item->set_animation( get_level_globals().get_animation
                           ("animation/forest/wasp/sting_explosion.canim") );
      item->set_bottom_left(get_bottom_left());
      item->get_rendering_attributes().set_angle
        (get_rendering_attributes().get_angle());

      item->set_kill_when_finished(true);

      new_item( *item );

      CLAW_ASSERT( item->is_valid(),
                   "The explosion of sting isn't correctly initialized" );

      kill();
    }
  else if ( has_contact() )
    m_is_dead = true;
  else
    super::progress( elapsed_time );
} // sting::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief The item has attacked.
 * \param other The monster that is attacked.
 */
void ptb::sting::has_attacked(const monster& other)
{
  m_is_dead = true;
} // sting::has_attacked()

/*---------------------------------------------------------------------------*/
/**
 * \brief Inform the item tat he left the active region.
 */
void ptb::sting::leaves_active_region()
{
  super::leaves_active_region();

  kill();
} // sting::leaves_active_region()
