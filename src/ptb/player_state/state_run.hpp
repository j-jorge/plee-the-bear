/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing the state where the player run.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATE_RUN_HPP__
#define __PTB_STATE_RUN_HPP__

#include "ptb/player_state/state_player.hpp"

namespace ptb
{
  /**
   * \brief The class describing a state where the player run.
   * \author Sebastien Angibaud
   */
  class state_run : public ptb::state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef ptb::state_player super;

  public:
    state_run(const player_proxy& player);

    virtual std::string get_name() const;

    virtual void do_slap();
    virtual void do_start_throw();
  }; // class state_run
} // namespace ptb

#endif // __PTB_STATE_RUN_HPP__
