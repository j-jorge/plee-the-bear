/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This class represent the position of a player when a level starts.
 * \author Julien Jorge
 */
#ifndef __PTB_PLAYER_START_POSITION_HPP__
#define __PTB_PLAYER_START_POSITION_HPP__

#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief This class represent the position of a player when a level starts.
   *
   * The custom fields of this class are:
   * - player_index: (unsigned int) the index of the player to create,
   * - exit_name: (string) the name of the exit associated with this entry
   *   point.
   *
   * The player is created if the last exit name saved in
   * game_variables::get_next_level_name() is equal to the field
   * \a player_start_position.exit_name OR if this field is empty.
   *
   * \author Julien Jorge
   */
  class player_start_position:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(player_start_position);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    player_start_position();

    bool set_u_integer_field( const std::string& name, unsigned int value );
    bool set_string_field( const std::string& name, const std::string& value );
    bool is_valid() const;

    void build();

  private:
    /** \brief The index of the player to create. */
    unsigned int m_player_index;

    /** \brief The name of the exit in the previous level, associated with this
        entry point. */
    std::string m_exit_name;

    /** \brief The type of the player : plee or ray. */
    std::string m_character;

  }; // class player_start_position
} // namespace ptb

#endif // __PTB_PLAYER_START_POSITION_HPP__
