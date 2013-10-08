/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_profiles class.
 * \author Sebastien Angibaud
 */
#include "ptb/frame/frame_profiles.hpp"

#include "ptb/defines.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/frame/frame_choose_player_mode.hpp"
#include "ptb/frame/frame_profile_name.hpp"

#include "engine/game.hpp"
#include "engine/system/game_filesystem.hpp"
#include "gui/button.hpp"
#include "gui/radio_button.hpp"
#include "gui/radio_group.hpp"
#include "gui/callback_function.hpp"

#include <libintl.h>
#include <boost/bind.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer owning the window.
 */
ptb::frame_profiles::frame_profiles( windows_layer* owning_layer )
  : frame(owning_layer, gettext("Profiles")), m_msg_result(0)
{
  create_controls();
} // frame_profiles::frame_profiles()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when the frame is displayed.
 */
void ptb::frame_profiles::on_focus()
{
  frame::on_focus();

  const bear::gui::radio_button* selection(m_profiles->get_selection());

  if ( selection != NULL )
    {
      std::string profile(selection->get_text());
      if ( ( profile != gettext("Available") ) )
        {
          if ( m_msg_result & message_box::s_ok )
            {
              const bear::engine::game& g( bear::engine::game::get_instance() );

              boost::filesystem::path path
                ( g.get_game_filesystem().get_custom_config_file_name
                  ( PTB_PROFILES_FOLDER ) + profile );

              if ( boost::filesystem::exists(path) )
                {
                  boost::filesystem::remove_all( path );
                  update_controls();
                }
            }
          else
            m_msg_result = 0;
        }
    }

  update_controls();
} // frame_profiles::on_focus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_profiles::create_controls()
{
  bear::visual::font font = get_font();

  m_profiles = create_profiles_radio_buttons( font );
  bear::gui::visual_component* ok_button = create_ok_button( font );
  bear::gui::visual_component* cancel_button = create_back_button( font );
  bear::gui::visual_component* remove_button = create_remove_button( font );

  ok_button->set_top( m_profiles->bottom());

  cancel_button->set_top( ok_button->top() );
  cancel_button->set_left( ok_button->right() + get_margin() );

  remove_button->set_top( ok_button->top() );
  remove_button->set_left( cancel_button->right() + get_margin() );

  ok_button->set_focus();
  update_controls();

  fit( get_margin() );
} // frame_profiles::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the radio button group.
 * \param f The font to use for the text.
 */
bear::gui::radio_group*
ptb::frame_profiles::create_profiles_radio_buttons( bear::visual::font f )
{
  bear::gui::radio_group* radio_group = new bear::gui::radio_group();
  get_content().insert( radio_group );

  m_profile_radio_buttons.resize(PTB_NUMBER_OF_PROFILES);

  for ( unsigned int i = 0; i < PTB_NUMBER_OF_PROFILES; ++i )
    {
      m_profile_radio_buttons[i] =
        new bear::gui::radio_button( get_radio_off(), get_radio_on(), f );

      insert_control(*m_profile_radio_buttons[i]);
      radio_group->add_button(m_profile_radio_buttons[i], get_margin());
    }

  m_profile_radio_buttons.back()->check();

  set_borders_up(*radio_group);

  return radio_group;
} // frame_profiles::create_profiles_radio_buttons()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "ok" button.
 * \param f The font to use for the texts.
 * \return The top position of the controls.
 */
bear::gui::visual_component*
ptb::frame_profiles::create_ok_button( bear::visual::font f )
{
  bear::gui::button* result =
    new bear::gui::button
    ( f, gettext("OK"),
      bear::gui::callback_function_maker
      ( boost::bind(&frame_profiles::on_ok, this) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_profiles::create_ok_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "back" button.
 * \param f The font to use for the texts.
 */
bear::gui::visual_component*
ptb::frame_profiles::create_back_button( bear::visual::font f )
{
  bear::gui::button* result =
    new bear::gui::button
    ( f, gettext("Back"),
      bear::gui::callback_function_maker
      ( boost::bind(&frame_profiles::on_back, this) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_profiles::create_back_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "remove" button.
 * \param f The font to use for the texts.
 */
bear::gui::visual_component*
ptb::frame_profiles::create_remove_button( bear::visual::font f )
{
  bear::gui::button* result =
    new bear::gui::button
    ( f, gettext("Remove"),
      bear::gui::callback_function_maker
      ( boost::bind(&frame_profiles::on_remove, this) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_profiles::create_remove_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Select the current profile.
 */
bool ptb::frame_profiles::on_ok()
{
  const bear::gui::radio_button* selection(m_profiles->get_selection());

  if ( selection != NULL )
    {
      std::string profile(selection->get_text());
      if ( profile == gettext("Available") )
        show_window( new frame_profile_name(&get_layer()) );
      else
        {
          game_variables::set_profile_name(profile);

          show_window
            ( new frame_choose_player_mode(&get_layer()) );
        }
    }

  return true;
} // frame_profiles::on_ok()

/*----------------------------------------------------------------------------*/
/**
 * \brief Exit.
 */
bool ptb::frame_profiles::on_back()
{
  close_window();

  return true;
} // frame_profiles::on_back()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove the current profile.
 */
bool ptb::frame_profiles::on_remove()
{
  const bear::gui::radio_button* selection(m_profiles->get_selection());

  if ( selection != NULL )
    {
      std::string profile(selection->get_text());
      if ( ( profile != gettext("Available") ) )
        {
          m_msg_result = message_box::s_ok | message_box::s_cancel;
          message_box* msg =
            new message_box
            ( &get_layer(),
              gettext("You are deleting the profile \"") +
                      profile + gettext("\". Are you sure?"),
              &m_msg_result );

          show_window(msg);
        }
    }

  return true;
} // frame_profiles::on_remove()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update_controls.
 */
void ptb::frame_profiles::update_controls()
{
  const bear::engine::game& g( bear::engine::game::get_instance() );

  boost::filesystem::path path
    ( g.get_game_filesystem().get_custom_config_file_name(PTB_PROFILES_FOLDER) );

  if ( !boost::filesystem::exists(path) )
    boost::filesystem::create_directory( path );

  unsigned int i = 0;

  if ( boost::filesystem::exists(path) )
    {
      boost::filesystem::directory_iterator it(path);
      boost::filesystem::directory_iterator eit;

      for ( ; it!=eit; ++it)
        if ( boost::filesystem::is_directory(*it) &&
             (i < PTB_NUMBER_OF_PROFILES) )
          {
            std::string dir(it->path().string());
            std::string name(dir, path.string().size(),
                             dir.size() - path.string().size());

            m_profile_radio_buttons[PTB_NUMBER_OF_PROFILES-i-1]->set_text
              (name);
            ++i;
          }
    }

  for ( ; i < PTB_NUMBER_OF_PROFILES; ++i )
    m_profile_radio_buttons[PTB_NUMBER_OF_PROFILES-i-1]->set_text
      (gettext("Available"));

  select_current_profile();
} // frame_profiles::update_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check the current profile.
 */
void ptb::frame_profiles::select_current_profile()
{
  bool ok = false;
  std::string selection = game_variables::get_profile_name();

  for ( unsigned int i = 0; ( i < PTB_NUMBER_OF_PROFILES ) && !ok; ++i )
    if ( m_profile_radio_buttons[i]->get_text() == selection )
      {
        ok = true;
        m_profile_radio_buttons[i]->check();
      }

  if ( !ok )
    m_profile_radio_buttons[PTB_NUMBER_OF_PROFILES-1]->check();
} // frame_profiles::select_current_profil()

