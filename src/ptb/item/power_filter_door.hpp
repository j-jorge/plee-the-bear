/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A door with power restriction. Ple must be have a given power to go
 *        throw the door.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_POWER_FILTER_DOOR_HPP__
#define __PTB_POWER_FILTER_DOOR_HPP__

#include "engine/base_item.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/item_brick/item_with_decoration.hpp"
#include "engine/export.hpp"

namespace ptb
{
  class player_proxy;
  class stone;

  /**
   * \brief A door with power restriction. Ple must be have a given power to go
   *        throw the door.
   *
   * The valid fields for this item are
   *  - \a type: (string) \b [required] the type of the bonus
   *      - "air_power"
   *      - "fire_power"
   *      - "water_power"
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class power_filter_door:
    public bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(power_filter_door);

  public:
    /** \brief The type of the parent class. */
    typedef
    bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item<bear::engine::base_item> > super;

     enum player_status
      {
        not_here = 0,
        collised,
        move_left,
        want_move_left,
        move_right,
        want_move_right
      }; // enum player_status


     enum door_type
      {
        unknown_type = 0,
        air_door,
        fire_door,
        water_door
      }; // enum attack_type

  public:
    power_filter_door();

    void pre_cache();
    void build();
    void progress( bear::universe::time_type elapsed_time );
    bool set_string_field
    ( const std::string& name, const std::string & value );
    bool set_bool_field
    ( const std::string& name, bool value );

  private:
     void collision_check_and_apply
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    virtual void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void create_decoration
    ( bear::universe::collision_info& info, bool push_up );
    bool check_power_of_stone( stone* s ) const;
    bool check_power_of_player( unsigned int index ) const;
    void update_player_status
    (unsigned int index,
     player_status& status, bear::universe::position_type& pos);
    void apply_collision_player
    ( bear::engine::base_item& that, bear::universe::collision_info& info,
      const player_proxy& p, player_status& status,
      bear::universe::position_type& pos );
    void apply_collision_stone
    ( bear::engine::base_item& that, bear::universe::collision_info& info,
      stone* s );
    void create_small_honeypot
    (player_status status, const bear::universe::position_type& pos);
    void create_power_restriction_zone();

  private:
    /** \brief The power of the door. */
    door_type m_door_type;

    /** \brief The status of the first player. */
    player_status m_first_player_status;

    /** \brief The status of the second player. */
    player_status m_second_player_status;

    /** \brief The last position of the first player. */
    bear::universe::position_type m_first_player_position;

    /** \brief The last position of the second player. */
    bear::universe::position_type m_second_player_position;

    /** \brief Indicates if the door removes the power when a player goes throw
        the door. */
    bool m_remove_power;
  }; // class power_filter_door
} // namespace ptb

#endif // __PTB_POWER_FILTER_DOOR_HPP__
