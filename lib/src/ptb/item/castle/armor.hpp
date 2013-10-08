/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing an armor.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_ARMOR_HPP__
#define __PTB_ARMOR_HPP__

#include "ptb/item_brick/counted_enemy.hpp"
#include "ptb/item_brick/monster.hpp"
#include "ptb/player_proxy.hpp"
#include "engine/model.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing an armor.
   *
   * The valid fields for this item are
   *  - \a distance: The maximum possible distance with start position
   * (default=200).
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class armor:
    public counted_enemy< bear::engine::model<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(armor);

  public:
    /** \brief The type of the parent class. */
    typedef counted_enemy
    < bear::engine::model<bear::engine::base_item> > super;
    
    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)
      
  private:
    typedef void ( armor::*progress_function_type)(bear::universe::time_type);

  public:
    armor();
    ~armor();
    
    void pre_cache();
    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );
    bool set_real_field( const std::string& name, double value );
    
  protected:
    void inform_no_energy(const monster& attacker);
    void leaves_active_region();

  private:
    std::string get_picture_filename() const;
    std::string get_picture_name() const;
    std::string get_notification_text() const;
    
    void progress_idle( bear::universe::time_type elapsed_time );
    void progress_wake_up( bear::universe::time_type elapsed_time );
    void progress_attack( bear::universe::time_type elapsed_time );
    void progress_punch( bear::universe::time_type elapsed_time );
    void progress_walk( bear::universe::time_type elapsed_time );
    void progress_dead( bear::universe::time_type elapsed_time );

    void start_idle();
    void start_wake_up();
    void start_attack();
    void start_punch();
    void start_walk();
    void start_dead();
    void create_axe();
    void create_head(bool right_orientation);

    bool scan
    (bear::universe::coordinate_type distance, bool only_main_direction);
    bool scan_for_player
    ( const player_proxy& p, bool left_orientation,
      bear::universe::coordinate_type distance ) const;
    bool scan_no_wall_in_direction
    ( const bear::universe::position_type& origin,
      const bear::universe::vector_type& dir,
      bear::universe::coordinate_type distance ) const;
    void on_hand_collision
    ( bear::engine::base_item& mark, bear::engine::base_item& that,
      bear::universe::collision_info& info );
    void on_head_collision
    ( bear::engine::base_item& mark, bear::engine::base_item& that,
      bear::universe::collision_info& info );

  protected:
    void to_string( std::string& str ) const;

  private:
    static void init_exported_methods();

  private:
    /** \brief The energy of the soul of an armor.*/
    static const unsigned int s_soul_energy;

    /** \brief The distance under which the armor scans to trow axe.*/
    static const unsigned int s_scan_axe_distance;

    /** \brief The distance under which the armor scans in wait state.*/
    static const unsigned int s_scan_wait_distance;

    /** \brief The distance under which the armor scans for punch.*/
    static const unsigned int s_scan_punch_distance;

    /** \brief Current progress function. */
    progress_function_type m_progress;

    /** \brief The position of the origin. */
    bear::universe::position_type m_origin_position;

    /** \brief The maximum possible distance with origin position. */
    bear::universe::coordinate_type m_max_distance;

    /** \brief The force given during walk state. */
    bear::universe::force_type m_walk_force;

    /** \brief Indicates if armor has its axe. */
    bool m_has_axe;

    /** \brief Indicates if armor has its head. */
    bool m_has_head;
  }; // class armor
} // namespace ptb

#endif // __PTB_ARMOR_HPP__
