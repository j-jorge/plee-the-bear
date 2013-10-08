/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A kicker.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_KICKER_HPP__
#define __PTB_KICKER_HPP__

#include "engine/base_item.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/item_brick/item_with_decoration.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A kicker.
   *
   * The valid fields for this item are
   *  - \a applied_force: (real) the force applied on the y-axis
   *    (default = 0),
   *  - \a left_fixed: (bool) Indicates if the item is fixed on the left,
   *    (default = false),
   *  - \a animation: (animation) \b [required] the animation played when the
   *    kicker is activated,
   *  - \a decorative_item: (item) \b the item generated when the kicker is
   *    activated,
   *  - \a decorative_instances: (unsigned integer) \b how many times the
   *    decorative item will be re-generated,
   *  - any field supported by the parent classes.
   *
   * When the kicker is not active, the last frame of the animation is
   * displayed.
   *
   * \author Sebastien Angibaud
   */
  class kicker:
    public bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(kicker);

  public:
    /** \brief The type of the parent class. */
    typedef
    bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item<bear::engine::base_item> > super;

  public:
    kicker();

    bool set_u_integer_field( const std::string& name, unsigned int value );
    bool set_real_field( const std::string& name, double value );
    bool set_bool_field( const std::string& name, bool value );
    bool set_item_field
    ( const std::string& name, bear::engine::base_item* value );

    void build();

  protected:
    void collision_check_and_bounce
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    /** \brief The force applied to the item. */
    bear::universe::force_type m_applied_force;

    /** \brief Indicates if the item the item is fixed on the left. */
    bool m_left_fixed;

    /** \brief The item created on activation. */
    bear::engine::base_item* m_decorative_item;

    /** \brief How many remaining instances of the decorative item will be
        generated. */
    unsigned int m_decorative_instances;

  }; // class kicker
} // namespace ptb

#endif // __PTB_KICKER_HPP__
