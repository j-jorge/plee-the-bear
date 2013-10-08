/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The main_menu_layer is a layer containing the windows of the title
 *        screen.
 * \author Julien Jorge
 */
#ifndef __PTB_MAIN_MENU_LAYER_HPP__
#define __PTB_MAIN_MENU_LAYER_HPP__

#include "ptb/layer/windows_layer.hpp"
#include "gui/static_text.hpp"

namespace ptb
{
  /**
   * \brief The main_menu_layer is a layer containing the windows of the title
   *        screen.
   * \author Julien Jorge
   */
  class main_menu_layer:
    public windows_layer
  {
  private:
    /** \brief The type of the parent class. */
    typedef windows_layer super;

  public:
    main_menu_layer( const claw::math::coordinate_2d<unsigned int>& pos );
    ~main_menu_layer();

    void build();
    void render( scene_element_list& e ) const;

  private:
    /** \brief The component in which we show the version of the engine. */
    bear::gui::static_text* m_engine_version;

    /** \brief The position of the menu. */
    const claw::math::coordinate_2d<unsigned int> m_position;

  }; // class main_menu_layer
} // namespace ptb

#endif // __PTB_MAIN_MENU_LAYER_HPP__
