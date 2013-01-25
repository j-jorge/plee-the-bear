/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a item that speaks from the beginning.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_GOSSIPY_ITEM_HPP__
#define __PTB_GOSSIPY_ITEM_HPP__

#include "ptb/item_brick/item_that_speaks.hpp"
#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a item that speaks from the beginning.
   * \author Sébastien Angibaud
   */
  class gossipy_item:
    public item_that_speaks<bear::engine::base_item>
  {
    DECLARE_BASE_ITEM(gossipy_item);

  }; // class gossipy_item
} // namespace ptb

#endif // __PTB_GOSSIPY_ITEM_HPP__
