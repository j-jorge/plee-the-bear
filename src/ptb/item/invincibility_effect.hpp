/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item that displays an effect to illustrate the invincibility of a
 *        player.
 * \author Julien Jorge
 */
#ifndef __PTB_INVINCIBILITY_EFFECT_HPP__
#define __PTB_INVINCIBILITY_EFFECT_HPP__

#include "engine/base_item.hpp"
#include "engine/export.hpp"

#include "ptb/player_proxy.hpp"

namespace ptb
{
  /**
   * \brief An item that displays an effect to illustrate the invincibility of a
   *        player.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Julien Jorge
   */
  class invincibility_effect:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(invincibility_effect);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    invincibility_effect( player_proxy player_index );

    void build();

  private:
    void create_star();
    void create_remanent_traces() const;

  private:
    /** \brief The player to which the effect is applied. */
    player_proxy m_player;

    /** The identifier of the music played during the invincibility. */
    std::size_t m_music_id;
 
  }; // class invincibility_effect
} // namespace ptb

#endif // __PTB_INVINCIBILITY_EFFECT_HPP__
