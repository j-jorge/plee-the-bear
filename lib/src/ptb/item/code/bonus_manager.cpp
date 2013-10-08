/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::bonus_manager class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/bonus_manager.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/defines.hpp"
#include "ptb/item/bonus_points/bonus_points.hpp"

#include "engine/game.hpp"
#include "engine/system/game_filesystem.hpp"
#include "engine/world.hpp"

BASE_ITEM_EXPORT( bonus_manager, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::bonus_manager::bonus_manager()
{

} // bonus_manager::bonus_manager()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::bonus_manager::~bonus_manager()
{
  save_game_variables();
} // bonus_manager::bonus_manager()

/*----------------------------------------------------------------------------*/
/**
 * \brief Manage bonus.
 * update_bonus Indicates if bonus must be updated.
 */
void ptb::bonus_manager::manage(bool update_bonus)
{
  if ( update_bonus )
    {
      bear::engine::world::const_item_iterator it;
      for ( it=get_world().living_items_begin();
            it!=get_world().living_items_end(); ++it)
        {
          const bonus_points* pts = dynamic_cast<const bonus_points*>(&(*it));

          if ( pts != NULL )
            pts->update_bonus_state();
        }
    }

  save_game_variables();
} // bonus_manager::manage()

/*----------------------------------------------------------------------------*/
/**
 * \brief Actions done when the state of the toggle changes from off to on.
 * \param activator The item that changed the state.
 */
void ptb::bonus_manager::on_toggle_on
(bear::engine::base_item *activator)
{
  manage();
} // bonus_manager::on_toggle_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save all game variables.
 */
void ptb::bonus_manager::save_game_variables() const
{
  const bear::engine::game& g( bear::engine::game::get_instance() );

  std::string filename
    ( g.get_game_filesystem().get_custom_config_file_name
      ( PTB_PROFILES_FOLDER ) + game_variables::get_profile_name() + "/");

  if ( game_variables::get_players_count() == 1 )
    filename += PTB_SAVE_ONE_PLAYER_FILENAME;
  else
    filename += PTB_SAVE_TWO_PLAYERS_FILENAME;

  std::ofstream f( filename.c_str() );

  bear::engine::game::get_instance().save_game_variables(f, "persistent/.*");
} // bonus_manager::save_game_variables()
