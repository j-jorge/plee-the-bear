/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The Objects of this class create a bear::path_trace for all stones
 *        that collided with them.
 * \author Julien Jorge
 */
#ifndef __PTB_STONE_TRACER_HPP__
#define __PTB_STONE_TRACER_HPP__

#include "generic_items/path_tracer.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The Objects of this class create a bear::path_trace for all stones
   *        that collided with them.
   *
   * \author Julien Jorge
   */
  class stone_tracer:
    public bear::path_tracer
  {
    DECLARE_BASE_ITEM(stone_tracer);

  public:
    /** \brief The type of the parent class. */
    typedef bear::path_tracer super;

  public:
    stone_tracer();
    stone_tracer( const stone_tracer& that );

  }; // class stone_tracer
} // namespace ptb

#endif // __PTB_STONE_TRACER_HPP__
