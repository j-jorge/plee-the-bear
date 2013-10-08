/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::soul class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/soul.hpp"
#include "ptb/player_proxy.hpp"
#include "engine/export.hpp"

#include "universe/forced_movement/forced_translation.hpp"
#include "universe/physical_item_state.hpp"
#include "universe/world.hpp"

BASE_ITEM_EXPORT( soul, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::soul::soul()
{
  m_energy = 0;

  set_phantom(true);
  set_can_move_items(false);
  set_mass(1);
  set_density(0.0009);
  set_friction(1);
} // soul::soul()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::soul::~soul()
{
} // soul::soul()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::soul::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy other(&that);

  if (other != NULL)
    {
      other.receive_energy(m_energy);
      m_energy = 0;
      kill();
    }
} // soul::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the energy of the soul.
 * \param energy The new energy of the soul.
 */
void ptb::soul::set_energy( double energy )
{
  m_energy = energy;
} // soul::set_energy()

/*---------------------------------------------------------------------------*/
/**
 * \brief Inform the item tat he left the active region.
 */
void ptb::soul::leaves_active_region()
{
  super::leaves_active_region();

  kill();
} // ptb::soul::leaves_active_region()
