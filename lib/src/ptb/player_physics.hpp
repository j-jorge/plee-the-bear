/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The player_physics class stores the physics constants defining the
 *        behavior of a player.
 * \author Julien Jorge
 */
#ifndef __PTB_PLAYER_PHYSICS_HPP__
#define __PTB_PLAYER_PHYSICS_HPP__

#include "universe/types.hpp"

namespace ptb
{
  /**
   * \brief The class describing a player_physics.
   * \author Julien Jorge
   */
  struct player_physics
  {
    /** \brief The right force of the player in jump state. */
    bear::universe::coordinate_type move_force_in_jump;
    
    /** \brief The right force of the player in vertical jump state. */
    bear::universe::coordinate_type move_force_in_vertical_jump;
    
    /** \brief The right force of the player in run state. */
    bear::universe::coordinate_type move_force_in_run;
    
    /** \brief The right force of the player in swim state. */
    bear::universe::coordinate_type move_force_in_swimming;
    
    /** \brief The force of the player in walk state. */
    bear::universe::coordinate_type move_force_in_walk;

    /** \brief The impulse force given when the player jumps. */
    bear::universe::coordinate_type jump_force;
    
    /** \brief The impulse force given when the player jumps in float state. */
    bear::universe::coordinate_type jump_force_in_float;
    
    /** \brief The speed over which the player is running. */
    bear::universe::coordinate_type speed_to_run;

  }; // class player_physics
} // namespace ptb

#endif // __PTB_PLAYER_PHYSICS_HPP__
