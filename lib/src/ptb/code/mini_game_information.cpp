/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::mini_game_information class.
 * \author Sebastien Angibaud
 */
#include "ptb/mini_game_information.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/util/level_util.hpp"
#include "engine/game.hpp"
#include "engine/system/game_filesystem.hpp"
#include "engine/variable/variable.hpp"

#include <algorithm>
#include <claw/logger.hpp>
#include <claw/string_algorithm.hpp>
#include <libintl.h>

/*----------------------------------------------------------------------------*/
const std::string ptb::mini_game_information::s_level_file_field =
  "level_file";
const std::string ptb::mini_game_information::s_locked_informations_field =
  "locked_informations";
const std::string ptb::mini_game_information::s_unlocked_informations_field =
  "unlocked_informations";
const std::string ptb::mini_game_information::s_playability_field =
  "playability";
const std::string ptb::mini_game_information::s_score_format_field =
  "score_format";
const std::string ptb::mini_game_information::s_score_ordering =
  "score_ordering";
const std::string ptb::mini_game_information::s_unlocked = "unlocked";

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::mini_game_information::mini_game_information()
{

} // mini_game_information::mini_game_information()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::mini_game_information::mini_game_information(const std::string& name)
  : m_id(name), m_playability(playability_type::one_or_two_players),
    m_score_format("%v (%p)")
{
  const bear::engine::game& g( bear::engine::game::get_instance() );

  const std::string filename
    ( g.get_game_filesystem().get_custom_config_file_name( m_id ) );

  m_score_table.load( filename );
} // mini_game_information::mini_game_information()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of the mini-game.
 * \param field The considered field.
 * \param value The value of the field.
 */
void ptb::mini_game_information::load
(const std::string& field, const std::string& value)
{
  if ( field == s_level_file_field )
    {
      m_filename = value;
      m_thumb_filename = util::get_thumbnail(m_filename);
    }
  else if ( field == s_locked_informations_field )
    m_locked_informations = value;
  else if ( field == s_unlocked_informations_field )
    m_unlocked_informations = value;
  else if ( field == s_playability_field )
    m_playability = playability_type::from_string( value );
  else if ( field == s_score_format_field )
    m_score_format = gettext(value.c_str());
  else if ( field == s_score_ordering )
    m_score_table.set_score_ordering( value == "max" );
  else if ( field == s_unlocked )
    game_variables::set_mini_game_status( m_id, (value == "true") );
  else
    claw::logger << claw::log_error
                 << "The field '" << field << "' is unknown."  << std::endl;
} // mini_game_information::load()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::mini_game_information::is_valid() const
{
  return (!m_id.empty()) && (!m_thumb_filename.empty());
} // mini_game_information::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the mini-game is unlocked.
 */
bool ptb::mini_game_information::is_unlocked() const
{
  return game_variables::get_all_mini_game_unlocked_status()
    || game_variables::get_mini_game_status( m_id );
} // mini_game_information::is_unlocked()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the identifier of the mini-game.
 */
const std::string& ptb::mini_game_information::get_id() const
{
   return m_id;
} // mini_game_information::get_id()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the filename of the mini-game.
 */
const std::string& ptb::mini_game_information::get_filename() const
{
   return m_filename;
} // mini_game_information::get_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the filename of thumb.
 * \param f The filename.
 */
void ptb::mini_game_information::set_thumb_filename(const std::string& f)
{
  m_thumb_filename = f;
} // mini_game_information::set_thumb_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the filename of thumb.
 */
const std::string& ptb::mini_game_information::get_thumb_filename() const
{
  return m_thumb_filename;
} // mini_game_information::get_thumb_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set informations when the game is locked.
 * \param info Informations.
 */
void ptb::mini_game_information::set_locked_informations
(const std::string& info)
{
  m_locked_informations = info;
} // mini_game_information::set_locked informations()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set informations when the game is unlocked.
 * \param info Informations.
 */
void ptb::mini_game_information::set_unlocked_informations
(const std::string& info)
{
  m_unlocked_informations = info;
} // mini_game_information::set_unlocked informations()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get informations of the mini-game.
 */
const std::string& ptb::mini_game_information::get_informations() const
{
  if ( is_unlocked() )
    return m_unlocked_informations;
  else
    return m_locked_informations;
} // mini_game_information::get_informations()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the mini-game has already been finished.
 */
bool ptb::mini_game_information::is_finished() const
{
  return !m_score_table.empty();
} // mini_game_information::is_finished()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get records informations of the mini-game.
 */
std::string ptb::mini_game_information::get_record_informations() const
{
  std::string result;

  for (score_table::const_iterator it=m_score_table.begin();
       it!=m_score_table.end(); ++it)
    result += it->format(m_score_format) + '\n';

  return result;
} // mini_game_information::get_record_informations()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the best medal won for the mini-game.
 */
std::string ptb::mini_game_information::get_best_medal_name() const
{
  return m_score_table.get_best_medal_name();
} // mini_game_information::get_best_medal_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the playability of the mini-game : number of players.
 */
ptb::playability_type::value_type
ptb::mini_game_information::get_playability() const
{
  return m_playability;
} // mini_game_information::get_playability()
