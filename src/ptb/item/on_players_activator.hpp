/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This item activates an item of class activate_on_players.
 * \author Julien Jorge
 */
#ifndef __PTB_ON_PLAYERS_ACTIVATOR_HPP__
#define __PTB_ON_PLAYERS_ACTIVATOR_HPP__

#include "ptb/item_brick/item_waiting_for_players.hpp"

#include "universe/derived_item_handle.hpp"
#include "engine/export.hpp"

namespace ptb
{
  class activate_on_players;

  /**
   * \brief This item activates an item of class activate_on_players.
   *
   * The custom fields of this class are:
   * - item: item list, the activate_on_players items controlled by this
   *   activator (default = none),
   * - any field supported by the parent classes.
   *
   * \author Julien Jorge
   */
  class on_players_activator:
    public item_waiting_for_players<bear::engine::base_item>
  {
    DECLARE_BASE_ITEM(on_players_activator);

  private:
    /** \brief The type of the parent class. */
    typedef item_waiting_for_players<bear::engine::base_item> super;

    /** \brief The type of an handle on a toggle. */
    typedef
    bear::universe::derived_item_handle<activate_on_players> handle_type;

    /** \brief The type of a list of toggles. */
    typedef std::list<handle_type> handle_list;

  public:
    bool set_item_list_field
    ( const std::string& name,
      const std::vector<bear::engine::base_item*>& value);

  protected:
    void on_one_player( const player_proxy& p );
    void on_all_players( const player_proxy& p1, const player_proxy& p2 );

  private:
    void get_dependent_items
    ( std::list<bear::universe::physical_item*>& d ) const;

  private:
    /** \brief The items to activate. */
    handle_list m_item;

  }; // class on_players_activator
} // namespace ptb

#endif // __PTB_ON_PLAYERS_ACTIVATOR_HPP__
