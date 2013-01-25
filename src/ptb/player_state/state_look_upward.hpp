/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing the state where the player look up.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATE_LOOK_UPWARD_HPP__
#define __PTB_STATE_LOOK_UPWARD_HPP__

#include "ptb/player_state/state_player.hpp"

namespace ptb
{
  /**
   * \brief The class describing a state where the player idle.
   * \author Sebastien Angibaud
   */
  class state_look_upward : public state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef state_player super;

  public:
    state_look_upward(const player_proxy& player);

    virtual std::string get_name() const;

    virtual void do_move_left();
    virtual void do_move_right();
    virtual void do_jump();
    virtual void do_stop_look_upward();
    virtual void do_crouch();
  }; // class state_look_upward
} // namespace ptb

#endif // __PTB_STATE_LOOK_UPWARD_HPP__
