/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A headstone appears when a monster is killed.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_HEADSTONE_HPP__
#define __PTB_HEADSTONE_HPP__

#include "engine/base_item.hpp"
#include "engine/model.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A headstone appears when a monster is killed.
   * \author Sébastien Angibaud
   */
  class headstone:
    public bear::engine::model<bear::engine::base_item>
  {
    DECLARE_BASE_ITEM(headstone);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::model<bear::engine::base_item> super;

  public:
    headstone();

    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );
    bool is_valid() const;

    void set_soul_energy(double soul_energy);
    void set_soul_animation( const bear::visual::animation& value );

  private:
    void create_soul() const;

  private:
    /** \brief Indicates if the soul has appeared. */
    bool m_soul_has_appeared;

    /** \brief The energy of the soul. */
    double m_soul_energy;

    /** \brief The soul animation. */
    bear::visual::animation m_soul_animation;

    /** \brief Indicates the time when headstone appears. */
    bear::universe::time_type m_time_start;

    /** \brief The time over which the soul appears.*/
    static const bear::universe::time_type s_time_to_appear;

  }; // class headstone
} // namespace ptb

#endif // __PTB_HEADSTONE_HPP__
