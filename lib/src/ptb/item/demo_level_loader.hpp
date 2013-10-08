/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item that starts a demo level.
 * \author Julien Jorge
 */
#ifndef __PTB_DEMO_LEVEL_LOADER_HPP__
#define __PTB_DEMO_LEVEL_LOADER_HPP__

#include "engine/base_item.hpp"
#include "engine/item_brick/item_with_input_listener.hpp"

#include "engine/export.hpp"

#include <limits>

namespace ptb
{
  /**
   * \brief An item that starts a demo level.
   *
   * The custom fields of this class are :
   * - \a levels: (list of string) The levels to load,
   * - \a players_count: (list of unsigned int) The count of players in each of
   *   those levels,
   * - \a delay: (real), number of seconds before starting a level
   *   (default = 30).
   *
   * The list \a levels and \a players_count must have the same size. Moreover,
   * all levels in the former must exist.
   *
   * When created, this item sets the boolean game variable "demo/is_on" to
   * false. Then, before starting the level, this variable is set to true. You
   * can use it to check if your level runs in demo mode or not.
   *
   * Each time an item of this class is created, he saves the index of the next
   * level in the sequence in the unsigned int game variable named
   * "demo/next_index".
   *
   * The level is loaded if the user stays inactive for \a delay successive
   * seconds. A one second fade to black effect appears between the end of the
   * delay and the loading of the level. Actually, the "loading" level is used
   * to start the level, using the adequate game variable to store the name of
   * the level.
   *
   * \author Julien Jorge
   */
  class demo_level_loader:
    public bear::engine::item_with_input_listener<bear::engine::base_item>
  {
    DECLARE_BASE_ITEM(demo_level_loader);

  public:
    /** \brief The type of the parent class. */
    typedef
    bear::engine::item_with_input_listener<bear::engine::base_item> super;

  public:
    demo_level_loader();

    bool set_real_field( const std::string& name, const double value );
    bool set_string_list_field
    ( const std::string& name, const std::vector<std::string>& value );
    bool set_u_integer_list_field
    ( const std::string& name, const std::vector<unsigned int>& value );

    bool is_valid() const;

    void build();
    void progress( bear::universe::time_type elapsed_time );

  private:
    bool key_pressed( const bear::input::key_info& key );
    bool button_pressed
    ( bear::input::joystick::joy_code button, unsigned int joy_index );
    bool mouse_pressed( bear::input::mouse::mouse_code button,
                        const claw::math::coordinate_2d<unsigned int>& pos );

  private:
    /** \brief The names of the levels to load. */
    std::vector<std::string> m_level_name;

    /** \brief The count of players in each level. */
    std::vector<unsigned int> m_players_count;

    /** \brief The delay before starting a level. */
    bear::universe::time_type m_delay;

    /** \brief Elapsed time since the creation of the item. */
    bear::universe::time_type m_elapsed_time;

  }; // class demo_level_loader
} // namespace ptb

#endif // __PTB_DEMO_LEVEL_LOADER_HPP__
