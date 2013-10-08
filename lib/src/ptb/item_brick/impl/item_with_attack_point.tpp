/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::item_with_attack_point class.
 * \author Sébastien Angibaud
 */
#include "engine/base_item.hpp"

/*----------------------------------------------------------------------------*/
/**
 * Return the prefered position where this item can be attacked.
 */
template<class Base>
bear::universe::position_type
ptb::item_with_attack_point<Base>::get_attack_point() const
{
  return this->get_center_of_mass();
} // item_with_attack_point::get_attack_point()

/*----------------------------------------------------------------------------*/
/**
 * Tell if the value returned by get_attack_point() is meaningful.
 */
template<class Base>
bool ptb::item_with_attack_point<Base>::has_attack_point() const
{
  return true;
} // item_with_attack_point::has_attack_point()

