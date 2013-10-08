/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::message_box class.
 * \author Julien Jorge
 */
#include "ptb/frame/message_box.hpp"

#include "gui/button.hpp"
#include "gui/callback_function.hpp"
#include "gui/static_text.hpp"

#include <boost/bind.hpp>
#include <libintl.h>

/*----------------------------------------------------------------------------*/
const ptb::message_box::flags ptb::message_box::s_ok     = (1 << 0);
const ptb::message_box::flags ptb::message_box::s_cancel = (1 << 1);

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param in_layer The layer containing this frame.
 * \param msg The text to display.
 * \param buttons (in) The buttons to display. (out) The selected button.
 *        Can be NULL if you don't care about the result.
 *
 * A button labelled 'Ok' is created, even if the corresponding flag is not set.
 */
ptb::message_box::message_box
( windows_layer* in_layer, const std::string& msg, flags* buttons )
  : frame(in_layer, gettext("Message")), m_flags(buttons)
{
  create_controls(msg);

  if ( m_flags != NULL )
    *m_flags = 0;
} // message_box::message_box()

/*----------------------------------------------------------------------------*/
/**
 * \brief Answer to a click on 'ok'.
 */
void ptb::message_box::on_ok()
{
  if ( m_flags != NULL )
    *m_flags |= s_ok;

  close_window();
} // message_box::on_ok()

/*----------------------------------------------------------------------------*/
/**
 * \brief Answer to a click on 'cancel'.
 */
void ptb::message_box::on_cancel()
{
  if ( m_flags != NULL )
    *m_flags |= s_cancel;

  close_window();
} // message_box::on_cancel()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the controls in this frame.
 * \param msg The string to display.
 */
void ptb::message_box::create_controls( const std::string& msg )
{
  typedef std::list<bear::gui::visual_component*> component_list;

  bear::gui::visual_component* text = create_text( msg );
  component_list buttons;

  if ( m_flags != NULL )
    {
      if ( *m_flags & s_ok )
        buttons.push_back( create_ok_button() );

      if ( *m_flags & s_cancel )
        buttons.push_back( create_cancel_button() );
    }

  bear::gui::size_type sum_w( 0 );

  if ( !buttons.empty() )
    {
      text->set_bottom( buttons.front()->top() + get_margin() );
      sum_w = (buttons.size() - 1) * get_margin();
    }

  for ( component_list::const_iterator it=buttons.begin(); it!=buttons.end();
        ++it )
    sum_w += (*it)->width();

  bear::gui::size_type w;

  if ( sum_w > text->width() )
    {
      w = 0;
      text->set_left( (sum_w - text->width()) / 2 );
    }
  else
    w = ( text->width() - sum_w ) / 2;

  for ( component_list::const_iterator it=buttons.begin(); it!=buttons.end();
        ++it )
    {
      (*it)->set_left(w);
      w += (*it)->width() + get_margin();
    }

  fit( get_margin() );
} // message_box::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the controls that displays the text.
 * \param msg The string to display.
 */
bear::gui::visual_component*
ptb::message_box::create_text( const std::string& msg )
{
  bear::gui::static_text* result = new bear::gui::static_text( get_font() );

  get_content().insert(result);

  result->set_size( get_size() / 2 );
  result->set_text( msg );
  result->expand_vertically();

  return result;
} // message_box::create_text()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "OK" button.
 */
bear::gui::visual_component* ptb::message_box::create_ok_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("OK"),
      bear::gui::callback_function_maker
      ( boost::bind(&message_box::on_ok, this) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // message_box::create_ok_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "Cancel" button.
 */
bear::gui::visual_component* ptb::message_box::create_cancel_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Cancel"),
      bear::gui::callback_function_maker
      ( boost::bind(&message_box::on_cancel, this) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // message_box::create_cancel_button()
