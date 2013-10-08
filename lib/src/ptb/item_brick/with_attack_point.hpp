/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The base for items that have an attack point.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_WITH_ATTACK_POINT_HPP__
#define __PTB_WITH_ATTACK_POINT_HPP__

#include "universe/types.hpp"
#include "engine/base_item.hpp"

namespace ptb
{
  /**
   * \brief The base of items that have an attack point.
   */
  class with_attack_point
  {
  public:
    with_attack_point();
    virtual ~with_attack_point();

    /**
     * Return the prefered position where this item can be attacked.
     */
    virtual bear::universe::position_type get_attack_point() const = 0;

    /**
     * Tell if the value returned by get_attack_point() is meaningful.
     */
    virtual bool has_attack_point() const = 0;
  }; // class with_attack_point
} // namespace ptb

#endif // __PTB_WITH_ATTACK_POINT_HPP__
