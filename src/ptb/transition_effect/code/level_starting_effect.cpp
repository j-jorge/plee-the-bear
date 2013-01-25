/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::level_starting_effect class.
 * \author Julien Jorge
 */
#include "ptb/transition_effect/level_starting_effect.hpp"

#include "engine/level.hpp"
#include "engine/level_globals.hpp"
#include "engine/resource_pool.hpp"
#include "visual/scene_line.hpp"
#include "visual/scene_rectangle.hpp"
#include "visual/scene_sprite.hpp"
#include "visual/scene_writing.hpp"

#include "ptb/defines.hpp"
#include "ptb/util/level_util.hpp"

#include <libintl.h>
#include <algorithm>

/*----------------------------------------------------------------------------*/
const bear::visual::size_type
ptb::level_starting_effect::s_widescreen_strip_height(150);

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::level_starting_effect::level_starting_effect()
  : m_visibility_duration(5), m_fade_time(3), m_elapsed_time(0),
    m_thumb_center(686, 75), m_thumb_zoom_max(1.1), m_thumb_zoom(1),
    m_thumb_zoom_direction(0.02), m_widescreen_delta(0)
{

} // level_starting_effect::level_starting_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the effect is finished.
 */
bool ptb::level_starting_effect::is_finished() const
{
  return m_elapsed_time >= m_visibility_duration;
} // level_starting_effect::is_finished()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the effect.
 */
void ptb::level_starting_effect::build()
{
  create_controls();
  fill_controls();
} // level_starting_effect::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Adjust the components of the effect.
 * \param elapsed_time Elapsed time since the last call.
 */
bear::universe::time_type
ptb::level_starting_effect::progress( bear::universe::time_type elapsed_time )
{
  bear::universe::time_type result(0);

  if ( m_elapsed_time < m_visibility_duration )
    {
      if ( m_elapsed_time > m_fade_time )
        {
          if ( m_thumb.is_valid() )
            {
              m_thumb.set_size
                ( (unsigned int)
                  (m_thumb.clip_rectangle().width * m_thumb_zoom),
                  (unsigned int)
                  (m_thumb.clip_rectangle().height * m_thumb_zoom) );

              m_thumb.set_angle( m_thumb.get_angle() + 0.1 );
            }

          if ( m_thumb_zoom > 0 )
            {
              m_thumb_zoom += m_thumb_zoom_direction;

              if ( m_thumb_zoom + m_thumb_zoom_direction > m_thumb_zoom_max )
                m_thumb_zoom_direction = -m_thumb_zoom_direction;
            }

          ++m_widescreen_delta;
        }

      m_elapsed_time += elapsed_time;

      if ( m_elapsed_time > m_visibility_duration )
        result = m_elapsed_time - m_visibility_duration;
    }

  return result;
} // level_starting_effect::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the components of the effect.
 * \param e (out) The scene elements.
 */
void ptb::level_starting_effect::render( scene_element_list& e ) const
{
  const bear::visual::position_type act_position
    ( (get_layer().get_size().x - m_act.get_width()) / 2,
      (s_widescreen_strip_height - m_act.get_height()) / 2 );
  std::vector<bear::visual::position_type> act_line(2);
  act_line[0].x = 0;
  act_line[0].y = act_position.y + m_act.get_height() / 2;
  act_line[1].x = get_layer().get_size().x;
  act_line[1].y = act_line[0].y;

  e.push_back
    ( bear::visual::scene_rectangle
      (0, -m_widescreen_delta, claw::graphic::black_pixel,
       m_widescreen_strip) );
  e.push_back
    ( bear::visual::scene_rectangle
      (0,
       get_layer().get_size().y - s_widescreen_strip_height
       + m_widescreen_delta,
       claw::graphic::black_pixel, m_widescreen_strip) );

  e.push_back
    ( bear::visual::scene_line(0, 0, PTB_ORANGE_PIXEL, act_line, 1) );

  if ( m_thumb.is_valid() )
    e.push_back
      ( bear::visual::scene_sprite
        (m_thumb_center.x - m_thumb.width() / 2,
         m_thumb_center.y - m_thumb.height() / 2, m_thumb) );

  e.push_back
    ( bear::visual::scene_writing
      (50, get_layer().get_size().y - s_widescreen_strip_height
       + m_widescreen_delta
       + (s_widescreen_strip_height - m_level_name.get_height()) / 2,
       m_level_name) );
  e.push_back
    ( bear::visual::scene_writing( act_position.x, act_position.y, m_act ) );
  e.push_back
    ( bear::visual::scene_writing
      ( get_layer().get_size().x - m_game_name.get_width() - 7,
        s_widescreen_strip_height / 2 - 1.5 * m_game_name.get_height()
        - m_widescreen_delta,
        m_game_name ) );
} // level_starting_effect::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the controls of the interface.
 */
void ptb::level_starting_effect::create_controls()
{
  m_game_name.create
    ( get_level_globals().get_font("font/fixed_white-7x12.fnt", 12),
      "Plee the Bear" );

  m_widescreen_strip.set
    ( 0, 0, get_layer().get_size().x, s_widescreen_strip_height );
} // level_starting_effect::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Fill the controls of the interface.
 */
void ptb::level_starting_effect::fill_controls()
{
  bear::visual::font fnt
    ( get_level_globals().get_font("font/level_name-42x50.fnt", 50) );

  const std::string act_keyword(" act ");
  std::string level_name = get_layer().get_level().get_name();
  std::string::size_type pos = level_name.rfind(act_keyword);

  std::string sub_act = "1";

  // extract the level name and the act number
  if ( pos != std::string::npos )
    {
      if ( pos + act_keyword.length() != level_name.size() )
        sub_act = level_name.substr( pos + act_keyword.length() );

      level_name = level_name.substr(0, pos);
    }

  m_act.create(fnt, gettext("act") + (' ' + sub_act));

  // get the thumbnail
  const std::string thumb_name =
    util::get_thumbnail(get_layer().get_level().get_filename());

  bear::visual::size_box_type s
    ( get_layer().get_size().x - 100, 2 * fnt.get_line_spacing() );

  if ( bear::engine::resource_pool::get_instance().exists( thumb_name ) )
    {
      bear::engine::level_globals& glob = get_level_globals();

      m_thumb = bear::visual::sprite( glob.get_image( thumb_name ) );
      s.x -= m_thumb.width() + 50;
      m_thumb_center.x = get_layer().get_size().x - 50 - m_thumb.width() / 2;
      m_thumb_center.y =
        get_layer().get_size().y - m_thumb.height() / 2
        - (s_widescreen_strip_height - m_thumb.height()) / 2;
    }

  if ( !level_name.empty() )
    m_level_name.create(fnt, gettext(level_name.c_str()), s );
} // level_starting_effect::fill_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the effect that a key had been pressed.
 * \param key The value of the pressed key.
 * \remark This effect pretends to treat all keys, so we can maintain the pause
 *         mode.
 */
bool ptb::level_starting_effect::key_pressed( const bear::input::key_info& key )
{
  // prevent pausing the game
  return true;
} // level_starting_effect::key_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the effect that a joystick button had been pressed.
 * \param button The value of the pressed button.
 * \param joy_index The index of the joystick.
 * \remark This effect pretends to treat all keys, so we can maintain the pause
 *         mode.
 */
bool ptb::level_starting_effect::button_pressed
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  // prevent pausing the game
  return true;
} // level_starting_effect::button_pressed()
