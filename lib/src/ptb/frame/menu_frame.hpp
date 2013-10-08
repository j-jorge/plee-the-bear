/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Inherit from this class if you need a frame containing just a menu.
 * \author Julien Jorge
 */
#ifndef __PTB_MENU_FRAME_HPP__
#define __PTB_MENU_FRAME_HPP__

#include "ptb/frame/frame.hpp"
#include "gui/callback.hpp"

namespace ptb
{
  /**
   * \brief Inherit from this class if you need a frame containing just a menu.
   * \author Julien Jorge
   */
  class menu_frame:
    public frame
  {
  public:
    menu_frame( windows_layer* owning_layer, const std::string& title );

  protected:
    void push( const std::string& text, const bear::gui::callback& c );

  private:
    /** \brief The top entry of the menu. */
    bear::gui::visual_component* m_top;

  }; // class menu_frame
} // namespace ptb

#endif // __PTB_MENU_FRAME_HPP__
