/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Information about corrupting items that Plee can throw.
 * \author Julien Jorge
 */
#ifndef __PTB_CORRUPTING_ITEM_THROWABLE_ITEM_HPP__
#define __PTB_CORRUPTING_ITEM_THROWABLE_ITEM_HPP__

#include "ptb/item/corrupting_item.hpp"
#include "ptb/throwable_item/throwable_item.hpp"

namespace ptb
{
  /**
   * \brief Informations about corrupting_items that Plee can throw.
   * \author Julien Jorge
   */
  class corrupting_item_throwable_item:
    public throwable_item
  {
  public:
    typedef throwable_item super;

  public:
    corrupting_item_throwable_item
    ( const std::string& anim, const corrupting_item& ref, double ratio );

    bear::engine::base_item* create_throwable_item() const;
    void decrease_stock() const;
    unsigned int get_stock() const;
    bool can_throw() const;
    std::string get_animation() const;

  private:
    /** \brief The name of the animation of the throwable. */
    const std::string m_animation;

    /** \brief The item to throw. */
    const corrupting_item m_reference;

    /** \brief The amount of corrupting bonus used per each unit of the amount
        of ref. */
    const double m_ratio;

  }; // class corrupting_item_throwable_item
} // namespace ptb

#endif // __PTB_CORRUPTING_ITEM_THROWABLE_ITEM_HPP__
