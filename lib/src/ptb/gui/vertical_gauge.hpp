/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A vertical progress bar.
 * \author Julien Jorge
 */
#ifndef __PTB_VERTICAL_GAUGE_HPP__
#define __PTB_VERTICAL_GAUGE_HPP__

#include "engine/level_globals.hpp"
#include "universe/types.hpp"
#include "visual/scene_element.hpp"
#include "visual/sprite.hpp"
#include "gui/visual_component.hpp"

namespace ptb
{
  /**
   * \brief A vertical progress bar.
   * \author Julien Jorge
   */
  class vertical_gauge :
    public bear::gui::visual_component
  {
  public:
    typedef std::list<bear::visual::scene_element> scene_element_list;

  public:
    vertical_gauge
    ( bear::engine::level_globals& glob, unsigned int length,
      const std::string& level_sprite, const std::string& icon_sprite = "" );

    unsigned int width() const;
    unsigned int height() const;

    void set_level( double lev );
    bool is_critical() const;
    void progress( bear::universe::time_type elapsed_time );
    void render
    ( scene_element_list& e, const bear::visual::position_type& pos ) const;
    void display( std::list<bear::visual::scene_element>& e ) const;

  private:
    /** \brief The icon displayed on the bar. */
    bear::visual::sprite m_icon;

    /** \brief The sprite displaying the level of the bar. */
    bear::visual::sprite m_level;

    /** \brief Sprite displayed over the ends of the bars. */
    bear::visual::sprite m_tube_clamp;

    /** \brief Sprite displayed over the bar. */
    bear::visual::sprite m_glass_tube;

    /** \brief The current level of the bar. */
    double m_level_value;

    /** \brief The current loss of the bar. */
    double m_loss_value;

  }; // class vertical_bar
} // namespace ptb

#endif // __PTB_VERTICAL_GAUGE_HPP__
