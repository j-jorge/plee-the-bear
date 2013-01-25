/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An item that plays a script with black stripes.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_SCRIPT_DIRECTOR_HPP__
#define __PTB_SCRIPT_DIRECTOR_HPP__

#include "generic_items/script/script_director.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that plays a script with black stripes.
   * \author Sébastien
   *
   * The custom fields of this class are:
   * - any field supported by the parent class.
   */
  class script_director:
    public bear::script_director
  {
    DECLARE_BASE_ITEM(script_director);

  public:
    /** \brief The type of the parent class. */
    typedef bear::script_director super;

  protected:
    void on_script_started();

  }; // class script_director
} // namespace ptb

#endif // __PTB_SCRIPT_DIRECTOR_HPP__
