/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An item that gives bonus if players use different exits.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_BONUS_EXITS_HPP__
#define __PTB_BONUS_EXITS_HPP__

#include "ptb/item/bonus_points/bonus_points.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that gives bonus if players use different exits.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class bonus_exits:
    public bonus_points
  {
    DECLARE_BASE_ITEM(bonus_exits);

  public:
    /** \brief The type of the parent class. */
    typedef bonus_points super;

  public:
    bonus_exits();

    void build();
    bool different_exits();
    void on_give_points() const;
  }; // class bonus_exits
} // namespace ptb

#endif // __PTB_BONUS_EXITS_HPP__
