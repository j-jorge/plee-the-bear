/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A table of scores to manages the results of the mini-games.
 * \author Julien Jorge
 */
#ifndef __PTB_SCORE_TABLE_HPP__
#define __PTB_SCORE_TABLE_HPP__

#include <string>
#include <list>

#include <claw/configuration_file.hpp>

namespace ptb
{
  /**
   * \brief A table of scores to manages the results of the mini-games.
   * \author Julien Jorge
   */
  class score_table
  {
  public:
    /**
     * \brief An entry of the table.
     */
    struct entry
    {
    public:
      explicit entry( double _score );
      entry( const std::string& _player_name, double _score );

      std::string format( const std::string& f ) const;

    public:
      /** \brief The name of the player who made this score. */
      std::string player_name;

      /** \brief The score of the player. */
      double score;

    }; // struct entry

  private:
    /** \brief The type of the container in which the entries are stored. */
    typedef std::list<entry> entry_container;

  public:
    /** \brief Iterator on the entries. */
    typedef entry_container::const_iterator const_iterator;

  public:
    score_table();
    explicit score_table( const std::string& file_name );

    void set_score_ordering( bool maximize );
    bool get_score_ordering() const;

    void load();
    void load( const std::string& file_name );
    void save() const;

    bool is_good_candidate( double score ) const;
    void insert( const std::string& player_name, double score );
    const entry& get( std::size_t i ) const;

    const_iterator begin() const;
    const_iterator end() const;

    std::size_t size() const;
    bool empty() const;

    void set_gold_medal( double score );
    void set_silver_medal( double score );
    void set_bronze_medal( double score );

    std::string get_medal_name( double score ) const;
    std::string get_best_medal_name() const;

  private:
    void save_medals( claw::configuration_file& cfg ) const;
    void save_scores( claw::configuration_file& cfg ) const;

  private:
    /** \brief The name of the file from which we have read the values. */
    std::string m_file_name;

    /** \brief Indicates if the goal is to maximize the score. */
    bool m_maximize_score;

    /** \brief The records. */
    entry_container m_records;

    /** \brief The maximum size of the table. */
    std::size_t m_max_size;

    /** \brief The minimal value to get the gold medal. */
    double m_gold;

    /** \brief The minimal value to get the silver medal. */
    double m_silver;

    /** \brief The minimal value to get the bronze medal. */
    double m_bronze;

    /** \brief The name of the section where the records are stored when
        saving. */
    static const std::string s_section_name;

    /** \brief The name of the field where the ordering of the score is
        stored. */
    static const std::string s_score_ordering_field;

    /** \brief The name of the field where the minimal score for the gold medal
        is stored. */
    static const std::string s_gold_field;

    /** \brief The name of the field where the minimal score for the silver
        medal is stored. */
    static const std::string s_silver_field;

    /** \brief The name of the field where the minimal score for the bronze
        medal is stored. */
    static const std::string s_bronze_field;

  }; // class score_table
} // namespace ptb

#endif // __PTB_SCORE_TABLE_HPP__
