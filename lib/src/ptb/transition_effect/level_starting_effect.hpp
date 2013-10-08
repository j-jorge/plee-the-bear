/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The effect displayed at the introduction of the levels.
 * \author Julien Jorge
 */
#ifndef __PTB_LEVEL_STARTING_EFFECT_HPP__
#define __PTB_LEVEL_STARTING_EFFECT_HPP__

#include "visual/writing.hpp"
#include "engine/transition_effect/transition_effect.hpp"

namespace ptb
{
  /**
   * \brief The effect displayed at the introduction of the levels.
   * \author Julien Jorge
   */
  class level_starting_effect:
    public bear::engine::transition_effect
  {
  public:
    /** \brief The type of a list of scene elements retrieved from the layer. */
    typedef std::list<bear::visual::scene_element> scene_element_list;

  public:
    level_starting_effect();

    bool is_finished() const;
    void build();
    bear::universe::time_type
    progress( bear::universe::time_type elapsed_time );
    void render( scene_element_list& e ) const;

  private:
    void create_controls();
    void fill_controls();

    bool key_pressed( const bear::input::key_info& key );
    bool button_pressed
    ( bear::input::joystick::joy_code button, unsigned int joy_index );

  private:
    /** \brief How long the layer stays visible. */
    const bear::universe::time_type m_visibility_duration;

    /** \brief The time before m_fill_color starts to fade. */
    const bear::universe::time_type m_fade_time;

    /** \brief Elapsed time since the effect was created. */
    bear::universe::time_type m_elapsed_time;

    /** \brief The name of the level. */
    bear::visual::writing m_level_name;

    /** \brief The act of the level. */
    bear::visual::writing m_act;

    /** \brief The thumbnail of the level. */
    bear::visual::sprite m_thumb;

    /** \brief The position of the thumbnail of the level. */
    bear::visual::position_type m_thumb_center;

    /** \brief The maximum zoom of the thumbnail of the level. */
    const double m_thumb_zoom_max;

    /** \brief The zoom of the thumbnail of the level. */
    double m_thumb_zoom;

    /** \brief The directrion of the zoom of the thumbnail of the level. */
    double m_thumb_zoom_direction;

    /** \brief The polygon of the strip at the top and the bottom of the
        screen. */
    bear::visual::rectangle_type m_widescreen_strip;

    /** \brief A delta applied on the y-position of the strip at the top and the
        bottom of the screen. */
    bear::visual::coordinate_type m_widescreen_delta;

    /** \brief The name of the game. */
    bear::visual::writing m_game_name;

    /** \brief The height of the widescreen strip. */
    static const bear::visual::size_type s_widescreen_strip_height;

  }; // class level_starting_effect
} // namespace ptb

#endif // __PTB_LEVEL_STARTING_EFFECT_HPP__
