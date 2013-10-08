/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing the state where the player dead.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATE_DEAD_HPP__
#define __PTB_STATE_DEAD_HPP__

#include "ptb/player_state/state_player.hpp"

namespace ptb
{
  /**
   * \brief The class describing a state where the player dead.
   * \author Sebastien Angibaud
   */
  class state_dead : public ptb::state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef ptb::state_player super;

  public:
    state_dead(const player_proxy& player);

    virtual std::string get_name() const;

    void do_move_left();
    void do_move_right();
    void do_jump();
    void do_slap();
    void do_stop_vertical_jump();
    void do_look_upward();
    void do_continue_look_upward();
    void do_stop_look_upward();
    void do_continue_crouch();
    void do_crouch();
    void do_stop_crouch();
    void unchain();
    void chain();
    void do_start_throw();
    void do_start_change_object();
    void do_stop_throw();
    void do_injured();
    void do_finish_injured();
  }; // class state_dead
} // namespace ptb

#endif // __PTB_STATE_DEAD_HPP__
