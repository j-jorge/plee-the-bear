/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A target for stone in jet stone mini-game.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_STONE_TARGET_HPP__
#define __PTB_STONE_TARGET_HPP__

#include "ptb/item_brick/monster_item.hpp"
#include "engine/base_item.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A target for stone in jet stone mini-game.
   *
   * The valid fields for this item are
   *
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class stone_target:
    public monster_item
    < bear::engine::basic_renderable_item<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(stone_target);

  public:
    /** \brief The type of the parent class. */
    typedef
    monster_item
    < bear::engine::basic_renderable_item<bear::engine::base_item> > super;

  public:
    stone_target();

    void pre_cache();
    bool set_animation_field
    ( const std::string& name, const bear::visual::animation& value );
    void progress( bear::universe::time_type elapsed_time );
    void on_enters_layer();
    void get_visual( std::list<bear::engine::scene_visual>& visuals ) const;
    virtual void kill();

  private:
     void collision_check_and_apply
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    virtual void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void create_floating_score();
    unsigned int get_stone_target(bool hit) const;
    void create_decoration();

  protected:
    bool get_defensive_power
    ( unsigned int index, const monster& attacker,
        bear::universe::zone::position side ) const;

  private:
    /** \brief Indicates if the target has been hit. */
    bool m_hit;

    /** \brief The animation to display when the target is not hit. */
    bear::visual::animation m_starting_animation;

    /** \brief The animation to display when the target is hit. */
    bear::visual::animation m_hit_animation;

    /** \brief The current animation. */
    bear::visual::animation* m_current_animation;

    /** \brief Indicates if the target has been visible. */
    bool m_started;
  }; // class stone_target
} // namespace ptb

#endif // __PTB_STONE_TARGET_HPP__
