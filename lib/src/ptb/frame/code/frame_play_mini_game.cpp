/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_play_mini_game class.
 * \author Sébastien Angibaud
 */
#include "ptb/frame/frame_play_mini_game.hpp"

#include "ptb/mini_game_information.hpp"
#include "ptb/frame/frame_start_menu.hpp"
#include "ptb/frame/theme_colors.hpp"
#include "ptb/layer/windows_layer.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/defines.hpp"

#include "engine/resource_pool.hpp"
#include "engine/game.hpp"
#include "engine/level.hpp"
#include "engine/level_globals.hpp"

#include "gui/button.hpp"
#include "gui/callback_function.hpp"

#include "visual/scene_writing.hpp"

#include <libintl.h>
#include <boost/bind.hpp>
#include <claw/logger.hpp>
#include <claw/configuration_file.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer onwing the window.
 * \param filename The name of configuration file.
 */
ptb::frame_play_mini_game::frame_play_mini_game
( windows_layer* owning_layer,  const std::string& filename )
  : frame(owning_layer, gettext("Mini-game")), m_index(0)
{
  create_controls();
  load_levels(filename);

  for ( unsigned int i=0; i != m_levels.size(); ++i)
    CLAW_PRECOND( m_levels[i].is_valid() );

  if ( game_variables::get_last_mini_game() < m_levels.size() )
    m_index = game_variables::get_last_mini_game();

  update_controls();
} // frame_play_mini_game::frame_play_mini_game()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when the frame is displayed.
 */
void ptb::frame_play_mini_game::on_focus()
{
  frame::on_focus();

  update_controls();
} // frame_play_mini_game::on_focus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Delete mini-game.
 */
void ptb::frame_play_mini_game::delete_mini_games()
{
  m_levels.resize(0);
} // frame_play_mini_game::delete_mini_games()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_play_mini_game::create_controls()
{
  m_thumb = new bear::gui::picture( get_default_thumb() );
  m_status_picture = new bear::gui::picture( get_status_picture() );

  get_content().insert( m_thumb );
  get_content().insert( m_status_picture );

  create_text();

  bear::gui::visual_component* ok = create_ok_button();
  bear::gui::visual_component* back = create_back_button();
  bear::gui::visual_component* previous = create_previous_button();
  bear::gui::visual_component* next = create_next_button();

  position_controls( ok->top() + get_margin() );

  bear::gui::size_type sum_w
    ( 3 * get_margin() + ok->width() + back->width() + previous->width()
      + next->width() );

  const bear::gui::size_type w
    ( (m_thumb->width() + get_margin() + m_informations->width() - sum_w) / 3);

  back->set_left( ok->right() + w );
  previous->set_left( back->right() + w );
  next->set_right( m_status_picture->right() );

  next->set_focus();

  fit( get_margin() );
} // frame_play_mini_game::create_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load levels.
 * \param filename The name of file containing level descriptions.
 */
void ptb::frame_play_mini_game::load_levels(const std::string& filename )
{
  std::stringstream f;

  bear::engine::resource_pool::get_instance().get_file(filename, f);

  if (f)
    {
      claw::configuration_file config(f);
      m_levels.clear();

      claw::configuration_file::const_file_iterator it;
      for (it=config.file_begin(); it!=config.file_end(); ++it)
        m_levels.push_back( mini_game_information(*it) );

      for ( unsigned int i=0; i != m_levels.size(); ++i )
        {
          claw::configuration_file::const_section_iterator it2;
          for ( it2=config.section_begin(m_levels[i].get_id());
                it2!=config.section_end(m_levels[i].get_id()); ++it2 )
            m_levels[i].load(*it2, config(m_levels[i].get_id(), *it2));
        }
    }
   else
     claw::logger << claw::log_error
                  << "can't find file named '"
                  << filename << "'."  << std::endl;

} // frame_play_mini_game::load_mini_game()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "Play!" button.
 */
bear::gui::visual_component* ptb::frame_play_mini_game::create_ok_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Play!"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_play_mini_game::on_ok, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up( *result );
  insert_control( *result );

  return result;
} // frame_play_mini_game::create_ok_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "Back" button.
 */
bear::gui::visual_component* ptb::frame_play_mini_game::create_back_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Back"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_play_mini_game::close_window, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up( *result );
  insert_control( *result );

  return result;
} // frame_play_mini_game::create_back_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "Previous" button.
 */
bear::gui::visual_component* ptb::frame_play_mini_game::create_previous_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Previous"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_play_mini_game::on_previous, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up( *result );
  insert_control( *result );

  return result;
} // frame_play_mini_game::create_previous_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the "Next" button.
 */
bear::gui::visual_component* ptb::frame_play_mini_game::create_next_button()
{
  bear::gui::button* result =
    new bear::gui::button
    ( get_font(), gettext("Next"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_play_mini_game::on_next, this ) ) );

  result->set_margin( get_margin() / 2 );
  set_borders_up( *result );
  insert_control( *result );

  return result;
} // frame_play_mini_game::create_next_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create static text.
 */
void ptb::frame_play_mini_game::create_text()
{
  m_records = new bear::gui::static_text(get_font());
  m_records->set_background_color(PTB_THEME_FACE);
  set_borders_down(*m_records);
  m_records->set_auto_size(false);

  m_informations = new bear::gui::static_text(get_font());
  m_informations->set_background_color(PTB_THEME_FACE);
  set_borders_down(*m_informations);
  m_informations->set_auto_size(false);

  m_name_text = new bear::gui::scene_element();

  get_content().insert(m_records);
  get_content().insert(m_informations);
  get_content().insert(m_name_text);
} // frame_play_mini_game::create_text()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set position of controls.
 * \param b The bottom position of the controls.
 */
