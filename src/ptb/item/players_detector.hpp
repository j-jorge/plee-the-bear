/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An item that kills itself after collision with a player.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_PLAYERS_DETECTOR_HPP__
#define __PTB_PLAYERS_DETECTOR_HPP__

#include "ptb/item_brick/item_waiting_for_players.hpp"
#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
 /**
   * \brief An item that kills itself after collision with a player.
   *
   * The custom fields of this class are:
   * - \a category:
   *  \c (string) The category used by ptb::bonus_all_dead_by_category items,
   * - any field supported by the parent classes.
   *
   * \author Sébastien Angibaud
   */
  class players_detector:
    public item_waiting_for_players<bear::engine::base_item>
  {
    DECLARE_BASE_ITEM(players_detector);

  public:
    /** \brief The type of the parent class. */
    typedef item_waiting_for_players< bear::engine::base_item> super;

  public:
    players_detector();

    bool set_string_field( const std::string& name, const std::string& value );
    const std::string& get_category() const;

  protected:
    void on_one_player( const player_proxy& p );
    void on_all_players( const player_proxy& p1, const player_proxy& p2 );

  private:
    /** \brief The category of the item
     * (used by ptb::bonus_all_dead_by_category items). */
    std::string m_category;
  }; // class players_detector
} // namespace ptb

#endif // __PTB_PLAYERS_DETECTOR_HPP__
