/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::level_ending_effect class.
 * \author Julien Jorge
 */
#include "ptb/transition_effect/level_ending_effect.hpp"

#include "ptb/item/bonus_points/bonus_points.hpp"
#include "ptb/item/bonus_manager.hpp"
#include "ptb/util/player_util.hpp"

#include "engine/game.hpp"
#include "engine/level.hpp"
#include "visual/scene_sprite.hpp"
#include "visual/scene_line.hpp"
#include "visual/scene_writing.hpp"

#include "ptb/defines.hpp"
#include "ptb/level_variables.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/gui/horizontal_gauge.hpp"

#include <claw/configuration_file.hpp>

#include <libintl.h>
#include <limits>

/*----------------------------------------------------------------------------*/
const bear::visual::coordinate_type
ptb::level_ending_effect::score_line::s_shadow_delta(2);
const double ptb::level_ending_effect::score_line::s_scale_factor(0.5);
const bear::visual::coordinate_type
ptb::level_ending_effect::score_line::s_bonus_picture_margin(10);

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param glob Level globals in which we take the resources.
 * \param f The font to use for the texts.
 * \param text A short description of the reason we're giving the points for.
 * \param points The initial score.
 * \param picture_filename The filename containing the bonus picture.
 * \param picture_name The name of the bonus picture.
 */
ptb::level_ending_effect::score_line::score_line
( bear::engine::level_globals& glob,
  const bear::visual::font& f, const std::string& text, unsigned int points,
  const std::string& picture_filename, const std::string& picture_name)
  : m_font(f), m_label(m_font, text), m_points(points), m_y(0), m_time(0)
{
  // force creating the writing
  decrease_score(0);

  if ( !picture_filename.empty() && !picture_name.empty() )
    {
      m_bonus_sprite = glob.auto_sprite( picture_filename, picture_name );
      m_bonus_sprite.set_size(32, 32);
    }
} // level_ending_effect::score_line::score_line()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the scene elements of the score.
 * \param e (out) The scene element of the score.
 * \param left The minimum x-position of the elements.
 * \param right The maximum x-position of the elements.
 */
void ptb::level_ending_effect::score_line::render
( scene_element_list& e, bear::visual::coordinate_type left,
  bear::visual::coordinate_type right ) const
{
  // text shadow
  bear::visual::scene_writing label
    (left + s_shadow_delta + m_bonus_sprite.get_size().x
     + s_bonus_picture_margin, m_y, m_label);

  label.set_scale_factor(s_scale_factor, s_scale_factor);
  label.get_rendering_attributes().set_intensity(0, 0, 0);

  e.push_back( label );

  // underline
  std::vector<bear::visual::position_type> p(2);
  p[0].set(left + m_bonus_sprite.get_size().x, m_y);
  p[1].set(right, p[0].y);

  e.push_back
    ( bear::visual::scene_line
      ( s_shadow_delta, 0, claw::graphic::black_pixel, p, 1) );
  e.push_back
    ( bear::visual::scene_line( 0, s_shadow_delta, PTB_ORANGE_PIXEL, p, 1) );

  // text
  label.set_position(left + m_bonus_sprite.get_size().x
                     + s_bonus_picture_margin, m_y + s_shadow_delta);
  label.get_rendering_attributes().set_intensity(1, 1, 1);

  e.push_back( label );

  // points shadow
  bear::visual::coordinate_type x
    (right - m_points_text.get_width() * s_scale_factor);
  bear::visual::scene_writing points(x + s_shadow_delta, m_y, m_points_text);

  points.set_scale_factor(s_scale_factor, s_scale_factor);
  points.get_rendering_attributes().set_intensity(0, 0, 0);

  e.push_back( points );

  // points text
  points.set_position(x - s_shadow_delta, m_y + s_shadow_delta);
  points.get_rendering_attributes().set_intensity(1, 1, 1);

  e.push_back( points );

  // bonus picture
  bear::visual::scene_sprite sp
    (left, m_y+(m_bonus_sprite.get_size().y-get_height())/2, m_bonus_sprite );

  e.push_back( sp );
} // level_ending_effect::score_line::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the score.
 */
unsigned int ptb::level_ending_effect::score_line::get_score() const
{
  return m_points;
} // level_ending_effect::score_line::get_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Decrease the score.
 * \param delta The value of the decrement.
 * \return How much the score was decreased (ie. min(delta, get_score())).
 */
unsigned int
ptb::level_ending_effect::score_line::decrease_score( unsigned int delta )
{
  unsigned int s;

  if (m_points <= delta)
    s = m_points;
  else
    s = delta;

  m_points -= s;

  std::ostringstream oss;
  oss << m_points;

  m_points_text.create(m_font, oss.str());

  return s;
} // level_ending_effect::score_line::decrease_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the height of the line.
 */
