/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing the state where the player slap.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATE_SLAP_HPP__
#define __PTB_STATE_SLAP_HPP__

#include "ptb/player_state/state_player.hpp"

namespace ptb
{
  /**
   * \brief The class describing a state where the player slap.
   * \author Sebastien Angibaud
   */
  class state_slap : public state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef ptb::state_player super;

  public:
    state_slap(const player_proxy& player);

    virtual std::string get_name() const;
    virtual void start();
    virtual void stop();

    virtual void do_slap();

  private:
    /* \brief The initial value of normal_defensive_power. */
    bool m_initial_normal_defensive_power;
  }; // class state_slap
} // namespace ptb

#endif // __PTB_STATE_SLAP_HPP__
