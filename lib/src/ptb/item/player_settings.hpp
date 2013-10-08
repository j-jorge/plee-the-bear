/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item to set each parameter of a player.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_PLAYER_SETTINGS_HPP__
#define __PTB_PLAYER_SETTINGS_HPP__

#include "engine/base_item.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item to set each parameter of a player.
   *
   * The valid fields for this item are
   *  - \a index:
   *  \c (unsigned integer) (required) The index of the player,
   *  - \a power.air:
   *  \c (bool) Indicates if the player has the air power,
   *  - \a power.fire:
   *  \c (unsigned integer) Indicates if the player has the fire power,
   *  - \a power.water:
   *  \c (unsigned integer) Indicates if the player has the water power,
   *  - \a stones:
   *  \c (unsigned integer) The number of stones,
   *  - \a lives:
   *  \c (unsigned integer) The number of lives,
   *  - \a score:
   *  \c (unsigned integer) The score of the player,
   *  - \a max_energy:
   *  \c (real) The size of the energy's gauge,
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class player_settings:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(player_settings);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    player_settings();

    void build();

    virtual bool set_u_integer_field
    ( const std::string& name, unsigned int value );
    virtual bool set_bool_field( const std::string& name, bool value );
    virtual bool set_real_field( const std::string& name, double value );

  private:
    /** \brief The index of the player. */
    unsigned int m_player_index;

    /** \brief Indicates if player's parameters must be save with 
	persistent variables. */
    bool m_global_settings;
  }; // class player_settings
} // namespace ptb

#endif // __PTB_PLAYER_SETTINGS_HPP__
