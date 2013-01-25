/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A spring gives a force to the items colliding with him.
 * \author Julien Jorge
 */
#ifndef __PTB_SPRING_HPP__
#define __PTB_SPRING_HPP__

#include "engine/base_item.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/item_brick/item_with_decoration.hpp"
#include "engine/item_brick/activable_sides.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A spring gives a force to the items colliding with him.
   *
   * The valid fields for this item are
   *  - \a applied_force_x: (real) the force applied on the x-axis
   *    (default = 0),
   *  - \a applied_force_y: (real) the force applied on the y-axis
   *    (default = 0),
   *  - any field supported by the parent classes.
   *
   * When the spring is not active, the last frame of the animation is
   * displayed.
   *
   * \author Julien Jorge
   */
  class spring:
    public bear::engine::item_with_decoration
  < bear::engine::basic_renderable_item<bear::engine::base_item> >,
    public bear::engine::activable_sides
  {
    DECLARE_BASE_ITEM(spring);

  public:
    /** \brief The type of the parent class. */
    typedef
    bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item<bear::engine::base_item> > super;

  public:
    spring();

    bool set_real_field( const std::string& name, double value );

    void build();

  protected:
    void populate_loader_map( bear::engine::item_loader_map& m );

    void collision_check_and_bounce
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    /** \brief The force applied to the item. */
    bear::universe::force_type m_applied_force;

  }; // class spring
} // namespace ptb

#endif // __PTB_SPRING_HPP__
