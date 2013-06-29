/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing an object which reaveal a zone
 * when a player enter.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_HIDEOUT_REVEALING_HPP__
#define __PTB_HIDEOUT_REVEALING_HPP__

#include "engine/base_item.hpp"

#include "ptb/player_proxy.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing an object which reaveal a zone
   * when a player enter.
   * \author Sébastien Angibaud
   *  - \a hiding_items: \c (list of items) The items to reveal.
   *  - \a definitive_disclosure: \c Indicates if the disclosure is definitive.
   *  - \a revealing_opacity: \c (real)
   * The opacity when we reveal items.
   *  - \a hideout_opacity: \c (real) The opacity when we hide items.
   *  - \a revelation_duration: \c (real) The duration of the revealation.
   */
  class hideout_revealing:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(hideout_revealing);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    hideout_revealing();

    void progress( bear::universe::time_type elapsed_time );
    void build();

    virtual bool set_item_list_field
      ( const std::string& name, const std::vector<base_item*>& value );
    virtual bool set_bool_field( const std::string& name, bool value );
    virtual bool set_real_field( const std::string& name, double value );

  private:
    void search_players();
    void reveal();
    void hide();

  private:
    /** \brief The list of items to reveal. */
    std::vector<bear::universe::item_handle> m_items;

    /** \brief Indicate there is a player in the zone. */
    bool m_player_in_zone;

    /** \brief Indicates if the disclosure is definitive. */
    bool m_definitive_disclosure;

    /** \brief The opacity when the zone is revealing. */
    double m_revealing_opacity;

    /** \brief The opacity when the zone is not revealing. */
    double m_hideout_opacity;

    /** \brief Indicates if items have been revealed
     * in the current iteration. */
    bool m_current_revealed;

    /** \brief Indicates if items have been revealed
     * in the last iteration. */
    bool m_last_revealed;

    /** \brief Indicates if the hideout have been definitively found. */
    bool m_hideout_found;

    /** \brief The duration of the revelation. */
    bear::universe::time_type m_revelation_duration;

    /** \brief The time since the last modification. */
    bear::universe::time_type m_last_modification;

    /** \brief The first player. */
    player_proxy m_first_player;

    /** \brief The second player. */
    player_proxy m_second_player;

    /** \brief The identifier of the hideout. */
    std::string m_hideout_name;

  }; // class hideout_revealing
} // namespace ptb

#endif // __PTB_HIDEOUT_REVEALING_HPP__
