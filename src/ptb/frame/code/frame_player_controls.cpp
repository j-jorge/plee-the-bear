/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_player_controls class.
 * \author Julien Jorge
 */
#include "ptb/frame/frame_player_controls.hpp"

#include "ptb/controller_config.hpp"
#include "ptb/gui/key_edit.hpp"

#include "gui/button.hpp"
#include "gui/callback_function.hpp"

#include <boost/bind.hpp>

#include <libintl.h>
#include <sstream>
#include <claw/string_algorithm.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param v The edited action.
 * \param e The control used to edit the value.
 */
template<typename ValueType>
ptb::frame_player_controls::key_edit_data<ValueType>::key_edit_data
( ValueType v, key_edit* e )
  : value(v), edit(e)
{

} // frame_player_controls::key_edit_data::key_edit_data()




/*----------------------------------------------------------------------------*/
const bear::gui::size_type ptb::frame_player_controls::s_text_box_width = 250;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer onwing the window.
 * \param player_index The index of the player for which we change the controls.
 */
ptb::frame_player_controls::frame_player_controls
( windows_layer* owning_layer, unsigned int player_index )
  : frame(owning_layer, gettext("Player's controls")),
    m_player_index(player_index)
{
  controller_config cfg;
  m_controller_layout = cfg.get_layout(player_index);

  if (player_index==1)
    m_other_controller_layout = cfg.get_layout(2);
  else
    m_other_controller_layout = cfg.get_layout(1);

  create_controls();
  show_key_values();
} // frame_player_controls::frame_player_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Answer to a click on 'ok'.
 */
void ptb::frame_player_controls::on_ok()
{
  save();
  close_window();
} // frame_player_controls::on_ok()

/*----------------------------------------------------------------------------*/
/**
 * \brief The button for an action has been changed.
 * \param e The key_edit control containing the button.
 * \param a The action associated to this button.
 */
void ptb::frame_player_controls::on_action_changed
( const key_edit* e, player_action::value_type a )
{
  m_controller_layout.set_action(e->get_key(), a);
  m_other_controller_layout.remove(e->get_key());
  show_key_values();
} // frame_player_controls::on_action_changed()

/*----------------------------------------------------------------------------*/
/**
 * \brief The button for a gui command has been changed.
 * \param e The key_edit control containing the button.
 * \param c The command associated to this button.
 */
void ptb::frame_player_controls::on_command_changed
( const key_edit* e, gui_command::value_type c )
{
  m_controller_layout.set_command(e->get_key(), c);
  m_other_controller_layout.remove(e->get_key());
  show_key_values();
} // frame_player_controls::on_command_changed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_player_controls::create_controls()
{
  bear::gui::visual_component* ok = create_ok_button();
  bear::gui::visual_component* cancel = create_cancel_button();

  bear::gui::size_type w =
    create_command_entries( ok->top() + get_margin() );

  w = std::max
    ( w, create_action_entries
      ( m_commands.back().edit->top() + 2*get_margin() ) );

  for ( std::size_t i=0; i!=m_commands.size(); ++i )
    m_commands[i].edit->set_left( w + get_margin() );

  for ( std::size_t i=0; i!=m_actions.size(); ++i )
    m_actions[i].edit->set_left( w + get_margin() );

  cancel->set_right(m_commands.back().edit->right());

  fit( get_margin() );
} // frame_player_controls::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "OK" button.
 */
