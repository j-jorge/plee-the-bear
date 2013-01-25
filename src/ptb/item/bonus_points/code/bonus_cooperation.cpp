/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::bonus_cooperation class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/bonus_points/bonus_cooperation.hpp"
#include "ptb/game_variables.hpp"

BASE_ITEM_EXPORT( bonus_cooperation, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::bonus_cooperation::bonus_cooperation()
: super("Two players cooperation", 10000)
{

} // bonus_cooperation::bonus_cooperation()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::bonus_cooperation::build()
{
  if ( game_variables::get_players_count() > 1 )
    {
      set_picture_filename("gfx/ui/bonus-icons/bonus-icons.png");
      set_picture_name("cooperation");
      set_category("two_players_area");

      super::build();
    }
  else
    kill();
} // bonus_cooperation::build()

