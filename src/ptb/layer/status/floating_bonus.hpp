/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A class that contains floating_bonus' information.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_FLOATING_BONUS_HPP__
#define __PTB_FLOATING_BONUS_HPP__

#include "universe/types.hpp"
#include "visual/animation.hpp"
#include <claw/tween/tweener_group.hpp>

namespace ptb
{
  /**
   * \brief A class that contains floating_bonus' informations.
   * \author Sebastien Angibaud
   */
  class floating_bonus
  {
  public:
    floating_bonus( const std::string& name );

    void progress(bear::universe::time_type elapsed_time);
    bool is_finished() const;

    const std::string&  get_name() const;
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
    
    /** \brief Position of the floating bonus. */
    bear::visual::position_type m_position;

    /** \brief The name of the bonus. */
    std::string m_name;
  }; // class floating_bonus
} // namespace ptb

#endif // __PTB_FLOATING_BONUS_HPP__
