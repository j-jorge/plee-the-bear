/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::bonus_all_dead_by_category class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/bonus_points/bonus_all_dead_by_category.hpp"
#include "ptb/item/players_detector.hpp"
#include "expr/boolean_function.hpp"
#include "engine/world.hpp"
#include <libintl.h>

BASE_ITEM_EXPORT( bonus_all_dead_by_category, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::bonus_all_dead_by_category::bonus_all_dead_by_category()
: super()
{

} // bonus_all_dead_by_category::bonus_all_dead_by_category()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param name The name of the bonus.
 * \param points The number of points given for this bonus.
 */
ptb::bonus_all_dead_by_category::bonus_all_dead_by_category
( const std::string& name, unsigned int points )
  : super(name, points)
{

} // bonus_all_dead_by_category::bonus_all_dead_by_category()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::bonus_all_dead_by_category::build()
{
  super::build();

  set_condition
    ( bear::expr::boolean_function_maker
      ( this,
        std::mem_fun_ref( &ptb::bonus_all_dead_by_category::check_all_dead )));
} // bonus_all_dead_by_category::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type string.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::bonus_all_dead_by_category::set_string_field
( const std::string& name, const std::string& value )
{
  bool result(true);

  if ( name == "bonus_all_dead_by_category.category" )
    m_category = value;
  else
    result = super::set_string_field( name, value );

  return result;
} // bonus_all_dead_by_category::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the category.
 */
void ptb::bonus_all_dead_by_category::set_category(const std::string& category)
{
  m_category = category;
} // bonus_all_dead_by_category::set_category()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if all players_detector of category are dead.
 */
bool ptb::bonus_all_dead_by_category::check_all_dead()
{
  bear::engine::world::const_item_iterator it;
  bool result(true);

  for ( it=get_world().living_items_begin();
        it!=get_world().living_items_end() && result; ++it )
    {
      const players_detector* item =
        dynamic_cast<const players_detector*>(&(*it));

      if ( item != NULL )
        result = ( item->get_category() != m_category );
    }

  return result ;
} // bonus_all_dead_by_category::check_all_dead()
