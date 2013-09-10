/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item to set parameters of level.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_LEVEL_SETTINGS_HPP__
#define __PTB_LEVEL_SETTINGS_HPP__

#include "generic_items/level_settings.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item to set parameters of level.
   *
   * The valid fields for this item are
   *  - \a is_main_level:
   *  \c (bool) Indicates if the level is a main level.
   *  - \a game_over_allowed:
   *  \c (bool) Indicates if game over is allowed.
   *  - \a friendly_fire:
   *  \c (bool) Indicates if a player can harm each other.
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class level_settings:
    public bear::level_settings
  {
    DECLARE_BASE_ITEM(level_settings);

  public:
    /** \brief The type of the parent class. */
    typedef bear::level_settings super;

  public:
    level_settings();

    void build();

    virtual bool set_bool_field( const std::string& name, bool value );
    virtual bool set_string_field
    ( const std::string& name, const std::string& value );

  private:
    /** \brief Indicates if the level is a main level. */
    bool m_is_main_level; 

    /** \brief Indicates if the player status is always displayed. */
    bool m_player_status_fixed;
  }; // class level_settings
} // namespace ptb

#endif // __PTB_LEVEL_SETTINGS_HPP__
