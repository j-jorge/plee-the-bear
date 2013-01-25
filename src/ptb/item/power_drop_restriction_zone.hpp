/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A zone in which Plee cannot drop a given power.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_POWER_DROP_RESTRICTION_ZONE_HPP__
#define __PTB_POWER_DROP_RESTRICTION_ZONE_HPP__

#include "engine/base_item.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief  A zone in which Plee cannot drop a given power.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *  - \a air: (bool) Indicates if the air power is restricted,
   *    (default = false),
   *  - \a fire: (bool) Indicates if the fire power is restricted,
   *    (default = false),
   *  - \a water: (bool) Indicates if the water power is restricted,
   *    (default = false),
   *
   * \author Sebastien Angibaud
   */
  class power_drop_restriction_zone:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(power_drop_restriction_zone);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    power_drop_restriction_zone();

    void set_powers_restriction(bool air, bool fire, bool water);
    bool set_bool_field( const std::string& name, bool value );

  private:
     void collision_check_and_apply
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    virtual void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    /** \brief Indicates if a player can drop the air power. */
    bool m_air;

    /** \brief Indicates if a player can drop the fire power. */
    bool m_fire;

    /** \brief Indicates if a player can drop the water power. */
    bool m_water;
  }; // class power_drop_restriction_zone
} // namespace ptb

#endif // __PTB_POWER_DROP_RESTRICTION_ZONE_HPP__
