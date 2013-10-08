/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item that creates a border around the layer and dies.
 * \author Julien Jorge
 */
#ifndef __PTB_LAYER_BORDER_HPP__
#define __PTB_LAYER_BORDER_HPP__

#include "engine/base_item.hpp"

#include "generic_items/class_export.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that creates a border around the layer and dies.
   *
   * The fields of this item are
   *  - \a block_width: (real) \c the width of the blocks (default = 100).
   *
   * \author Julien Jorge
   */
  class layer_border:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(layer_border);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    layer_border();

    bool set_real_field( const std::string& name, double value );
    bool is_valid() const;

    void build();

  private:
    void create_margins();

    void create_top_margin
    ( const claw::math::coordinate_2d<unsigned int>& screen_size );
    void create_bottom_margin
    ( const claw::math::coordinate_2d<unsigned int>& screen_size );

    void create_vertical_margin
    ( bear::universe::size_type h, bear::universe::coordinate_type x,
      const std::string& solid_side ) const;

    void new_align_block
    ( bear::universe::size_type x, bear::universe::coordinate_type y,
      bear::universe::size_type width, bear::universe::size_type height,
      const std::string& solid_side ) const;

    void new_margin_block
    ( bear::universe::coordinate_type x, bear::universe::coordinate_type y,
      bear::universe::size_type width, bear::universe::size_type height,
      base_item& block ) const;

  private:
    /** \brief The width of the blocks. */
    bear::universe::size_type m_block_width;

  }; // class layer_border
} // namespace ptb

#endif // __PTB_LAYER_BORDER_HPP__
