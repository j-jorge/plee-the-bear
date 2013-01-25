/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the bear::player_stop_block class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/player_stop_block.hpp"

#include "universe/collision_info.hpp"

#include "ptb/player_proxy.hpp"

BASE_ITEM_EXPORT( player_stop_block, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if \a that is a player align the other item.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::player_stop_block::collision_check_player_and_align
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if (p != NULL)
    collision_check_and_align(that, info);
} // player_stop_block::collision_check_player_and_align()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_align().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::player_stop_block::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_player_and_align(that, info);
} // player_stop_block::collision()
