/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::friend_ghost class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/castle/friend_ghost.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/player.hpp"

#include "universe/forced_movement/forced_tracking.hpp"

BASE_ITEM_EXPORT( friend_ghost, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::friend_ghost::friend_ghost()
{
} // friend_ghost::friend_ghost()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::friend_ghost::~friend_ghost()
{
} // friend_ghost::~friend_ghost()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::friend_ghost::pre_cache()
{
  get_level_globals().load_model("model/castle/friend_ghost.cm");
} // friend_ghost::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::friend_ghost::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor
    ( get_level_globals().get_model("model/castle/friend_ghost.cm") );
  start_model_action("wait");
  set_origin();
} // friend_ghost::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Control the current player.
 */
void ptb::friend_ghost::control_player()
{
  bear::universe::forced_tracking mvt;
  mvt.set_reference_point_on_center(*(m_player.get_player_instance()));
  mvt.set_distance(bear::universe::position_type(0, 0));
  set_forced_movement( mvt );
} // friend_ghost::control_player()
