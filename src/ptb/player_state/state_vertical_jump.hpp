/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing the state where the player prepare
 * a vertical jump.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATE_VERTICAL_JUMP_HPP__
#define __PTB_STATE_VERTICAL_JUMP_HPP__

#include "ptb/player_state/state_player.hpp"

namespace ptb
{
  /**
   * \brief The class describing a state where the player jump vertically.
   * \author Sebastien Angibaud
   */
  class state_vertical_jump : public state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef state_player super;

  public:
    state_vertical_jump(const player_proxy& player);

    virtual std::string get_name() const;
    virtual void start();

    virtual void do_jump();
  }; // class state_vertical_jump
} // namespace ptb

#endif // __PTB_STATE_VERTICAL_JUMP_HPP__
