/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Save the position of the player.
 * \author Julien Jorge
 */
#ifndef __PTB_SAVE_PLAYER_POSITION_HPP__
#define __PTB_SAVE_PLAYER_POSITION_HPP__

#include "engine/base_item.hpp"
#include "engine/level_globals.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief Tell the player to save its position. The position given to the
   *        player, as a reference position, is the center of mass of the
   *        save_player_position item.
   *
   * The position of the player is saved only on the first collision. Never
   * after.
   *
   * The custom fields of this item are:
   * - \a player_index: (unsigned int) The index of the player whose position is
   *   saved (default = 1),
   * - any field supported by the parent class.
   *
   * \author Julien Jorge
   */
  class save_player_position:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(save_player_position);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    save_player_position();

    bool set_u_integer_field( const std::string& name, unsigned int value );
    void progress( bear::universe::time_type elapsed_time );

  protected:
    unsigned int get_player_index() const;
    void set_player_index( unsigned int i );
    void can_be_reactivated( bool b );

    bool is_activated() const;
    virtual void activate();
    virtual void reactivate();

  private:
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    /** \brief The index of the player concerned by this item. */
    unsigned int m_player_index;

    /** \brief Tell if the item has been activated. */
    bool m_activated;

    /** \brief Tell if there has been a collision since the last progress. */
    bool m_collision;

    /** \brief Tell if the item is ready to be (re)activated. */
    bool m_ready;

    /** \brief Tell if the item is allowed to be reactivated. */
    bool m_can_be_reactivated;

  }; // class save_player_position
} // namespace ptb

#endif // __PTB_SAVE_PLAYER_POSITION_HPP__
