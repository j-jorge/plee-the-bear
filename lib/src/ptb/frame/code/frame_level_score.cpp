/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_level_score class.
 * \author Julien Jorge
 */
#include "ptb/frame/frame_level_score.hpp"

#include "ptb/frame/theme_colors.hpp"
#include "ptb/layer/windows_layer.hpp"
#include "ptb/score_table.hpp"
#include "ptb/util/player_util.hpp"

#include "gui/button.hpp"
#include "gui/callback_function.hpp"
#include "gui/static_text.hpp"
#include "gui/picture.hpp"

#include "engine/game.hpp"
#include "engine/level.hpp"
#include "engine/level_globals.hpp"

#include <boost/bind.hpp>
#include <claw/string_algorithm.hpp>
#include <claw/system_info.hpp>
#include <libintl.h>

/*----------------------------------------------------------------------------*/
std::string ptb::frame_level_score::s_player_name;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param in_layer The layer owning the window.
 * \param t The table in which the scores are saved.
 * \param score The score to save.
 * \param medal The type of the medal corresponging to this score ("gold",
 *        "silver", "bronze", "empty").
 * \param format How to format the value of the score.
 * \param next_level The name path to the level to load once the score is saved.
 */
ptb::frame_level_score::frame_level_score
( windows_layer* in_layer, score_table& t, double score,
  const std::string& medal, const std::string& format,
  const std::string& next_level )
  : frame(in_layer), m_text(NULL), m_score_table(t), m_score(score),
    m_next_level(next_level),
    m_new_record(m_score_table.is_good_candidate(m_score))
{
  create_controls(medal, format);

  player_proxy p =
    util::find_player( get_layer().get_level().get_globals(), 1 );

  if ( p != NULL )
    p.set_marionette(true);

  p = util::find_player( get_layer().get_level().get_globals(), 2 );

  if ( p != NULL )
    p.set_marionette(true);
} // frame_level_score::frame_level_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the controls.
 * \param medal The type of the medal to show.
 * \param format How to format the value of the score.
 */
void ptb::frame_level_score::create_controls
( const std::string& medal, const std::string& format )
{
  if ( m_new_record )
    create_new_record_controls(medal, format);
  else
    create_no_new_record_controls(medal, format);

  fit( get_margin() );
} // frame_level_score::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the controls for the case of a new record.
 * \param medal The type of the medal to show.
 * \param format How to format the value of the score.
 */
void ptb::frame_level_score::create_new_record_controls
( const std::string& medal, const std::string& format )
{
  CLAW_PRECOND( m_new_record );

  set_title( gettext("New record") );

  bear::gui::visual_component* text = create_input();
  bear::gui::visual_component* discard = create_discard_button();
  create_save_button();

  text->set_bottom( discard->top() + get_margin() );

  bear::gui::visual_component* score = create_score(format);
  bear::gui::visual_component* m = create_medal(medal);

  const bear::visual::size_type w( std::max(text->width(), score->width()) );

  score->set_bottom_left
    ( (w - score->width()) / 2, text->top() + get_margin() );

  m->set_bottom_left( w + get_margin(), discard->top() + get_margin() );

  const double r = m->width() / m->height();
  m->set_height( score->top() - m->bottom() );
  m->set_width( r * m->height());

  discard->set_right( m->right() );
} // frame_level_score::create_new_record_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the controls for the case where there is no new record.
 * \param medal The type of the medal to show.
 * \param format How to format the value of the score.
 */
void ptb::frame_level_score::create_no_new_record_controls
( const std::string& medal, const std::string& format )
{
  CLAW_PRECOND( !m_new_record );

  set_title( gettext("No new record") );

  bear::gui::visual_component* discard = create_discard_button();

  bear::gui::static_text* msg = new bear::gui::static_text( get_font() );
  bear::gui::visual_component* score = create_score(format);
  bear::gui::visual_component* m = create_medal(medal);

  get_content().insert(msg);
  msg->set_auto_size(true);
  msg->set_text( gettext("You didn't get a high score. Try again!") );

  const bear::visual::size_type w( std::max(msg->width(), score->width()) );

  score->set_left( (w - score->width()) / 2 );
  msg->set_bottom( discard->top() + get_margin() );
  score->set_bottom( msg->top() + get_margin() );
  m->set_bottom_left( w + get_margin(), discard->top() + get_margin() );

  const double r = m->width() / m->height();
  m->set_height( score->top() - m->bottom() );
  m->set_width( r * m->height());

  discard->set_right( m->right() );
} // frame_level_score::create_no_new_record_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the text input control.
 */
bear::gui::visual_component* ptb::frame_level_score::create_input()
{
  m_text = new bear::gui::text_input( get_font(), claw::graphic::red_pixel );

  m_text->add_enter_callback
    ( bear::gui::callback_function_maker
      ( boost::bind( &frame_level_score::on_save_button, this ) ) );
  m_text->set_width(500);
  set_borders_down(*m_text);
  insert_control(*m_text);

  if ( s_player_name.empty() )
    s_player_name = claw::system_info::get_user_name();

  m_text->set_text( s_player_name );

  return m_text;
} // frame_level_score::create_input()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "discard" button.
 */
bear::gui::visual_component* ptb::frame_level_score::create_discard_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Discard"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_level_score::close_window, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_level_score::create_discard_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "save" button.
 */
bear::gui::visual_component* ptb::frame_level_score::create_save_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Save"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_level_score::on_save_button, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_level_score::create_save_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the medal picture.
 * \param medal The type of the medal.
 */
bear::gui::visual_component*
ptb::frame_level_score::create_medal( const std::string& medal )
{
  bear::gui::visual_component* result =
    new bear::gui::picture
    ( get_layer().get_level().get_globals().auto_sprite
      ( "gfx/mini-game/medal.png", medal ) );

  get_content().insert(result);
  return result;
} // frame_level_score::create_medal()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the controls displaying the score
 * \param format How to format the value of the score.
 */
bear::gui::visual_component*
ptb::frame_level_score::create_score( const std::string& format )
{
  bear::gui::static_text* result = new bear::gui::static_text( get_font() );

  get_content().insert(result);

  const score_table::entry e(m_score);
  result->set_auto_size(true);
  result->set_text( e.format(gettext(format.c_str())) );

  return result;
} // frame_level_score::create_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Exit.
 */
bool ptb::frame_level_score::on_close()
{
  if ( !m_next_level.empty() )
    bear::engine::game::get_instance().set_waiting_level(m_next_level);

  player_proxy p =
    util::find_player( get_layer().get_level().get_globals(), 1 );

  if ( p != NULL )
    p.set_marionette(false);

  p = util::find_player( get_layer().get_level().get_globals(), 2 );

  if ( p != NULL )
    p.set_marionette(false);

  return true;
} // frame_level_score::on_close()

/*----------------------------------------------------------------------------*/
/**
 * \brief Action done when the "save" button is pressed.
 */
void ptb::frame_level_score::on_save_button()
{
  CLAW_PRECOND( m_new_record );

  std::string text( m_text->get_text() );
  claw::text::trim( text );

  m_score_table.insert( text, m_score );
  m_score_table.save();

  close_window();
} // frame_level_score::on_save_button()
