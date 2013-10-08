/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::stone_tracer class.
 * \author Julien Jorge
 */
#include "ptb/item/stone_tracer.hpp"

#include "engine/expr/check_item_class_hierarchy.hpp"
#include "ptb/item/stone/stone.hpp"

BASE_ITEM_EXPORT(stone_tracer, ptb)

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::stone_tracer::stone_tracer()
{
  bear::engine::check_item_class_hierarchy<stone> e;
  e.set_collision_data( get_collision_in_expression() );
  set_condition( e );
} // stone_tracer::stone_tracer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Copy constructor.
 * \param that The instance to copy from.
 */
ptb::stone_tracer::stone_tracer( const stone_tracer& that )
  : super(that)
{
  bear::engine::check_item_class_hierarchy<stone> e;
  e.set_collision_data( get_collision_in_expression() );
  set_condition( e );
} // stone_tracer::stone_tracer()
