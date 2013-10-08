/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item that adds points if all enemies are dead.
 * \author Julien Jorge
 */
#ifndef __PTB_BONUS_CARNAGE_HPP__
#define __PTB_BONUS_CARNAGE_HPP__

#include "ptb/item/bonus_points/bonus_all_dead.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that adds points if all enemies are dead.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Julien Jorge
   */
  class bonus_carnage:
    public bonus_all_dead
  {
    DECLARE_BASE_ITEM(bonus_carnage);

  private:
    /** \brief The type of the parent class. */
    typedef bonus_all_dead super;

  public:
    bonus_carnage();
  }; // class bonus_carnage
} // namespace ptb

#endif // __PTB_BONUS_CARNAGE_HPP__
