/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::bonus_exits class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/bonus_points/bonus_exits.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/message/status_layer_notification_message.hpp"
#include "ptb/defines.hpp"

#include "expr/boolean_function.hpp"

#include "engine/level_globals.hpp"

#include <libintl.h>

BASE_ITEM_EXPORT( bonus_exits, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::bonus_exits::bonus_exits()
: super("Different exits", 10000)
{

} // bonus_exits::bonus_exits()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::bonus_exits::build()
{
  if ( game_variables::get_players_count() > 1 )
    {
      set_picture_filename("gfx/ui/bonus-icons/bonus-icons.png");
      set_picture_name("exits");

      set_condition
        ( bear::expr::boolean_function_maker
          ( this, std::mem_fun_ref( &ptb::bonus_exits::different_exits ) ) );

      super::build();
    }
  else
    kill();
} // bonus_exits::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if players used different exits.
 */
bool ptb::bonus_exits::different_exits()
{
  return game_variables::get_last_level_exit
    ( game_variables::get_next_level_name(), 1 ) !=
    game_variables::get_last_level_exit
    ( game_variables::get_next_level_name(), 2 ) ;
} // bonus_exits::different_exits()

/*----------------------------------------------------------------------------*/
/**
 * \brief Fonction tell when the bonus give points.
 */
void ptb::bonus_exits::on_give_points() const
{
  status_layer_notification_message msg;

  bear::visual::sprite sp;
  
  if ( ( ! get_picture_filename().empty() ) && 
       ( ! get_picture_name().empty() ) ) 
    sp = get_level_globals().auto_sprite
      ( get_picture_filename(), get_picture_name());
  msg.set_notification( 0, sp, get_name());

  get_level_globals().send_message
    ( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
} // bonus_exits::on_give_points()
