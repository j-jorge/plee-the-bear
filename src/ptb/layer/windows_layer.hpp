/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The windows_layer is a layer containing the windows.
 * \author Julien Jorge
 */
#ifndef __PTB_WINDOWS_LAYER_HPP__
#define __PTB_WINDOWS_LAYER_HPP__

#include "communication/messageable.hpp"
#include "engine/layer/gui_layer.hpp"
#include "gui/types.hpp"
#include "input/keyboard.hpp"
#include "input/joystick.hpp"

#include <list>
#include <map>
#include <claw/tween/tweener_group.hpp>

namespace ptb
{
  class frame;
  class score_message;

  /**
   * \brief The windows_layer is a layer containing windows.
   * \author Julien Jorge
   */
  class windows_layer:
    public bear::communication::messageable,
    public bear::engine::gui_layer
  {
  public:
    /** \brief The type of a list of scene elements retrieved from the layer. */
    typedef bear::engine::gui_layer::scene_element_list scene_element_list;

  private:
    /** \brief Informations on a window in the stack. */
    typedef frame* window_item;

    /** \brief The type of the main super class. */
    typedef bear::engine::gui_layer super;

  public:
    windows_layer();
    explicit windows_layer( const std::string& name );

    ~windows_layer();

    void build();
    void progress( bear::universe::time_type elapsed_time );

    bool key_pressed( const bear::input::key_info& key );
    bool char_pressed( const bear::input::key_info& key );
    bool button_pressed( bear::input::joystick::joy_code button,
                         unsigned int joy_index );
    bool mouse_pressed( bear::input::mouse::mouse_code key,
                        const claw::math::coordinate_2d<unsigned int>& pos );
    bool mouse_released( bear::input::mouse::mouse_code key,
                        const claw::math::coordinate_2d<unsigned int>& pos );
    bool mouse_maintained( bear::input::mouse::mouse_code key,
                        const claw::math::coordinate_2d<unsigned int>& pos );
    bool mouse_move( const claw::math::coordinate_2d<unsigned int>& pos );

    void render( scene_element_list& e ) const;

    void clear();
    bool empty() const;
    void show_centered_window( window_item wnd );
    void replace_window( window_item old_wnd, window_item new_wnd );
    void show_window( window_item wnd );

    bool close_window();

    virtual bool process_score_message( const score_message& msg );

  private:
    void pop_window();
    void delete_next_window();

    void apply_show_effect( window_item wnd );
    void apply_hide_effect( window_item wnd, bool d );

  private:
    /** \brief The pending windows. */
    std::list<window_item> m_windows;

    /** \brief The windows that are going to be deleted. */
    std::list<window_item> m_dying_windows;

    /** \brief The bottom of the each window when shown for the first time. */
    std::map<window_item, bear::gui::coordinate_type> m_ref_bottom;

    /** \brief The tweeners that manage the position of the windows. */
    claw::tween::tweener_group m_tweener;

    /** \brief The duration of the effects that show and hide the frames. */
    static const double s_effect_duration;

  }; // class windows_layer
} // namespace ptb

#endif // __PTB_WINDOWS_LAYER_HPP__
