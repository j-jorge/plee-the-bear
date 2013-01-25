/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The effect displayed at the introduction of the levels.
 * \author Julien Jorge
 */
#ifndef __PTB_LEVEL_ENDING_EFFECT_HPP__
#define __PTB_LEVEL_ENDING_EFFECT_HPP__

#include "engine/transition_effect/transition_effect.hpp"
#include "engine/world.hpp"
#include "visual/writing.hpp"

namespace ptb
{
  class horizontal_gauge;

  /**
   * \brief The effect displayed at the introduction of the levels.
   * \author Julien Jorge
   */
  class level_ending_effect:
    public bear::engine::transition_effect
  {
  public:
    /** \brief The type of a list of scene elements retrieved from the layer.*/
    typedef std::list<bear::visual::scene_element> scene_element_list;

  private:
    /** \brief A line of points displayed on the screen. */
    class score_line
    {
    public:
      score_line
      ( bear::engine::level_globals& glob, const bear::visual::font& f,
        const std::string& text, unsigned int points,
        const std::string& picture_filename, const std::string& picture_name );

      void render
      ( scene_element_list& e, bear::visual::coordinate_type left,
        bear::visual::coordinate_type right ) const;

      unsigned int get_score() const;
      unsigned int decrease_score( unsigned int delta );
      bear::visual::coordinate_type get_height() const;

      double get_y_position() const;
      void set_y_position( double y );

      bear::universe::time_type get_time() const;
      void add_time( bear::universe::time_type t );

    private:
      /** \brief The font used for the writings. */
      bear::visual::font m_font;

      /** \brief Explain the reason of the points. */
      bear::visual::writing m_label;

      /** \brief The remaining points, as a text. */
      bear::visual::writing m_points_text;

      /** \brief The sprite of the bonus picture. */
      bear::visual::sprite m_bonus_sprite;

      /** \brief The remaining points. */
      unsigned int m_points;

      /** \brief The y-position of the score. */
      bear::visual::coordinate_type m_y;

      /** \brief How long the line has been displayed. */
      bear::universe::time_type m_time;

      /** \brief A delta applied to the text to create shadows. */
      static const bear::visual::coordinate_type s_shadow_delta;

      /** \brief Margin on the right of bonus picture. */
      static const bear::visual::coordinate_type s_bonus_picture_margin;

      /** \brief The scale factor applied to the text. */
      static const double s_scale_factor;

    }; // class score_line

  public:
    level_ending_effect();
    level_ending_effect( const level_ending_effect& that );
    ~level_ending_effect();

    void set_world( const bear::engine::world* w );

    bool is_finished() const;
    void build();
    bear::universe::time_type
    progress( bear::universe::time_type elapsed_time );
    void render( scene_element_list& e ) const;

  private:
    void create_controls();
    void fill_controls();

    bool key_pressed( const bear::input::key_info& key );
    bool key_maintained( const bear::input::key_info& key );
    bool button_pressed
    ( bear::input::joystick::joy_code button, unsigned int joy_index );
    bool button_maintained
    ( bear::input::joystick::joy_code button, unsigned int joy_index );
    void check_new_try(unsigned int s);

    void fill_points();
    void update_bonus_state();

    bool update_lines( bear::universe::time_type elapsed_time );
    void update_score_bar( bear::universe::time_type elapsed_time );
    void update_tick( bear::universe::time_type elapsed_time );

    // not implemented
    level_ending_effect& operator=( const level_ending_effect& that );

  private:
    /** \brief The remaining points to give. */
    std::list<score_line> m_points;

    /** \brief A factor applied to s_points_per_second. */
    double m_speed_factor;

    /** \brief The date at which we emit the next tick sound. */
    bear::universe::time_type m_next_tick;

    /** \brief The bar displaying the sum of the players' points. */
    horizontal_gauge* m_score_bar;

    /** \brief The world where we search for the bonus points. */
    const bear::engine::world* m_world;

    /** \brief How many points are given per second. */
    static const unsigned int s_points_per_second;

    /** \brief The default margin around the score lines. */
    static const bear::visual::coordinate_type s_screen_margin;

    /** \brief The margin between two score lines. */
    static const bear::visual::coordinate_type s_margin;

    /** \brief The speed in screen unit/sec. of the movement of a score line. */
    static const double s_score_line_speed;

  }; // class level_ending_effect
} // namespace ptb

#endif // __PTB_LEVEL_ENDING_EFFECT_HPP__
