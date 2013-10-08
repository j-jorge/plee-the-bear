/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A bonus given to the player when colliding with him.
 * \author Julien Jorge
 */
#ifndef __PTB_FREE_BONUS_HPP__
#define __PTB_FREE_BONUS_HPP__

#include "ptb/item_brick/base_bonus.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A bonus given to the player when colliding with him..
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Julien Jorge
   */
  class free_bonus:
    public base_bonus
  {
    DECLARE_BASE_ITEM(free_bonus);

  public:
    /** \brief The type of the parent class. */
    typedef base_bonus super;

  public:
    free_bonus();
    void pre_cache();

  private:
    void collision_check_and_apply
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void do_set_type(base_bonus_type t);

  }; // class free_bonus
} // namespace ptb

#endif // __PTB_FREE_BONUS_HPP__
