/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A sequencer plays a song and displays the notes. The player has to
 *        execute some actions to stay in rhythm.
 * \author Julien Jorge
 */
#ifndef __PTB_SEQUENCER_HPP__
#define __PTB_SEQUENCER_HPP__

#include "ptb/item_brick/item_with_single_player_action_reader.hpp"

#include "audio/sample.hpp"
#include "engine/item_brick/item_with_toggle.hpp"
#include "engine/item_brick/with_expression_creation.hpp"
#include "engine/base_item.hpp"
#include "universe/derived_item_handle.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A sequencer plays a song and displays the notes. The player has to
   *        execute some actions to stay in rhythm.
   *
   * The custom fields of this class are:
   * - notes.sprite (list of sprites), the sprites used to display
   *   the notes,
   * - notes.animations (list of animations), the animations used to display
   *   the notes,
   * - notes.track (string) [required], the track file, describing the sequence
   *   of notes.
   * - view_distance (double), how far in time, in seconds, the notes are
   *   displayed (default=2),
   * - song (sample) [required], the song to play,
   * - score.success (unsigned int), the score given to the player when he's
   *   right (default=100),
   * - score.miss (unsigned int), the score taken from the player when he miss a
   *   note (default=10),
   * - score.fail (unsigned int), the score taken from the player when he's
   *   wrong (default=20),
   * - score.trigger_threshold (unsigned int), the score over which
   *   toggle.on_success is toggled (default=0),
   * - toggle.on_success (item), the item toggled if the player's score is
   *   greater or equal to score.trigger_threshold (default=none),
   * - toggle.on_failure (item), the item toggled if the player's score is
   *   less than score.trigger_threshold (default=none),
   * - any field supported by the parent class.
   *
   * \remark At least one of \a notes.sprites and \a notes.animations has to be
   * set.
   *
   * The format of the track file is as follows. The first line contains the
   * duration of the song, in seconds, and the width of the sequencer (ie. how
   * many notes). Then come the chords: a sequence of lines with the date at
   * which the notes must be played and the pattern of the notes as a string,
   * where a dot means the note must not be pressed, while a one means the note
   * has to be pressed.
   *
   * Lines beginning with a # are ignored. Here is an example:
   *
   * <tt>\verbatim
# 30 seconds song, 4 notes displayed<br/>
30 4

# 120 bpm, 2 s. per measure

# measure #1 is empty<br/>
# measure #2 is empty

# measure #3<br/>
4.00      1...<br/>
4.25      .1..<br/>
4.50      ..1.<br/>
4.75      ...1<br/>
5.00      ..1.<br/>
\endverbatim</tt>
   *
   * \author Julien Jorge
   */
  class sequencer:
    public item_with_single_player_action_reader
  < bear::engine::item_with_toggle
    < bear::engine::base_item > >,
    public bear::engine::with_linear_expression_creation
  {
    DECLARE_BASE_ITEM(sequencer);

  public:
    /** \brief The type of the parent class. */
    typedef item_with_single_player_action_reader
    < bear::engine::item_with_toggle
      < bear::engine::base_item > > super;

  private:
    /** \brief The type of the handles on the toggles activated by the
        sequencer. */
    typedef bear::universe::derived_item_handle<with_toggle> toggle_handle;

    /** \brief The data associated with a note of the song. */
    struct chord
    {
      /** \brief The chords on which the chord is played. */
      std::string pressed;

      /** \brief The date when the chord has to be played. */
      bear::universe::time_type date;

      /** \brief Tell if the chord has been pressed on time. */
      bool played;

    }; // struct chord

    /** \brief The data of the track currently played. */
    struct track
    {
      /** \brief The total duration of the track. */
      bear::universe::time_type duration;

      /** \brief The width of the track, as the number of notes. */
      unsigned int width;

      /** \brief The chords to play. */
      std::vector<chord> chords;

    }; // struct track

  public:
    sequencer();
    ~sequencer();

    void pre_cache();
    void build();
    void get_visual( std::list<bear::engine::scene_visual>& visuals) const;

    bool set_sprite_list_field
    ( const std::string& name, const std::vector<bear::visual::sprite>& value );
    bool set_animation_list_field
    ( const std::string& name,
      const std::vector<bear::visual::animation>& value );
    bool set_string_field( const std::string& name, const std::string& value );
    bool set_real_field( const std::string& name, double value );
    bool set_u_integer_field( const std::string& name, unsigned int value );
    bool set_item_field
    ( const std::string& name, bear::engine::base_item* value );
    bool set_sample_field
    ( const std::string& name, bear::audio::sample* value );

    bool is_valid() const;

    bear::audio::sample const* get_song() const;

    unsigned int get_performance() const;

  private:
    void on_toggle_on(bear::engine::base_item *activator);
    void on_toggle_off(bear::engine::base_item *activator);
    void progress_on(bear::universe::time_type elapsed_time);

    bool adjust_current_position( bear::universe::time_type threshold );
    void check_pressed( bear::universe::time_type threshold );
    void restore_volume();

    void start_action(player_action::value_type a);
    void stop_action(player_action::value_type a);

    bool load_track_file( const std::string& file_name );
    void song_finished();

    bear::expr::linear_expression do_get_expression() const;

  private:
    /** \brief The song played by this sequencer. */
    bear::audio::sample* m_song;

    /** \brief The data of the song. */
    track m_track;

    /** \brief The animations representing the notes. */
    std::vector<bear::visual::animation> m_note_visual;

    /** \brief The animations representing the bridge. */
    std::vector<bear::visual::animation> m_bridge_visual;

    /** \brief The volume of the song, saved before muting the song. Set to
               zero when the song is not muted.*/
    double m_saved_volume;

    /** \brief Elapsed time since the beginning of the song. */
    bear::universe::time_type m_elapsed_time;

    /** \brief The position from which we start displaying the tracker. */
    std::size_t m_current_position;

    /** \brief The chords currently pressed. */
    std::string m_current_chord;

    /** \brief How far do we display the notes. */
    bear::universe::time_type m_view_distance;

    /** \brief The current state of the bridge. */
    std::string m_pressed;

    /** \brief The previous state of the bridge. */
    std::string m_previous_pressed;

    /** \brief The score given to the player when he's right. */
    unsigned int m_score_success;

    /** \brief The score taken from the player when he miss a note. */
    unsigned int m_score_miss;

    /** \brief The score taken from the player when he's wrong. */
    unsigned int m_score_fail;

    /** \brief The score that will be given to the player at the end. */
    int m_current_score;

    /** \brief The score over which we activate the trigger of the winner. */
    int m_trigger_score;

    /** \brief The item toggled when the player's score is greater or equal to
        m_trigger_score. */
    toggle_handle m_toggle_win;

    /** \brief The item toggled when the player's score is less than
        m_trigger_score. */
    toggle_handle m_toggle_lose;

    /** \brief The action to do to give up the song. */
    player_action::value_type m_give_up_action;

    /** \brief The margin between two notes. */
    static const bear::universe::coordinate_type s_margin;

  }; // class sequencer
} // namespace ptb

#endif // __PTB_SEQUENCER_HPP__
