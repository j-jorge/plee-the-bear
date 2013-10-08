/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item that records the actions sent to a player.
 * \author Julien Jorge
 */
#ifndef __PTB_ACTION_FILE_RECORDER_HPP__
#define __PTB_ACTION_FILE_RECORDER_HPP__

#include "ptb/item_brick/item_with_single_player_action_reader.hpp"
#include "engine/base_item.hpp"

#include "engine/export.hpp"

#include <map>
#include <fstream>

namespace ptb
{
  /**
   * \brief An item that records the actions sent to a player.
   *
   * This item saves the actions in a file that can be given to a
   * player_commander item to control a player.
   *
   * The valid fields for this item are
   *  - \a file_path: (string) [required] The path to the file in which the
   *    actions are saved,
   *  - any field supported by the parent classes.
   *
   * \author Julien Jorge
   */
  class action_file_recorder:
    public item_with_single_player_action_reader<bear::engine::base_item>
  {
    DECLARE_BASE_ITEM(action_file_recorder);

  private:
    /** \brief The type of the parent class. */
    typedef
    item_with_single_player_action_reader<bear::engine::base_item> super;

  private:
    /** \brief A class to store action informations. */
    class action_information
    {
    public:
      bool operator<( const action_information& other) const;

    public:
      /** \brief The date of the action. */
      bear::universe::time_type date;

      /** \brief The name of the action. */
      player_action::value_type action;

      /** \brief The duration of the action. */
      bear::universe::time_type duration;

    }; // class  action_information

    /** \brief All actions of a given player. */
    typedef std::vector<action_information> actions_vector;

    /** \brief The current actions of a given player. */
    typedef std::map
    <player_action::value_type, action_information> current_actions_map;

  public:
    action_file_recorder();
    action_file_recorder( const action_file_recorder& that );
    ~action_file_recorder();

    bool set_string_field( const std::string& name, const std::string& value );

    void build();
    void progress( bear::universe::time_type elapsed_time );

  private:
    void start_action( player_action::value_type a );
    void stop_action( player_action::value_type a );

  private:
    /** \brief The file in which we save the actions. */
    std::ofstream m_file;

    /** \brief The current date. */
    bear::universe::time_type m_date;

    /** \brief The current actions of a given player. */
    current_actions_map m_current_actions;

    /** \brief All actions of a given player. */
    actions_vector m_actions;

  }; // class action_file_recorder
} // namespace ptb

#endif // __PTB_ACTION_FILE_RECORDER_HPP__
