/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::corrupting_bonus_attractor class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/corrupting_bonus_attractor.hpp"

#include "ptb/item/corrupting_bonus.hpp"

BASE_ITEM_EXPORT( corrupting_bonus_attractor, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::corrupting_bonus_attractor::corrupting_bonus_attractor()
{
  set_phantom(true);
  set_can_move_items(false);
  set_size(600, 600);
} // corrupting_bonus_attractor::corrupting_bonus_attractor()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_apply().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::corrupting_bonus_attractor::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  corrupting_bonus* item = dynamic_cast<corrupting_bonus*>(&that);

  if ( item != NULL )
    item->attract(*this);
} // corrupting_bonus_attractor::collision()