bear::visual::coordinate_type
ptb::level_ending_effect::score_line::get_height() const
{
  return std::max
    ( m_label.get_height() * s_scale_factor + s_shadow_delta,
      m_bonus_sprite.get_size().y );
} // level_ending_effect::score_line::get_height()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the y-position of the line.
 */
bear::visual::coordinate_type
ptb::level_ending_effect::score_line::get_y_position() const
{
  return m_y;
} // level_ending_effect::score_line::get_y_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the y-position of the line.
 * \param y The position.
 */
void ptb::level_ending_effect::score_line::set_y_position
( bear::visual::coordinate_type y )
{
  m_y = y;
} // level_ending_effect::score_line::set_y_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell how long the line has been displayed.
 */
bear::universe::time_type ptb::level_ending_effect::score_line::get_time() const
{
  return m_time;
} // level_ending_effect::score_line::get_time()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add some time to how long the line has been displayed.
 * \param t The time to add.
 */
void ptb::level_ending_effect::score_line::add_time
( bear::universe::time_type t )
{
  m_time += t;
} // level_ending_effect::score_line::add_time()




/*----------------------------------------------------------------------------*/
const unsigned int ptb::level_ending_effect::s_points_per_second(1000);
const bear::visual::coordinate_type
ptb::level_ending_effect::s_screen_margin(80);
const bear::visual::coordinate_type ptb::level_ending_effect::s_margin(10);
const double ptb::level_ending_effect::s_score_line_speed(50);

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::level_ending_effect::level_ending_effect()
  : m_speed_factor(1), m_next_tick(0.1), m_score_bar(NULL), m_world(NULL)
{

} // level_ending_effect::level_ending_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Copy constructor.
 * \param that The instance to copy from.
 */
ptb::level_ending_effect::level_ending_effect( const level_ending_effect& that )
  : bear::engine::transition_effect(that), m_speed_factor(that.m_speed_factor),
    m_next_tick(that.m_next_tick), m_score_bar(NULL), m_world(that.m_world)
{

} // level_ending_effect::level_ending_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::level_ending_effect::~level_ending_effect()
{
  delete m_score_bar;
} // level_ending_effect::~level_ending_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the world in which we search the bonus points.
 * \param w The world.
 */
void ptb::level_ending_effect::set_world( const bear::engine::world* w )
{
  m_world = w;
} // level_ending_effect::set_world()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the effect is finished.
 */
bool ptb::level_ending_effect::is_finished() const
{
  return false;
} // level_ending_effect::is_finished()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the effect.
 */
void ptb::level_ending_effect::build()
{
  fill_points();
  update_bonus_state();

  std::list<score_line>::iterator it;
  bear::visual::coordinate_type top
    (get_layer().get_size().y - s_screen_margin);

  for (it=m_points.begin(); it!=m_points.end(); ++it)
    {
      it->set_y_position(top - it->get_height());
      top -= it->get_height() + s_margin;
    }

  m_score_bar =
    new horizontal_gauge
    ( get_level_globals(), get_layer().get_size().x - 2 * s_screen_margin,
      "bar (violet)" );
  // arbitrary value
  m_score_bar->set_max_level( std::numeric_limits<unsigned int>::max() );
} // level_ending_effect::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Adjust the components of the effect.
 * \param elapsed_time Elapsed time since the last call.
 */
bear::universe::time_type
ptb::level_ending_effect::progress( bear::universe::time_type elapsed_time )
{
  bool do_start_level = update_lines(elapsed_time);

  update_score_bar(elapsed_time);
  update_tick(elapsed_time);

  if (do_start_level)
    bear::engine::game::get_instance().set_waiting_level
      ( PTB_LOADING_LEVEL_NAME );

  m_speed_factor = 1;

  return 0;
} // level_ending_effect::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the components of the effect.
 * \param e (out) The scene elements.
 */
void ptb::level_ending_effect::render( scene_element_list& e ) const
{
  bear::visual::coordinate_type left(s_screen_margin);
  bear::visual::coordinate_type right(get_layer().get_size().x -  left);
  bool stop(false);
  const bear::visual::coordinate_type bottom(s_screen_margin);
  std::list<score_line>::const_iterator it;

  for (it=m_points.begin(); !stop && (it!=m_points.end()); ++it)
    if ( it->get_score() != 0 )
      {
        if ( it->get_y_position() < bottom )
          stop = true;
        else
          it->render(e, left, right);
      }

  m_score_bar->render
    (e,
     bear::visual::position_type
     ( (get_layer().get_size().x - m_score_bar->width()) / 2,
       s_screen_margin - m_score_bar->height()/2 ) );
} // level_ending_effect::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the effect that a key had been pressed.
 * \param key The value of the pressed key.
 * \remark This effect pretends to treat all keys, so we can maintain the pause
 *         mode.
 */
bool ptb::level_ending_effect::key_pressed( const bear::input::key_info& key )
{
  // prevent pausing the game
  return true;
} // level_ending_effect::key_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the effect that a key is maintained.
 * \param key The value of the pressed key.
 */
