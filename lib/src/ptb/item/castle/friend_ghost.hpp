/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a ghost that desactivates specific walls
 * if it possess a player.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_FRIEND_GHOST_HPP__
#define __PTB_FRIEND_GHOST_HPP__

#include "ptb/item/castle/ghost.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a ghost that desactivates specific walls
   * if it possess a player.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class friend_ghost:
    public ghost
  {
    DECLARE_BASE_ITEM(friend_ghost);

  public:
    /** \brief The type of the parent class. */
    typedef ghost super;

  public:
    friend_ghost();
    ~friend_ghost();

    void pre_cache();
    void on_enters_layer();

  protected:
    void control_player();
  }; // class friend_ghost
} // namespace ptb

#endif // __PTB_FRIEND_GHOST_HPP__
