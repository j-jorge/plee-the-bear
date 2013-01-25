/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Some interface related things that do not need an individual layer.
 * \author Julien Jorge
 */
#ifndef __PTB_MISC_LAYER_HPP__
#define __PTB_MISC_LAYER_HPP__

#include "engine/layer/gui_layer.hpp"
#include "input/key_info.hpp"
#include "time/time.hpp"
#include "visual/sprite.hpp"

#include <claw/smart_ptr.hpp>

// predeclarations
namespace bear
{
  namespace engine
  {
    class sync;
  } // namespace engine

  namespace gui
  {
    class static_text;
  } // namespace gui

} // namespace bear

namespace ptb
{
  /**
   * \brief Some interface related things that do not need an individual layer.
   * \author Julien Jorge
   */
  class misc_layer:
    public bear::engine::gui_layer
  {
  public:
    /** \brief The type of a list of scene elements retrieved from the layer. */
    typedef bear::engine::gui_layer::scene_element_list scene_element_list;

  private:
    /**
     * \brief A function object that saves an image.
     */
    template<typename ImageWriter>
    class screenshot_file_save
    {
    public:
      void operator()() const;

    public:
      /** \brief The image to save. */
      claw::memory::smart_ptr<claw::graphic::image> image;

      /** \brief The path to the image to save. */
      std::string file_path;

    }; // struct screenshot_file_save

  public:
    misc_layer();
    ~misc_layer();

    void build();
    void progress( bear::universe::time_type elapsed_time );
    void render( scene_element_list& e ) const;

    bool key_pressed( const bear::input::key_info& key );
    bool mouse_move( const claw::math::coordinate_2d<unsigned int>& pos );

  private:
    void levelshot() const;
    void screenshot() const;
    template<typename ImageWriter>
    void screenshot( const std::string& name ) const;

    void sequence_screenshot();
    void start_screenshot_sequence();
    void stop_screenshot_sequence();

    void render_fps( scene_element_list& e ) const;
    void render_demo( scene_element_list& e ) const;
    void render_network_status( scene_element_list& e ) const;

    std::string format_sync( const bear::engine::sync& sync ) const;

  private:
    /** \brief The component in which we show the numer of frames per second. */
    bear::gui::static_text* m_fps_text;

    /** \brief The number of frames rendered in the current second. */
    mutable unsigned int m_fps_count;

    /** \brief The number of iterations done in the current second. */
    mutable unsigned int m_its_count;

    /** \brief Tell if we must show the number tof frames per second. */
    bool m_show_fps;

    /** \brief The mouse cursor. */
    bear::visual::sprite m_cursor;

    /** \brief The last position of the mouse. */
    bear::visual::position_type m_cursor_position;

    /** \brief Elapsed time since the last move of the mouse. */
    bear::universe::time_type m_mouse_idle;

    /** \brief The prefix of the name given to the screenshots in the current
        sequence. */
    std::string m_screenshot_prefix;

    /** \brief How many screenshots did we do in the current sequence. */
    std::size_t m_screenshots_count;

    /** \brief The date at which we started to record the game. */
    bear::systime::milliseconds_type m_first_screenshot;

    /** \brief The date of the last screenshot in the sequence. */
    bear::systime::milliseconds_type m_last_screenshot;

    /** \brief The date of the last fps check. */
    mutable bear::systime::milliseconds_type m_last_fps_check;

    /** \brief The key to display the number of frames per second. */
    bear::input::key_code m_fps_key;

    /** \brief The key to take a screenshot. */
    bear::input::key_code m_screenshot_key;

    /** \brief The key to toggle fullscreen mode. */
    bear::input::key_code m_fullscreen_key;

    /** \brief The key to record the a sequence of screenshots. */
    bear::input::key_code m_screenshot_sequence_key;

    /** \brief The key to take a picture of the whole level. */
    bear::input::key_code m_levelshot_key;

    /** \brief The key to toggle the overview of the level. */
    bear::input::key_code m_overview_key;

  }; // class misc_layer
} // namespace ptb

#endif // __PTB_MISC_LAYER_HPP__
