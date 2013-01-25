/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::level_information class.
 * \author Sebastien Angibaud
 */
#include "ptb/level_information.hpp"

#include "ptb/util/level_util.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/defines.hpp"

#include "engine/game.hpp"
#include "engine/variable/variable.hpp"

#include <algorithm>
#include <claw/logger.hpp>
#include <claw/string_algorithm.hpp>
#include <libintl.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::level_information::level_information()
{

} // level_information::level_information()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param filename The filename of the level.
 * \param name The name of the level.
 */
ptb::level_information::level_information
(const std::string& filename, const std::string& name)
  : m_id(name), m_filename(filename)
{
  m_thumb_filename = util::get_thumbnail(filename);
  load_bonus_list();
} // level_information::level_information()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::level_information::is_valid() const
{
  return (!m_id.empty()) && (!m_thumb_filename.empty());
} // level_information::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the identifier of the level.
 */
const std::string& ptb::level_information::get_id() const
{
   return m_id;
} // level_information::get_id()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the filename of the level.
 */
const std::string& ptb::level_information::get_filename() const
{
   return m_filename;
} // level_information::get_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the filename of thumb.
 * \param f The filename.
 */
void ptb::level_information::set_thumb_filename(const std::string& f)
{
  m_thumb_filename = f;
} // level_information::set_thumb_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the filename of thumb.
 */
const std::string& ptb::level_information::get_thumb_filename() const
{
  return m_thumb_filename;
} // level_information::get_thumb_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the bonus.
 */
const ptb::level_information::bonus_list&
ptb::level_information::get_bonus() const
{
  return m_bonus;
} // level_information::get_bonus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the medal won for the level.
 */
std::string ptb::level_information::get_medal_name() const
{
  std::string result = "none";

  if ( game_variables::level_is_finished(m_filename) )
    {
      bonus_list::const_iterator it;
      unsigned int nb(0);

      for ( it = m_bonus.begin(); it != m_bonus.end(); ++it)
        {
          if ( game_variables::get_level_object_state(m_filename, *it) )
            ++nb;
        }

      if ( m_bonus.empty() || (nb ==  m_bonus.size()) )
        result = "gold";
      else if ( nb >=  (m_bonus.size() / 2) )
        result = "silver";
      else
        result = "bronze";
    }

  return result;
} // level_information::get_medal_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the bonus to found in the level.
 */
void ptb::level_information::load_bonus_list()
{
  m_bonus.resize(0);
  bear::engine::var_map vars;
  bear::engine::game::get_instance().get_game_variables
    ( vars, PTB_PERSISTENT_PREFIX + m_filename + "/level_object/.*/state" );

  bear::engine::var_map::iterator<bool>::type it;
  for ( it=vars.begin<bool>();
        it!=vars.end<bool>(); ++it )
    {
      std::string prefix(PTB_PERSISTENT_PREFIX +m_filename + "/level_object/");
      std::string var(it->first);
      std::string c1;
      std::string c2;
      c1 = var.erase(0, prefix.size());

      size_t pos = c1.find("/state");
      if (pos != std::string::npos)
        c2 = c1.erase(pos, c1.size()-pos);

      m_bonus.push_back(c2);
    }
} // level_information::loead_bonus_list()

