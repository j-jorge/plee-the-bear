/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the attack_point_reference_point class.
 * \author Julien Jorge
 */
#include "ptb/reference_point/attack_point_reference_point.hpp"

#include "ptb/item_brick/with_attack_point.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param item The item of which the attack point is returned.
 */
ptb::attack_point_reference_point::attack_point_reference_point
( bear::universe::physical_item& item )
  : m_item(item)
{

} // attack_point_reference_point::attack_point_reference_point()

/*----------------------------------------------------------------------------*/
/**
 * \brief Duplicate this instance.
 */
bear::universe::base_reference_point*
ptb::attack_point_reference_point::clone() const
{
  return new attack_point_reference_point(*this);
} // attack_point_reference_point::clone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if this reference is usable.
 */
bool ptb::attack_point_reference_point::is_valid() const
{
  return has_item() && m_item->has_attack_point();
} // attack_point_reference_point::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the center of mass of the item.
 */
bear::universe::position_type
ptb::attack_point_reference_point::get_point() const
{
  CLAW_PRECOND( has_item() );
  return m_item->get_attack_point();
} // attack_point_reference_point::get_point()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is still valid.
 */
bool ptb::attack_point_reference_point::has_item() const
{
  return m_item != (with_attack_point*)NULL;
} // attack_point_reference_point::has_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the item of which the center of mass is returned.
 */
bear::universe::physical_item&
ptb::attack_point_reference_point::get_item() const
{
  CLAW_PRECOND( has_item() );
  return *m_item.get_item();
} // attack_point_reference_point::get_item()
