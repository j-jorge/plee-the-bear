/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Information about stones that Plee can throw.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_STONE_THROWABLE_ITEM_HPP__
#define __PTB_STONE_THROWABLE_ITEM_HPP__

#include "ptb/player_proxy.hpp"

#include "ptb/throwable_item/throwable_item.hpp"

namespace ptb
{
  /**
   * \brief Informations about stones that Plee can throw.
   *
   * \author Sebastien Angibaud
   */
  class stone_throwable_item
    : public throwable_item
  {
  public:
    typedef throwable_item super;

  public:
    stone_throwable_item(const player_proxy& p);

    bear::engine::base_item* create_throwable_item() const;
    void decrease_stock() const;
    unsigned int get_stock() const;
    bool can_throw() const;
    std::string get_animation() const;

  private:
    bear::engine::base_item* create_air_water_stone() const;
    unsigned int get_required_stones() const;

  private:
    /** \brief The pointer on the player. */
    const player_proxy m_player;

  }; // class stone_throwable_item
} // namespace ptb

#endif // __PTB_STONE_THROWABLE_ITEM_HPP__
