/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class containing all player's signal.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_PLAYER_SIGNALS_HPP__
#define __PTB_PLAYER_SIGNALS_HPP__

#include <boost/signals2.hpp>

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
    boost::signals2::signal<void ()> enters_water_zone;

    /** \brief The signal when the player leaves the water. */
    boost::signals2::signal<void ()> leaves_water_zone;

    /** \brief The signal when the the oxygen gauge changes. */
    boost::signals2::signal<void (double)> oxygen_gauge_changed;

    /** \brief The signal when the player enters in a cold zone. */
    boost::signals2::signal<void ()> enters_cold_zone;

    /** \brief The signal when the player gos in a cold zone. */
    boost::signals2::signal<void ()> leaves_cold_zone;

    /** \brief The signal when the the ice gauge changes. */
    boost::signals2::signal<void (double)> cold_gauge_changed;

    /** \brief The signal when the player enters in a heat zone. */
    boost::signals2::signal<void ()> enters_heat_zone;

    /** \brief The signal when the player leaves in a heat zone. */
    boost::signals2::signal<void ()> leaves_heat_zone;

    /** \brief The signal when the the heat gauge changes. */
    boost::signals2::signal<void (double)> heat_gauge_changed;

    /** \brief The signal when the player wins energy. */
    boost::signals2::signal<void (double)> energy_added;

    /** \brief The signal when the player loses energy. */
    boost::signals2::signal<void (double)> energy_removed;
  }; // class player_signals
} // namespace ptb

#endif // __PTB_PLAYER_SIGNALS_HPP__
