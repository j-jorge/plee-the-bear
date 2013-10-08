/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::corrupting_item_throwable_item class.
 * \author Julien Jorge
 */
#include "ptb/throwable_item/corrupting_item_throwable_item.hpp"

#include "ptb/game_variables.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 * \param anim The animation of the throwable item.
 * \param ref An example of the item to throw.
 * \param ratio The amount of corrupting bonus used per each unit of the amount
 *        of ref.
 */
ptb::corrupting_item_throwable_item::corrupting_item_throwable_item
( const std::string& anim, const corrupting_item& ref, double ratio )
  : throwable_item("corrupting_item", true), m_animation(anim),
    m_reference(ref), m_ratio(ratio)
{

} // corrupting_item_throwable_item::corrupting_item_throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the throwable_item.
 */
bear::engine::base_item*
ptb::corrupting_item_throwable_item::create_throwable_item() const
{
  return m_reference.clone();
} // throwable_item::create_throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Decrease the stock.
 */
void ptb::corrupting_item_throwable_item::decrease_stock() const
{
  const unsigned int c = game_variables::get_corrupting_bonus_count();
  const double s = m_reference.get_amount() * m_ratio;

  if ( c >= s )
    game_variables::set_corrupting_bonus_count( c - s );
  else
    game_variables::set_corrupting_bonus_count(0);
} // throwable_item::decrease_stock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the stock.
 */
unsigned int ptb::corrupting_item_throwable_item::get_stock() const
{
  return game_variables::get_corrupting_bonus_count();
} // corrupting_item_throwable_item::get_stock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if Plee can throw this throwable_item.
 */
bool ptb::corrupting_item_throwable_item::can_throw() const
{
  return get_stock() >= m_reference.get_amount();;
}// corrupting_item_throwable_item::can_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the animation of the throwable_item.
 */
std::string ptb::corrupting_item_throwable_item::get_animation() const
{
  return m_animation;
} // corrupting_item_throwable_item::get_animation()
