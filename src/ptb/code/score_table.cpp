/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::score_table class.
 * \author Julien Jorge
 */
#include "ptb/score_table.hpp"

#include <sstream>
#include <libintl.h>
#include <fstream>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param _score The score made by the player.
 */
ptb::score_table::entry::entry( double _score )
  : score(_score)
{

} // score_table::entry::entry()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param _player_name The name of the player who made this score.
 * \param _score The score made by the player.
 */
ptb::score_table::entry::entry( const std::string& _player_name, double _score )
  : player_name(_player_name), score(_score)
{

} // score_table::entry::entry()

/*----------------------------------------------------------------------------*/
/**
 * \brief Convert the entry into a string according to a given format.
 * \param f The format of the output string.
 *
 * The resulting string is made by replacing the following escape
 * sequences by the associated value:
 *
 * - %p the value of player_name
 * - %v the value of score
 * - %t the value of score interpreted as a count of seconds
 * - %% the character %
 */
std::string ptb::score_table::entry::format( const std::string& f ) const
{
  bool escape = false;
  std::ostringstream oss;

  for (std::size_t i=0; i!=f.size(); ++i)
    if ( escape )
      {
        escape = false;

        switch (f[i])
          {
          case 'p': oss << player_name; break;
          case 'v': oss << score; break;
          case 't':
            {
              std::size_t val(score);

              std::size_t s = val % 60;
              val = (val - s) / 60; /* minutes */

              std::size_t m = val % 60;
              val = (val - m) / 60; /* hours */

              std::size_t h = val;

              if ( h!=0 )
                oss << h << ' ' << ngettext("hour", "hours", h) << ", "
                    << m << ' ' << ngettext("minute", "minutes", m) << ' '
                    << gettext("and")
                    << ' ' << s << ' ' << ngettext("second", "seconds", s);
              else if ( m!=0 )
                oss << m << ' ' << ngettext("minute", "minutes", m) << ' '
                    << gettext("and") << ' ' << s << ' '
                    << ngettext("second", "seconds", s);
              else
                oss << s << ' ' << ngettext("second", "seconds", s);

              break;
            }
          default: oss << f[i];
          }
      }
    else if ( f[i] == '%' )
      escape = true;
    else
      oss << f[i];

  return oss.str();
} // score_table::entry::format()



/*----------------------------------------------------------------------------*/
const std::string ptb::score_table::s_section_name("score table");
const std::string ptb::score_table::s_score_ordering_field("score ordering");
const std::string ptb::score_table::s_gold_field("gold");
const std::string ptb::score_table::s_silver_field("silver");
const std::string ptb::score_table::s_bronze_field("bronze");

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::score_table::score_table()
  : m_maximize_score(true), m_max_size(6), m_gold(0), m_silver(0), m_bronze(0)
{

} // score_table::score_table()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param file_name The file from which we read the scores.
 */
ptb::score_table::score_table( const std::string& file_name )
  : m_file_name(file_name), m_maximize_score(true), m_max_size(6), m_gold(0),
    m_silver(0), m_bronze(0)
{
  load();
} // score_table::score_table()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give the order in which the scores are sorted.
 * \param maximize Maximize the value. The lower scores will be thrown away.
 */
void ptb::score_table::set_score_ordering( bool maximize )
{
  if ( maximize != m_maximize_score )
    {
      m_maximize_score = !m_maximize_score;
      m_records.reverse();
    }
} // score_table::set_score_ordering()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give the order in which the scores are sorted.
 * \return True if the score are maximized, false otherwise.
 */
bool ptb::score_table::get_score_ordering() const
{
  return m_maximize_score;
} // score_table::get_score_ordering()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the scores from a file.
 */
void ptb::score_table::load()
{
  std::ifstream f( m_file_name.c_str() );
  const claw::configuration_file cfg( f );

  if ( cfg.has_field( s_section_name, s_score_ordering_field ) )
    m_maximize_score = cfg( s_section_name, s_score_ordering_field ) != "min";

  if ( cfg.has_field( s_section_name, s_gold_field ) )
    std::istringstream( cfg( s_section_name, s_gold_field ) ) >> m_gold;

  if ( cfg.has_field( s_section_name, s_silver_field ) )
    std::istringstream( cfg( s_section_name, s_silver_field ) ) >> m_silver;

  if ( cfg.has_field( s_section_name, s_bronze_field ) )
    std::istringstream( cfg( s_section_name, s_bronze_field ) ) >> m_bronze;

  m_records.clear();

  bool stop(false);

  for ( std::size_t i=1; !stop; ++i )
    {
      std::ostringstream field_index;
      field_index << i;
      std::string player_name;
      double score;

      if ( !cfg.has_field( s_section_name, "score_" + field_index.str() ) )
        stop = true;
      else
        {
          std::istringstream iss
            ( cfg( s_section_name, "score_" + field_index.str() ) );
          if ( !(iss >> score) )
            stop = true;
        }

      if ( !cfg.has_field( s_section_name, "player_" + field_index.str() ) )
        stop = true;
      else
        player_name = cfg( s_section_name, "player_" + field_index.str() );

      if ( !stop )
        insert( player_name, score );
    }
} // score_table::load()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the scores from a file.
 * \param file_name The path of the file to load.
 */
void ptb::score_table::load( const std::string& file_name )
{
  m_file_name = file_name;
  load();
} // score_table::load()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the records.
 */
