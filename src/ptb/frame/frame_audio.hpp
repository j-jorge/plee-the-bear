/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This frame is shown to choose the audio parameters.
 * \author Julien Jorge
 */
#ifndef __PTB_FRAME_AUDIO_HPP__
#define __PTB_FRAME_AUDIO_HPP__

#include "ptb/frame/frame.hpp"
#include "gui/slider.hpp"

namespace ptb
{
  /**
   * \brief This frame is shown to choose the audio parameters.
   * \author Julien Jorge
   */
  class frame_audio:
    public frame
  {
  public:
    typedef frame super;

  public:
    frame_audio( windows_layer* in_layer );

    void set_volume();

  private:
    void create_controls();
    bear::gui::visual_component* create_music_checkbox( bear::visual::font f );
    bear::gui::visual_component* create_sound_checkbox( bear::visual::font f );
    bear::gui::visual_component* create_music_slider();
    bear::gui::visual_component* create_sound_slider();
    bear::gui::visual_component* create_ok_button( bear::visual::font f );
    bear::gui::visual_component* create_cancel_button( bear::visual::font f );

    void save();
    void cancel() const;

    bool on_ok();
    bool on_cancel();
    bool on_close();

  private:
    /* \brief The sound 'mute' status when the frame was shown. */
    const bool m_saved_sound_muted;

    /* \brief The music 'mute' status when the frame was shown. */
    const bool m_saved_music_muted;

    /* \brief The sound volume when the frame was shown. */
    const bool m_saved_sound_volume;

    /* \brief The music volume when the frame was shown. */
    const double m_saved_music_volume;

    /** \brief Slider to control the volume of the sounds. */
    bear::gui::slider<double>* m_sound_volume;

    /** \brief Slider to control the volume of the music. */
    bear::gui::slider<double>* m_music_volume;

    /** \brief Indicates if ok button has been pressed. */
    bool m_ok_is_pressed;

  }; // class frame_audio
} // namespace ptb

#endif // __PTB_FRAME_AUDIO_HPP__
