/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a wasp.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_WASP_HPP__
#define __PTB_WASP_HPP__

#include "ptb/item_brick/counted_enemy.hpp"
#include "ptb/item_brick/monster.hpp"
#include "ptb/player_proxy.hpp"
#include "engine/model.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a wasp.
   * \author Sébastien Angibaud
   * The parameters accepted by this item are:
   * The custom fields of this class are :
   *  - \a fly_duration: duration of a travel.
   *  - \a translation_x: \c The x-coordonate translation,
   *  - \a translation_y: \c The y-coordonate translation.
   */
  class wasp:
    public counted_enemy< bear::engine::model<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(wasp);

  public:

    /** \brief The type of the parent class. */
    typedef counted_enemy
    < bear::engine::model<bear::engine::base_item> > super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

    /** \brief Number of states considered. */
    static const unsigned int states_cardinality = 3;

    /** \brief  The size of the offensive. */
    static const unsigned int s_zone_offensive_width = 200;

    /** \brief The oscillation angle in an iteration.*/
    static const unsigned int s_oscillation_angle = 10;

    /** \brief The offensive_force of a wasp.*/
    static const unsigned int s_wasp_offensive_force = 30;

    /** \brief The energy of the soul of a wasp.*/
    static const unsigned int s_soul_energy = 30;

  private:
    typedef void (wasp::*progress_function_type)(bear::universe::time_type);

  public:
    wasp();

    void pre_cache();
    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );

    bool set_real_field( const std::string& name, double value );

    virtual void inform_no_energy(const monster& attacker);
    void leaves_active_region();
    void set_bottom_contact(bear::universe::physical_item& item);

  private:
    std::string get_picture_filename() const;
    std::string get_picture_name() const;
    std::string get_notification_text() const;

    void progress_fly( bear::universe::time_type elapsed_time );
    void progress_attack( bear::universe::time_type elapsed_time );
    void progress_dead( bear::universe::time_type elapsed_time );

    void start_fly();
    void start_attack();
    void start_dead();

    bool player_in_zone( const bear::universe::position_type& pos ) const;
    void next_position( bear::universe::position_type& origin,
                        bear::universe::position_type& target);
    void oriente();
    void create_sting();
    bool scan_players() const;
    void search_players();

    static void init_exported_methods();

  private:
    /** \brief Current progress function. */
    progress_function_type m_progress;

    /** \brief Indicates if the wasp is in an attack movement. */
    bool m_is_in_attack;

    /** \brief Indicates if the item come back. */
    bool m_come_back;

    /** \brief Indicates the angle of the oscillation. */
    double m_oscillation_angle;

    /** \brief The time until the start of travel. */
    double m_fly_time;

    /** \brief Indicates if the wasp have attacked. */
    bool m_have_attacked;

    /** \brief Indicates if the wasp had a contact. */
    bool m_contact;

    /** \brief Pointer to the first target. */
    bear::universe::position_type m_first_target;

    /** \brief Pointer to the second target. */
    bear::universe::position_type m_second_target;

    /** \brief The way of the wasp. */
    bear::universe::speed_type m_translation;

    /** \brief Indicates the duration of a travel. */
    double m_fly_duration;

    /** \brief The first player. */
    player_proxy m_first_player;

    /** \brief The second player. */
    player_proxy m_second_player;

  }; // class wasp
} // namespace ptb

#endif // __PTB_WASP_HPP__
