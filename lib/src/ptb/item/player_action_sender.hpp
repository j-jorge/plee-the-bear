/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Inherit from this class to allow your item to read the player's
 *        inputs.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_PLAYER_ACTION_SENDER_HPP__
#define __PTB_PLAYER_ACTION_SENDER_HPP__

#include "ptb/player_action.hpp"
#include "ptb/player_pending_action.hpp"
#include "engine/item_brick/item_with_input_listener.hpp"
#include "engine/base_item.hpp"
#include "engine/export.hpp"
#include "net/server.hpp"

namespace ptb
{
  /**
   * \brief Inherit from this class to allow your item to read the player's
   *        inputs.
   *
   * \b template \b parameters :
   * - \a Base: the base class for this item. Must inherit from
   *    engine::base_item.
   *
   * There is no custom field of this class.
   *
   * \author Sebastien Angibaud
   */
  class player_action_sender:
    public bear::engine::item_with_input_listener<bear::engine::base_item>
  {
    DECLARE_BASE_ITEM(player_action_sender);
  
  public:

    /** \brief The type of the parent class. */
    typedef bear::engine::item_with_input_listener
    <bear::engine::base_item> super;

  public:
    player_action_sender();

    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );
    bool set_u_integer_field( const std::string& name, unsigned int value );
    bool set_string_field( const std::string& name, const std::string& value );
    
  private:
    bool key_pressed( const bear::input::key_info& key );
    bool key_released( const bear::input::key_info& key );
    bool key_maintained
    ( bear::universe::time_type elapsed_time,
      const bear::input::key_info& key );

    bool button_pressed
    ( bear::input::joystick::joy_code button, unsigned int joy_index );
    bool button_released
    ( bear::input::joystick::joy_code button, unsigned int joy_index );
    bool button_maintained
    ( bear::universe::time_type elapsed_time,
      bear::input::joystick::joy_code button, unsigned int joy_index );

    bool mouse_pressed( bear::input::mouse::mouse_code button,
                        const claw::math::coordinate_2d<unsigned int>& pos );
    bool mouse_released( bear::input::mouse::mouse_code button,
                         const claw::math::coordinate_2d<unsigned int>& pos );
    bool mouse_maintained
    ( bear::universe::time_type elapsed_time,
      bear::input::mouse::mouse_code button,
      const claw::math::coordinate_2d<unsigned int>& pos );
    
    void send( const player_pending_action& a );

  private:
    /** \brief The date of the system. */
    bear::universe::time_type m_date;
  }; // class player_action_sender
} // namespace ptb

#endif // __PTB_PLAYER_ACTION_SENDER_HPP__
