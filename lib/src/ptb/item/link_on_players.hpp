/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This item adds a link between the players.
 * \author Julien Jorge
 */
#ifndef __PTB_LINK_ON_PLAYERS_HPP__
#define __PTB_LINK_ON_PLAYERS_HPP__

#include "generic_items/link/base_link_visual.hpp"

#include "ptb/item_brick/item_waiting_for_players.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief This item adds a link between the players.
   *
   * The valid fields for this item are
   *  - \a strength: (real) the strength of the link (default = infinity),
   *  - \a length.minimal: (real) the minimal length of the link (default = 0),
   *  - \a length.maximal: (real) the maximal length of the link
   *    (default = infinity),
   *  - any field supported by the parent classes.
   *
   * \author Julien Jorge
   */
  class link_on_players:
    public item_waiting_for_players< bear::engine::base_item >
  {
    DECLARE_BASE_ITEM(link_on_players);

  public:
    /** \brief The type of the parent class. */
    typedef item_waiting_for_players< bear::engine::base_item> super;

  public:
    link_on_players();
    link_on_players( const link_on_players& that );
    ~link_on_players();

    bool set_real_field( const std::string& name, double value );
    bool set_item_field
    ( const std::string& name, bear::engine::base_item* item );

  private:
    void on_all_players( const player_proxy& p1, const player_proxy& p2 );

  private:
    /** \brief The strength of the link. */
    double m_strength;

    /** \brief The minimal length of the link. */
    double m_minimal_length;

    /** \brief The maximal length of the link. */
    double m_maximal_length;

    /** \brief The decoration of the link.. */
    bear::base_link_visual* m_link_visual;

  }; // class link_on_players
} // namespace ptb

#endif // __PTB_LINK_ON_PLAYERS_HPP__
