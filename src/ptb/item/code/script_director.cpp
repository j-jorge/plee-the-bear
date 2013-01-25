/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the bear::script_director class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/script_director.hpp"

#include "ptb/defines.hpp"

#include "engine/transition_effect/strip_effect.hpp"
#include "engine/message/transition_effect_message.hpp"
#include "engine/level_globals.hpp"

BASE_ITEM_EXPORT( script_director, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform each actor that the script begins.
 */
void ptb::script_director::on_script_started()
{
  super::on_script_started();

  bear::engine::transition_effect_message<bear::engine::strip_effect> msg;
  msg.get_effect().set_duration(0.25, get_script_duration(), 0.75);
  msg.get_effect().set_color( 0, 0, 0 );
  msg.get_effect().set_strip_height(60);
  get_level_globals().send_message
    ( PTB_SCRIPT_EFFECT_DEFAULT_TARGET_NAME, msg );
} // script_director::on_script_started()
