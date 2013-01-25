/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing the state where the player crouch.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATE_CROUCH_HPP__
#define __PTB_STATE_CROUCH_HPP__

#include "ptb/player_state/state_player.hpp"

namespace ptb
{
  /**
   * \brief The class describing a state where the player idle.
   * \author Sebastien Angibaud
   */
  class state_crouch : public state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef state_player super;

  public:
    state_crouch(const player_proxy& player);

    virtual std::string get_name() const;

    virtual void do_move_left();
    virtual void do_move_right();
    virtual void do_stop_crouch();
    virtual void do_look_upward();
    virtual void do_slap();
    virtual void do_continue_crouch();
  }; // class state_crouch
} // namespace ptb

#endif // __PTB_STATE_CROUCH_HPP__
