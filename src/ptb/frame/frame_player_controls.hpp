/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This frame is the configuration menu.
 * \author Julien Jorge
 */
#ifndef __PTB_FRAME_PLAYER_CONTROLS_HPP__
#define __PTB_FRAME_PLAYER_CONTROLS_HPP__

#include "ptb/frame/frame.hpp"
#include "ptb/controller_layout.hpp"

#include "gui/picture.hpp"
#include "gui/static_text.hpp"

namespace ptb
{
  class key_edit;

  /**
   * \brief This frame is the configuration menu.
   * \author Julien Jorge
   */
  class frame_player_controls:
    public frame
  {
  private:
    typedef
    std::pair<unsigned int, bear::input::joystick::joy_code> joystick_pair;

    /**
     * \brief This class groups a key_edit with the associated action or
     *        command.
     */
    template<typename ValueType>
    class key_edit_data
    {
    public:
      key_edit_data( ValueType v, key_edit* e );

    public:
      /** \brief The action/command/etc. edited. */
      ValueType value;

      /** \brief The control used to edit the value. */
      key_edit* edit;

    }; // class key_edit_data

    typedef key_edit_data<gui_command::value_type> command_edit_data;
    typedef key_edit_data<player_action::value_type> action_edit_data;

  public:
    frame_player_controls
    ( windows_layer* owning_layer, unsigned int player_index );

  private:
    void on_ok();
    void on_action_changed( const key_edit* e, player_action::value_type a );
    void on_command_changed( const key_edit* e, gui_command::value_type c );

    void create_controls();
    bear::gui::visual_component* create_ok_button();
    bear::gui::visual_component* create_cancel_button();
    bear::gui::size_type create_command_entries( bear::gui::coordinate_type b );
    bear::gui::size_type create_action_entries( bear::gui::coordinate_type b );

    void show_key_values();

    void save() const;

    bear::gui::static_text*
    make_static_text( const std::string& t, bear::visual::coordinate_type b );

    key_edit* make_key_edit_command( gui_command::value_type c );
    key_edit* make_key_edit_action( player_action::value_type a );

  private:
    /** \brief Index of the plyer for which we change the controls. */
    const unsigned int m_player_index;

    /** \brief The controller layout of the current player. */
    controller_layout m_controller_layout;

    /** \brief The controller layout of the other player. */
    controller_layout m_other_controller_layout;

    /** \brief The controls used to edit the gui commands. */
    std::vector<command_edit_data> m_commands;

    /** \brief The controls used to edit the actions. */
    std::vector<action_edit_data> m_actions;

    /** \brief The width of the text boxes. */
    static const bear::gui::size_type s_text_box_width;

  }; // class frame_player_controls
} // namespace ptb

#endif // __PTB_FRAME_PLAYER_CONTROLS_HPP__
