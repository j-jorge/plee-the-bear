/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A toggle that applies its status to a given toggle if we are playing a
 *        single player game, and to an other toggle otherwise.
 * \author Julien Jorge
 */
#ifndef __PTB_ONE_OR_TWO_PLAYERS_TOGGLE_HPP__
#define __PTB_ONE_OR_TWO_PLAYERS_TOGGLE_HPP__

#include "engine/item_brick/item_with_toggle.hpp"
#include "engine/base_item.hpp"
#include "universe/derived_item_handle.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A toggle that applies its status to a given toggle if we are playing
   *        a single player game, and to an other toggle otherwise.
   *
   * The custom fields of this class are:
   * - single_player_game (item), the item toggled in a single player game
   *   (default=none),
   * - two_players_game (item), the item toggled in a two players game
   *   (default=none),
   * - any field supported by the parent class.
   *
   * \author Julien Jorge
   */
  class one_or_two_players_toggle:
    public bear::engine::item_with_toggle
  < bear::engine::base_item >
  {
    DECLARE_BASE_ITEM(one_or_two_players_toggle);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::item_with_toggle
    < bear::engine::base_item > super;

  private:
    /** \brief The type of the handles on the toggles to activate. */
    typedef bear::universe::derived_item_handle<with_toggle> toggle_handle;

  public:
    one_or_two_players_toggle();

    bool set_item_field
    ( const std::string& name, bear::engine::base_item* value );

  private:
    void on_toggle_on(bear::engine::base_item *activator);
    void on_toggle_off(bear::engine::base_item *activator);

  private:
    /** \brief The item toggled in a single player game. */
    toggle_handle m_toggle_single;

    /** \brief The item toggled in a two players game. */
    toggle_handle m_toggle_coop;

  }; // class one_or_two_players_toggle
} // namespace ptb

#endif // __PTB_ONE_OR_TWO_PLAYERS_TOGGLE_HPP__
