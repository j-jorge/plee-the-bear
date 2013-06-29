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
 * \author sebastien Angibaud
 */
#ifndef __PTB_ITEM_WITH_PLAYER_ACTION_READER_HPP__
#define __PTB_ITEM_WITH_PLAYER_ACTION_READER_HPP__

#include "ptb/player_action.hpp"
#include "ptb/player_pending_action.hpp"
#include "engine/item_brick/item_with_input_listener.hpp"

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
  template<class Base>
  class item_with_player_action_reader:
    public bear::engine::item_with_input_listener<Base>
  {
  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::item_with_input_listener<Base> super;
    
  public:
    item_with_player_action_reader();

  protected:
    void add_pending_action(const player_pending_action& a);
    void progress_input_actions( bear::universe::time_type elapsed_time );
    void dummy_progress_input_actions
    ( bear::universe::time_type elapsed_time);

    /**
     * \brief Start an action asked by the human player.
     * \param player_index The index of the player asking the action.
     * \param a The action.
     */
    virtual void start_action
    ( unsigned int player_index, player_action::value_type a );

    /**
     * \brief Continue an action asked by the human player.
     * \param elapsed_time How long the action is done.
     * \param player_index The index of the player asking the action.
     * \param a The action.
     */
    virtual void do_action
    ( bear::universe::time_type elapsed_time, unsigned int player_index,
      player_action::value_type a );

    /**
     * \brief Stop an action asked by the human player.
     * \param player_index The index of the player asking the action.
     * \param a The action.
     */
    virtual void stop_action
    ( unsigned int player_index, player_action::value_type a );

  private:
    virtual void read_input_action(bear::universe::time_type elapsed_time);
    void pop_actions(bool send_actions);

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

  protected:
    /** \brief List of the pending action. */
    std::list<player_pending_action> m_pending_actions;

  private:
    /** \brief The date of the system. */
    bear::universe::time_type m_date;

    /** \brief Delay before sending. */
    bear::universe::time_type m_delay;
  }; // class item_with_player_action_reader
} // namespace ptb

#include "ptb/item_brick/impl/item_with_player_action_reader.tpp"

#endif // __PTB_ITEM_WITH_PLAYER_ACTION_READER_HPP__
