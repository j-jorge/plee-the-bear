/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A message sent to a windows_layer to ask for the name of the player,
 *        to add in a score_table.
 * \author Julien Jorge
 */
#ifndef __PTB_SCORE_MESSAGE_HPP__
#define __PTB_SCORE_MESSAGE_HPP__

#include "ptb/layer/windows_layer.hpp"

#include "communication/typed_message.hpp"

#include <string>

namespace ptb
{
  class windows_layer;
  class score_table;

  /**
   * \brief A message sent to a windows_layer to ask for the name of the player,
   *        to add in a score_table.
   * \author Julien Jorge
   */
  class score_message:
    public bear::communication::typed_message<windows_layer>
  {
  public:
    score_message
    ( score_table& t, double value, const std::string& medal,
      const std::string& format, const std::string& next_level );

    bool apply_to( windows_layer& that );

    score_table& get_score_table() const;
    double get_value() const;
    const std::string& get_medal() const;
    const std::string& get_next_level() const;
    const std::string& get_format() const;

  private:
    /** \brief The table in which the score is added. */
    score_table& m_score_table;

    /** \brief The score of the player. */
    const double m_value;

    /** \brief The type of the medal corresponding to this score. */
    const std::string m_medal;

    /** \brief How to format the value of the score. */
    const std::string m_score_format;

    /** \brief The path to the next level to load. */
    const std::string m_next_level;

  }; // class score_message
} // namespace ptb

#endif // __PTB_SCORE_MESSAGE_HPP__
