/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the bear::player_killer class.
 * \author Julien Jorge
 */
#include "ptb/item/player_killer.hpp"

#include "universe/collision_info.hpp"
#include "engine/export.hpp"
#include "ptb/player_proxy.hpp"
#include "ptb/player_action.hpp"

BASE_ITEM_EXPORT( player_killer, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Kill \a that if it is a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::player_killer::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if ( p != NULL )
    p.start_action( player_action::die );
} // player_killer::collision()
