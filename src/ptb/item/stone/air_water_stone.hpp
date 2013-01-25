/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a stone with the air and water powers.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_AIR_WATER_STONE_HPP__
#define __PTB_AIR_WATER_STONE_HPP__

#include "ptb/item/stone/air_stone.hpp"

namespace ptb
{
  /**
   * \brief The class describing a stone with the air and water powers.
   * \author Sébastien Angibaud
   */
  class air_water_stone:
    public air_stone
  {
   DECLARE_BASE_ITEM(air_water_stone);

  public:
    /** \brief The type of the parent class. */
    typedef air_stone super;

  public:
    air_water_stone();

    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );
    virtual void inform_new_stone();
    virtual bool has_water_power() const;

  protected:
    virtual void create_decorations();
    virtual void initialize_intensity();

  private:
    /* \brief The last position of the item. */
    bear::universe::position_type m_last_position;

    /* \brief The number of iterations without move. */
    unsigned int m_iteration_without_move;
  }; // class air_water_stone
} // namespace ptb

#endif // __PTB_AIR_WATER_STONE_HPP__
