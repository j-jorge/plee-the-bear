/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item to set parameters of game.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_GAME_SETTINGS_HPP__
#define __PTB_GAME_SETTINGS_HPP__

#include "engine/base_item.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item to set parameters of game.
   *
   * The valid fields for this item are
   *  - \a corrupting_bonus_count:
   *  \c (unsigned integer) The number of corrupting bonus.
   *  - \a corrupting_bonus_animation_name:
   *  \c (string) The path of corrupting bonus animation.
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class game_settings:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(game_settings);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    game_settings();

    void build();

    virtual bool set_u_integer_field
    ( const std::string& name, unsigned int value );

  }; // class game_settings
} // namespace ptb

#endif // __PTB_GAME_SETTINGS_HPP__
