/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item that changes the level when a player is colliding with it.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_LEVEL_EXIT_HPP__
#define __PTB_LEVEL_EXIT_HPP__

#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief Items of this class start a level when all players are in collision
   *        with one of them.
   * \author Sébastien Angibaud
   * The custom fields of this class are :
   * - level: (string) The next level,
   * - exit_name: (string) The name of this exit,
   * - use_loading_screen: (bool) Use the level "loading" to load \a level
   *   (default = true).
   */
  class level_exit:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(level_exit);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    level_exit();

    void build();
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

    /** \brief The name of this exit. */
    std::string m_exit_name;
  }; // class level_exit
} // namespace ptb

#endif // __PTB_LEVEL_EXIT_HPP__
