/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This item kill the player on collision.
 * \author Julien Jorge
 */
#ifndef __PTB_PLAYER_KILLER_HPP__
#define __PTB_PLAYER_KILLER_HPP__

#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief This item kill the player on collision.
   *
   * This class has no custom field.
   *
   * \author Julien Jorge
   */
  class player_killer:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(player_killer);

  public:
    typedef bear::engine::base_item super;

  private:
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  }; // class player_killer
} // namespace ptb

#endif // __PTB_PLAYER_KILLER_HPP__
