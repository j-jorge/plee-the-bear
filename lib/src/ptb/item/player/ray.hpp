/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing Ray, the Plee's son.
 * \author Julien Jorge
 */
#ifndef __PTB_RAY_HPP__
#define __PTB_RAY_HPP__

#include "engine/export.hpp"
#include "ptb/player.hpp"

namespace ptb
{
  /**
   * \brief The class describing Ray, the Plee's son.
   * \author Sébastien Angibaud
   */
  class ray :
    public player
  {
    DECLARE_BASE_ITEM(ray);

  public:
    /** \brief The type of the parent class. */
    typedef player super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  public:
    ray();
    ~ray();

    void pre_cache();
    void on_enters_layer();

    void start_cry();
    void stop_cry();

    bool set_bool_field( const std::string& name, bool value );

    void choose_wait_state();
    void choose_idle_state();
    void choose_walk_state();
    bear::universe::coordinate_type get_vertical_jump_force() const;

  protected:
    void to_string( std::string& str ) const;

  private:
    bear::visual::sprite get_soul_sprite() const;
    void update_cry_action();

    player_physics get_physics() const;

    static void init_exported_methods();

  private:
    /** \brief The impulse force given for vertical jumps. */
    static const bear::universe::coordinate_type s_vertical_jump_force;

    /** \brief The mass of Ray. */
    static const double s_mass;

    /** \brief The density of Ray. */
    static const double s_density;

  private:
    /** \brief Indicates if Ray is crying. */
    bool m_cry;

  }; // class ray
} // namespace ptb

#endif // __PTB_RAY_HPP__
