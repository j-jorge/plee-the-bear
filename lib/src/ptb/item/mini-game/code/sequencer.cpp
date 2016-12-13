/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::sequencer class.
 * \author Julien Jorge
 */
#include "ptb/item/mini-game/sequencer.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/item/floating_score.hpp"
#include "engine/level_globals.hpp"
#include "engine/resource_pool.hpp"
#include "expr/linear_function.hpp"
#include "visual/scene_sprite.hpp"

#include <claw/logger.hpp>
#include <claw/string_algorithm.hpp>
#include <algorithm>

BASE_ITEM_EXPORT( sequencer, ptb )

/*----------------------------------------------------------------------------*/
const bear::universe::coordinate_type ptb::sequencer::s_margin(5);

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::sequencer::sequencer()
  : m_song(NULL), m_view_distance(3), m_score_success(100), m_score_miss(10),
    m_score_fail(20), m_current_score(0), m_trigger_score(0),
    m_toggle_win(NULL), m_toggle_lose(NULL)
{
  set_phantom(true);
  set_can_move_items(false);
} // sequencer::sequencer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::sequencer::~sequencer()
{
  delete m_song;
} // sequencer::~sequencer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the datas required for this item.
 */
void ptb::sequencer::pre_cache()
{
  super::pre_cache();

  get_level_globals().load_image
    ("gfx/mini-game/sequencer/bridge-button.png");
  get_level_globals().load_sound("sound/sequencer/fail.ogg");
} // ptb::sequencer::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::sequencer::build()
{
  super::build();

  bear::visual::size_type w
    ( (get_width() - m_track.width * s_margin) / m_track.width );

  m_bridge_visual.push_back
    ( get_level_globals().auto_sprite
      ("gfx/mini-game/sequencer/bridge-button.png", "left") );
  m_bridge_visual.push_back
    ( get_level_globals().auto_sprite
      ("gfx/mini-game/sequencer/bridge-button.png", "up") );
  m_bridge_visual.push_back
    ( get_level_globals().auto_sprite
      ("gfx/mini-game/sequencer/bridge-button.png", "down") );
  m_bridge_visual.push_back
    ( get_level_globals().auto_sprite
      ("gfx/mini-game/sequencer/bridge-button.png", "right") );

  for (std::size_t i=0; i!=m_track.width; ++i)
    {
      m_note_visual[i].set_size
        ( w, m_note_visual[i].height() / m_note_visual[i].width() * w );

      m_bridge_visual[i].set_size
        ( w, m_bridge_visual[i].height() / m_bridge_visual[i].width() * w );
      m_bridge_visual[i].set_intensity(0.5, 0.5, 0.5);
    }
} // sequencer::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visuals of this item.
 * \param visuals (out) The visuals.
 */
