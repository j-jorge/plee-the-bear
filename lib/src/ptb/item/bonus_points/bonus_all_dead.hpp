/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item that adds points if all items of given classes are dead.
 * \author Julien Jorge
 */
#ifndef __PTB_BONUS_ALL_DEAD_HPP__
#define __PTB_BONUS_ALL_DEAD_HPP__

#include "ptb/item/bonus_points/bonus_points.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that adds points if all items of given classes are dead.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Julien Jorge
   */
  class bonus_all_dead:
    public bonus_points
  {
    DECLARE_BASE_ITEM(bonus_all_dead);

  private:
    /** \brief The type of the parent class. */
    typedef bonus_points super;

  public:
    bonus_all_dead();
    explicit bonus_all_dead
    ( const std::string& name, unsigned int points = 0 );

    void build();

    bool set_item_list_field
    ( const std::string& name,
      const std::vector<bear::engine::base_item*>& value );
    void set_class_names(const std::list<std::string>& class_names);

  private:
    /** \brief The class names of all the items that have to be dead. */
    std::list<std::string> m_class_names;

  }; // class bonus_all_dead
} // namespace ptb

#endif // __PTB_BONUS_ALL_DEAD_HPP__
