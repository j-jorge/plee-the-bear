/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item with a single sprite.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_ITEM_THAT_SPEAKS_HPP__
#define __PTB_ITEM_THAT_SPEAKS_HPP__

#include "engine/comic/item/item_that_speaks.hpp"

namespace ptb
{
  /**
   * \brief An item that speaks.
   *
   * \b template \b parameters :
   * - \a Base : the base class for this item. Must inherit from
   *    bear::engine::base_item,
   * \author Sebastien Angibaud
   */
  template<class Base>
  class item_that_speaks:
    public bear::engine::item_that_speaks<Base>
  {
    typedef bear::engine::item_that_speaks<Base> super;

  public:
    item_that_speaks();

    void pre_cache();
    void build();

  }; // class item_that_speaks
} // namespace ptb

#include "ptb/item_brick/impl/item_that_speaks.tpp"

#endif // __PTB_ITEM_THAT_SPEAKS_HPP__
