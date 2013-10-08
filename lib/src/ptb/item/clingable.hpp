/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A clingable.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_CLINGABLE_HPP__
#define __PTB_CLINGABLE_HPP__

#include "engine/base_item.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A bonus box.
   *
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class clingable:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(clingable);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

    /** \brief The type of the list in which we store the items depending on the
        train. */
    typedef std::list<bear::universe::item_handle> item_list;

  public:
    clingable();

    void build();
    void progress( bear::universe::time_type elapsed_time );

  protected:
    void move( bear::universe::time_type elapsed_time );

  private:
    void collision_check_and_apply
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void get_dependent_items( std::list<physical_item*>& d ) const;

  private:
    /** \brief The list of items that are clung. */
    item_list m_list_items;

    /** \brief The list of the items that were clung. */
    item_list m_old_items;

    /** \brief The last position of the platform. */
    bear::universe::position_type m_last_position;
  }; // class clingable
} // namespace ptb

#endif // __PTB_CLINGABLE_HPP__
