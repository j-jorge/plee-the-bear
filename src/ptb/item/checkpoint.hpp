/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Save the position of the player.
 * \author Julien Jorge
 */
#ifndef __PTB_CHECKPOINT_HPP__
#define __PTB_CHECKPOINT_HPP__

#include "ptb/item_brick/sniffable.hpp"

#include "engine/item_brick/basic_renderable_item.hpp"
#include "ptb/item/save_player_position.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief Tell the player to save its position. The position given to the
   *        player, as a reference position, is the center of mass of the
   *        checkpoint.
   *
   * This item has no field.
   *
   * \author Julien Jorge
   */
  class checkpoint:
    public bear::engine::basic_renderable_item<save_player_position>,
    public sniffable
  {
    DECLARE_BASE_ITEM(checkpoint);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::basic_renderable_item<save_player_position> super;

  public:
    checkpoint();

    void pre_cache();
    void build();

    void progress( bear::universe::time_type elapsed_time );
    void get_visual( std::list<bear::engine::scene_visual>& visuals ) const;

  private:
    void activate();
    void reactivate();

  private:
    /** \brief The animation of the checkpoint. */
    bear::visual::animation m_animation;

  }; // class checkpoint
} // namespace ptb

#endif // __PTB_CHECKPOINT_HPP__
