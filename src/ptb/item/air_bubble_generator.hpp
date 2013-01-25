/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a generator of air bubble.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_AIR_BUBBLE_GENERATOR_HPP__
#define __PTB_AIR_BUBBLE_GENERATOR_HPP__

#include "engine/base_item.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/item_brick/item_with_decoration.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a generator of air bubble.
   * \author Sébastien Angibaud
   *  - \a oxygen_sequence:
   *  \c (list of double) (required) The sequence of oxygen capacity,
   *  - \a duration_sequence:
   *  \c (list of double) (required) The sequence of duration,
   *  - \a duration_decorative_sequence:
   *  \c (list of double) The sequence of duration for decorative bubble,
   */
  class air_bubble_generator:
    public bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(air_bubble_generator);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item<bear::engine::base_item> > super;

  public:
    air_bubble_generator();

    void progress( bear::universe::time_type elapsed_time );
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    bool set_real_list_field
    ( const std::string& name, const std::vector<double>& value );
    bool is_valid() const;

  private:
    void create_bubble();
    void create_decorative_bubble();

  private:
    /** \brief The sequence of oxygen quantity. */
    std::vector<double> m_oxygen_sequence;

    /** \brief The duration sequence. */
    std::vector<double> m_duration_sequence;

    /** \brief The duration sequence for decorative bubbles. */
    std::vector<double> m_duration_decorative_sequence;

    /** \brief The duration since the last bubble. */
    bear::universe::time_type m_last_bubble;

    /** \brief The duration since the last decorative bubble. */
    bear::universe::time_type m_last_decorative_bubble;

    /** \brief The current index in the oxygen sequence. */
    unsigned int m_index_oxygen;

    /** \brief The current index in the duration sequence. */
    unsigned int m_index_duration;

    /** \brief The current index in the duration sequence
     * for decorative bubbles. */
    unsigned int m_index_decorative_duration;

    /** \brief Indicates if the item is activated. */
    bool m_activated;
  }; // class air_bubble_generator
} // namespace ptb

#endif // __PTB_AIR_BUBBLE_GENERATOR_HPP__
