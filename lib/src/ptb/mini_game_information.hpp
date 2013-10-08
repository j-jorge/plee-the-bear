/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class containing informations on a mini-game.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_MINI_GAME_INFORMATION_HPP__
#define __PTB_MINI_GAME_INFORMATION_HPP__

#include "ptb/playability_type.hpp"
#include "ptb/score_table.hpp"

namespace ptb
{
  /**
   * \brief The class containing informations on a mini-game.
   * \author Sebastien Angibaud
   */
  class mini_game_information
  {
  public:
    mini_game_information();
    explicit mini_game_information(const std::string& name);

    void load(const std::string& field, const std::string& value);

    bool is_valid() const;
    bool is_unlocked() const;

    const std::string& get_id() const;
    const std::string& get_name() const;
    const std::string& get_filename() const;

    void set_thumb_filename(const std::string& f);
    const std::string& get_thumb_filename() const;

    void set_locked_informations(const std::string& f);
    void set_unlocked_informations(const std::string& f);

    const std::string& get_informations() const;

    bool is_finished() const;
    std::string get_record_informations() const;
    std::string get_best_medal_name() const;
    playability_type::value_type get_playability() const;

  private:
    /** \brief The identifier of the mini-game. */
    std::string m_id;

    /** \brief The filename of the mini-game. */
    std::string m_filename;

    /** \brief The playability of the mini-game : number of players. */
    playability_type::value_type m_playability;

    /** \brief The filename of thumbnail. */
    std::string m_thumb_filename;

    /** \brief Informations when the mini-game is locked. */
    std::string m_locked_informations;

    /** \brief Informations when the mini-game is unlocked. */
    std::string m_unlocked_informations;

    /** \brief Record informations of the mini-game. */
    score_table m_score_table;

    /** \brief How the score must be formated when presented. */
    std::string m_score_format;

    /** \brief Field name for status picture filename in description file. */
    static const std::string s_status_picture_field;

    /** \brief Field name for mini-game filename. */
    static const std::string s_level_file_field;

    /** \brief Field name for informations when the mini-game is locked. */
    static const std::string s_locked_informations_field;

    /** \brief Field name for informations when the mini-game is unlocked. */
    static const std::string s_unlocked_informations_field;

    /** \brief Field name for playability: number of possible players. */
    static const std::string s_playability_field;

    /** \brief Field name for the format of the score. */
    static const std::string s_score_format_field;

    /** \brief Field name for the ordering of the scores. */
    static const std::string s_score_ordering;

    /** \brief Field name to tell if the mini-game is unlocked. */
    static const std::string s_unlocked;

   }; // class mini-game_information
} // namespace ptb

#endif // __PTB_MINI_GAME_INFORMATION_HPP__
