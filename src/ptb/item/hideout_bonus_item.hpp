/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A hideout to discover in order to have hideout bonus.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_HIDEOUT_BONUS_ITEM_HPP__
#define __PTB_HIDEOUT_BONUS_ITEM_HPP__

#include "ptb/item_brick/counted_item.hpp"
#include "ptb/item_brick/item_waiting_for_players.hpp"
#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
 /**
   * \brief A hideout to discover in order to have hideout bonus.
   *
   * The custom fields of this class are:
   * - any field supported by the parent classes.
   *
   * \author Sébastien Angibaud
   */
  class hideout_bonus_item:
    public item_waiting_for_players< bear::engine::base_item >
  {
    DECLARE_BASE_ITEM(hideout_bonus_item);

  public:
    /** \brief The type of the parent class. */
    typedef item_waiting_for_players< bear::engine::base_item> super;

  public:
    hideout_bonus_item();
    void build();

  protected:
    void on_one_player( const player_proxy& p );
    void on_all_players( const player_proxy& p1, const player_proxy& p2 );

  private:
    void discover(unsigned int index);
    void create_level_bonus();
    void send_notification
    (unsigned int index, unsigned int found, unsigned int total);

  private:
    /** \brief The identifier of the hideout_bonus item. */
    std::string m_id;
  }; // class hideout_bonus_item
} // namespace ptb

#endif // __PTB_HIDEOUT_BONUS_ITEM_HPP__
