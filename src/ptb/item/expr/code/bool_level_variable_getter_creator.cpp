/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::bool_level_variable_getter_creator class.
 * \author Julien Jorge
 */
#include "ptb/item/expr/bool_level_variable_getter_creator.hpp"

#include "ptb/game_variables.hpp"

BASE_ITEM_EXPORT( bool_level_variable_getter_creator, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::bool_level_variable_getter_creator::bool_level_variable_getter_creator()
{
  m_expr.set_default_value(false);
} // bool_level_variable_getter_creator::bool_level_variable_getter_creator()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::bool_level_variable_getter_creator::build()
{
  kill();
} // bool_level_variable_getter_creator::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::bool_level_variable_getter_creator::is_valid() const
{
  return !m_expr.get_name().empty() && super::is_valid();
} // bool_level_variable_getter_creator::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c string.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknown, true otherwise.
 */
bool ptb::bool_level_variable_getter_creator::set_string_field
( const std::string& name, const std::string& value )
{
  bool result = true;

  if ( name == "bool_level_variable_getter_creator.name" )
    m_expr.set_name
      ( game_variables::make_persistent_level_variable_name(value) );
  else
    result = super::set_string_field(name, value);

  return result;
} // bool_level_variable_getter_creator::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c bool.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::bool_level_variable_getter_creator::set_bool_field
( const std::string& name, bool value )
{
  bool result = true;

  if ( name == "bool_level_variable_getter_creator.default_value" )
    m_expr.set_default_value(value);
  else
    result = super::set_bool_field(name, value);

  return result;
} // bool_level_variable_getter_creator::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the expression created by this item.
 */
bear::expr::boolean_expression
ptb::bool_level_variable_getter_creator::do_get_expression() const
{
  return m_expr;
} // bool_level_game_variable_getter_creator::do_get_expression()
