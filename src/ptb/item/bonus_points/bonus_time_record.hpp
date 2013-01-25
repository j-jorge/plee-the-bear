/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An item that adds point if the level is
 * finished under a record time.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_BONUS_TIME_RECORD_HPP__
#define __PTB_BONUS_TIME_RECORD_HPP__

#include "ptb/item/bonus_points/bonus_points.hpp"
#include "generic_items/timer.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that adds point if the level is
   * finished under a record time.
   *
   * The valid fields for this item are
   *  - time_record:
   *   \c (real) The time record for the level.
   *  - level_timer:
   *   \c (item) The timer to use.
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class bonus_time_record:
    public bonus_points
  {
    DECLARE_BASE_ITEM(bonus_time_record);

  private:
    /** \brief The type of the parent class. */
    typedef bonus_points super;

    /** \brief The type of a handle on a timer. */
    typedef bear::universe::const_derived_item_handle<bear::timer> timer_handle;

  public:
    bonus_time_record();

    bool is_valid() const;
    void build();

    bool
    set_item_field( const std::string& name, bear::engine::base_item* value );
    bool set_real_field( const std::string& name, double value );
    void on_give_points() const;

  private:
    /** \brief The timer used to compute the time bonuses. */
    timer_handle m_timer;

    /** \brief The time under which points are given. */
    bear::universe::time_type m_time_record;

  }; // class bonus_time_record
} // namespace ptb

#endif // __PTB_BONUS_TIME_RECORD_HPP__
