/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a air bubble.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_AIR_BUBBLE_HPP__
#define __PTB_AIR_BUBBLE_HPP__

#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a air bubble.
   * \author Sébastien Angibaud
   */
  class air_bubble:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(air_bubble);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    air_bubble();

    void progress( bear::universe::time_type elapsed_time );
    void get_visual( std::list<bear::engine::scene_visual>& visuals ) const;
    void pre_cache();
    void build();
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );
    void set_oxygen(double oxygen);
    void give_max_size();
    void leaves_active_region();
    void update_size( bear::universe::time_type elapsed_time );

  private:
    /** \brief The oxygen quantity of the air_bubble. */
    double m_oxygen;

    /** \brief The max_size according its oxygen capacity. */
    double m_max_size;

    /** \brief The animation of the halo. */
    bear::visual::sprite m_sprite;

    /** \brief The maximum size of the bubble. */
    static const bear::universe::size_type s_max_size;

    /** \brief The minimu size of the bubble. */
    static const bear::universe::size_type s_min_size;

    /** \brief The oxygen in a maximal bubble. */
    static const double s_oxygen_in_max_size;
  }; // class air_bubble
} // namespace ptb

#endif // __PTB_AIR_BUBBLE_HPP__
