/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Inherit from this class to allow your item to read the player's
 *        inputs.
 * \author Julien Jorge
 */
#ifndef __PTB_ITEM_WITH_PLAYER_CONTROL_READER_HPP__
#define __PTB_ITEM_WITH_PLAYER_CONTROL_READER_HPP__

#include "ptb/player_action.hpp"
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
   * \author Julien Jorge
   */
  template<class Base>
  class item_with_player_control_reader:
    public bear::engine::item_with_input_listener<Base>
  {
  private:
   
    /**
     * \brief All informations we want to delay a action.
     */
    class waiting_action
    {
    public:
      enum waiting_action_type
      {
        start_action = 0,
        stop_action,
	do_action
      }; // enum waiting_action_type
      
    public:
      waiting_action
      ( waiting_action_type t, bear::universe::time_type d, 
	unsigned int index, player_action::value_type a, 
	bear::universe::time_type dur );

    public:
      /** \brief The type of waiting. */
      waiting_action_type waiting_type;
      
      /** \brief date of the action. */
      bear::universe::time_type date;

      /** \brief Index of player. */
      unsigned int player_index;

      /** \brief The action. */
      player_action::value_type action;

      /** \brief The duration of the action. */
      bear::universe::time_type duration;
    }; // class waiting_action

  public:
    item_with_player_control_reader();

  protected:
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
    
  private:
    /** \brief List of the waiting action. */
    std::list<waiting_action> m_waiting_actions;

    /** \brief The date of the system. */
    bear::universe::time_type m_date;

    /** \brief Delay before sending. */
    bear::universe::time_type m_delay;
  }; // class item_with_player_control_reader
} // namespace ptb

#include "ptb/item_brick/impl/item_with_player_control_reader.tpp"

#endif // __PTB_ITEM_WITH_PLAYER_CONTROL_READER_HPP__
