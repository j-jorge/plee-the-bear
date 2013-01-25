/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::throwable_item class.
 * \author Sebastien Angibaud
 */
#include "ptb/throwable_item/throwable_item.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 * \param name The name of this item.
 * \param always_visible Tell if the item is visible even with no stock.
 */
ptb::throwable_item::throwable_item
( const std::string& name, bool always_visible )
  : m_name(name), m_always_visible(always_visible)
{

} // throwable_item::throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::throwable_item::~throwable_item()
{

} // throwable_item::~throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if Plee can throw this throwable_item.
 */
bool ptb::throwable_item::can_throw() const
{
  return get_stock() > 0;
}// throwable_item::can_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if this throwable_item has not must be hidden.
 */
bool ptb::throwable_item::is_empty() const
{
  return !can_throw() && !m_always_visible;
}// throwable_item::is_empty()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the name of the throwable item.
 */
const std::string& ptb::throwable_item::get_name() const
{
  return m_name;
}// throwable_item::get_name()
