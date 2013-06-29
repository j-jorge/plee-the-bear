/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing the state where player is captive.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATE_CAPTIVE_HPP__
#define __PTB_STATE_CAPTIVE_HPP__

#include "ptb/player_state/state_player.hpp"

namespace ptb
{
  /**
   * \brief The class describing a state where the player captive.
   * \author Sebastien Angibaud
   */
  class state_captive : public ptb::state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef ptb::state_player super;

  public:
    state_captive(const player_proxy& player);

    virtual std::string get_name() const;
    virtual void start();
    virtual void stop();

    virtual void do_move_left();
    virtual void do_move_right();
    virtual void do_jump();
    virtual void do_slap();
    virtual void do_start_drop();
    virtual void do_start_throw();
    virtual void unchain();
    virtual void chain();
    virtual void do_injured();

  private:
    /** \brief The mass of the player. */
    double m_mass;

  }; // class state_captive
} // namespace ptb

#endif // __PTB_STATE_CAPTIVE_HPP__
