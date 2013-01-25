/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a woodpecker.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_WOODPECKER_HPP__
#define __PTB_WOODPECKER_HPP__

#include "ptb/item_brick/counted_enemy.hpp"
#include "ptb/item_brick/monster.hpp"
#include "ptb/player_proxy.hpp"
#include "engine/model.hpp"
#include "generic_items/reference_item.hpp"
#include "universe/forced_movement/forced_rotation.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a woodpecker.
   * \author Sebastien Angibaud
    * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   */
  class woodpecker:
    public counted_enemy< bear::engine::model<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(woodpecker);

  public:
    /** \brief The type of the parent class. */
    typedef counted_enemy
    < bear::engine::model<bear::engine::base_item> > super;

    /** \brief The offensive_force of a woodpecker.*/
    static const unsigned int s_woodpecker_offensive_force = 20;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  private:
    typedef
    void (woodpecker::*progress_function_type)(bear::universe::time_type);

  public:
    woodpecker();
    ~woodpecker();

    void pre_cache();
    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );

  protected:
    virtual void inform_no_energy(const monster& attacker);
    void leaves_active_region();
    virtual void injure
    ( const monster& attacker, bear::universe::zone::position side,
      double duration );
    virtual bool get_defensive_power_by_side
    ( unsigned int index, const monster& attacker,
      bear::universe::zone::position side ) const;
    virtual unsigned int get_offensive_coefficient
    ( unsigned int index, const monster& attacker,
      bear::universe::zone::position side ) const;
    virtual void has_attacked(const monster& other);

  private:
    std::string get_picture_filename() const;
    std::string get_picture_name() const;
    std::string get_notification_text() const;

    void progress_peck( bear::universe::time_type elapsed_time );
    void progress_attack( bear::universe::time_type elapsed_time );
    void progress_dead( bear::universe::time_type elapsed_time );
    void progress_scan( bear::universe::time_type elapsed_time );
    void progress_come_back( bear::universe::time_type elapsed_time );

    void start_peck();
    void start_attack();
    void start_dead();
    void start_scan();
    void start_come_back();

    bool listen(bool& left_orientation);
    bool scan( bear::universe::coordinate_type distance,
               unsigned int& index, bool& left_orientation) const;
    void search_players();
    void create_attack_movement(unsigned int index);
    void join_origin();

  protected:
    void to_string( std::string& str ) const;

  private:
    void create_wig();
    void create_feathers();
    void create_feather();
    void set_feather_reference(bear::decorative_item* ref);
    void set_feather(bear::decorative_item* item);

    static void init_exported_methods();

  private:
    /** \brief Current progress function. */
    progress_function_type m_progress;

    /** \brief The orientation when the object starts. */
    bool m_origin_orientation;

    /** \brief The position of the origin. */
    bear::reference_item* m_origin_item;

    /** \brief A reference item for attack movement. */
    bear::reference_item* m_attack_item;

   /** \brief The energy of the soul of a woodpecker.*/
    static const unsigned int s_soul_energy;

    /** \brief The distance under which the woodpecker listen.*/
    static const unsigned int s_listen_distance;

    /** \brief The distance under which the woodpecker scan.*/
    static const unsigned int s_scan_distance;

    /** \brief The first player. */
    player_proxy m_first_player;

    /** \brief The second player. */
    player_proxy m_second_player;

  }; // class woodpecker
} // namespace ptb

#endif // __PTB_WOODPECKER_HPP__
