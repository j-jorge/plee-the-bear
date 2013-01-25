/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A class that contains floating_corrupting_bonus' information.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_FLOATING_CORRUPTING_BONUS_HPP__
#define __PTB_FLOATING_CORRUPTING_BONUS_HPP__

#include "universe/types.hpp"
#include "visual/animation.hpp"
#include <claw/tween/tweener_group.hpp>

namespace ptb
{
  /**
   * \brief A class that contains floating_corrupting_bonus' informations.
   * \author Sebastien Angibaud
   */
  class floating_corrupting_bonus
  {
  public:
    void progress(bear::universe::time_type elapsed_time);
    bool is_finished() const;

    const bear::visual::position_type&  get_position() const;
    void set_position
    ( const bear::visual::position_type& init_position,
      const bear::visual::position_type& end_position );
    
  private:
    void on_x_position_update(double x);
    void on_y_position_update(double x);

  private:
    /** \brief The set of current tweeners. */
    claw::tween::tweener_group m_tweeners;
    
    /** \brief Position of the floating corrupting bonus. */
    bear::visual::position_type m_position;

  }; // class floating_corrupting_bonus
} // namespace ptb

#endif // __PTB_FLOATING_CORRUPTING_BONUS_HPP__
