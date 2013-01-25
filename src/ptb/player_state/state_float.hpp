/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing the state where the player float.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_STATE_FLOAT_HPP__
#define __PTB_STATE_FLOAT_HPP__

#include "ptb/player_state/state_player.hpp"

namespace ptb
{
  /**
   * \brief The class describing a state where the player float.
   * \author Sebastien Angibaud
   */
  class state_float : public ptb::state_player
  {
  public:
    /** \brief The type of the parent class. */
    typedef ptb::state_player super;

  public:
    state_float(const player_proxy& player);

    virtual std::string get_name() const;
    virtual void start();
    virtual void stop();
    virtual void do_jump();
    virtual void do_crouch();
    virtual void do_continue_crouch();

  private:
    /** \brief The density of the player. */
    double m_density;
  }; // class state_float
} // namespace ptb

#endif // __PTB_STATE_FLOAT_HPP__
