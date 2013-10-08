/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A small_honeypot.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_SMALL_HONEYPOT_HPP__
#define __PTB_SMALL_HONEYPOT_HPP__

#include "ptb/item_brick/base_bonus.hpp"

namespace ptb
{
  /**
   * \brief A small honeypot.
   *
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class small_honeypot:
    public base_bonus
  {
    DECLARE_BASE_ITEM(small_honeypot);

  public:
    /** \brief The type of the parent class. */
    typedef ptb::base_bonus super;

  public:
    small_honeypot();

    void pre_cache();

  private:
    void collision_check_and_apply
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void do_set_type(base_bonus_type t);

  }; // class small_honeypot
} // namespace ptb

#endif // __PTB_SMALL_HONEYPOT_HPP__
