/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::notification_widget class.
 * \author Julien Jorge
 */
#include "ptb/gui/notification_widget.hpp"

#include "visual/scene_sprite.hpp"
#include "visual/scene_writing.hpp"
#include "visual/scene_polygon.hpp"
#include "visual/scene_rectangle.hpp"

#include "universe/types.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::notification_widget::notification_widget()
  : visual_component()
{
} // notification_widget::notification_widget()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the text.
 * \param f The font to use to display the text.
 * \param text The text to display.
 */
void ptb::notification_widget::set_text
( const bear::visual::font& f, const std::string& text )
{
  m_text.create( f, text, bear::universe::size_box_type(174, 35) );
} // notification_widget::set_text

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the picture.
 * \param picture The picture to display.
 */
void ptb::notification_widget::set_picture
( const bear::visual::sprite& picture )
{
   m_picture = picture;
} // notification_widget::set_picture()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the background sprite.
 * \param picture The background to display.
 */
void ptb::notification_widget::set_background
( const bear::visual::sprite& picture )
{
   m_background = picture;
} // notification_widget::set_background()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the component.
 */
unsigned int ptb::notification_widget::width() const
{
   return m_background.width();
} // notification_widget::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the component.
 */
unsigned int ptb::notification_widget::height() const
{
  return m_background.height();
} // notification_widget::height()

/*----------------------------------------------------------------------------*/
/**
 * \brief Display the bar.
 * \param e (out) The scene elements.
 * \param pos The position of the bar.
 */
void ptb::notification_widget::render
( scene_element_list& e, const bear::visual::position_type& pos ) const
{
  e.push_back
    ( bear::visual::scene_sprite(pos.x, pos.y, m_background) );

  e.push_back
    ( bear::visual::scene_sprite(pos.x + 14 , pos.y + 8, m_picture) );

  e.push_back
    ( bear::visual::scene_writing
      (pos.x + 73, pos.y + 9, m_text) );  
} // notification_widget::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get text control.
 */
bear::visual::writing& ptb::notification_widget::get_text()
{
   return m_text;
} // notification_widget::get_text()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the scene elements of the component.
 * \param e (out) The scene elements.
 */
void ptb::notification_widget::display
( std::list<bear::visual::scene_element>& e ) const
{
  render(e, bear::visual::position_type(bottom(), left()));
} // notification_widget::display()
