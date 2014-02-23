/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The base frame, with default borders and background.
 * \author Julien Jorge
 */
#ifndef __PTB_FRAME_HPP__
#define __PTB_FRAME_HPP__

#include "gui/frame.hpp"

namespace ptb
{
  class windows_layer;

  /**
   * \brief The base frame, with default borders and background.
   * \author Julien Jorge
   */
  class frame:
    public bear::gui::frame
  {
  private:
    /** \brief The type of the list of controls that can be activated with the
        cursor. */
    typedef std::vector<bear::gui::visual_component*> control_group;

  public:
    explicit frame( windows_layer* owning_layer );
    frame( windows_layer* owning_layer, const std::string& title );

    bear::visual::sprite get_arrow() const;
    bear::visual::sprite get_cursor() const;
    bear::visual::sprite get_checkbox_off() const;
    bear::visual::sprite get_checkbox_on() const;
    bear::visual::sprite get_radio_off() const;
    bear::visual::sprite get_radio_on() const;
    bear::visual::sprite get_slider_bar() const;
    bear::visual::sprite get_slider() const;
    bear::visual::font get_font() const;
    bear::visual::size_type get_margin() const;

    windows_layer& get_layer() const;

    static void set_borders_up( bear::gui::visual_component& c );
    static void set_borders_down( bear::gui::visual_component& c );

    virtual void on_focus();

  protected:
    void show_window( frame* wnd ) const;
    void replace_with( frame* wnd );
    void close_window() const;

    void insert_control( bear::gui::visual_component& c );
    void allow_focus( bear::gui::visual_component& c );

    bool process_key_press( const bear::input::key_info& key );
    bool process_button_press( bear::input::joystick::joy_code button,
                               unsigned int joy_index );
    bool process_mouse_move
    ( const claw::math::coordinate_2d<unsigned int>& pos );

    bool on_key_press( const bear::input::key_info& key );
    bool on_button_press( bear::input::joystick::joy_code button,
                          unsigned int joy_index );
    bool on_mouse_move( const claw::math::coordinate_2d<unsigned int>& pos );

  private:
    bear::visual::sprite get_frame_sprite( const std::string& name ) const;

    void common_init();

    void move_cursor_up();
    void move_cursor_down();
    void move_cursor_left();
    void move_cursor_right();

    template< typename CurrentValue1, typename OtherValue1,
              typename CurrentValue2, typename OtherValue2 >
    std::size_t find_nearest_control
    ( const CurrentValue1& current_value_1, const OtherValue1& other_value_1,
      const CurrentValue2& current_value_2,
      const OtherValue2& other_value_2,
      bool reversed = false) const;

    bool highlight_control_at
    ( const claw::math::coordinate_2d<unsigned int>& pos );

    void switch_to_control( std::size_t i );

    void on_focused();

  private:
    /** \brief The layer owning this window. */
    windows_layer* const m_owning_layer;

    /** \brief A group of controls that can be activated with the cursor. */
    control_group m_controls;

    /** \brief The control currently highlighted. */
    std::size_t m_current_control;
  }; // class frame
} // namespace ptb

#endif // __PTB_FRAME_HPP__
