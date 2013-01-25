/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a ghost that steals corrupting_bonus.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_THIEF_GHOST_HPP__
#define __PTB_THIEF_GHOST_HPP__

#include "ptb/item/castle/ghost.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a ghost that steals corrupting_bonus.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class thief_ghost:
    public ghost
  {
    DECLARE_BASE_ITEM(thief_ghost);

  public:
    /** \brief The type of the parent class. */
    typedef ghost super;

  public:
    thief_ghost();
    ~thief_ghost();

    void pre_cache();
    void on_enters_layer();

  private:
    void progress_control( bear::universe::time_type elapsed_time );

  protected:
    void control_player();

  }; // class thief_ghost
} // namespace ptb

#endif // __PTB_THIEF_GHOST_HPP__
