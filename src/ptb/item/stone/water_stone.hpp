/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a stone with water power.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_WATER_STONE_HPP__
#define __PTB_WATER_STONE_HPP__

#include "ptb/item/stone/stone.hpp"

namespace ptb
{
  /**
   * \brief The class describing a stone with water power.
   * \author Sébastien Angibaud
   */
  class water_stone:
    public stone
  {
    DECLARE_BASE_ITEM(water_stone);

  public:
    /** \brief The type of the parent class. */
    typedef stone super;

  public:
    water_stone();

    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );
    virtual bool has_water_power() const;

  private:
    /* \brief The last position of the item. */
    bear::universe::position_type m_last_position;

    /* \brief The number of iterations without move. */
    unsigned int m_iteration_without_move;
  }; // class water_stone
} // namespace ptb

#endif // __PTB_WATER_STONE_HPP__
