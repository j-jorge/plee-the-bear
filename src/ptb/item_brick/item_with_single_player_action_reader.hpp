/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Inherit from this class to allow your item to read the inputs for a
 *        given player.
 * \author Julien Jorge
 */
#ifndef __PTB_ITEM_WITH_SINGLE_PLAYER_ACTION_READER_HPP__
#define __PTB_ITEM_WITH_SINGLE_PLAYER_ACTION_READER_HPP__

#include "ptb/item_brick/item_with_player_action_reader.hpp"
#include "engine/network/client_observer.hpp"

#include <map>
#include <set>

namespace ptb
{
  class player_action_message;

  /**
   * \brief Inherit from this class to allow your item to read the inputs for a
   *        given player.
   *
   * \b template \b parameters :
   * - \a Base: the base class for this item. Must inherit from
   *    engine::base_item.
   *
   * The valid fields for this item are
   *  - \a player_index: (unsigned int) The index of the player actionling this
   *    item (default = 1),
   *  - any field supported by the parent classes.
   *
   * \author Julien Jorge
   */
  template<class Base>
  class item_with_single_player_action_reader:
    public item_with_player_action_reader<Base>
  {
  private:
    /** \brief The type of the parent class. */
    typedef item_with_player_action_reader<Base> super;

    /** \brief The type of map containing switch actions. */
    typedef std::map
    < player_action::value_type, player_action::value_type> actions_map;

    /** \brief The type of list containing current actions. */
    typedef std::set< player_action::value_type> actions_set;

  public:
    item_with_single_player_action_reader();
    
    void on_enters_layer();
    bool set_u_integer_field( const std::string& name, unsigned int value );

    unsigned int get_player_index() const;
    void switch_action
    (player_action::value_type a, player_action::value_type b);
    void clear_switched_action
    (player_action::value_type a, player_action::value_type b);

  protected:
    virtual void start_action( player_action::value_type a );
    virtual void do_action
    ( bear::universe::time_type elapsed_time, player_action::value_type a );
    virtual void stop_action( player_action::value_type a );

    void set_player_index( unsigned int i );

  private:
    player_action::value_type
    get_switched_action(player_action::value_type a) const;

    void start_action
    ( unsigned int player_index, player_action::value_type a );

    void do_action
    ( bear::universe::time_type elapsed_time, unsigned int player_index,
      player_action::value_type a );

    void stop_action( unsigned int player_index, player_action::value_type a );

    void update_action
    (player_action::value_type a, player_action::value_type b,
     bool insertion, player_action::value_type clear_action);

    void read_input_action(bear::universe::time_type elapsed_time);
    void on_message(const player_action_message& m);

  private:
    /** \brief The index of the player to listen to. */
    unsigned int m_player_index;

    /** \brief The map of switch actions. */
    actions_map m_switch_actions;

    /** \brief The set of current actions. */
    actions_set m_current_actions;

    /** \brief A client observer for player action. */
    bear::engine::client_observer m_client_observer;

  }; // class item_with_single_player_action_reader
} // namespace ptb

#include "ptb/item_brick/impl/item_with_single_player_action_reader.tpp"

#endif // __PTB_ITEM_WITH_SINGLE_PLAYER_ACTION_READER_HPP__