bool
ptb::level_ending_effect::key_maintained( const bear::input::key_info& key )
{
  m_speed_factor = 10;

  return true;
} // level_ending_effect::key_maintained()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the effect that a joystick button had been pressed.
 * \param button The value of the pressed button.
 * \param joy_index The index of the joystick.
 * \remark This effect pretends to treat all keys, so we can maintain the pause
 *         mode.
 */
bool ptb::level_ending_effect::button_pressed
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  // prevent pausing the game
  return true;
} // level_ending_effect::button_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the effect that a joystick button is maintained.
 * \param button The value of the pressed button.
 * \param joy_index The index of the joystick.
 */
bool ptb::level_ending_effect::button_maintained
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  m_speed_factor = 10;

  return true;
} // level_ending_effect::button_maintained()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if a player wins a new try with a given amount of points.
 * \param s The points that would be given.
 */
void ptb::level_ending_effect::check_new_try(unsigned int s)
{
  for ( unsigned int i = 1; i <= 2; ++i )
    {
      const unsigned int old_score(game_variables::get_score(i));
      const unsigned int new_score( old_score + s );
      if ( (old_score / PTB_ONE_UP_POINTS_COUNT)
           < (new_score / PTB_ONE_UP_POINTS_COUNT) )
        {
          player_proxy p = util::find_player( get_level_globals(), i );

          if ( p != NULL )
            p.give_one_up();
        }
    }
} // level_ending_effect::check_new_try()

/*----------------------------------------------------------------------------*/
/**
 * \brief Fill m_points with the values of the bonus_points alive in the world.
 */
void ptb::level_ending_effect::fill_points()
{
  if ( m_world == NULL )
    return;

  bear::visual::font f
    ( get_level_globals().get_font("font/level_name-42x50.fnt", 50) );

  bear::engine::world::const_item_iterator it;
  for (it=m_world->living_items_begin(); it!=m_world->living_items_end(); ++it)
    {
      const bonus_points* pts = dynamic_cast<const bonus_points*>(&(*it));

      if ( pts != NULL )
        {
          unsigned int point(pts->get_points());
          if ( point != 0 )
            m_points.push_back
              ( score_line
                ( get_level_globals(), f, pts->get_name(), point,
                  pts->get_picture_filename(), pts->get_picture_name()) );
        }
    }
} // level_ending_effect::fill_points()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update bonus states alive in the world.
 */
void ptb::level_ending_effect::update_bonus_state()
{
  if ( m_world == NULL )
    return;

  bear::engine::world::const_item_iterator it;
  for (it=m_world->living_items_begin(); it!=m_world->living_items_end(); ++it)
    {
      const bonus_points* pts = dynamic_cast<const bonus_points*>(&(*it));

      if ( pts != NULL )
        pts->update_bonus_state();
    }

  for (it=m_world->living_items_begin(); it!=m_world->living_items_end(); ++it)
    {
      bonus_manager* manager =
        dynamic_cast<bonus_manager*>(&(*it));

      if ( manager != NULL )
        manager->manage();
    }
} // level_ending_effect::update_bonus_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the position and the content of the lines.
 * \param elapsed_time Elapsed time since the last call.
 */
bool ptb::level_ending_effect::update_lines
( bear::universe::time_type elapsed_time )
{
  std::list<score_line>::iterator it;
  // is it the time to start the next level?
  bool start_level(true);
  bear::visual::coordinate_type top(get_layer().get_size().y - s_screen_margin);

  for (it=m_points.begin(); it!=m_points.end(); ++it)
    if ( (it->get_score() != 0) || (it->get_time() <= 2) )
      {
        start_level = false;

        it->add_time( elapsed_time );
        const unsigned int s =
          it->decrease_score
          (s_points_per_second * m_speed_factor * elapsed_time);

        check_new_try(s);

        game_variables::add_score(1, s);
        game_variables::add_score(2, s);

        if ( it->get_y_position() + it->get_height() < top )
          it->set_y_position
            ( std::min
              (top - it->get_height(),
               it->get_y_position() + s_score_line_speed * elapsed_time) );

        top -= it->get_height() + s_margin;
      }

  return start_level;
} // level_ending_effect::update_lines()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the score bar.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::level_ending_effect::update_score_bar
( bear::universe::time_type elapsed_time )
{
  m_score_bar->set_level
    ( game_variables::get_score(1) + game_variables::get_score(2) );
  m_score_bar->progress(elapsed_time);
} // update_score_bar()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the date of the tick and play the sound if needed.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::level_ending_effect::update_tick
( bear::universe::time_type elapsed_time )
{
  if ( m_next_tick > elapsed_time )
    m_next_tick -= elapsed_time;
  else
    {
      get_level_globals().play_sound("sound/tick.ogg");

      if ( m_speed_factor > 1 )
        m_next_tick = 0.05;
      else
        m_next_tick = 0.1;
    }
} // level_ending_effect::update_tick()
