/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a ghost.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_GHOST_HPP__
#define __PTB_GHOST_HPP__

#include "ptb/player_proxy.hpp"

#include "engine/model.hpp"
#include "generic_items/reference_item.hpp"

namespace ptb
{
  /**
   * \brief The class describing a ghost.
   *
   * The valid fields for this item are
   *  - \a distance: The maximum possible distance with start position
   * (default=600).
   *  - \a distance: The maximum possible distance with start position
   * in fly state (default=400).
   *  - \a distance: The maximum possible distance for scanning players
   * (default=200).
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class ghost:
    public bear::engine::model< bear::engine::base_item >
  {
  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::model< bear::engine::base_item > super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  private:
    typedef void (ghost::*progress_function_type)(bear::universe::time_type);

  public:
    ghost();
    ~ghost();

    void build();
    void progress( bear::universe::time_type elapsed_time );
    bool set_real_field( const std::string& name, double value );
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );
    bool possess() const;
    player_proxy get_player();

  protected:
    void progress_fly( bear::universe::time_type elapsed_time );
    void progress_appear( bear::universe::time_type elapsed_time );
    void progress_come_back( bear::universe::time_type elapsed_time );
    virtual void progress_control( bear::universe::time_type elapsed_time );
    void progress_wait( bear::universe::time_type elapsed_time );
    void start_fly();
    void start_appear();
    void start_come_back();
    void start_control();
    void start_wait();
    void start_scan();
    bool scan_players();
    bool scan_player(unsigned int index);
    void set_origin();

    void to_string( std::string& str ) const;

  protected:
    virtual void control_player();
    virtual void release_player();

  private:
    void create_fly_movement(player_proxy& p);
    void create_come_back_movement();

    static void init_exported_methods();

  protected:
    /** \brief Current progress function. */
    progress_function_type m_progress;

    /** \brief The maximum possible distance with origin position. */
    bear::universe::coordinate_type m_max_distance;

    /** \brief The maximum possible distance with origin in fly state. */
    bear::universe::coordinate_type m_fly_distance;

    /** \brief The maximum possible distance for scaning players. */
    bear::universe::coordinate_type m_scan_distance;

    /** \brief The player controled by ghost. */
    player_proxy m_player;

    /** \brief The item origin reference. */
    bear::reference_item m_origin;

    /** \brief Indicates if ghost can scan players. */
    bool m_scan;
  }; // class ghost
} // namespace ptb

#endif // __PTB_GHOST_HPP__
