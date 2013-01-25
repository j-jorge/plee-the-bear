/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class containing informations on a level.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_LEVEL_INFORMATION_HPP__
#define __PTB_LEVEL_INFORMATION_HPP__

#include <string>
#include <list>

namespace ptb
{
  /**
   * \brief The class containing informations on a level.
   * \author Sebastien Angibaud
   */
  class level_information
  {
  public:
    typedef std::list<std::string> bonus_list;

  public:
    level_information();
    explicit level_information
    (const std::string& filename, const std::string& name);

    bool is_valid() const;

    const std::string& get_id() const;
    const std::string& get_name() const;
    const std::string& get_filename() const;
    const bonus_list& get_bonus() const;

    void set_thumb_filename(const std::string& f);
    const std::string& get_thumb_filename() const;
    std::string get_medal_name() const;

    void load_bonus_list();

  private:
    /** \brief The identifier of the level. */
    std::string m_id;

    /** \brief The filename of the level. */
    std::string m_filename;

    /** \brief The filename of thumbnail. */
    std::string m_thumb_filename;

    /** \brief List of bonus to found. */
    bonus_list m_bonus;
   }; // class level_information
} // namespace ptb

#endif // __PTB_LEVEL_INFORMATION_HPP__
