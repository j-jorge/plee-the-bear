/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Information about honeypots that Plee can throw.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_WATER_HONEYPOT_THROWABLE_ITEM_HPP__
#define __PTB_WATER_HONEYPOT_THROWABLE_ITEM_HPP__

#include "ptb/player_proxy.hpp"

#include "ptb/throwable_item/throwable_item.hpp"

namespace ptb
{
  /**
   * \brief Information about honeypots that Plee can throw.
   *
   * \author Sebastien Angibaud
   */
  class water_honeypot_throwable_item
    : public throwable_item
  {
  public:
    typedef throwable_item super;

  public:
    explicit water_honeypot_throwable_item(const player_proxy& p);

    bear::engine::base_item* create_throwable_item() const;
    bool can_throw() const;
    void decrease_stock() const;
    unsigned int get_stock() const;
    std::string get_animation() const;

  private:
    /** \brief The pointer on the player. */
    const player_proxy m_player;

  }; // class water_honeypot_throwable_item
} // namespace ptb

#endif // __PTB_WATER_HONEYPOT_THROWABLE_ITEM_HPP__
