/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This item corrupts a boss.
 * \author Julien Jorge
 */
#ifndef __PTB_CORRUPTING_ITEM_HPP__
#define __PTB_CORRUPTING_ITEM_HPP__

#include "engine/base_item.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/item_brick/item_with_decoration.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief This item corrupts a boss.
   *
   * The custom fields of this item are:
   * - any field supported by the parent class.
   *
   * \author Julien Jorge
   */
  class corrupting_item:
    public bear::engine::item_with_decoration
  < bear::engine::basic_renderable_item<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(corrupting_item);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item<bear::engine::base_item> > super;

  public:
    corrupting_item( double amount = 0 );

    double get_amount() const;
    void set_amount( double a );

    void progress( bear::universe::time_type elapsed_time );

  private:
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    /** \brief The amount of curruption passed to the boss. */
    double m_amount;

  }; // class corrupting_item
} // namespace ptb

#endif // __PTB_CORRUPTING_ITEM_HPP__