bear::gui::visual_component* ptb::frame_player_controls::create_ok_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("OK"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_player_controls::on_ok, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_player_controls::create_ok_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "Cancel" button.
 */
bear::gui::visual_component* ptb::frame_player_controls::create_cancel_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Cancel"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_player_controls::close_window, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_player_controls::create_cancel_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the controls for the gui commands.
 * \param b The bottom position of the group of controls.
 * \return The width of the largest static text displaying the name of a
 *         command.
 */
bear::gui::size_type ptb::frame_player_controls::create_command_entries
( bear::gui::coordinate_type b )
{
  gui_command::value_type c( gui_command::null_command );
  bear::gui::size_type result(0);

  while ( c!=gui_command::max_value )
    {
      ++c;

      bear::gui::visual_component* text =
        make_static_text( gui_command::to_string(c), b );
      key_edit* edit = make_key_edit_command( c );

      edit->set_bottom( text->bottom() );
      edit->set_height( text->height() );
      m_commands.push_back( command_edit_data(c, edit) );

      b = text->top() + get_margin() / 2;
      result = std::max(result, text->width());
    }

  return result;
} // frame_player_controls::create_command_entries()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the controls for the actions.
 * \param b The bottom position of the group of controls.
 */
bear::gui::size_type ptb::frame_player_controls::create_action_entries
( bear::gui::coordinate_type b )
{
  player_action::value_type actions[] =
    { player_action::get_camera, player_action::jump,
      player_action::change_object, player_action::throw_stone,
      player_action::slap, player_action::crouch,
      player_action::look_upward, player_action::move_right,
      player_action::move_left, player_action::action_null
    };

  bear::gui::size_type result(0);

  for ( std::size_t i=0; actions[i]!=player_action::action_null; ++i )
    {
      bear::gui::visual_component* text =
        make_static_text( player_action::to_string(actions[i]), b );
      key_edit* edit = make_key_edit_action( actions[i] );

      edit->set_bottom( text->bottom() );
      edit->set_height( text->height() );
      m_actions.push_back( action_edit_data(actions[i], edit) );

      b = text->top() + get_margin() / 2;
      result = std::max(result, text->width());
    }

  return result;
} // frame_player_controls::create_action_entries()

/*----------------------------------------------------------------------------*/
/**
 * \brief Show the human readable values of the keys and store the actions in
 *        m_action_value.
 */
void ptb::frame_player_controls::show_key_values()
{
  for ( std::size_t i=0; i!=m_commands.size(); ++i )
    m_commands[i].edit->set_key
      ( m_controller_layout.get_from_command(m_commands[i].value) );

  for ( std::size_t i=0; i!=m_actions.size(); ++i )
    m_actions[i].edit->set_key
      ( m_controller_layout.get_from_action(m_actions[i].value) );
} // frame_player_controls::show_key_values()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the controller_layout.
 */
void ptb::frame_player_controls::save() const
{
  unsigned int o = 2;

  if (m_player_index==2)
    o = 1;

  controller_config cfg;
  cfg.set_layout( m_player_index, m_controller_layout );
  cfg.save_controller_layout( m_player_index );

  cfg.set_layout( o, m_other_controller_layout );
  cfg.save_controller_layout( o );
} // frame_player_controls::save()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a bear::gui::static_text for the action and command names.
 * \param t The text of the static_text.
 * \param b The bottom position of the static text.
 */
bear::gui::static_text*
ptb::frame_player_controls::make_static_text
( const std::string& t, bear::visual::coordinate_type b )
{
  std::locale loc;

  std::string s(t);
  claw::text::replace( s, std::string("_"), std::string(" ") );
  if (!s.empty())
    s[0] = std::toupper(s[0], loc);

  bear::gui::static_text* result = new bear::gui::static_text(get_font());
  get_content().insert(result);
  result->set_auto_size(true);
  result->set_bottom(b);
  result->set_text( gettext(s.c_str()) );

  return result;
} // frame_player_controls::make_static_text()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a key_edit for a command.
 * \param c The edited command.
 */
ptb::key_edit*
ptb::frame_player_controls::make_key_edit_command( gui_command::value_type c )
{
  key_edit* result =
    new key_edit( get_font(), m_controller_layout.get_from_command(c) );

  result->set_change_callback
    ( bear::gui::callback_function_maker
      ( boost::bind
        ( &frame_player_controls::on_command_changed, this, result, c ) ) );

  result->set_width(s_text_box_width);
  set_borders_down(*result);
  insert_control(*result);

  return result;
} // frame_player_controls::make_key_edit_command()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a key_edit for a player action.
 * \param a The edited action.
 */
ptb::key_edit*
ptb::frame_player_controls::make_key_edit_action( player_action::value_type a )
{
  key_edit* result =
    new key_edit( get_font(), m_controller_layout.get_from_action(a) );

  result->set_change_callback
    ( bear::gui::callback_function_maker
      ( boost::bind
        ( &frame_player_controls::on_action_changed, this, result, a ) ) );

  result->set_width(s_text_box_width);
  set_borders_down(*result);
  insert_control(*result);

  return result;
} // frame_player_controls::make_key_edit_action()
