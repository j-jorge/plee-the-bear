/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A timer object that kills the players when the time is over.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_TIMER_KILL_PLAYERS_HPP__
#define __PTB_TIMER_KILL_PLAYERS_HPP__

#include "generic_items/timer.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A timer object that kills the players when the time is over.
   * \author Sébastien Angibaud
   */
  class timer_kill_players:
    public bear::timer
  {
    DECLARE_BASE_ITEM(timer_kill_players);

  public:
    /** \brief The type of the parent class. */
    typedef bear::timer super;

  public:
    void build();

  private:
    void create_trigger();
    void create_toggles();

    bear::engine::base_item* create_kill_toggle( unsigned int i ) const;

  }; // class timer_kill_players
} // namespace bear

#endif // __PTB_TIMER_KILL_PLAYERS_HPP__