void ptb::sequencer::get_visual
( std::list<bear::engine::scene_visual>& visuals ) const
{
  super::get_visual(visuals);

  if ( !is_on() )
    return;

  bool stop = false;

  const bear::universe::coordinate_type delta
    ( m_bridge_visual[0].height() / 2 );

  for ( std::size_t i=m_current_position;
        !stop && (i!=m_track.chords.size()); ++i )
    if ( m_track.chords[i].date - m_elapsed_time > m_view_distance )
      stop = true;
    else
      {
        bear::universe::coordinate_type x = get_left() + s_margin / 2;
        bear::universe::coordinate_type y = get_bottom() + delta
          + (m_track.chords[i].date - m_elapsed_time) / m_view_distance
          * (get_height() - delta);

        for ( std::size_t j=0; j!=m_track.width; ++j )
          {
            if ( m_track.chords[i].pressed[j] != '.' )
              {
                bear::visual::scene_sprite e
                  ( x,
                    y - m_note_visual[j].height() / 2,
                    m_note_visual[j].get_sprite() );

                visuals.push_back( bear::engine::scene_visual(e) );
              }

            x += m_note_visual[j].width() + s_margin;
          }
      }

  bear::universe::coordinate_type x = get_left() + s_margin / 2;

  for ( std::size_t j=0; j!=m_track.width; ++j )
    {
      bear::visual::scene_sprite e
        ( x,
          get_bottom(),
          m_bridge_visual[j].get_sprite() );

      visuals.push_back( bear::engine::scene_visual(e) );

      x += m_bridge_visual[j].width() + s_margin;
    }
} // sequencer::get_visual()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type list of sprite.
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::sequencer::set_sprite_list_field
( const std::string& name, const std::vector<bear::visual::sprite>& value )
{
  bool result(true);

  if ( name == "sequencer.notes.sprites" )
    {
      m_note_visual.resize(value.size());

      for (std::size_t i=0; i!=value.size(); ++i)
        m_note_visual[i] = value[i];
    }
  else
    result = super::set_sprite_list_field(name, value);

  return result;
} // sequencer::set_sprite_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type list of animation.
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::sequencer::set_animation_list_field
( const std::string& name, const std::vector<bear::visual::animation>& value )
{
  bool result(true);

  if ( name == "sequencer.notes.animations" )
    m_note_visual = value;
  else
    result = super::set_animation_list_field(name, value);

  return result;
} // sequencer::set_animation_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type string.
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::sequencer::set_string_field
( const std::string& name, const std::string& value)
{
  bool result(true);

  if ( name == "sequencer.notes.track" )
    result = load_track_file(value);
  else if ( name == "sequencer.give_up_action" )
    m_give_up_action = player_action::from_string(value);
  else
    result = super::set_string_field(name, value);

  return result;
} // sequencer::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type double.
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::sequencer::set_real_field( const std::string& name, double value)
{
  bool result(true);

  if ( name == "sequencer.view_distance" )
    m_view_distance = value;
  else
    result = super::set_real_field(name, value);

  return result;
} // sequencer::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type unsigned int.
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::sequencer::set_u_integer_field
( const std::string& name, unsigned int value)
{
  bool result(true);

  if ( name == "sequencer.score.success" )
    m_score_success = value;
  else if ( name == "sequencer.score.miss" )
    m_score_miss = value;
  else if ( name == "sequencer.score.fail" )
    m_score_fail = value;
  else if ( name == "sequencer.score.trigger_threshold" )
    m_trigger_score = value;
  else
    result = super::set_u_integer_field(name, value);

  return result;
} // sequencer::set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type item
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::sequencer::set_item_field
( const std::string& name, base_item* value)
{
  bool result(true);

  if ( name == "sequencer.toggle.on_success" )
    {
      m_toggle_win = value;
      result = m_toggle_win != (bear::engine::with_toggle*)NULL;
    }
  else if ( name == "sequencer.toggle.on_failure" )
    {
      m_toggle_lose = value;
      result = m_toggle_lose != (bear::engine::with_toggle*)NULL;
    }
  else
    result = super::set_item_field(name, value);

  return result;
} // sequencer::set_item_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type sample.
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::sequencer::set_sample_field
( const std::string& name, bear::audio::sample* value)
{
  bool result(true);

  if ( name == "sequencer.song" )
    m_song = value;
  else
    result = super::set_sample_field(name, value);

  return result;
} // sequencer::set_sample_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if all fields have a correct value.
 */
bool ptb::sequencer::is_valid() const
{
  return (m_song != NULL)
    && ( m_track.width <= 4 )
    && ( m_note_visual.size() >= m_track.width )
    && super::is_valid();
} // sequencer::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the song played in this sequencer.
 */
bear::audio::sample const* ptb::sequencer::get_song() const
{
  return m_song;
} // sequencer::get_song()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the performance of the player as the ratio between 0 and 100
 *        percents.
 */
unsigned int ptb::sequencer::get_performance() const
{
  return m_current_score * 100 / ( m_track.chords.size() * m_score_success );
} // sequencer::get_performance()

/*----------------------------------------------------------------------------*/
/**
 * \brief Actions done when the state of the toggle changes from off to on.
 * \param activator The item that changed the state.
 */
void ptb::sequencer::on_toggle_on(bear::engine::base_item *activator)
{
  m_saved_volume = 0;
  m_elapsed_time = 0;
  m_current_position = 0;
  m_pressed = std::string(m_track.width, '.');
  m_previous_pressed = m_pressed;
  m_current_score = 0;
  m_song->play();
} // sequencer::on_toggle_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Actions done when the state of the toggle changes from on to off.
 * \param activator The item that changed the state.
 */
