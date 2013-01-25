/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This item activates a set of toggles when some players are present.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_PLAYERS_PRESENT_HPP__
#define __PTB_PLAYERS_PRESENT_HPP__

#include "ptb/item_brick/item_waiting_for_players.hpp"

#include "engine/base_item.hpp"
#include "engine/item_brick/with_toggle.hpp"
#include "universe/derived_item_handle.hpp"

#include "engine/export.hpp"

namespace ptb
{
 /**
   * \brief This item activates a set of toggles when some players are present.
   *
   * The custom fields of this class are:
   * - item: item list, the activate_on_players items controlled by this
   *   activator (default = none),
   * - check_all_players: Indicates that this item checks if all players are
   *   present (default = true),
   * - any field supported by the parent classes.
   *
   * \author Sébastien Angibaud
   */
  class players_present:
    public item_waiting_for_players<bear::engine::base_item>
  {
    DECLARE_BASE_ITEM(players_present);

  public:
    /** \brief The type of the parent class. */
    typedef item_waiting_for_players< bear::engine::base_item> super;

  private:
    /** \brief The type of an handle on a toggle. */
    typedef
    bear::universe::derived_item_handle<bear::engine::with_toggle> handle_type;

    /** \brief The type of a list of toggles. */
    typedef std::list<handle_type> handle_list;

  public:
    players_present();
    players_present(const players_present& that);

    bool set_item_list_field
    ( const std::string& name,
      const std::vector<bear::engine::base_item*>& value);
    bool set_bool_field( const std::string& name, bool value );

  protected:
    void on_one_player( const player_proxy& p );
    void on_all_players( const player_proxy& p1, const player_proxy& p2 );

  private:
    void activate_toggles();

    void get_dependent_items
    ( std::list<bear::universe::physical_item*>& d ) const;

  private:
    /** \brief The items to activate. */
    handle_list m_items;

    /* \brief Indicates that this item checks if all players are present. */
    bool m_check_all_players;

  }; // class players_present
} // namespace ptb

#endif // __PTB_PLAYERS_PRESENT_HPP__
