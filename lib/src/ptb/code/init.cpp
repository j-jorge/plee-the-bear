/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \brief Implementation of the functions called at the begining of
 *        the game.
 * \author Julien Jorge
 */
#include "ptb/init.hpp"

#include "ptb/defines.hpp"
#include "ptb/config_file.hpp"
#include "ptb/controller_config.hpp"
#include "ptb/game_variables.hpp"
#include "engine/game.hpp"
#include "engine/game_initializer.hpp"
#include "engine/system/game_filesystem.hpp"
#include "engine/variable/variable.hpp"
#include "engine/resource_pool.hpp"
#include "engine/i18n/gettext_translator.hpp"
#include "engine/i18n/translator.hpp"

#include <locale>
#include <claw/logger.hpp>
#include <claw/string_algorithm.hpp>
#include <claw/configuration_file.hpp>
#include <sstream>
#include <boost/preprocessor/stringize.hpp>

BEAR_ENGINE_GAME_INIT_FUNCTION( init_plee_the_bear )

/*----------------------------------------------------------------------------*/
/**
 * \brief Load minigame names and set if there are unlocked.
 */
void load_mini_game()
{
  const std::string filename(PTB_UNLOCKED_MINI_GAME_FILENAME);
  const bear::engine::game& g( bear::engine::game::get_instance() );

  const std::string path
    ( g.get_game_filesystem().get_custom_config_file_name(filename) );
  std::ifstream f( path.c_str() );

  if ( !f )
    claw::logger << claw::log_verbose
                 << "Can't find the mini-game list in file '"
                 << PTB_UNLOCKED_MINI_GAME_FILENAME << "'."  << std::endl;
  else
    {
      std::string line;

      while ( claw::text::getline(f, line) )
        {
          claw::text::trim( line, " \t" );

          if ( !line.empty() )
            if ( line[0] != '#' )
              {
                claw::logger << claw::log_verbose << "Add mini-game '"
                             << line << "'" << std::endl;

                bear::engine::game::get_instance().set_game_variable
                  ( bear::engine::variable<bool>("mini-game/"+line, true ) );
              }
        }
    }
} // load_mini_game()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialisation of the game.
 */
void init_plee_the_bear()
{
  bindtextdomain( "plee-the-bear", "/usr/share/locale" );
  bind_textdomain_codeset( "plee-the-bear", "ISO-8859-15" );
  textdomain( "plee-the-bear" );

  bear::engine::game::get_instance().set_translator
    ( bear::engine::gettext_translator( "plee-the-bear" ) );

  srand( time(NULL) );

  ptb::config_file config;
  config.apply();
  config.save();

  ptb::controller_config controller;
  controller.load();

  load_mini_game();
} // init_plee_the_bear()
