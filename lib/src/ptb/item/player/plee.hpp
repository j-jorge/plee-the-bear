/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing the player (Plee).
 * \author Julien Jorge
 */
#ifndef __PTB_PLEE_HPP__
#define __PTB_PLEE_HPP__

#include "engine/export.hpp"
#include "ptb/player.hpp"

namespace ptb
{
  /**
   * \brief The class describing Plee.
   * \author Sébastien Angibaud
   */
  class plee :
    public player
  {
    DECLARE_BASE_ITEM(plee);

  public:
    /** \brief The type of the parent class. */
    typedef player super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  public:
    plee();

    void pre_cache();
    void on_enters_layer();

    bear::universe::coordinate_type get_vertical_jump_force() const;

  protected:
    void progress_in_water(bear::universe::time_type elapsed_time);

  private:
    bear::visual::sprite get_soul_sprite() const;
    void progress_continue_idle(bear::universe::time_type elapsed_time);
    void take_new_hat();
    void start_take_hat();
    void take_out_hat();

    player_physics get_physics() const;

    static void init_exported_methods();

  private:
    /** \brief The impulse force given for vertical jumps. */
    static const bear::universe::coordinate_type s_vertical_jump_force;

    /** \brief The mass of Plee. */
    static const double s_mass;

    /** \brief The density of Plee. */
    static const double s_density;

  private:
    /** \brief Indicates if Plee has his main hat. */
    bool m_has_main_hat;

    /** \brief Indicates if Plee has a hat. */
    bool m_has_hat;

  }; // class plee
} // namespace ptb

#endif // __PTB_PLEE_HPP__
