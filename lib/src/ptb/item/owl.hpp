/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The owl opens a secret level if the player has found the hazelnut.
 * \author Julien Jorge
 */
#ifndef __PTB_OWL_HPP__
#define __PTB_OWL_HPP__

#include "ptb/item_brick/sniffable.hpp"
#include "ptb/player_proxy.hpp"
#include "ptb/item_brick/item_that_speaks.hpp"
#include "ptb/item_brick/activate_on_players.hpp"

#include "engine/model.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The owl opens a secret level if the player has found the hazelnut.
   *
   * The custom fields of this class are :
   * - level: (string) [required] The level to load.
   *
   * \sa level_popper
   * \author Julien Jorge
   */
  class owl :
    public item_that_speaks< bear::engine::model<bear::engine::base_item> >,
    public activate_on_players,
    public sniffable
  {
    DECLARE_BASE_ITEM(owl);

  private:
    typedef void (owl::*progress_function_type)(bear::universe::time_type);

    /** \brief The type of the parent class. */
    typedef
    item_that_speaks< bear::engine::model<bear::engine::base_item> > super;

    /** \brief Identifiers of the actions of the owl. */
    enum action
      {
        /** \brief The owl does nothing, no player is present. */
        action_idling,

        /** \brief The owl is speaking, or has spoken and the player is still
            here. */
        action_speaking,

        /** \brief One player is here, the owl is waiting for the second
            player. */
        action_wait_for_player,

        /** \brief All players are here, with the hazelnut. The owl is dowing
            the scenario before starting the sub level. */
        action_start_level_scenario

      }; // enum action

  public:
    owl();

    void pre_cache();
    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );
    bool is_valid() const;

    bool set_string_field( const std::string& name, const std::string& value );
    bool set_string_list_field
    ( const std::string& name, const std::vector<std::string>& value );

  private:
    void on_one_player( const player_proxy& p );
    void on_all_players( const player_proxy& p1, const player_proxy& p2 );

    void progress_ask_hazelnut( bear::universe::time_type elapsed_time );
    void progress_looking_hazelnut( bear::universe::time_type elapsed_time );
    void progress_start_level( bear::universe::time_type elapsed_time );

    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void say( const std::vector<std::string>& s );
    void create_level_bonus();
    void send_owl_notification(unsigned int index);
    
  private:
    /** \brief The current action of the owl. */
    action m_action;

    /** \brief The activity function. */
    progress_function_type m_progress;

    /** \brief The first player, when activating the owl. */
    player_proxy m_first_player;

    /** \brief The first player, when activating the owl. */
    player_proxy m_second_player;

    /** \brief Tell if the owl has been activated during a progress. */
    bool m_activated;

    /** \brief The name of the level to load. */
    std::string m_level_name;

    /** \brief Tell if the owl has her hazelnut. */
    bool m_has_hazelnut;

    /** \brief A set of speeches for requesting an hazelnut. */
    std::vector<std::string> m_want_hazelnut;

    /** \brief A set of speeches to tell that the owl is happy. */
    std::vector<std::string> m_happy;

    /** \brief A set of speeches for requesting the other player. */
    std::vector<std::string> m_other_player;

    /** \brief A set of speeches to tell that the owl already has his
        hazelnut. */
    std::vector<std::string> m_already_have;

    /** \brief A set of speeches to say goodbye. */
    std::vector<std::string> m_goodbye;

    /** \brief A set of speeches sait when receiving the hazelnut. */
    std::vector<std::string> m_receive_hazelnut;

  }; // class owl
} // namespace ptb

#endif // __PTB_OWL_HPP__