void ptb::sequencer::on_toggle_off(bear::engine::base_item *activator)
{
  m_song->stop();
} // sequencer::on_toggle_off()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item when turned on.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::sequencer::progress_on(bear::universe::time_type elapsed_time)
{
  progress_input_actions(elapsed_time);

  // update the position in the song
  m_elapsed_time += elapsed_time;

  const bear::universe::time_type threshold
    (m_bridge_visual[0].height() / get_height() * m_view_distance);

  // we don't care until the first note
  if ( m_elapsed_time < m_track.chords[0].date - threshold )
    return;

  if ( adjust_current_position(threshold) )
    check_pressed(threshold);

  for (std::size_t i=0; i!=m_bridge_visual.size(); ++i)
    m_bridge_visual[i].next(elapsed_time);

  if ( m_elapsed_time >= m_track.duration )
    song_finished();
} // sequencer::progress_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Adjust the current position with the elapsed time. Decrease the score
 *        for missed notes.
 * \param threshold The time interval in which we allow to press the notes.
 * \return true if the song is not finished.
 */
bool
ptb::sequencer::adjust_current_position( bear::universe::time_type threshold )
{
  bool stop=false;

  while ( !stop && (m_current_position!=m_track.chords.size()) )
    if ( m_elapsed_time - m_track.chords[m_current_position].date > threshold )
      {
        if ( !m_track.chords[m_current_position].played
             && (m_saved_volume == 0) )
          {
            bear::audio::sound_effect e(m_song->get_effect());
            m_saved_volume = e.get_volume();
            e.set_volume( m_saved_volume * 0.25 );
            m_song->set_effect(e);

            m_current_score -= m_score_miss;
          }

        ++m_current_position;
      }
    else
      stop = true;

  return stop;
} // sequencer::adjust_current_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check the currently pressed notes and adjust the score.
 * \param threshold The time interval in which we allow to press the notes.
 */
void ptb::sequencer::check_pressed( bear::universe::time_type threshold )
{
  if ( m_pressed==m_previous_pressed )
    return;

  m_previous_pressed = m_pressed;

  if ( m_pressed.find_first_not_of('.') != std::string::npos )
    {
      bool fail(true);

      // check if the notes are in the bridge
      if ( std::abs(m_track.chords[m_current_position].date - m_elapsed_time)
           < threshold )
        if ( m_track.chords[m_current_position].pressed == m_pressed )
          {
            m_track.chords[m_current_position].played = true;

            if ( m_saved_volume != 0 )
              restore_volume();

            fail = false;

            m_current_score += m_score_success;
          }

      if (fail)
        {
          bear::audio::sound_effect e(m_song->get_effect());

          if (m_saved_volume == 0)
            m_saved_volume = e.get_volume();

          get_level_globals().play_sound("sound/sequencer/fail.ogg");

          e.set_volume(0);

          m_song->set_effect(e);

          m_current_score -= m_score_fail;
        }
    }
} // sequencer::check_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Restore the initial volume of the song.
 */
void ptb::sequencer::restore_volume()
{
  bear::audio::sound_effect e(m_song->get_effect());
  e.set_volume(m_saved_volume);
  m_saved_volume = 0;
  m_song->set_effect(e);
} // sequencer::restore_volume()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start an action asked by the human player.
 * \param a The action to start.
 */
void ptb::sequencer::start_action(player_action::value_type a)
{
  switch(a)
    {
    case player_action::move_left:
      if ( m_track.width > 0 )
        {
          m_pressed[0] = '1';
          m_bridge_visual[0].reset();
          m_bridge_visual[0].set_intensity(1, 1, 1);
        }
      break;
    case player_action::look_upward:
      if ( m_track.width > 1 )
        {
          m_pressed[1] = '1';
          m_bridge_visual[1].reset();
          m_bridge_visual[1].set_intensity(1, 1, 1);
        }
      break;
    case player_action::crouch:
      if ( m_track.width > 2 )
        {
          m_pressed[2] = '1';
          m_bridge_visual[2].reset();
          m_bridge_visual[2].set_intensity(1, 1, 1);
        }
      break;
    case player_action::move_right:
      if ( m_track.width > 3 )
        {
          m_pressed[3] = '1';
          m_bridge_visual[3].reset();
          m_bridge_visual[3].set_intensity(1, 1, 1);
        }
      break;
    }
} // sequencer::start_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop an action asked by the human player.
 * \param a The action to start.
 */
