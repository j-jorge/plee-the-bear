/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item that adds points if the boss has been killed.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_BONUS_BOSS_HPP__
#define __PTB_BONUS_BOSS_HPP__

#include "ptb/item/bonus_points/bonus_points.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that adds points if the boss has been killed.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class bonus_boss:
    public bonus_points
  {
    DECLARE_BASE_ITEM(bonus_boss);

  public:
    /** \brief The type of the parent class. */
    typedef bonus_points super;

  public:
    bonus_boss();

    void build();

  private:
    bool check() const;

  private:
    /* \brief Indicates if the boss has already been killed. */
    bool m_already_killed;
  }; // class bonus_boss
} // namespace ptb

#endif // __PTB_BONUS_BOSS_HPP__
