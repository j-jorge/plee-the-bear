/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame_pause class.
 * \author Julien Jorge
 */
#include "ptb/frame/frame_pause.hpp"

#include "engine/game.hpp"
#include "engine/level.hpp"
#include "ptb/frame/frame_configure.hpp"
#include "ptb/layer/windows_layer.hpp"

#include "gui/callback_function.hpp"

#include <boost/bind.hpp>
#include <libintl.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer onwing the window.
 */
ptb::frame_pause::frame_pause( windows_layer* owning_layer )
  : menu_frame(owning_layer, gettext("Pause")), m_msg_result(0)
{
  get_layer().get_level().set_pause();
  create_controls();
} // frame_pause::frame_pause()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when the frame is about to be closed.
 */
bool ptb::frame_pause::on_close()
{
  get_layer().get_level().unset_pause();
  return true;
} // frame_pause::on_close()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when the frame is displayed.
 */
void ptb::frame_pause::on_focus()
{
  // This method is called when the message box asking the player if
  // he really wants to come back to the title screen.
  if ( m_msg_result & message_box::s_ok )
    {
      bear::engine::game::get_instance().set_waiting_level
        ("level/title_screen.cl");
      close_window();
    }
  else
    m_msg_result = 0;
} // frame_pause::on_focus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Close the window.
 */
void ptb::frame_pause::on_resume() const
{
  close_window();
} // frame_pause::on_resume()

/*----------------------------------------------------------------------------*/
/**
 * \brief Restart the level.
 */
void ptb::frame_pause::on_restart_level()
{
  bear::engine::game::get_instance().set_waiting_level
    ( get_layer().get_level().get_filename() );
  close_window();
} // frame_pause::on_restart_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Come back to the title screen.
 */
void ptb::frame_pause::on_title_screen()
{
  m_msg_result = message_box::s_ok | message_box::s_cancel;
  message_box* msg =
    new message_box
    ( &get_layer(), gettext("Are you sure you want to leave this level?"),
      &m_msg_result );

  show_window(msg);
} // frame_pause::on_title_screen()

/*----------------------------------------------------------------------------*/
/**
 * \brief Show the frame used to configure the game.
 */
void ptb::frame_pause::on_configuration()
{
  show_window( new frame_configure(&get_layer()) );
} // frame_pause::on_configuration()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the static text components.
 */
void ptb::frame_pause::create_controls()
{
#ifdef PTB_CAN_RESTART_LEVEL
  push
    ( gettext("Restart level"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_pause::on_restart_level, this ) ) );
#endif

  push
    ( gettext("Back to title screen"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_pause::on_title_screen, this ) ) );
  push
    ( gettext("Configuration"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_pause::on_configuration, this ) ) );
  push
    ( gettext("Resume game"),
      bear::gui::callback_function_maker
      ( boost::bind( &frame_pause::on_resume, this ) ) );

  fit( get_margin() );
} // frame_pause::create_controls()
