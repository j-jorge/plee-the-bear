/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item that adds point according to the remaining time.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_BONUS_TIME_HPP__
#define __PTB_BONUS_TIME_HPP__

#include "ptb/item/bonus_points/bonus_points.hpp"
#include "generic_items/timer.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that adds point according to the remaining time.
   *
   * The valid fields for this item are
   *  - level_timer:
   *   \c (item) The timer to use.
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class bonus_time:
    public bonus_points
  {
    DECLARE_BASE_ITEM(bonus_time);

  public:
    /** \brief The type of the parent class. */
    typedef bonus_points super;

  private:
    /** \brief The type of a handle on a timer. */
    typedef bear::universe::const_derived_item_handle<bear::timer> timer_handle;

  public:
    bonus_time();

    bool is_valid() const;
    void build();

    bool
    set_item_field( const std::string& name, bear::engine::base_item* value );
    bool set_u_integer_field( const std::string& name, unsigned int value );

  private:
    /** \brief The timer used to compute the time bonuses. */
    timer_handle m_timer;

    /** \brief The number of points given by each remaining second. */
    unsigned int m_points_per_second;

  }; // class bonus_time
} // namespace ptb

#endif // __PTB_BONUS_TIME_HPP__