void
ptb::frame_play_mini_game::position_controls( bear::gui::coordinate_type b )
{
  m_records->set_size
    ( get_layer().get_size().x - 100 - m_status_picture->width(),
      m_status_picture->height() );
  m_records->set_bottom( b );

  m_status_picture->set_bottom_left
    ( m_records->right() + get_margin(), m_records->bottom() );

  m_informations->set_size( m_records->get_size() );
  m_thumb->set_bottom( m_records->top() + get_margin() );
  m_informations->set_bottom_left
    ( m_thumb->right() + get_margin(), m_thumb->bottom() );

  // The height of the font used for the name of the mini-game
  m_name_text->set_height(50);
  m_name_text->set_bottom( m_thumb->top() + get_margin() );
} // frame_play_mini_game::position_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update controls.
 */
void ptb::frame_play_mini_game::update_controls()
{
  if ( !m_levels.empty() )
    {
      m_informations->set_text
        (gettext(m_levels[m_index].get_informations().c_str()));

      // Adjust the height of m_name_text in position_controls() to the height
      // of this font
      const bear::visual::writing w
        ( get_layer().get_level().get_globals().get_font
          ("font/level_name-42x50.fnt", 50),
          gettext(m_levels[m_index].get_id().c_str()) );

      m_name_text->set_size
        ( std::min(w.get_width(), get_content().width()), 50 );
      m_name_text->set_scene_element( bear::visual::scene_writing(0, 0, w) );
      m_name_text->set_position
        ( (get_content().width() - m_name_text->width()) / 2,
          m_informations->top() + get_margin());

      m_thumb->set_picture(get_thumb());

      if ( m_levels[m_index].is_unlocked() )
        {
          m_status_picture->set_picture(get_status_picture());
          m_records->set_text( m_levels[m_index].get_record_informations() );
        }
      else
        m_records->clear();
    }
} // frame_play_mini_game::update_controls()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the configuration.
 */
void ptb::frame_play_mini_game::on_ok()
{
  if ( m_levels[m_index].is_unlocked() )
    {
      game_variables::set_last_level_exit
        ( m_levels[m_index].get_filename(),  1, PTB_DEFAULT_EXIT_NAME );
      game_variables::set_last_level_exit
        ( m_levels[m_index].get_filename(),  2, PTB_DEFAULT_EXIT_NAME );
      game_variables::set_next_level_name
        ( m_levels[m_index].get_filename() );

      const playability_type::value_type playability
        (  );

      frame_start_menu* const dialog
        ( frame_start_menu::launch
          ( &get_layer(), true, m_levels[m_index].get_playability() ) );

      if ( dialog != NULL )
        show_window( dialog );
    }
} // frame_play_mini_game::on_ok()

/*----------------------------------------------------------------------------*/
/**
 * \brief Last function called before closing the frame.
 */
bool ptb::frame_play_mini_game::on_close()
{
  game_variables::set_mini_game( false );

  return true;
} // frame_play_mini_game::on_close()

/*----------------------------------------------------------------------------*/
/**
 * \brief Choose the previous mini-game.
 */
void ptb::frame_play_mini_game::on_previous()
{
  if ( m_levels.size() > 1 )
    {
      if ( m_index == 0 )
        m_index = m_levels.size() - 1;
      else
        --m_index;

      game_variables::set_last_mini_game( m_index );

      update_controls();
    }
} // frame_play_mini_game::on_previous()

/*----------------------------------------------------------------------------*/
/**
 * \brief Choose the next mini-game.
 */
void ptb::frame_play_mini_game::on_next()
{
  if ( m_levels.size() > 1 )
    {
      ++m_index;

      if ( m_index == m_levels.size() )
        m_index = 0;

      game_variables::set_last_mini_game( m_index );

      update_controls();
    }
} // frame_play_mini_game::on_next()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the thumb of the mini-game.
 */
bear::visual::sprite ptb::frame_play_mini_game::get_thumb() const
{
  bear::visual::sprite result;

  if ( !m_levels.empty() )
    {
      if ( !m_levels[m_index].is_unlocked() )
        result = get_default_thumb();
      else
        {
          bear::engine::level_globals& glob =
            get_layer().get_level().get_globals();

          try
            {
              result = bear::visual::sprite
                ( glob.get_image( m_levels[m_index].get_thumb_filename() ) );
            }
          catch(...)
            { }
        }
    }

  return result;
} // frame_play_mini_game::get_thumb()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the default thumb of the mini-game.
 */
bear::visual::sprite ptb::frame_play_mini_game::get_default_thumb() const
{
  bear::engine::level_globals& glob =
    get_layer().get_level().get_globals();
  const bear::visual::image& img = glob.get_image( "gfx/thumb/none.png" );

  return bear::visual::sprite( img );
} // frame_play_mini_game::get_default_thumb()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the status picture of the mini-game.
 */
bear::visual::sprite ptb::frame_play_mini_game::get_status_picture() const
{
  std::string medal("none");

  if ( !m_levels.empty() )
    if ( m_levels[m_index].is_finished() )
      medal = m_levels[m_index].get_best_medal_name();

  return get_layer().get_level().get_globals().auto_sprite
    ( "gfx/mini-game/medal.png", medal );
} // frame_play_mini_game::get_thumb()
