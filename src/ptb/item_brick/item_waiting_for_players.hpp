/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief This item is activated when all players are colliding with it.
 * \author Julien Jorge
 */
#ifndef __PTB_ITEM_WAITING_FOR_PLAYERS_HPP__
#define __PTB_ITEM_WAITING_FOR_PLAYERS_HPP__

#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/base_item.hpp"

#include "ptb/player_proxy.hpp"

namespace ptb
{
  /**
   * \brief This item is activated when all players are colliding with it.
   * The custom fields of this class are:
   * - allowed_actions List of allowed actions for activation.
   * - (default = all actions)
   * - any field supported by the parent classes.
   * \author Julien Jorge
   */
  template<class Base>
  class item_waiting_for_players:
    public bear::engine::basic_renderable_item<Base>
  {
    /** \brief The type of the parent class. */
    typedef bear::engine::basic_renderable_item <Base> super;

  public:
    item_waiting_for_players();
    item_waiting_for_players(const item_waiting_for_players<Base>& that );

    void progress( bear::universe::time_type elapsed_time );
    void build();
    void get_visual( std::list<bear::engine::scene_visual>& visuals ) const;

    bool set_animation_field
    ( const std::string& name, const bear::visual::animation& value );
    bool set_string_list_field
    ( const std::string& name, const std::vector<std::string>& value );

    bool all_players_present() const;
    bool one_player_present() const;

  private:
    void one_player( const player_proxy& p );
    void all_players( const player_proxy& p1, const player_proxy& p2 );
    void no_player();

    void progress_one_player
    ( bear::universe::time_type elapsed_time, const player_proxy& p );
    void progress_all_players
    ( bear::universe::time_type elapsed_time, const player_proxy& p1,
      const player_proxy& p2 );
    void progress_no_player( bear::universe::time_type elapsed_time );

    virtual void on_one_player( const player_proxy& p );
    virtual void on_all_players
    ( const player_proxy& p1, const player_proxy& p2 );
    virtual void on_no_player();

    virtual void do_progress_one_player
    ( bear::universe::time_type elapsed_time, const player_proxy& p );
    virtual void do_progress_all_players
    ( bear::universe::time_type elapsed_time, const player_proxy& p1,
      const player_proxy& p2 );
    virtual void
    do_progress_no_player( bear::universe::time_type elapsed_time );
    bool check_action( const player_proxy& p );
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    /** \brief The first player, if colliding with this item. */
    player_proxy m_first_player;

    /** \brief The second player, if colliding with this item. */
    player_proxy m_second_player;

    /** \brief Previous check of first player. */
    bool m_previous_check_first_player;

    /** \brief Previous check of the second player. */
    bool m_previous_check_second_player;

    /** \brief The animation to display when no player is there. */
    bear::visual::animation m_off;

    /** \brief The animation to display when only the first player is there. */
    bear::visual::animation m_single_one;

    /** \brief The animation to display when only the second player is there.*/
    bear::visual::animation m_single_two;

    /** \brief The animation to display when all players are there. */
    bear::visual::animation m_all;

    /** \brief The animation currently displayed. */
    bear::visual::animation* m_current_animation;

    /* \brief Set of allowed actions for activation. */
    std::set<std::string> m_allowed_actions;
  }; // class item_waiting_for_players
} // namespace ptb

#include "ptb/item_brick/impl/item_waiting_for_players.tpp"

#endif // __PTB_ITEM_WAITING_FOR_PLAYERS_HPP__
