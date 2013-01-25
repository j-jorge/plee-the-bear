/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a wall that is desactivated when a friend
 * ghost possess a player.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_FRIEND_BLOCK_HPP__
#define __PTB_FRIEND_BLOCK_HPP__

#include "ptb/item/castle/friend_ghost.hpp"
#include "universe/derived_item_handle.hpp"
#include "generic_items/block.hpp"
#include "engine/export.hpp"
#include <set>

namespace ptb
{
  /**
   * \brief The class describing a block that is desactivated when a friend
   * ghost possess a player.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class friend_block:
    public bear::block
  {
    DECLARE_BASE_ITEM(friend_block);

  public:
    /** \brief The type of the parent class. */
    typedef bear::block super;

    /** \brief The type of the item handle. */
    typedef bear::universe::derived_item_handle< friend_ghost > item_handle;

  public:
    friend_block();
    ~friend_block();

    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );
    bool set_item_field( const std::string& name, base_item* value );
    bool is_valid() const;

  private:
    /* \brief The friend ghost. */
    item_handle m_friend_ghost;
  }; // class friend_block
} // namespace ptb

#endif // __PTB_FRIEND_BLOCK_HPP__
