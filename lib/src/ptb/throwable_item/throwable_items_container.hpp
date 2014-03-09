/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The set of throwable_items that Plee can throw.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_THROWABLE_ITEMS_CONTAINER_HPP__
#define __PTB_THROWABLE_ITEMS_CONTAINER_HPP__

#include "ptb/throwable_item/throwable_item.hpp"
#include "universe/types.hpp"

#include <boost/signals2.hpp>
#include <map>

namespace ptb
{
  class player_proxy;

  /**
   * \brief The set of throwable_items that Plee can throw.
   * \author Sebastien Angibaud
   */
  class throwable_items_container
  {
  public:
    explicit throwable_items_container();
    ~throwable_items_container();

    void progress( bear::universe::time_type elapsed_time );

    bool has_next() const;
    void next();

    void control_current_throwable_item();
    void select( const::std::string& name );
    throwable_item* get_current_throwable_item() const;

    void add( throwable_item* t );
    throwable_item* remove( const std::string& name );
    bool contains( const std::string& name ) const;

  private:
    std::size_t find_next() const;

  private:
    /* \brief The current throwable_item. */
    std::size_t m_current_throwable_item;

    /* \brief The map of throwable_items. */
    std::vector<throwable_item*> m_throwable_items;

    /* \brief The last stock of the current item. */
    unsigned int m_last_stock;

    /* \brief The last animation of the current item. */
    std::string m_last_animation;

  public:
    /** \brief The signal when the selected throwable item changes. */
    boost::signals2::signal<void (const std::string&)> throwable_item_changed;

    /** \brief The signal when stock of current throwable item changes. */
    boost::signals2::signal<void (unsigned int)> throwable_item_stock_changed;

    /** \brief The signal when there is no stock. */
    boost::signals2::signal<void (void)> throwable_item_no_stock;
  }; // class throwable_items_container
} // namespace ptb

#endif // __PTB_THROWABLE_ITEMS_CONTAINER_HPP__
