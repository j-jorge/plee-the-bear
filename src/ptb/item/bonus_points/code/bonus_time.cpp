/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::bonus_time class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/bonus_points/bonus_time.hpp"
#include "ptb/level_variables.hpp"
#include "expr/linear_function.hpp"

#include <libintl.h>

BASE_ITEM_EXPORT( bonus_time, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::bonus_time::bonus_time()
: super("Time bonus"), m_timer(NULL), m_points_per_second(10)
{

} // bonus_time::bonus_time()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is valid.
 */
bool ptb::bonus_time::is_valid() const
{
  return (m_timer != (bear::timer*)NULL) && super::is_valid();
} // bonus_time::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::bonus_time::build()
{
  super::build();

  set_condition
    ( bear::expr::linear_function_maker
      ( m_timer, std::mem_fun_ref(&bear::timer::get_loops) ) == 0 );
  set_points
    ( bear::expr::linear_function_maker
      ( m_timer, std::mem_fun_ref(&bear::timer::get_time) )
      * m_points_per_second );
} // bonus_time::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "item".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::bonus_time::set_item_field
( const std::string& name, bear::engine::base_item* value )
{
  bool result(true);

  if ( name == "bonus_time.level_timer" )
    m_timer = value;
  else
    result = super::set_item_field( name, value );

  return result;
} // bonus_time::set_item_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c unsigned int.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::bonus_time::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result = true;

  if (name == "bonus_time.points_per_second")
    m_points_per_second = value;
  else
    result = super::set_u_integer_field(name, value);

  return result;
} // bonus_time::set_u_intger_field()
