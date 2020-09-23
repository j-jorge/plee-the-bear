/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::floating_bonus class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/status/floating_bonus.hpp"

#include "ptb/level_variables.hpp"

#include "visual/scene_sprite.hpp"

#include <boost/bind.hpp>
#include <claw/tween/single_tweener.hpp>
#include <claw/tween/easing/symmetric_easing.hpp>
#include <claw/tween/easing/easing_linear.hpp>
#include <claw/tween/easing/easing_back.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief This easing function is applied to the floating_bonus for
 *        a fun movement.
 * \param t The ratio of the time at which the easing is computed during the
 *        tweener.
 */
double easing_back_bonus_func( double t )
{
  if ( t <= 0.0045 )
    return 0;
  else
    return 1 - 2.5 * (1 - t*t*t*t) * std::log( 0.8 * t + 0.1 ) / log(0.8 * t);
} // easing_back_bonus_func()

/*----------------------------------------------------------------------------*/
/**
 * \brief Implementation of the in/out/in_out versions of the
 *        easing_back_large_func easing function.
 */
typedef claw::tween::symmetric_easing<easing_back_bonus_func> easing_back_bonus;

/*----------------------------------------------------------------------------*/
/**
 * \brief Do an iteration.
 * \param name The name of the bonus.
 */
ptb::floating_bonus::floating_bonus( const std::string& name )
  : m_name(name)
{
  
} // floating_bonus::floating_bonus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do an iteration.
 */
void ptb::floating_bonus::progress
( bear::universe::time_type elapsed_time )
{
  m_tweeners.update(elapsed_time);
} // floating_bonus::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the movement is finished.
 */
bool ptb::floating_bonus::is_finished() const
{
  return m_tweeners.is_finished();
} // floating_bonus::is_finished()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of the bonus.
 */
const std::string& ptb::floating_bonus::get_name() const
{
  return m_name;
} // floating_bonus::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the current position of the component.
 */
const bear::visual::position_type& 
ptb::floating_bonus::get_position() const
{
  return m_position;
} // floating_bonus::get_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set position.
 * \param init_position The init position.
 * \param end_position The end position.
 */
void ptb::floating_bonus::set_position
( const bear::visual::position_type& init_position,
  const bear::visual::position_type& end_position)
{
  m_position = init_position;

  const claw::tween::single_tweener tween_x
    ( init_position.x, end_position.x, 1.0,
      boost::bind
      (&floating_bonus::on_x_position_update,
       this, boost::placeholders::_1 ), &claw::tween::easing_back::ease_in );
  
  m_tweeners.insert(tween_x);

  const claw::tween::single_tweener tween_y
    ( init_position.y, end_position.y, 1.0,
      boost::bind
      (&floating_bonus::on_y_position_update,
       this, boost::placeholders::_1 ), &claw::tween::easing_back::ease_in );
  
  m_tweeners.insert(tween_y);
} // floating_bonus::set_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the x-position of the component.
 * \param x The x-position of the component.
 */
void ptb::floating_bonus::on_x_position_update(double x)
{  
  m_position.x = x;
} // floating_bonus::on_x_position_update()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the y-position of the component.
 * \param y The y-position of the component.
 */
void ptb::floating_bonus::on_y_position_update(double y)
{
  m_position.y = y;
} // floating_bonus::on_y_position_update()
