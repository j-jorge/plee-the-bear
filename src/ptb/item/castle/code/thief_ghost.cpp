/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::thief_ghost class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/castle/thief_ghost.hpp"
#include "ptb/game_variables.hpp"

#include "universe/forced_movement/forced_goto.hpp"

BASE_ITEM_EXPORT( thief_ghost, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::thief_ghost::thief_ghost()
{
} // thief_ghost::thief_ghost()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::thief_ghost::~thief_ghost()
{
} // thief_ghost::~thief_ghost()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::thief_ghost::pre_cache()
{
  get_level_globals().load_model("model/castle/thief_ghost.cm");
} // thief_ghost::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::thief_ghost::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor
    ( get_level_globals().get_model("model/castle/thief_ghost.cm") );
  start_model_action("wait");
  set_origin();
} // thief_ghost::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state control.
 */
void ptb::thief_ghost::progress_control
( bear::universe::time_type elapsed_time )
{
   if ( !has_forced_movement() )
    {
      if ( m_player != NULL )
        release_player();
      m_player = player_proxy();

      if ( !scan_players() )
        start_model_action("come_back");
    }
   else if ( get_center_of_mass().distance
       (m_origin.get_center_of_mass()) > m_max_distance )
    start_model_action("come_back");
} // thief_ghost::progress_control()

/*----------------------------------------------------------------------------*/
/**
 * \brief Control the current player.
 */
void ptb::thief_ghost::control_player()
{
  if ( game_variables::get_corrupting_bonus_count() > 0 )
    game_variables::set_corrupting_bonus_count
      (game_variables::get_corrupting_bonus_count() - 1);

  if ( m_player != NULL )
    {
      bear::universe::forced_goto mvt;
      bear::universe::speed_type dir(get_speed());
      dir.normalize();
      dir = dir * 200;
      mvt.set_length(dir);
      mvt.set_auto_remove(true);
      mvt.set_total_time( 1 );

      set_forced_movement( mvt );
    }
} // thief_ghost::control_player()

