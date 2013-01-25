/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Game definess.
 * \author Julien Jorge
 */
#ifndef __PTB_DEFINES_HPP__
#define __PTB_DEFINES_HPP__

/** \brief The name of the level displayed when loading a level. */
#define PTB_LOADING_LEVEL_NAME "level/loading.cl"

/** \brief The maximum number of points a player can receive at once. */
#define PTB_MAX_POINTS_AT_ONCE 50000

/** \brief The number of points over which the player wins a new try. */
#define PTB_ONE_UP_POINTS_COUNT 50000

/** \brief The maximum energy that a player can have. */
#define PTB_MAXIMUM_ENERGY 200

/** \brief The name of the layer displaying the transition effects. */
#define PTB_TRANSITION_EFFECT_DEFAULT_TARGET_NAME "transition_effect_layer"

/** \brief The name of the layer displaying the transition effects. */
#define PTB_SCRIPT_EFFECT_DEFAULT_TARGET_NAME "script_effect_layer"

/** \brief The name of the layer displaying the balloons. */
#define PTB_BALLOON_LAYER_DEFAULT_TARGET_NAME "balloon_layer"

/** \brief The name of the layer displaying the frames during the game. */
#define PTB_WINDOWS_LAYER_DEFAULT_TARGET_NAME "windows_layer"

/** \brief The name of the layer displaying the informations about the
    players. */
#define PTB_STATUS_LAYER_DEFAULT_TARGET_NAME "status_layer"

/** \brief The default orange color, used in gui layers. */
#define PTB_ORANGE_PIXEL bear::visual::color_type(254, 160, 0, 255)

/** \brief The name of the file containing the list of unlocked mini-games. */
#define PTB_UNLOCKED_MINI_GAME_FILENAME "mini-game.txt"

/** \brief The name of the file containing the list of unlocked mini-games. */
#define PTB_MINI_GAME_INFORMATIONS "mini-game/informations.txt"

/** \brief The number of record lines for mini-games. */
#define PTB_NUMBER_OF_RECORDS 6

/** \brief The number of profiles. */
#define PTB_NUMBER_OF_PROFILES 3

/** \brief The name of the folder in which profiles are saved. */
#define PTB_PROFILES_FOLDER "profiles/"

/** \brief The prefix for game variable to save. */
#define PTB_PERSISTENT_PREFIX "persistent/"

/** \brief The filename for one player save. */
#define PTB_SAVE_ONE_PLAYER_FILENAME "1p-game-variables.sav"

/** \brief The filename for one player save. */
#define PTB_SAVE_TWO_PLAYERS_FILENAME "2p-game-variables.sav"

/** \brief The filename for one player save. */
#define PTB_DEFAULT_EXIT_NAME "default"

/** \brief The name of service that dispatches first player's controls. */
#define PTB_PLAYER_ACTIONS_SERVICE "player_actions"

/** \brief The color of the aura of god */
#define PTB_GOD_AURA_COLOR bear::visual::color_type(255, 255, 133, 255)

/** \brief The color of the border of the aura of god */
#define PTB_GOD_AURA_BORDER_COLOR bear::visual::color_type(192, 192, 100, 255)

#endif // __PTB_DEFINES_HPP__
