/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::menu_frame class.
 * \author Julien Jorge
 */
#include "ptb/frame/menu_frame.hpp"

#include "gui/button.hpp"

#include <libintl.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer onwing the window.
 * \param title The title of the frame.
 */
ptb::menu_frame::menu_frame
( windows_layer* owning_layer, const std::string& title )
  : frame(owning_layer, title), m_top(NULL)
{

} // menu_frame::menu_frame()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add an entry at the top of the other entries.
 * \param text The label of the entry.
 * \param c The callback executed when the entry is clicked.
 */
void
ptb::menu_frame::push( const std::string& text, const bear::gui::callback& c )
{
  bear::gui::button* b = new bear::gui::button( get_font(), text, c );
  b->set_margin(3);

  if ( m_top != NULL )
    b->set_bottom( m_top->top() );

  m_top = b;

  insert_control(*b);
  b->set_focus();
} // menu_frame::push()
