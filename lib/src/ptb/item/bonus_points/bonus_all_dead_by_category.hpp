/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item that adds points if all players_detector of given category
 * are dead.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_BONUS_ALL_DEAD_BY_CATEGORY_HPP__
#define __PTB_BONUS_ALL_DEAD_BY_CATEGORY_HPP__

#include "ptb/item/bonus_points/bonus_points.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that adds points if all players_detector of given category
   * are dead.
   * The valid fields for this item are
   *  - \a category:
   *  \c (string) (required) The category of players_detector to consider,
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class bonus_all_dead_by_category:
    public bonus_points
  {
    DECLARE_BASE_ITEM(bonus_all_dead_by_category);

  private:
    /** \brief The type of the parent class. */
    typedef bonus_points super;

  public:
    bonus_all_dead_by_category();
    explicit bonus_all_dead_by_category
    ( const std::string& name, unsigned int points = 0 );

    void build();

    bool set_string_field
    ( const std::string& name, const std::string& value );
    void set_category(const std::string& category);
    bool check_all_dead();

  private:
    /** \brief The category of players_detector to consider. */
    std::string m_category;

  }; // class bonus_all_dead_by_category
} // namespace ptb

#endif // __PTB_BONUS_ALL_DEAD_BY_CATEGORY_HPP__
