/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An item that controls a player during a script.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_SCRIPT_ACTOR_PLAYER_HPP__
#define __PTB_SCRIPT_ACTOR_PLAYER_HPP__

#include "engine/base_item.hpp"
#include "ptb/player_action.hpp"
#include "engine/script/script_context.hpp"
#include "engine/script/script_runner.hpp"
#include "engine/export.hpp"
#include "universe/derived_item_handle.hpp"

#include <set>

namespace ptb
{
  class player;

  /**
   * \brief An item that controls a player during a script.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sébastien Angibaud
   */
  class script_actor_player:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(script_actor_player);

  private:
     /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

    /** \brief The current actions of a given player. */
    typedef std::map<player_action::value_type, bear::universe::time_type>
    current_actions_map;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  private:
    /** \brief A class to store action informations. */
    struct action_information
    {
      /** \brief The date of the action. */
      bear::universe::time_type date;

      /** \brief The name of the action. */
      player_action::value_type action;

      /** \brief The duration of the action. */
      bear::universe::time_type duration;

      /** \brief The speech that Plee says. */
      std::string speech;

    }; // struct action_information

    /** \brief All actions of a given player. */
    typedef std::list<action_information> actions_list;

  public:
    script_actor_player();

    bool set_u_integer_field( const std::string& name, unsigned int value );
    bool set_item_field
    ( const std::string& name, bear::engine::base_item* value );

    bool is_valid() const;
    void progress( bear::universe::time_type elapsed_time );
    void progress_actions( bear::universe::time_type elapsed_time );
    void do_action( const std::string& action_name,
                    bear::universe::time_type duration );
    void talk(const std::vector<std::string>& speech);
    void give_stone(unsigned int stock);
    void set_power(const std::string& power, bool status);
    void stop();
    void control_player();
    void release_player();
    void authorize_action(const std::string& action);
    void refuse_action(const std::string& action);
    void give_oxygen(double oxygen);
    void add_player_in_script
    (bear::engine::script_runner& script, const std::string& name);

  private:
    void search_player();
    void get_dependent_items( std::list<physical_item*>& d ) const;

    static void init_exported_methods();

  private:
    /** \brief The current date. */
    bear::universe::time_type m_date;

    /** \brief The current actions to do. */
    current_actions_map m_current_actions;

    /** \brief The new actions to do. */
    std::set<player_action::value_type> m_new_actions;

    /** \brief All actions of a given player. */
    actions_list m_actions;

    /** \brief The index of the player to control. */
    unsigned int m_player_index;

    /** \brief The player to control. */
    bear::universe::derived_item_handle<player> m_player;

  }; // class script_actor_player
} // namespace ptb

#endif // __PTB_SCRIPT_ACTOR_PLAYER_HPP__
