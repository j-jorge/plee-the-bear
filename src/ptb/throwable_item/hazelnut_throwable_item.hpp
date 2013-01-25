/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Information about hazelnuts that Plee can throw.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_AZELNUT_THROWABLE_ITEM_HPP__
#define __PTB_AZELNUT_THROWABLE_ITEM_HPP__

#include "ptb/player_proxy.hpp"

#include "ptb/throwable_item/throwable_item.hpp"

namespace ptb
{
  /**
   * \brief Informations about hazelnut that Plee can throw.
   *
   * \author Sebastien Angibaud
   */
  class hazelnut_throwable_item
    : public throwable_item
  {
  public:
    typedef throwable_item super;

  public:
    /** \brief The name of hazelnut_throwable_item. */
    static const std::string s_name;

  public:
    hazelnut_throwable_item(const player_proxy& p);

    bear::engine::base_item* create_throwable_item() const;
    void decrease_stock() const;
    unsigned int get_stock() const;
    std::string get_animation() const;

  private:
    /** \brief The pointer on the player. */
    const player_proxy m_player;

  }; // class hazelnut_throwable_item
} // namespace ptb

#endif // __PTB_AZELNUT_THROWABLE_ITEM_HPP__
