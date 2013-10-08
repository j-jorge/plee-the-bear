/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::score_message class.
 * \author Julien Jorge
 */
#include "ptb/message/score_message.hpp"

#include "ptb/layer/windows_layer.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param t The table in which the scores are stored.
 * \param value The score of the player.
 * \param medal The type of the medal corresponding to the score.
 * \param format How to format the value of the score.
 * \param next_level The next level to load.
 */
ptb::score_message::score_message
( score_table& t, double value, const std::string& medal,
  const std::string& format, const std::string& next_level )
  : m_score_table(t), m_value(value), m_medal(medal), m_score_format(format),
    m_next_level(next_level)
{

} // score_message::score_message()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the message to a window layer.
 * \param that The layer to which the message is applied.
 */
bool ptb::score_message::apply_to( windows_layer& that )
{
  return that.process_score_message(*this);
} // score_message::apply_to()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the score table.
 */
ptb::score_table& ptb::score_message::get_score_table() const
{
  return m_score_table;
} // score_message::get_score_table()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the value of the score.
 */
double ptb::score_message::get_value() const
{
  return m_value;
} // score_message::get_value()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the type of the medal.
 */
const std::string& ptb::score_message::get_medal() const
{
  return m_medal;
} // score_message::get_medal()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the level to load.
 */
const std::string& ptb::score_message::get_next_level() const
{
  return m_next_level;
} // score_message::get_next_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the format of the score.
 */
const std::string& ptb::score_message::get_format() const
{
  return m_score_format;
} // score_message::get_format()
