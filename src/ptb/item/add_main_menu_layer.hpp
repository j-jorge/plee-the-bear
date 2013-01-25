/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This class adds the main menu in the graphical user interface in the
 *        current level.
 * \author Julien Jorge
 */
#ifndef __PTB_ADD_MAIN_MENU_LAYER_HPP__
#define __PTB_ADD_MAIN_MENU_LAYER_HPP__

#include "engine/base_item.hpp"
#include "engine/layer/gui_layer.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief This class adds the main menu in the graphical user interface in the
   *        current level.
   *
   * \author Julien Jorge
   */
  class add_main_menu_layer:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(add_main_menu_layer);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    add_main_menu_layer();

    void pre_cache();
    void build();

  }; // class add_main_menu_layer
} // namespace ptb

#endif // __PTB_ADD_MAIN_MENU_LAYER_HPP__
