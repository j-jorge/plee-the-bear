/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An item that restore the last level pushed in the engine.
 * \author Julien Jorge
 */
#ifndef __PTB_LEVEL_POPPER_HPP__
#define __PTB_LEVEL_POPPER_HPP__

#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that restore the last level pushed in the engine.
   *
   * - \a fade_duration: real, the duration of the fading effect before starting
   *   the level (default = 1),
   * - \a transition_layer_name: string, the name of the transition layer
   *   receiving the fade effect (default = none).
   * - any field supported by the parent class.
   *
   * \sa level_pusher
   * \author Julien Jorge
   */
  class level_popper:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(level_popper);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    level_popper();
    void destroy();

    void progress( bear::universe::time_type elapsed_time );
    bool set_string_field( const std::string& name, const std::string& value );
    bool set_real_field( const std::string& name, double value );

  private:
    void collision_check_and_apply
    ( bear::engine::base_item& that, bear::universe::collision_info& info );
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );
    void start_fading();
    std::string get_string_from_vars( const std::string& name ) const;

  private:
    /** \brief How many players are colliding with this item. */
    std::size_t m_players_count;

    /** \brief Tell if the level has been popped. */
    bool m_applied;

   /** \brief The name of the transition layer receiving the fade effect. */
    std::string m_transition_layer_name;

    /** \brief The duration of the fading. */
    bear::universe::time_type m_fade_duration;

    /** \brief The time elapsed since the creation of the item. */
    bear::universe::time_type m_time;

    /** \brief The identifier of the fading effect. */
    std::size_t m_effect_id;
  }; // class level_popper
} // namespace ptb

#endif // __PTB_LEVEL_POPPER_HPP__
