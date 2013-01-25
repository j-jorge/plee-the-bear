/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a player_speaker_zone.hpp.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_PLAYER_SPEAKER_ZONE_HPP__
#define __PTB_PLAYER_SPEAKER_ZONE_HPP__

#include "ptb/player_proxy.hpp"

#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a object when a player speak
   *         when a player go in the zone.
   * \author Sébastien Angibaud
   * The valid fields for this item are
   *  - \a speeches: \c A new speech
   *  - any field supported by the parent classes.
   */
  class player_speaker_zone:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(player_speaker_zone);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    player_speaker_zone();

    void progress( bear::universe::time_type elapsed_time );
    bool is_valid() const;

    bool set_string_list_field
    ( const std::string& name, const std::vector<std::string>& value );

  private:
    void search_players();

    void test_player_enter( const player_proxy& p, bool& player_in_zone  );

  private:
    /** \brief Indicates if the first player spoke. */
    bool m_first_player_spoke;

    /** \brief Indicates if the second player spoke. */
    bool m_second_player_spoke;

    /** \brief The speech. */
    std::vector<std::string> m_speeches;

    /** \brief Indicate if the first player was in the zone. */
    bool m_first_player_in_zone;

    /** \brief Indicate if the second player was in the zone. */
    bool m_second_player_in_zone;

    /** \brief The first player. */
    player_proxy m_first_player;

    /** \brief The second player. */
    player_proxy m_second_player;

  }; // class player_speaker_zone
} // namespace ptb

#endif // __PTB_PLAYER_SPEAKER_ZONE_HPP__
