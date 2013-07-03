/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing the state where the player idle.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATE_IDLE_HPP__
#define __PTB_STATE_IDLE_HPP__

#include "ptb/player_state/state_player.hpp"

namespace ptb
{
  /**
   * \brief The class describing a state where the player idle.
   * \author Sebastien Angibaud
   */
  class state_idle : public state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef state_player super;

  public:
    state_idle(const player_proxy& player);

    virtual std::string get_name() const;

    virtual void do_move_left();
    virtual void do_move_right();
    virtual void do_look_upward();
    virtual void do_continue_look_upward();
    virtual void do_crouch();
    virtual void do_continue_crouch();
  }; // class state_idle
} // namespace ptb

#endif // __PTB_STATE_IDLE_HPP__
