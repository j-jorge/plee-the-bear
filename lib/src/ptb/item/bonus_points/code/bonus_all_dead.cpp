/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::bonus_all_dead class.
 * \author Julien Jorge
 */
#include "ptb/item/bonus_points/bonus_all_dead.hpp"

#include "engine/expr/count_items_by_class_name.hpp"
#include "expr/linear_constant.hpp"

#include <libintl.h>

BASE_ITEM_EXPORT( bonus_all_dead, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::bonus_all_dead::bonus_all_dead()
: super()
{

} // bonus_all_dead::bonus_all_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param name The name of the bonus.
 * \param points The number of points given for this bonus.
 */
ptb::bonus_all_dead::bonus_all_dead
( const std::string& name, unsigned int points )
  : super(name, points)
{

} // bonus_all_dead::bonus_all_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::bonus_all_dead::build()
{
  super::build();

  bear::expr::linear_expression count( bear::expr::linear_constant(0) );
  std::list<std::string>::const_iterator it;

  for ( it=m_class_names.begin(); it!=m_class_names.end(); ++it )
    count += bear::engine::count_items_by_class_name( *this, *it );

  set_condition( count == 0 );
} // bonus_all_dead::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type list of items.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::bonus_all_dead::set_item_list_field
( const std::string& name, const std::vector<bear::engine::base_item*>& value )
{
  bool result(true);

  if ( name == "bonus_all_dead.class_instances" )
    for ( std::size_t i=0; i!=value.size(); ++i )
      m_class_names.push_back( value[i]->get_class_name() );
  else
    result = super::set_item_list_field( name, value );

  return result;
} // bonus_all_dead::set_item_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type list of items.
 * \param class_names The names of classes to check.
 */
void ptb::bonus_all_dead::set_class_names
(const std::list<std::string>& class_names)
{
  m_class_names = class_names;
} // bonus_all_dead::set_class_names()
