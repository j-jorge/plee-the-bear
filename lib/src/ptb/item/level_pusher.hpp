/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item that starts a level when all players are colliding with it.
 * \author Julien Jorge
 */
#ifndef __PTB_LEVEL_PUSHER_HPP__
#define __PTB_LEVEL_PUSHER_HPP__

#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that starts a level when all players are colliding with it.
   *
   * The current level is saved by the engine and must be restored when the new
   * one is finished.
   *
   * The custom fields of this class are :
   * - level: (string) The level to load.
   *
   * \sa level_popper
   * \author Julien Jorge
   */
  class level_pusher:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(level_pusher);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    level_pusher();

    void progress( bear::universe::time_type elapsed_time );
    bool is_valid() const;
    bool set_string_field( const std::string& name, const std::string& value );

  private:
    void collision_check_and_apply
    ( bear::engine::base_item& that, bear::universe::collision_info& info );
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    /** \brief The name of the level to load. */
    std::string m_level_name;

    /** \brief Remember that the level has been pushed and wait until both
        players are outside before allowing to push the level again. */
    bool m_pushed;

    /** \brief How many players are colliding with this item. */
    std::size_t m_players_count;

  }; // class level_pusher
} // namespace ptb

#endif // __PTB_LEVEL_PUSHER_HPP__
