/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing the state where the player jump.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATE_JUMP_HPP__
#define __PTB_STATE_JUMP_HPP__

#include "ptb/player_state/state_player.hpp"

namespace ptb
{
  /**
   * \brief The class describing a state where the player jump.
   * \author Sebastien Angibaud
   */
  class state_jump : public ptb::state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef ptb::state_player super;

  public:
    state_jump(const player_proxy& player);

    virtual std::string get_name() const;

    virtual void do_jump();
    virtual void do_continue_jump();
    virtual void do_start_throw();
  }; // class state_jump
} // namespace ptb

#endif // __PTB_STATE_JUMP_HPP__