void ptb::sequencer::stop_action(player_action::value_type a)
{
  switch(a)
    {
    case player_action::move_left:
      if ( m_track.width > 0 )
        {
          m_pressed[0] = '.';
          m_bridge_visual[0].set_intensity(0.5, 0.5, 0.5);
        }
      break;
    case player_action::look_upward:
      if ( m_track.width > 1 )
        {
          m_pressed[1] = '.';
          m_bridge_visual[1].set_intensity(0.5, 0.5, 0.5);
        }
      break;
    case player_action::crouch:
      if ( m_track.width > 2 )
        {
          m_pressed[2] = '.';
          m_bridge_visual[2].set_intensity(0.5, 0.5, 0.5);
        }
      break;
    case player_action::move_right:
      if ( m_track.width > 3 )
        {
          m_pressed[3] = '.';
          m_bridge_visual[3].set_intensity(0.5, 0.5, 0.5);
        }
      break;
    }
} // sequencer::stop_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the file with the position of the notes.
 * \param file_name The name of the file to load.
 */
bool ptb::sequencer::load_track_file( const std::string& file_name )
{
  std::stringstream f;
  bear::engine::resource_pool::get_instance().get_file(file_name, f);
  std::string line;
  track t;
  bool result(false);
  bear::universe::time_type prev_date(0);
  std::size_t n(0);

  while ( !result && std::getline(f, line) )
    {
      claw::text::trim(line);

      if ( !line.empty() )
        if ( line[0] != '#' )
          {
            std::istringstream iss(line);
            result = bool( iss >> t.duration >> t.width );
          }

      ++n;
    }

  while ( result && std::getline(f, line) )
    {
      claw::text::trim(line);

      if ( !line.empty() )
        if ( line[0] != '#' )
          {
            std::istringstream iss(line);
            chord c;

            c.played = false;

            if (iss >> c.date >> c.pressed)
              {
                if ( c.date <= prev_date )
                  claw::logger << claw::log_warning
                               << file_name
                               << ": The date of the chord on line " << n
                               << " is before the previous one. Skipping."
                               << std::endl;
                else if ( c.pressed.length() != t.width )
                  claw::logger << claw::log_warning
                               << file_name
                               << ": Incorrect width on line " << n
                               << ". Skipping." << std::endl;
                else
                  {
                    t.chords.push_back(c);
                    prev_date = c.date;
                  }
              }
            else
              result = false;
        }

      ++n;
    }

  if (result)
    std::swap(m_track, t);

  return result;
} // sequencer::load_track_file()

/*----------------------------------------------------------------------------*/
/**
 * \brief The song is finished. Give the score to the player and change the
 *        state of the toggles.
 */
void ptb::sequencer::song_finished()
{
  floating_score* s = new floating_score;
  new_item(*s);

  s->add_points( get_player_index(), std::max(0, m_current_score) );
  s->set_bottom_middle( get_bottom_middle() );
  s->set_z_position( get_z_position() + 1 );

  if ( m_current_score >= m_trigger_score )
    {
      if ( m_toggle_win != (bear::engine::with_toggle*)NULL )
        m_toggle_win->toggle(this);
    }
  else if ( m_toggle_lose != (bear::engine::with_toggle*)NULL )
    m_toggle_lose->toggle(this);

  toggle_off(this);
} // sequencer::song_finished()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a linear expression returning the performance of the player.
 */
bear::expr::linear_expression ptb::sequencer::do_get_expression() const
{
  return bear::expr::linear_function_maker
    ( bear::universe::const_derived_item_handle<sequencer>(this),
      std::mem_fun_ref(&sequencer::get_performance) );
} // sequencer::do_get_expression();
