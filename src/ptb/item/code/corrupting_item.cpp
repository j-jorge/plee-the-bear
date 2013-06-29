/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::corrupting_item class.
 * \author Julien Jorge
 */
#include "ptb/item/corrupting_item.hpp"

#include "ptb/item_brick/boss.hpp"

BASE_ITEM_EXPORT( corrupting_item, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 * \param amount The amount of corruption passed to the boss.
 */
ptb::corrupting_item::corrupting_item( double amount )
  : m_amount(amount)
{
  set_can_move_items(false);
  set_mass(1);
} // corrupting_item::corrupting_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the amount of corruption.
 */
double ptb::corrupting_item::get_amount() const
{
  return m_amount;
} // corrupting_item::get_amount()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the amount of corruption.
 * \param a The amount of corruption.
 */
void ptb::corrupting_item::set_amount( double a )
{
  m_amount = a;
} // corrupting_item::set_amount()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item.
 * \param elapsed_time The elapsed time since the last call.
 */
void ptb::corrupting_item::progress( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);

  if ( has_contact() )
    kill();
} // corrupting_item::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Collision with an other item.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::corrupting_item::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  super::collision( that, info );

  boss* b = dynamic_cast<boss*>(&that);

  if ( b != NULL )
    {
      b->corrupt(m_amount);
      kill();
    }
} // corrupting_item::collision()