void ptb::score_table::save() const
{
  std::ifstream f( m_file_name.c_str() );
  claw::configuration_file cfg(f);

  cfg.clear_section( s_section_name );

  if ( m_maximize_score )
    cfg.set_value( s_section_name, s_score_ordering_field, "max" );
  else
    cfg.set_value( s_section_name, s_score_ordering_field, "min" );

  save_medals(cfg);
  save_scores(cfg);

  std::ofstream of( m_file_name.c_str() );
  cfg.save(of);
} // score_table::save()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if a score would be stored in the table if inserted.
 * \param score The score to check.
 */
bool ptb::score_table::is_good_candidate( double score ) const
{
  entry_container::const_iterator it=m_records.begin();
  bool stop(false);

  if ( m_maximize_score )
    {
      while ( !stop && it!=m_records.end() )
        if ( it->score < score )
          stop = true;
        else
          ++it;
    }
  else
    {
      while ( !stop && it!=m_records.end() )
        if ( it->score > score )
          stop = true;
        else
          ++it;
    }

  return stop || (size() < m_max_size);
} // score_table::is_good_candidate()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add a new score in the table.
 * \param player_name The name of the player who made the score.
 * \param score The score made by the player.
 */
void ptb::score_table::insert( const std::string& player_name, double score )
{
  entry_container::iterator it=m_records.begin();
  bool stop(false);

  if ( m_maximize_score )
    {
      while ( !stop && it!=m_records.end() )
        if ( it->score < score )
          stop = true;
        else
          ++it;
    }
  else
    {
      while ( !stop && it!=m_records.end() )
        if ( it->score > score )
          stop = true;
        else
          ++it;
    }

  m_records.insert(it, entry(player_name, score));

  if ( m_records.size() > m_max_size )
    m_records.pop_back();
} // score_table::insert()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get an entry of the table.
 */
const ptb::score_table::entry& ptb::score_table::get( std::size_t i ) const
{
  const_iterator it(begin());
  std::advance(it, i);
  return *it;
} // score_table::get()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get an iterator pointing on the first entry.
 */
ptb::score_table::const_iterator ptb::score_table::begin() const
{
  return m_records.begin();
} // score_table::begin()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get an iterator pointing just past the last entry.
 */
ptb::score_table::const_iterator ptb::score_table::end() const
{
  return m_records.end();
} // score_table::end()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the number of entries.
 */
std::size_t ptb::score_table::size() const
{
  return m_records.size();
} // score_table::size()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the table is empty.
 */
bool ptb::score_table::empty() const
{
  return m_records.empty();
} // score_table::empty()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the minimal score for the gold medal.
 * \param score The minimal score.
 */
void ptb::score_table::set_gold_medal( double score )
{
  m_gold = score;
} // score_table::set_gold_medal()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the minimal score for the silver medal.
 * \param score The minimal score.
 */
void ptb::score_table::set_silver_medal( double score )
{
  m_silver = score;
} // score_table::set_silver_medal()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the minimal score for the bronze medal.
 * \param score The minimal score.
 */
void ptb::score_table::set_bronze_medal( double score )
{
  m_bronze = score;
} // score_table::set_bronze_medal()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the name of the medal won for a given score.
 * \param score The score.
 * \return One of "gold", "silver", "bronze" and "none".
 */
std::string ptb::score_table::get_medal_name( double score ) const
{
  std::string result = "none";

  if ( m_maximize_score )
    {
      if ( score >= m_gold )
        result = "gold";
      else if ( score >= m_silver )
        result = "silver";
      else if ( score >= m_bronze )
        result = "bronze";
    }
  else
    {
      if ( score <= m_gold )
        result = "gold";
      else if ( score <= m_silver )
        result = "silver";
      else if ( score <= m_bronze )
        result = "bronze";
    }

  return result;
} // score_table::get_medal_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the name of the medal for the best score.
 * \return One of "gold", "silver", "bronze" and "none".
 */
std::string ptb::score_table::get_best_medal_name() const
{
  if ( empty() )
    return "none";
  else
    return get_medal_name( m_records.front().score );
} // score_table::get_best_medal_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the scores associated with the medals.
 * \param cfg The configuration in which the scores are saved.
 */
void ptb::score_table::save_medals( claw::configuration_file& cfg ) const
{
  std::ostringstream oss;

  oss << m_gold;
  cfg.set_value( s_section_name, s_gold_field, oss.str() );

  oss.str("");
  oss << m_silver;
  cfg.set_value( s_section_name, s_silver_field, oss.str() );

  oss.str("");
  oss << m_bronze;
  cfg.set_value( s_section_name, s_bronze_field, oss.str() );
} // score_table::save_medals()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the scores.
 * \param cfg The configuration in which the scores are saved.
 */
void ptb::score_table::save_scores( claw::configuration_file& cfg ) const
{
  entry_container::const_iterator it = m_records.begin();
  std::size_t i=1;

  for ( it=m_records.begin(); it!=m_records.end(); ++i, ++it )
    {
      std::ostringstream field;
      field << "player_" << i;
      cfg.set_value( s_section_name, field.str(), it->player_name );

      field.str("");

      field << "score_" << i;
      std::ostringstream score;
      score << it->score;

      cfg.set_value( s_section_name, field.str(), score.str() );
    }
} // score_table::save_scores()
