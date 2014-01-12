/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing  the boss of the forest : a big rabbit.
 * \author S�bastien Angibaud
 */
#ifndef __PTB_BIG_RABBIT_HPP__
#define __PTB_BIG_RABBIT_HPP__

#include "ptb/item_brick/boss.hpp"

#include "engine/export.hpp"

#include "generic_items/reference_item.hpp"

namespace ptb
{
  class clingable;

  /**
   * \brief The class describing the boss of the forest : a big rabbit.
   *
   * The valid fields for this item are
   * - any field supported by the parent classes.
   *
   * \author S�bastien Angibaud
   */
  class big_rabbit:
    public boss
  {
    DECLARE_BASE_ITEM(big_rabbit);

  public:
    /** \brief The type of the parent class. */
    typedef boss super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  private:
    /** \brief The type of the functions used to do the progression of the
        big_rabbit. */
    typedef void
    (big_rabbit::*progress_function_type)(bear::universe::time_type);

    /** \brief The type of an handle on a reference_item. */
    typedef
    bear::universe::derived_item_handle<bear::engine::base_item> handle_type;

    /** \brief The type of a list of reference_item. */
    typedef std::vector<handle_type> handle_list;

    /** \brief The type of the map used to compute the initial speed for the
        jumps. */
    typedef
    std::map<bear::universe::coordinate_type, bear::universe::coordinate_type>
    jump_map_type;

  public:
    big_rabbit();

    void pre_cache();
    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );
    bear::universe::position_type get_attack_point() const;
    bool set_item_list_field
    ( const std::string& name,
      const std::vector<bear::engine::base_item*>& value);

    bool in_second_attack_phase() const;

  protected:
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void get_dependent_items
    ( bear::universe::physical_item::item_list& d ) const;

    virtual void inform_no_energy(const monster& attacker);
    virtual std::string get_bonus_picture_filename() const;
    virtual std::string get_bonus_picture_name() const;

  private:
    void progress_idle( bear::universe::time_type elapsed_time );
    void progress_jump( bear::universe::time_type elapsed_time );
    void progress_fall( bear::universe::time_type elapsed_time );
    void progress_create_carrot( bear::universe::time_type elapsed_time );

    void progress_create_carrot_radial
    ( bear::universe::time_type elapsed_time );

    void progress_self_attack( bear::universe::time_type elapsed_time );
    void progress_dig( bear::universe::time_type elapsed_time );
    void progress_underground( bear::universe::time_type elapsed_time );

    void start_die();
    void start_dead();
    void start_idle();
    void start_fall();
    void start_jump();
    void start_create_carrot();
    void start_self_attack();
    void start_dig();
    void start_underground();
    void finish_underground();
    void start_jump_from_ground();

    void set_progress( progress_function_type f );

    void create_ground_blast() const;

    bear::engine::base_item* create_carrot() const;
    bear::engine::base_item* create_carrot( std::size_t i ) const;
    void create_straight_carrot();
    void create_radial_carrot();
    void create_snout_carrot();

    void jump_on_player();

    void fill_jump_map( bear::universe::time_type t );
    double get_jump_speed( bear::universe::coordinate_type d );

    void jump_to( bear::universe::coordinate_type x );

    bool test_in_sky();
    void adjust_clingable() const;

    bear::engine::base_item* create_piece_of_ground
    ( bear::universe::coordinate_type x, bear::universe::coordinate_type y,
      bear::universe::coordinate_type dx,
      bear::universe::coordinate_type dy ) const;
    void initialize_ground_object
    ( bear::engine::base_item* item, bear::universe::coordinate_type x,
      bear::universe::coordinate_type y, bear::universe::coordinate_type dx,
      bear::universe::coordinate_type dy ) const;
    bear::engine::base_item* create_stone_bonus() const;
    bear::engine::base_item* create_earth_decoration() const;

    void generate_underground_earth() const;

    void on_head_collision
    ( bear::engine::base_item& mark, bear::engine::base_item& that,
      bear::universe::collision_info& info );

    void on_snout_collision
    ( bear::engine::base_item& mark, bear::engine::base_item& that,
      bear::universe::collision_info& info );

    void on_snout_attacked
    ( bear::engine::base_item& mark, bear::engine::base_item& that,
      bear::universe::collision_info& info );

    void on_tooth_collision
    ( bear::engine::base_item& mark, bear::engine::base_item& that,
      bear::universe::collision_info& info );

    static void init_exported_methods();

  private:
    /** \brief Current progress function. */
    progress_function_type m_progress;

    /** \brief The number of created carrot. */
    std::size_t m_carrot_number;

    /** \brief The delta applied to the position of the radial carrots. */
    std::size_t m_carrot_index_delta;

    /** \brief The list of item_reference to set carrot position. */
    handle_list m_carrot_positions;

    /** \brief This map associates a distance with the corresponding initial
        speed to apply to travel this distance. */
    jump_map_type m_jump_map;

    /** \brief The duration of a step of the progress in the current action. */
    bear::universe::time_type m_progress_step;

    /** \brief The elapsed time in the current action. */
    bear::universe::time_type m_elapsed_time;

    /** \brief The clingable attached to the snout. */
    clingable* m_clingable;

    /** \brief The level of earth when underground. */
    bear::universe::size_type m_earth_level;

    /** \brief The increment in the earth level, in units per second. */
    bear::universe::size_type m_earth_level_increment;

    /** \brief The time interval between two update of the earth heap. */
    bear::universe::time_type m_earth_effect_interval;

    /** \brief Tell that the current jump started underground. */
    bool m_jumping_from_underground;

    /** \brief Tell if the rabbit is dead. */
    bool m_dead;

  }; // class big_rabbit
} // namespace ptb

#endif // __PTB_BIG_RABBIT_HPP__
