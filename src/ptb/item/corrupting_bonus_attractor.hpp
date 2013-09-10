/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item that attracts corrupting_bonus items.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_CORRUPTING_BONUS_ATTRACTOR_HPP__
#define __PTB_CORRUPTING_BONUS_ATTRACTOR_HPP__

#include "engine/base_item.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that attracts corrupting_bonus items.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class corrupting_bonus_attractor:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(corrupting_bonus_attractor);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    corrupting_bonus_attractor();
    ~corrupting_bonus_attractor();

  private:
    virtual void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  }; // class corrupting_bonus_attractor
} // namespace ptb

#endif // __PTB_CORRUPTING_BONUS_ATTRACTOR_HPP__
