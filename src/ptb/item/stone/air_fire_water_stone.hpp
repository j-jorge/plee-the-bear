/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a stone with air, fire and water powers..
 * \author Sébastien Angibaud
 */
#ifndef __PTB_AIR_FIRE_WATER_STONE_HPP__
#define __PTB_AIR_FIRE_WATER_STONE_HPP__

#include "ptb/item/stone/stone.hpp"

namespace ptb
{
  /**
   * \brief The class describing a stone with air, fire and water powers.
   * \author Sébastien Angibaud
   */
  class air_fire_water_stone:
    public stone
  {
    DECLARE_BASE_ITEM(air_fire_water_stone);

  public:
    /** \brief The type of the parent class. */
    typedef stone super;

  public:
    air_fire_water_stone();

    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );
    virtual void kill();

    virtual bool has_air_power() const;
    virtual bool has_fire_power() const;
    virtual bool has_water_power() const;

  private:
    void search_enemy();
    void blast();
    void create_stone
    ( monster::attack_type power, bear::universe::speed_type& speed );

  private:
    /* \brief Indicates if an enemy is found. */
    bool m_enemy_found;

    /* \brief The last position. */
    bear::universe::position_type m_last_position;

    /* \brief The number of iterations without movement. */
    unsigned int m_idle_iterations;

    /** \brief The distance under which the stone detect an enemy. */
    static const double s_view_distance;
  }; // class air_fire_water_stone
} // namespace ptb

#endif // __PTB_AIR_FIRE_WATER_STONE_HPP__
