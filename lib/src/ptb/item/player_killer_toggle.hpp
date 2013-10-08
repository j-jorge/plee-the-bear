/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This toggle kill a player when activated.
 * \author Julien Jorge
 */
#ifndef __PTB_PLAYER_KILLER_TOGGLE_HPP__
#define __PTB_PLAYER_KILLER_TOGGLE_HPP__

#include "engine/base_item.hpp"
#include "engine/item_brick/item_with_toggle.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief This toggle kill a player when activated.
   *
   * The custom fields of this class are:
   * - player_index (unsigned integer): the index of the player to kill,
   * - any field supported by the parent classes.
   *
   * \author Julien Jorge
   */
  class player_killer_toggle:
    public bear::engine::item_with_toggle<bear::engine::base_item>
  {
    DECLARE_BASE_ITEM(player_killer_toggle);

  public:
    typedef bear::engine::item_with_toggle<bear::engine::base_item> super;

  public:
    player_killer_toggle( unsigned int player_index = 0 );

    bool set_u_integer_field( const std::string& name, unsigned int value );

  private:
    void on_toggle_on( bear::engine::base_item* activator );

  private:
    /** \brief The index of the player to kill. */
    unsigned int m_player_index;

  }; // class player_killer_toggle
} // namespace ptb

#endif // __PTB_PLAYER_KILLER_TOGGLE_HPP__
