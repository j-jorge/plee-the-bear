/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An block that blocks only the players.
 * \author Julien Jorge
 */
#ifndef __PTB_PLAYER_STOP_BLOCK_HPP__
#define __PTB_PLAYER_STOP_BLOCK_HPP__

#include "generic_items/block.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An block that blocks only the players.
   * \author Julien Jorge
   */
  class player_stop_block:
    public bear::block
  {
    DECLARE_BASE_ITEM(player_stop_block);

    typedef bear::block super;

  protected:
    void collision_check_player_and_align
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    /** Tell if the player is aligned without setting contacts. */
    bool m_clear_contact;

  }; // class player_stop_block
} // namespace ptb

#endif // __PTB_PLAYER_STOP_BLOCK_HPP__
