/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A message sent to get the instance of a player.
 * \author Julien Jorge
 */
#ifndef __PTB_GET_PLAYER_INSTANCE_HPP__
#define __PTB_GET_PLAYER_INSTANCE_HPP__

#include "ptb/player.hpp"

#include "communication/typed_message.hpp"

#include "ptb/player.hpp" // must be included, not predeclared.

namespace ptb
{
  /**
   * \brief A message sent to get the instance of a player.
   * \author Julien Jorge
   */
  class get_player_instance:
    public bear::communication::typed_message<player>
  {
  public:
    get_player_instance();

    bool apply_to( player& that );

    player* get_instance() const;

  private:
    /** \brief The instance of the player. */
    player* m_player;

  }; // class get_player_instance
} // namespace ptb

#endif // __PTB_GET_PLAYER_INSTANCE_HPP__
