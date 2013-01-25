/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A control reading and displaying the name of a key.
 * \author Julien Jorge
 */
#ifndef __PTB_KEY_EDIT_HPP__
#define __PTB_KEY_EDIT_HPP__

#include "gui/callback.hpp"
#include "gui/static_text.hpp"
#include "input/controller_button.hpp"

namespace ptb
{
  /**
   * \brief A control reading and displaying the name of a key.
   * \author Julien Jorge
   */
  class key_edit:
    public bear::gui::static_text
  {
  private:
    typedef
    std::pair<unsigned int, bear::input::joystick::joy_code> joystick_pair;

  public:
    explicit key_edit
    ( const bear::visual::font& font,
      const bear::input::controller_button& b =
      bear::input::controller_button(),
      const bear::gui::callback& change_callback = bear::gui::callback() );

    void set_key( const bear::input::controller_button& c );
    const bear::input::controller_button& get_key() const;

    void set_change_callback( const bear::gui::callback& c );

  private:
    bool on_key_press( const bear::input::key_info& key );
    bool on_button_press
    ( bear::input::joystick::joy_code button, unsigned int joy_index );
    bool on_mouse_press( bear::input::mouse::mouse_code key,
                         const claw::math::coordinate_2d<unsigned int>& pos );

    void edit_mode_off();
    void edit_mode_on();

    void set_key_callback( const bear::input::controller_button& key );

    void set_label();

  private:
    /** \brief Tell if we are reading the input. */
    bool m_edit_mode;

    /** \brief The controller button displayed in the control. */
    bear::input::controller_button m_button;

    /** \brief The callback executed when the button is changed. */
    bear::gui::callback m_change_callback;

    /** \brief The color to which the background will be set the next time the
        edit mode is changed. */
    bear::gui::color_type m_next_background_color;

  }; // class key_edit
} // namespace ptb

#endif // __PTB_KEY_EDIT_HPP__
