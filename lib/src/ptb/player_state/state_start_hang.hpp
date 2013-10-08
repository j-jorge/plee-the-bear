/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing the state where the player want to hang.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATE_START_HANG_HPP__
#define __PTB_STATE_START_HANG_HPP__

#include "ptb/player_state/state_player.hpp"

namespace ptb
{
  /**
   * \brief The class describing a state where the player want to hang.
   * \author Sebastien Angibaud
   */
  class state_start_hang : public state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef state_player super;

  public:
    state_start_hang(const player_proxy& player);

    virtual std::string get_name() const;

    virtual void do_slap();
  }; // class state_start_hang
} // namespace ptb

#endif // __PTB_STATE_START_HANG_HPP__
