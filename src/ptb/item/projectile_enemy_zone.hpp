/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a projectile_enemy_zone.hpp.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_PROJECTILE_ENEMY_ZONE_HPP__
#define __PTB_PROJECTILE_ENEMY_ZONE_HPP__

#include "engine/base_item.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a object when a player speak
   *         when a player go in the zone.
   * \author Sébastien Angibaud
   * The valid fields for this item are
   *  - \a projectile_model: (string) \b [required] The model of the projectile,
   *  - \a projectile_number: (unsigned int) The number of projectile,
   *       if 0, the number is infinity,  (default = 0),
   *  - \a projectile_animation: (animation) \b the animation of
   *       projectile creation,
   *  - any field supported by the parent classes.
   */
  class projectile_enemy_zone:
    public bear::engine::basic_renderable_item< bear::engine::base_item >
  {
    DECLARE_BASE_ITEM(projectile_enemy_zone);

  public:
    /** \brief The type of the parent class. */
    typedef
    bear::engine::basic_renderable_item< bear::engine::base_item > super;

  public:
    projectile_enemy_zone();

    void progress( bear::universe::time_type elapsed_time );

    bool set_string_field
    ( const std::string& name, const std::string& value );
    bool set_u_integer_field
    ( const std::string& name, unsigned int value );
    bool set_animation_field
    ( const std::string& name, const bear::visual::animation& value );

    bool is_valid() const;
    void get_visual( std::list<bear::engine::scene_visual>& visuals ) const;

  private:
    void collision_check_monster
    ( bear::engine::base_item& that, bear::universe::collision_info& info );
    void create_projectile();
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    /** \brief The model of the projectile. */
    std::string m_projectile_model;

    /** \brief The animation played when the projectile is create. */
    bear::visual::animation m_animation;

    /** \brief The number of projectiles that zone has. */
    unsigned int m_projectile_number;

    /** \brief Indicates if all projectile has been lost. */
    bool m_is_finished;

  }; // class projectile_enemy_zone
} // namespace ptb

#endif // __PTB_PROJECTILE_ENEMY_ZONE_HPP__
