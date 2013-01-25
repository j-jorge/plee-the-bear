/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class containing all player's signal.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_PLAYER_SIGNALS_HPP__
#define __PTB_PLAYER_SIGNALS_HPP__

#include <boost/signal.hpp>

namespace ptb
{
  /**
   * \brief The class containing all player's signals.
   * \author Sebastien Angibaud
   */
  class player_signals
  {
  public:
    /** \brief The signal when the player enters in the water. */
    boost::signal<void ()> enters_water_zone;

    /** \brief The signal when the player leaves the water. */
    boost::signal<void ()> leaves_water_zone;

    /** \brief The signal when the the oxygen gauge changes. */
    boost::signal<void (double)> oxygen_gauge_changed;

    /** \brief The signal when the player enters in a cold zone. */
    boost::signal<void ()> enters_cold_zone;

    /** \brief The signal when the player gos in a cold zone. */
    boost::signal<void ()> leaves_cold_zone;

    /** \brief The signal when the the ice gauge changes. */
    boost::signal<void (double)> cold_gauge_changed;

    /** \brief The signal when the player enters in a heat zone. */
    boost::signal<void ()> enters_heat_zone;

    /** \brief The signal when the player leaves in a heat zone. */
    boost::signal<void ()> leaves_heat_zone;

    /** \brief The signal when the the heat gauge changes. */
    boost::signal<void (double)> heat_gauge_changed;

    /** \brief The signal when the player wins energy. */
    boost::signal<void (double)> energy_added;

    /** \brief The signal when the player loses energy. */
    boost::signal<void (double)> energy_removed;
  }; // class player_signals
} // namespace ptb

#endif // __PTB_PLAYER_SIGNALS_HPP__
