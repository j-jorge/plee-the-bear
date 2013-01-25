/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An item that gives bonus if players discover cooperation area.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_BONUS_COOPERATION_HPP__
#define __PTB_BONUS_COOPERATION_HPP__

#include "ptb/item/bonus_points/bonus_all_dead_by_category.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that gives bonus if players discover cooperation area.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class bonus_cooperation:
    public bonus_all_dead_by_category
  {
    DECLARE_BASE_ITEM(bonus_cooperation);

  public:
    /** \brief The type of the parent class. */
    typedef bonus_all_dead_by_category super;

  public:
    bonus_cooperation();

    void build();
  }; // class bonus_cooperation
} // namespace ptb

#endif // __PTB_BONUS_COOPERATION_HPP__
