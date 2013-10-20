/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \brief Implementation of the ptb::config_file class.
 * \author Julien Jorge
 */
#include "ptb/config_file.hpp"

#include <claw/configuration_file.hpp>
#include <claw/logger.hpp>
#include <sstream>
#include <fstream>

#include "engine/game.hpp"
#include "engine/system/game_filesystem.hpp"
#include "ptb/game_variables.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::config_file::config_file()
  : m_fullscreen(false), m_dumb_rendering(true),
    m_sound_on(true), m_music_on(true), m_sound_volume(1),
    m_music_volume(1), m_friendly_fire(true), m_config_name("config")
{
  const bear::engine::game& g( bear::engine::game::get_instance() );

  std::string full_config_path
    ( g.get_game_filesystem().get_custom_config_file_name(m_config_name) );
  std::ifstream f( full_config_path.c_str() );

  if (f)
    {
      claw::configuration_file config(f);

      str_to_bool( m_fullscreen, config("Video", "fullscreen") );
      str_to_bool( m_dumb_rendering, config("Video", "dumb_rendering") );

      str_to_bool( m_sound_on, config("Audio", "sound_on") );
      str_to_bool( m_music_on, config("Audio", "music_on") );
      str_to_double( m_sound_volume, config("Audio", "sound_volume") );
      str_to_double( m_music_volume, config("Audio", "music_volume") );

      str_to_bool( m_friendly_fire, config("Gameplay", "friendly_fire") );
    }
} // config_file::config_file

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the configuration to the game.
 */
void ptb::config_file::apply() const
{
  bear::engine::game::get_instance().set_fullscreen( m_fullscreen );
  bear::engine::game::get_instance().set_dumb_rendering( m_dumb_rendering );
  bear::engine::game::get_instance().set_sound_muted( !m_sound_on );
  bear::engine::game::get_instance().set_music_muted( !m_music_on );
  bear::engine::game::get_instance().set_sound_volume( m_sound_volume );
  bear::engine::game::get_instance().set_music_volume( m_music_volume );

  game_variables::set_friendly_fire(m_friendly_fire);
} // config_file::apply()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the configuration.
 */
void ptb::config_file::save() const
{
  const bear::engine::game& g( bear::engine::game::get_instance() );

  std::string full_config_path
    ( g.get_game_filesystem().get_custom_config_file_name(m_config_name) );
  std::ofstream f( full_config_path.c_str() );

  f << "# Configuration of the screen.\n"
    << "[Video]\n"
    << "# Do we use the fullscreen?\n"
    << "fullscreen = " << bool_to_str(m_fullscreen) << '\n'
    << "# Do we use the dumb but visually better procedure to render the "
    "elements?\n"
    << "dumb_rendering = " << bool_to_str(m_dumb_rendering) << '\n'
    << '\n'
    << "# Configuration of the sound system.\n"
    << "[Audio]\n"
    << "# Do we play the sounds?\n"
    << "sound_on = " << bool_to_str(m_sound_on) << '\n'
    << "# Do we play the music?\n"
    << "music_on = " << bool_to_str(m_music_on) << '\n'
    << "# Volume of the sounds.\n"
    << "sound_volume = " << m_sound_volume << '\n'
    << "# Volume of the the music.\n"
    << "music_volume = " << m_music_volume << '\n'
    << '\n'
    << "# Miscellaneous options of the game.\n"
    << "[Gameplay]\n"
    << "# Tell if the players can harm each other.\n"
    << "friendly_fire = " << bool_to_str(m_friendly_fire) << '\n'
    << std::endl;
} // config_file::save()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the fullscreen mode value.
 * \param b The new value.
 */
void ptb::config_file::set_fullscreen( bool b )
{
  m_fullscreen = b;
} // config_file::set_fullscreen()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the sound mode value.
 * \param b The new value.
 */
void ptb::config_file::set_sound_on( bool b )
{
  m_sound_on = b;
} // config_file::set_sound_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the music mode value.
 * \param b The new value.
 */
void ptb::config_file::set_music_on( bool b )
{
  m_music_on = b;
} // config_file::set_music_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the volume of the sound.
 * \param v The new volume.
 */
void ptb::config_file::set_sound_volume( double v )
{
  m_sound_volume = v;
} // config_file::set_sound_volume()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the volume of the music.
 * \param v The new volume.
 */
void ptb::config_file::set_music_volume( double v )
{
  m_music_volume = v;
} // config_file::set_music_volume()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the players can harm each other.
 * \param b Harm or don't harm.
 */
void ptb::config_file::set_friendly_fire( bool b )
{
  m_friendly_fire = b;
} // config_file::set_friendly_fire()

/*----------------------------------------------------------------------------*/
/**
 * \brief Convert a boolean value to its string respresentation.
 * \param b The boolean to convert.
 */
std::string ptb::config_file::bool_to_str( bool b ) const
{
  if (b)
    return "true";
  else
    return "false";
} // config_file::bool_to_str()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a boolean value from its string representation.
 * \param b The resulting boolean.
 * \param s The string representation.
 * \remark \a b is unchanged if \æ s does not represent a boolean value.
 */
void ptb::config_file::str_to_bool( bool& b, const std::string& s ) const
{
  b = (s != "false") && (s != "0");
} // config_file::str_to_bool()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a double value from its string representation.
 * \param d The resulting double.
 * \param s The string representation.
 * \remark \a d is unchanged if \æ s does not represent a double value.
 */
void ptb::config_file::str_to_double( double& d, const std::string& s ) const
{
  std::istringstream iss(s);
  iss >> d;
} // config_file::str_to_double()
