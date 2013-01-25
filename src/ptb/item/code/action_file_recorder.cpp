/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::action_file_recorder class.
 * \author Julien Jorge
 */
#include "ptb/item/action_file_recorder.hpp"

#include "ptb/defines.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/level_variables.hpp"
#include "engine/resource_pool.hpp"

#include <algorithm>

BASE_ITEM_EXPORT( action_file_recorder, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
  bool ptb::action_file_recorder::action_information::operator<
  (const action_information& other) const
{
  return date < other.date;
} // action_file_recorder::action_information::operator<()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::action_file_recorder::action_file_recorder()
  : m_date(0)
{
  set_phantom(true);
  set_can_move_items(false);
  set_artificial(true);
  set_global(true);
} // action_file_recorder::action_file_recorder()

/*----------------------------------------------------------------------------*/
/**
 * \brief Copy constructor.
 */
ptb::action_file_recorder::action_file_recorder
( const action_file_recorder& that )
  : m_date(that.m_date)
{
  /* we can't copy the stream. */
} // action_file_recorder::action_file_recorder()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::action_file_recorder::~action_file_recorder()
{
  std::ostringstream oss;
  oss << "player_" << get_player_index();
  const std::string player_name( oss.str() );

  std::sort(m_actions.begin(), m_actions.end());
  double max_date(0);
  double current_date(0);

  actions_vector::const_iterator it = m_actions.begin();
  if ( it != m_actions.end() )
    m_file << current_date << " " << player_name << ".control_player();\n";

  for ( ; it != m_actions.end(); ++it )
    {
      m_file << '+' << (it->date - current_date) << ' '
             << player_name << ".do_action( "
             << player_action::to_string(it->action)
             << ", " << it->duration << " );\n";

      current_date = it->date;
      double date = it->date + it->duration;
      if ( date > max_date )
        max_date = date;
    }

  m_file << '+' << (max_date - current_date) << " {\n"
         << "  " << player_name << ".release_player();\n"
         << "  script.end();\n"
         << "}\n";
} // action_file_recorder::~action_file_recorder()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "std::string".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::action_file_recorder::set_string_field
( const std::string& name, const std::string& value )
{
  bool result(true);

  if ( name == "action_file_recorder.file_name" )
    m_file.open(value.c_str());
  else
    result = super::set_string_field( name, value );

  return result;
} // action_file_recorder::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::action_file_recorder::build()
{
  m_file << "/*\n"
         << "  This file lists the actions sent to player number "
         << get_player_index()
         << "\n  It has been created with a ptb::action_file_recorder item.\n"
         << "*/\n";
} // action_file_recorder::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time The duration of the progression.
 */
void ptb::action_file_recorder::progress
( bear::universe::time_type elapsed_time )
{
  m_date += elapsed_time;

  progress_input_actions(elapsed_time);

  current_actions_map::iterator it;

  for ( it = m_current_actions.begin(); it != m_current_actions.end(); ++it )
    it->second.duration += elapsed_time;
} // action_file_recorder::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start an action asked by the human player.
 * \param a The action.
 */
void ptb::action_file_recorder::start_action( player_action::value_type a )
{
  m_current_actions[a].date = m_date;
  m_current_actions[a].action = a;
  m_current_actions[a].duration = 0;
} // action_file_recorder::start_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop an action asked by the human player.
 * \param a The action.
 */
void ptb::action_file_recorder::stop_action( player_action::value_type a )
{
  m_actions.push_back( m_current_actions[a] );
  m_current_actions.erase(a);
} // action_file_recorder::stop_action()
