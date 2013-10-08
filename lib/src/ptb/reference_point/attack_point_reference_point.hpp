/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Instances of attack_point_reference_point compute the reference point
 *        of in forced movements as the attack point of an item.
 * \author Julien Jorge
 */
#ifndef __PTB_ATTACK_POINT_REFERENCE_POINT_HPP__
#define __PTB_ATTACK_POINT_REFERENCE_POINT_HPP__

#include "universe/forced_movement/base_reference_point.hpp"
#include "universe/derived_item_handle.hpp"

namespace ptb
{
  class with_attack_point;

  /**
   * \brief Instances of attack_point_reference_point compute the reference
   *        point of in forced movements as the attack point of an item.
   *
   * \author Julien Jorge
   */
  class attack_point_reference_point:
    public bear::universe::base_reference_point
  {
  private:
    /** The type of the handle on the item. */
    typedef bear::universe::derived_item_handle<with_attack_point>
    item_handle_type;

  public:
    explicit attack_point_reference_point
    ( bear::universe::physical_item& item );

    virtual bear::universe::base_reference_point* clone() const;

    virtual bool is_valid() const;
    virtual bear::universe::position_type get_point() const;

    virtual bool has_item() const;
    virtual bear::universe::physical_item& get_item() const;

  private:
    /** The item on which we take the center of mass. */
    item_handle_type m_item;

  }; // class attack_point_reference_point
} // namespace ptb

#endif // __PTB_ATTACK_POINT_REFERENCE_POINT_HPP__
