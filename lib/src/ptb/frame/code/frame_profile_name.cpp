/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_profile_name class.
 * \author Sebastien Angibaud
 */
#include "ptb/frame/frame_profile_name.hpp"

#include "ptb/frame/frame_choose_player_mode.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/defines.hpp"

#include "engine/game.hpp"
#include "engine/system/game_filesystem.hpp"
#include "gui/button.hpp"
#include "gui/callback_function.hpp"
#include "gui/static_text.hpp"

#include <boost/bind.hpp>
#include <libintl.h>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

#include <claw/system_info.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer owning the window.
 */
ptb::frame_profile_name::frame_profile_name( windows_layer* owning_layer )
  : frame(owning_layer, gettext("Profile name"))
{
  create_controls();
} // frame_profile_name::frame_profile_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Validate the selected action.
 */
void ptb::frame_profile_name::validate()
{
  std::string name( m_profile_name->get_text() );

  if ( !name.empty() )
    {
      const bear::engine::game& g( bear::engine::game::get_instance() );
      
      boost::filesystem::path path
        ( g.get_game_filesystem().get_custom_config_file_name
          ( PTB_PROFILES_FOLDER ) + name );

      if ( !boost::filesystem::exists(path) )
        {
          game_variables::set_profile_name(name);

          if ( boost::filesystem::create_directory( path ) )
            replace_with
              ( new frame_choose_player_mode(&get_layer()));
        }
      else
        {
          // TO DO : display error
        }
    }
} // frame_profile_name::validate()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_profile_name::create_controls()
{
  bear::gui::visual_component* text = create_input();
  bear::gui::visual_component* back = create_back();
  create_create();

  back->set_right( text->right() );
  text->set_bottom( back->top() + get_margin() );

  fit( get_margin() );
} // frame_profile_name::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the text input control.
 */
bear::gui::visual_component* ptb::frame_profile_name::create_input()
{
  m_profile_name =
    new bear::gui::text_input( get_font(), claw::graphic::red_pixel );

  m_profile_name->add_enter_callback
    ( bear::gui::callback_function_maker
      ( boost::bind( &frame_profile_name::validate, this ) ) );

  m_profile_name->set_width(300);
  m_profile_name->set_text( claw::system_info::get_user_name() );

  set_borders_down(*m_profile_name);
  insert_control(*m_profile_name);

  return m_profile_name;
} // frame_profile_name::create_input()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "back" button.
 */
bear::gui::visual_component* ptb::frame_profile_name::create_back()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Back"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_profile_name::close_window, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_profile_name::create_back()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "create" button.
 */
bear::gui::visual_component* ptb::frame_profile_name::create_create()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Create"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_profile_name::validate, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up(*result);
  insert_control(*result);

  return result;
} // frame_profile_name::create_create()
