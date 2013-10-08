/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a gorilla.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_GORILLA_HPP__
#define __PTB_GORILLA_HPP__

#include "ptb/item_brick/counted_enemy.hpp"
#include "ptb/item_brick/monster.hpp"
#include "ptb/player_proxy.hpp"
#include "engine/model.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a gorilla.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class gorilla:
    public counted_enemy< bear::engine::model<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(gorilla);

  public:
    /** \brief The type of the parent class. */
    typedef counted_enemy
    < bear::engine::model<bear::engine::base_item> > super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

    /** \brief The offensive_force of a gorilla.*/
    static const unsigned int s_gorilla_offensive_force = 10;

  private:
    typedef void (gorilla::*progress_function_type)(bear::universe::time_type);

  public:
    gorilla();
    ~gorilla();

    void pre_cache();
    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );

  protected:
    void inform_no_energy(const monster& attacker);
    void leaves_active_region();
    void injure
    ( const monster& attacker, bear::universe::zone::position side,
      double duration);
    void has_attacked(const monster& other);
    bool get_defensive_power_by_side
    ( unsigned int index, const monster& attacker,
        bear::universe::zone::position side ) const;
    unsigned int get_offensive_coefficient
    ( unsigned int index, const monster& other,
      bear::universe::zone::position side ) const;

  private:
    std::string get_picture_filename() const;
    std::string get_picture_name() const;
    std::string get_notification_text() const;

    void progress_idle( bear::universe::time_type elapsed_time );
    void progress_attack( bear::universe::time_type elapsed_time );
    void progress_angry( bear::universe::time_type elapsed_time );
    void progress_dead( bear::universe::time_type elapsed_time );
    void progress_scan_left( bear::universe::time_type elapsed_time );
    void progress_scan_right( bear::universe::time_type elapsed_time );
    void progress_come_back( bear::universe::time_type elapsed_time );

    void start_idle();
    void start_attack();
    void start_angry();
    void start_dead();
    void start_scan_left();
    void start_scan_right();
    void start_scan();
    void start_come_back();

    bool listen();
    bool scan( bool left_orientation,
               bear::universe::coordinate_type distance ) const;
    bool scan_for_player
    ( const player_proxy& p, bool left_orientation,
      bear::universe::coordinate_type distance ) const;
    bool scan_no_wall_in_direction
    ( const bear::universe::position_type& origin,
      const bear::universe::vector_type& dir,
      bear::universe::coordinate_type distance ) const;

    void choose_angry_action();
    void hit();

    unsigned int get_offensive_coefficient_attack
    ( unsigned int index, const monster& other,
      bear::universe::zone::position side ) const;
    unsigned int get_offensive_coefficient_angry
    ( unsigned int index, const monster& other,
      bear::universe::zone::position side ) const;
    unsigned int get_offensive_coefficient_come_back
    ( unsigned int index, const monster& other,
      bear::universe::zone::position side ) const;

  protected:
    void to_string( std::string& str ) const;

  private:
    static void init_exported_methods();

  private:
    /** \brief The energy of the soul of a gorilla.*/
    static const unsigned int s_soul_energy;

    /** \brief The distance under which the gorilla listen.*/
    static const unsigned int s_listen_distance;

    /** \brief Current progress function. */
    progress_function_type m_progress;

    /** \brief The position of the origin. */
    bear::universe::position_type m_origin_position;

    /** \brief Indicates if the gorilla want to come back. */
    bool m_want_come_back;

    /** \brief Indicates if the gorilla want to scan. */
    bool m_want_scan;

    /** \brief The distance under which the gorilla scan.*/
    unsigned int m_scan_distance;
  }; // class gorilla
} // namespace ptb

#endif // __PTB_GORILLA_HPP__
