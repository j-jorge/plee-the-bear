/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This items controls at most two sequencers, the background music, the
 *        players who activate them and so on.
 * \author Julien Jorge
 */
#ifndef __PTB_SEQUENCER_CONTROL_HPP__
#define __PTB_SEQUENCER_CONTROL_HPP__

#include "ptb/item/mini-game/sequencer.hpp"
#include "universe/derived_item_handle.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief This items controls at most two sequencers, the background music,
   *        the players who activate them and so on.
   *
   * The custom fields of this class are:
   * - backround_music (sample), the song played in the background,
   * - game_interval (real), delay between two games (default=infinity),
   * - sequencer.first (item), the sequencer for the first player
   *   (default=none),
   * - sequencer.second (item), the sequencer for the second player
   *   (default=none),
   * - give_up_action (string), the name of the action to do to give up the song
   *   (default=jump),
   * - any field supported by the parent class.
   *
   * \author Julien Jorge
   */
  class sequencer_control:
    public item_with_player_action_reader
  < bear::engine::item_with_toggle
    < bear::engine::base_item > >
  {
    DECLARE_BASE_ITEM(sequencer_control);

  public:
    /** \brief The type of the parent class. */
    typedef item_with_player_action_reader
    < bear::engine::item_with_toggle
      < bear::engine::base_item > > super;

  private:
    /** \brief The type of the handles on the toggles activated by the
        sequencer_control. */
    typedef bear::universe::derived_item_handle<sequencer> sequencer_handle;

  public:
    sequencer_control();
    ~sequencer_control();

    bool set_string_field( const std::string& name, const std::string& value );
    bool set_real_field( const std::string& name, double value );
    bool set_item_field
    ( const std::string& name, bear::engine::base_item* value );
    bool set_sample_field
    ( const std::string& name, bear::audio::sample* value );

  private:
    void common_build();

    void build_on();
    void build_off();
    void on_toggle_on(bear::engine::base_item *activator);
    void on_toggle_off(bear::engine::base_item *activator);
    void progress_on(bear::universe::time_type elapsed_time);
    void progress_off(bear::universe::time_type elapsed_time);

    void start_action(unsigned int player_index, player_action::value_type a);

    void toggle_sequencer( const sequencer_handle& s, bool b );

  private:
    /** \brief Did we play at least one time? */
    bool m_played_once;

    /** \brief Are we currently playing the songs? */
    bool m_playing;

    /** \brief The background music. */
    bear::audio::sample* m_background_music;

    /** \brief The song of the second sequencer, in a single player game. */
    bear::audio::sample* m_second_track;

    /** \brief The sequencer for the first player. */
    sequencer_handle m_first_sequencer;

    /** \brief The sequencer for the second player. */
    sequencer_handle m_second_sequencer;

    /** \brief The action to do to give up the song. */
    player_action::value_type m_give_up_action;

    /** \brief The delay between two games. */
    bear::universe::time_type m_game_interval;

    /** \brief Elapsed time since we are off. */
    bear::universe::time_type m_elapsed_time_off;

  }; // class sequencer_control
} // namespace ptb

#endif // __PTB_SEQUENCER_CONTROL_HPP__
