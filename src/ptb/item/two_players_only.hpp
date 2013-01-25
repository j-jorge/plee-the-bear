/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This class implements an item taht kills items according to the player
 *        mode.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_TWO_PLAYERS_ONLY_HPP__
#define __PTB_TWO_PLAYERS_ONLY_HPP__

#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief This class implements an item taht kills items according to the
   *        player mode.
   *
   * The custom fields of this class are:
   * - killing_item_with_one_player: \c (list of items) The items to kill when
   * there is only one player.
   * - killing_item_with_two_players: \c (list of items) The items to kill
   * when there is two players.
   *  - any field supported by the parent classes.
   * \author Sebastien Angibaud
   */
  class two_players_only:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(two_players_only);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    two_players_only();

    virtual bool set_item_list_field
      ( const std::string& name, const std::vector<base_item*>& value );

    void build();

  private:
    /** \brief The list of items to kill when there is only one player. */
    std::vector<bear::universe::item_handle> m_items_one_player;

    /** \brief The list of items to kill when there is two players. */
    std::vector<bear::universe::item_handle> m_items_two_players;
  }; // class two_players_only
} // namespace ptb

#endif // __PTB_TWO_PLAYERS_ONLY_HPP__
