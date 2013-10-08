/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::sequencer_control class.
 * \author Julien Jorge
 */
#include "ptb/item/mini-game/sequencer_control.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/util/player_util.hpp"
#include "engine/level.hpp"
#include "engine/level_globals.hpp"

BASE_ITEM_EXPORT( sequencer_control, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::sequencer_control::sequencer_control()
: m_played_once(false), m_playing(false), m_background_music(NULL),
  m_second_track(NULL), m_first_sequencer(NULL), m_second_sequencer(NULL),
  m_give_up_action(player_action::jump),
  m_game_interval(std::numeric_limits<bear::universe::time_type>::infinity()),
  m_elapsed_time_off(0)
{
  set_phantom(true);
  set_can_move_items(false);
} // sequencer_control::sequencer_control()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::sequencer_control::~sequencer_control()
{
  delete m_background_music;
  delete m_second_track;
} // sequencer_control::~sequencer_control()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type string.
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::sequencer_control::set_string_field
( const std::string& name, const std::string& value)
{
  bool result(true);

  if ( name == "sequencer_control.give_up_action" )
    m_give_up_action = player_action::from_string(value);
  else
    result = super::set_string_field(name, value);

  return result;
} // sequencer_control::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type double.
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::sequencer_control::set_real_field
( const std::string& name, double value )
{
  bool result(true);

  if ( name == "sequencer_control.game_interval" )
    m_game_interval = value;
  else
    result = super::set_real_field(name, value);

  return result;
} // sequencer_control::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type item
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::sequencer_control::set_item_field
( const std::string& name, base_item* value)
{
  bool result(true);

  if ( name == "sequencer_control.sequencer.first" )
    {
      m_first_sequencer = value;
      result = m_first_sequencer != (sequencer*)NULL;
    }
  else if ( name == "sequencer_control.sequencer.second" )
    {
      m_second_sequencer = value;
      result = m_second_sequencer != (sequencer*)NULL;
    }
  else
    result = super::set_item_field(name, value);

  return result;
} // sequencer_control::set_item_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type sample.
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::sequencer_control::set_sample_field
( const std::string& name, bear::audio::sample* value)
{
  bool result(true);

  if ( name == "sequencer_control.background_music" )
    m_background_music = value;
  else
    result = super::set_sample_field(name, value);

  return result;
} // sequencer_control::set_sample_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Common initialisation for build_on() and build_off().
 */
void ptb::sequencer_control::common_build()
{
  if ( game_variables::get_players_count() == 1 )
    if ( m_second_sequencer != (sequencer*)NULL )
      {
        const bear::audio::sample* s = m_second_sequencer->get_song();

        if (s!=NULL)
          m_second_track = get_level_globals().new_sample( *s );
      }
} // sequencer_control::common_build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item in its on state.
 */
void ptb::sequencer_control::build_on()
{
  common_build();
  on_toggle_on(this);
} // sequencer_control::build_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item in its off state.
 */
void ptb::sequencer_control::build_off()
{
  common_build();
} // sequencer_control::build_off()

/*----------------------------------------------------------------------------*/
/**
 * \brief Actions done when the state of the toggle changes from off to on.
 * \param activator The item that changed the state.
 */
void ptb::sequencer_control::on_toggle_on(bear::engine::base_item *activator)
{
  if ( !m_played_once || (m_elapsed_time_off >= m_game_interval) )
    {
      get_level().stop_music();

      toggle_sequencer(m_first_sequencer, true);

      if ( game_variables::get_players_count() == 2 )
        toggle_sequencer(m_second_sequencer, true);
      else if (m_second_track != NULL)
        m_second_track->play();

      m_background_music->play();
      m_played_once = true;
      m_playing = true;
    }
} // sequencer_control::on_toggle_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Actions done when the state of the toggle changes from on to off.
 * \param activator The item that changed the state.
 */
void ptb::sequencer_control::on_toggle_off(bear::engine::base_item *activator)
{
  if (!m_playing )
    return;

  m_background_music->stop();

  toggle_sequencer(m_first_sequencer, false);

  if ( game_variables::get_players_count() == 2 )
    toggle_sequencer(m_second_sequencer, false);
  else if (m_second_track != NULL)
    m_second_track->stop();

  get_level().play_music();
  m_elapsed_time_off = 0;
  m_playing = false;
} // sequencer_control::on_toggle_off()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item when turned on.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::sequencer_control::progress_on(bear::universe::time_type elapsed_time)
{
  progress_input_reader(elapsed_time);

  bool off = true;

  if ( m_first_sequencer != (sequencer*)NULL )
    off = off && !m_first_sequencer->is_on();

  if ( m_second_sequencer != (sequencer*)NULL )
    off = off && !m_second_sequencer->is_on();

  if (off)
    toggle_off(this);
} // sequencer_control::progress_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item when turned off.
 * \param elapsed_time Elapsed time since the last call.
 */
void
ptb::sequencer_control::progress_off(bear::universe::time_type elapsed_time)
{
  m_elapsed_time_off += elapsed_time;
} // sequencer_control::progress_off()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start an action asked by the human player.
 * \param player_index The player doing the action.
 * \param a The action to start.
 */
void ptb::sequencer_control::start_action
( unsigned int player_index, player_action::value_type a )
{
  if (a == m_give_up_action)
    toggle_off(this);
} // sequencer_control::start_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Toggle the state of a sequencer.
 * \param s The sequencer to change.
 * \param b The new state of \a s.
 */
void ptb::sequencer_control::toggle_sequencer
( const sequencer_handle& s, bool b )
{
  if ( s != (sequencer*)NULL )
    {
      s->toggle(b, this);

      player_proxy p =
        util::find_player( get_level_globals(), s->get_player_index() );

      if (p!=NULL)
        p.set_marionette(b);
    }
} // sequencer_control::toggle_sequencer()

