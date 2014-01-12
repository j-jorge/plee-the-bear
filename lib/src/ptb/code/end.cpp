/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \brief Implementation of the functions called at the end of
 *        the game.
 * \author Sébastien Angibaud
 */
#include "ptb/end.hpp"

#include "ptb/defines.hpp"
#include "ptb/game_variables.hpp"

#include "engine/game.hpp"
#include "engine/game_initializer.hpp"
#include "engine/system/game_filesystem.hpp"
#include "engine/resource_pool.hpp"
#include "engine/variable/variable.hpp"

#include <libintl.h>
#include <claw/logger.hpp>
#include <claw/string_algorithm.hpp>
#include <claw/configuration_file.hpp>
#include <sstream>

BEAR_ENGINE_GAME_END_FUNCTION( end_plee_the_bear )

/*----------------------------------------------------------------------------*/
/**
 * \brief Save minigames that are unlocked.
 */
void save_mini_game()
{
  const bear::engine::game& g( bear::engine::game::get_instance() );

  const std::string path
    ( g.get_game_filesystem().get_custom_config_file_name
      ( PTB_UNLOCKED_MINI_GAME_FILENAME ) );
  std::ofstream f1( path.c_str() );

  if ( !f1 )
    claw::logger << claw::log_warning
                 << "Can't open list of mini-games in file '"
                 << path << "'." << std::endl;
  else
    {
      std::stringstream f;
      bear::engine::resource_pool::get_instance().get_file
        (PTB_MINI_GAME_INFORMATIONS, f);

      CLAW_PRECOND( f );

      if (f)
        {
          claw::configuration_file config(f);

          claw::configuration_file::const_file_iterator it;
          for (it=config.file_begin(); it!=config.file_end(); ++it)
            {
              bear::engine::variable<bool> v("mini-game/"+*it);

              if ( bear::engine::game::get_instance().
                   game_variable_exists(v) )
                {
                  bear::engine::game::get_instance().
                    get_game_variable(v);

                  if ( v.get_value() )
                    f1 << *it << std::endl;
                }
            }
        }
      else
        claw::logger << claw::log_error
                     << "can't find file named '"
                     << PTB_MINI_GAME_INFORMATIONS << "'."  << std::endl;
    }
} // save_mini_game()

void end_plee_the_bear()
{
  save_mini_game();
} // end_plee_the_bear()
