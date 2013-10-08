/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_talk class.
 * \author Julien Jorge
 */
#include "ptb/frame/frame_talk.hpp"

#include "ptb/frame/theme_colors.hpp"
#include "ptb/layer/windows_layer.hpp"
#include "ptb/util/player_util.hpp"

#include "gui/button.hpp"
#include "gui/callback_function.hpp"

#include <boost/bind.hpp>
#include <claw/string_algorithm.hpp>
#include <libintl.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer owning the window.
 * \param player_index The index of the talking player.
 */
ptb::frame_talk::frame_talk
( windows_layer* owning_layer, unsigned int player_index )
  : frame(owning_layer, gettext("Talk")), m_player_index(player_index)
{
  create_controls();

  player_proxy p =
    util::find_player( get_layer().get_level_globals(), m_player_index );

  if ( p!=NULL )
    p.set_marionette(true);
} // frame_talk::frame_talk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that a key has been pressed.
 * \param key The code of the key.
 */
bool ptb::frame_talk::on_key_press( const bear::input::key_info& key )
{
  bool result = true;

  if ( key.is_enter() )
    validate();
  else if ( !frame::on_key_press(key) )
    result = false;

  return result;
} // frame_talk::on_key_press()

/*----------------------------------------------------------------------------*/
/**
 * \brief Validate the selected action.
 */
void ptb::frame_talk::validate()
{
  std::string text( m_text->get_text() );
  claw::text::trim( text );

  if (!text.empty())
    {
      player_proxy p =
        util::find_player( get_layer().get_level_globals(), m_player_index );

      if ( p!=NULL )
        p.speak( text );
    }

  m_text->clear();
} // frame_talk::validate()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_talk::create_controls()
{
  bear::gui::visual_component* text = create_input();
  bear::gui::visual_component* close = create_close_button();

  close->set_right( text->right() );
  text->set_bottom( close->top() + get_margin() );

  fit( get_margin() );
} // frame_talk::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the text input control.
 */
bear::gui::visual_component* ptb::frame_talk::create_input()
{
  m_text = new bear::gui::text_input( get_font(), claw::graphic::red_pixel );

  m_text->set_width(500);

  set_borders_down(*m_text);
  insert_control(*m_text);

  return m_text;
} // frame_talk::create_input()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "Close" button.
 */
bear::gui::visual_component* ptb::frame_talk::create_close_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Close"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_talk::close_window, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_talk::create_close_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Exit.
 */
bool ptb::frame_talk::on_close()
{
  player_proxy p =
    util::find_player( get_layer().get_level_globals(), m_player_index );

  if ( p!=NULL )
    p.set_marionette(false);

  return true;
} // frame_talk::on_close()
