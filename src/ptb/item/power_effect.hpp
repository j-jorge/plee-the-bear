/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An item that displays an effect to illustrate the powers of a player.
 * \author Julien Jorge
 */
#ifndef __PTB_POWER_EFFECT_HPP__
#define __PTB_POWER_EFFECT_HPP__

#include "engine/base_item.hpp"
#include "engine/export.hpp"

#include "universe/forced_movement/forced_rotation.hpp"

#include <claw/smart_ptr.hpp>
#include <boost/signals.hpp>

namespace ptb
{
  /**
   * \brief An item that displays an effect to illustrate the powers of a
   *        player.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Julien Jorge
   */
  class power_effect:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(power_effect);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  private:
    typedef
    std::list< claw::memory::smart_ptr<boost::signals::scoped_connection> >
    signal_connection_list;

  public:
    power_effect();

    void pre_cache();
    void set_player_index( unsigned int i );

    virtual void get_dependent_items
    ( std::list<bear::universe::physical_item*>& d ) const;

  private:
    void connect( const boost::signals::connection& c );

    std::size_t get_powers_count() const;

    bear::engine::base_item* create_power_item( const std::string& anim ) const;
    void show_change_effect
    ( const bear::visual::color& fill_color,
      const bear::visual::color& border_color );

    void apply_movement( bear::engine::base_item& item );

    void apply_movement_1( bear::engine::base_item& item );
    void apply_movement_2( bear::engine::base_item& item );
    void apply_movement_3( bear::engine::base_item& item );

    bear::engine::base_item* get_first_power() const;
    bear::engine::base_item* get_second_power() const;

    bear::universe::forced_rotation create_forced_movement();

    void add_air_effect();
    void remove_air_effect();

    void add_fire_effect();
    void remove_fire_effect();

    void add_water_effect();
    void remove_water_effect();

    void on_air_power_changed( bool v );
    void on_fire_power_changed( bool v );
    void on_water_power_changed( bool v );

  private:
    /** The connections to the signals triggered when the powers change. */
    signal_connection_list m_signals;

    /** The item representing the power of air. */
    bear::engine::base_item* m_air;

    /** The item representing the power of fire. */
    bear::engine::base_item* m_fire;

    /** The item representing the power of water. */
    bear::engine::base_item* m_water;

  }; // class power_effect
} // namespace ptb

#endif // __PTB_POWER_EFFECT_HPP__
