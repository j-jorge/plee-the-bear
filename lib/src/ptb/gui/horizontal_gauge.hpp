/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A horizontal progress bar.
 * \author Julien Jorge
 */
#ifndef __PTB_HORIZONTAL_GAUGE_HPP__
#define __PTB_HORIZONTAL_GAUGE_HPP__

#include "engine/level_globals.hpp"
#include "gui/visual_component.hpp"
#include "universe/types.hpp"
#include "visual/scene_element.hpp"
#include "visual/sprite.hpp"

namespace ptb
{
  /**
   * \brief A horizontal progress bar.
   * \author Julien Jorge
   */
  class horizontal_gauge :
    public bear::gui::visual_component
  {
  public:
    typedef std::list<bear::visual::scene_element> scene_element_list;

  public:
    horizontal_gauge
    ( bear::engine::level_globals& glob, unsigned int length,
      const std::string& level_sprite, const std::string& loss_sprite = "",
      const std::string& icon_name = "", bool clamp_flashing = false );

    void set_length(unsigned int length);
    unsigned int length() const;
    unsigned int width() const;
    unsigned int height() const;

    void set_level_sprite
    ( bear::engine::level_globals& glob, const std::string& level_sprite );

    void set_level( double lev );
    double get_level() const;
    void set_max_level( double lev );

    bool is_critical() const;
    void progress( bear::universe::time_type elapsed_time );
    void render
    ( scene_element_list& e, const bear::visual::position_type& pos ) const;
    void update_bar();

  private:
    void display( std::list<bear::visual::scene_element>& e ) const;

  private:
    /** \brief The icon displayed on the bar. */
    bear::visual::sprite m_icon;

    /** \brief The sprite displaying the level of the bar. */
    bear::visual::sprite m_level;

    /** \brief The sprite displaying the amount of loss. */
    bear::visual::sprite m_loss;

    /** \brief Sprite displayed over the ends of the bars. */
    bear::visual::sprite m_tube_clamp;

    /** \brief Sprite displayed over the bar. */
    bear::visual::sprite m_glass_tube;

    /** \brief The maximum value of the bar. */
    double m_max_value;

    /** \brief The current value of the bar. */
    double m_level_value;

    /** \brief The green intensity of clamp. */
    double m_clamp_green_intensity;

    /** \brief Indicates how the clamp intensity increases. */
    double m_clamp_increment_direction;

  }; // class horizontal_gauge
} // namespace ptb

#endif // __PTB_HORIZONTAL_GAUGE_HPP__
