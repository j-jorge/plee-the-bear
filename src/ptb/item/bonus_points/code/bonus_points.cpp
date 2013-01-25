/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::bonus_points class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/bonus_points/bonus_points.hpp"
#include "ptb/game_variables.hpp"

#include "engine/level.hpp"

#include "expr/boolean_constant.hpp"
#include "expr/linear_constant.hpp"

#include <libintl.h>

BASE_ITEM_EXPORT( bonus_points, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::bonus_points::bonus_points()
  : m_bonus_points( bear::expr::linear_constant(0) ),
    m_condition( bear::expr::boolean_constant(true) )
{

} // bonus_points::bonus_points()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param id The identitifier of the bonus.
 * \param points The points to give.
 */
ptb::bonus_points::bonus_points( const std::string& id, unsigned int points )
  : m_bonus_id(id), m_bonus_name(gettext(id.c_str())),
    m_bonus_points( bear::expr::linear_constant(points) ),
    m_condition( bear::expr::boolean_constant(true) )
{

} // bonus_points::bonus_points()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::bonus_points::build()
{
  super::build();

  if ( is_level_bonus() )
    {
      game_variables::set_level_object_state
        ( m_bonus_id, game_variables::get_level_object_state( m_bonus_id ));
      game_variables::set_level_object_filename
        ( m_bonus_id, m_picture_filename);
      game_variables::set_level_object_name( m_bonus_id, m_picture_name);
    }
} // bonus_points::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type string.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::bonus_points::set_string_field
( const std::string& name, const std::string& value )
{
  bool result = true;

  if ( name == "bonus_points.name" )
    {
      m_bonus_id = value;
      m_bonus_name = gettext(value.c_str());
    }
  else if ( name == "bonus_points.picture_filename" )
    m_picture_filename = gettext(value.c_str());
  else if ( name == "bonus_points.picture_name" )
    m_picture_name = gettext(value.c_str());
  else
    result = super::set_string_field( name, value );

  return result;
} // bonus_bonus::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type unsigned int.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::bonus_points::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result = true;

  if ( name == "bonus_points.points" )
    m_bonus_points = value;
  else
    result = super::set_u_integer_field( name, value );

  return result;
} // bonus_bonus::set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the name of given points.
 */
const std::string& ptb::bonus_points::get_name() const
{
  return m_bonus_name;
} // bonus_points::get_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the identifier of the bonus.
 */
const std::string& ptb::bonus_points::get_bonus_id() const
{
  return m_bonus_id;
} // bonus_points::get_bonus_id()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the number of points.
 */
unsigned int ptb::bonus_points::get_points() const
{
  if ( m_condition.evaluate() )
    {
      on_give_points();
      return m_bonus_points.evaluate();
    }
  else
    return 0;
} // bonus_points::get_points()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the expression used to compute the points.
 * \param e The expression.
 */
void ptb::bonus_points::set_points( const bear::expr::linear_expression& e )
{
  with_linear_expression_assignment::set_expression(e);
} // bonus_points::set_points()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the condition to check before giving the points.
 * \param e The expression.
 */
void ptb::bonus_points::set_condition( const bear::expr::boolean_expression& e )
{
  with_boolean_expression_assignment::set_expression(e);
} // bonus_points::set_condition()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the bonus is in the list of bonus to found.
 */
bool ptb::bonus_points::is_level_bonus() const
{
  return !m_picture_name.empty() && !m_picture_filename.empty();
} // bonus_points::is_level_bonus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the filename of the bonus picture.
 * \param filename The filename of the bonus picture.
 */
void ptb::bonus_points::set_picture_filename( const std::string& filename )
{
  m_picture_filename = filename;
} // bonus_points::set_picture_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the filename of the bonus picture.
 */
const std::string& ptb::bonus_points::get_picture_filename() const
{
  return m_picture_filename;
} // bonus_points::get_picture_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the name of the bonus picture.
 * \param name The name of the bonus picture.
 */
void ptb::bonus_points::set_picture_name( const std::string& name )
{
  m_picture_name = name;
} // bonus_points::set_picture_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the name of the bonus picture.
 */
const std::string& ptb::bonus_points::get_picture_name() const
{
  return m_picture_name;
} // bonus_points::get_picture_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the condition to check before giving the points.
 * \param e The condition to check.
 */
void
ptb::bonus_points::do_set_expression( const bear::expr::boolean_expression& e )
{
  m_condition = e;
} // bonus_points::do_set_expression()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the expression used to compute the points.
 * \param e The expression.
 */
void
ptb::bonus_points::do_set_expression( const bear::expr::linear_expression& e )
{
  m_bonus_points = e;
} // bonus_points::do_set_expression()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update game variable of the bonus.
 */
void ptb::bonus_points::update_bonus_state() const
{
  if ( is_level_bonus() )
    if ( !game_variables::get_level_object_state
         (game_variables::get_main_level_name(), m_bonus_id ) )
      {
        game_variables::set_level_object_state
          ( m_bonus_id, m_condition.evaluate() );
        game_variables::set_level_object_filename
          ( m_bonus_id, m_picture_filename );
        game_variables::set_level_object_name
          ( m_bonus_id, m_picture_name );
      }
} // bonus_points::update_bonus_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Fonction tell when the bonus give points.
 */
void ptb::bonus_points::on_give_points() const
{
  // Do nothing
} // bonus_points::on_give_points()
