/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a rolling_ball.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_ROLLING_BALL_HPP__
#define __PTB_ROLLING_BALL_HPP__

#include "ptb/item/passive_enemy.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a rolling_ball.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class rolling_ball:
    public passive_enemy
  {
    DECLARE_BASE_ITEM(rolling_ball);

  public:
    /** \brief The type of the parent class. */
    typedef passive_enemy super;

  public:
    rolling_ball();

    void progress( bear::universe::time_type elapsed_time );
    void on_enters_layer();

  private:
    bool m_on_ground;

    /** \brief The visual position in the last iteration. */
    bear::universe::position_type m_last_visual_position;
  }; // class rolling_ball
} // namespace ptb

#endif // __PTB_ROLLING_BALL_HPP__
