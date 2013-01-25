/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing the state where the player prepare
 * to throw a stone.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATE_MAINTAIN_HPP__
#define __PTB_STATE_MAINTAIN_HPP__

#include "ptb/player_state/state_player.hpp"

namespace ptb
{
  /**
   * \brief The class describing a state where the player start to throw a
   *        stone.
   * \author Sebastien Angibaud
   */
  class state_maintain : public state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef state_player super;

  public:
    state_maintain(const player_proxy& player);

    virtual std::string get_name() const;
    virtual void start();

    virtual void do_start_throw();
    virtual void do_stop_throw();
    virtual void do_look_upward();
    virtual void do_continue_look_upward();
    virtual void do_crouch();
    virtual void do_continue_crouch();
  }; // class state_maintain
} // namespace ptb

#endif // __PTB_STATE_MAINTAIN_HPP__
