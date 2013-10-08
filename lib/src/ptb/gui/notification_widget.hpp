/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A component describing a notification.
 * \author Sebastien
 */
#ifndef __PTB_NOTIFICATION_WIDGET_HPP__
#define __PTB_NOTIFICATION_WIDGET_HPP__

#include "engine/level_globals.hpp"
#include "gui/visual_component.hpp"
#include "visual/sprite.hpp"
#include "visual/writing.hpp"

namespace ptb
{
  /**
   * \brief A component describing a notification.
   * \author Sebastien
   */
  class notification_widget :
    public bear::gui::visual_component
  {
  public:
    typedef std::list<bear::visual::scene_element> scene_element_list;

  public:
    notification_widget();

    void set_text( const bear::visual::font& f, const std::string& text);
    void set_picture(const bear::visual::sprite& picture );
    void set_background(const bear::visual::sprite& background );

    unsigned int width() const;
    unsigned int height() const;

    void render
    ( scene_element_list& e, const bear::visual::position_type& pos ) const;

    bear::visual::writing& get_text();

  private:
    void display( std::list<bear::visual::scene_element>& e ) const;

  private:
    /** \brief The picture displayed. */
    bear::visual::sprite m_picture;

    /** \brief The component in which we show the notification. */
    bear::visual::writing m_text;

    /** \brief The background sprite. */
    bear::visual::sprite m_background;
  }; // class notification_widget
} // namespace ptb

#endif // __PTB_NOTIFICATION_WIDGET_HPP__
