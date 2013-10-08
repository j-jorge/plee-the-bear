/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing the state where the player game_over.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATE_GAME_OVER_HPP__
#define __PTB_STATE_GAME_OVER_HPP__

#include "ptb/player_state/state_player.hpp"

namespace ptb
{
  /**
   * \brief The class describing a state where the player game_over.
   * \author Sebastien Angibaud
   */
  class state_game_over : public ptb::state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef ptb::state_player super;

  public:
    state_game_over(const player_proxy& player);

    virtual std::string get_name() const;

    virtual void do_move_left();
    virtual void do_move_right();
    virtual void do_jump();
    virtual void do_slap();
    virtual void do_start_throw();
    virtual void do_start_drop();
    virtual void do_injured();
  }; // class state_game_over
} // namespace ptb

#endif // __PTB_STATE_GAME_OVER_HPP__
