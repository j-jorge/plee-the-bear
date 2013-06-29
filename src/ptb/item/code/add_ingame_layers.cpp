/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::add_ingame_layers class.
 * \author Julien Jorge
 */
#include "ptb/item/add_ingame_layers.hpp"

#include "engine/export.hpp"
#include "engine/level.hpp"
#include "engine/level_globals.hpp"
#include "engine/layer/transition_layer.hpp"
#include "engine/comic/layer/balloon_layer.hpp"

#include "ptb/layer/ingame_menu_layer.hpp"
#include "ptb/layer/misc_layer.hpp"
#include "ptb/layer/player_arrows_layer.hpp"
#include "ptb/layer/status_layer.hpp"
#include "ptb/transition_effect/level_starting_effect.hpp"

#ifndef NDEBUG
#include "generic_items/layer/item_information_layer.hpp"
#include "generic_items/layer/link_layer.hpp"
#include "generic_items/layer/physics_layer.hpp"
#include "generic_items/layer/recent_path_layer.hpp"
#include "generic_items/layer/wireframe_layer.hpp"
#endif

#include "ptb/defines.hpp"

BASE_ITEM_EXPORT( add_ingame_layers, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::add_ingame_layers::add_ingame_layers()
: m_add_starting_effect(true), m_timer(NULL)
{

} // add_ingame_layers::add_ingame_layers()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::add_ingame_layers::pre_cache()
{
  get_level_globals().load_font("font/bouncy.fnt");
  get_level_globals().load_font("font/fixed_white-7x12.fnt");
  get_level_globals().load_font("font/fixed_yellow-10x20.fnt");
  get_level_globals().load_font("font/level_name-42x50.fnt");
  get_level_globals().load_image("gfx/ui/frame.png");
  get_level_globals().load_image("gfx/ui/status/status.png");
} // add_ingame_layers::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::add_ingame_layers::build()
{
  bear::engine::transition_layer* transition
    ( new bear::engine::transition_layer
      (PTB_TRANSITION_EFFECT_DEFAULT_TARGET_NAME) );

  bear::engine::transition_layer* script
    ( new bear::engine::transition_layer
      (PTB_SCRIPT_EFFECT_DEFAULT_TARGET_NAME) );

  status_layer* status
    ( new status_layer(PTB_STATUS_LAYER_DEFAULT_TARGET_NAME) );

  if ( m_timer != NULL )
    status->set_timer(m_timer);

  get_level().push_layer( script );
  get_level().push_layer( status );
  get_level().push_layer( new player_arrows_layer );
  get_level().push_layer
    ( new bear::engine::balloon_layer(PTB_BALLOON_LAYER_DEFAULT_TARGET_NAME) );
  get_level().push_layer
    ( new ingame_menu_layer(PTB_WINDOWS_LAYER_DEFAULT_TARGET_NAME) );
  // must be after ingame_menu_layer, so we can prevent the user from pausing
  // the game
  get_level().push_layer( transition );
  get_level().push_layer( new misc_layer );

#ifndef NDEBUG
  get_level().push_layer( new bear::link_layer );
  get_level().push_layer( new bear::physics_layer );
  get_level().push_layer( new bear::wireframe_layer );
  get_level().push_layer( new bear::item_information_layer );
  get_level().push_layer( new bear::recent_path_layer );
#endif

  if (m_add_starting_effect)
    transition->push_effect( new level_starting_effect, 1000 );

  kill();
} // add_ingame_layers::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c boolean.
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool
ptb::add_ingame_layers::set_bool_field( const std::string& name, bool value )
{
  bool result(true);

  if ( name == "add_ingame_layers.show_introduction" )
    m_add_starting_effect = value;
  else
    result = super::set_bool_field(name, value);

  return result;
} // add_ingame_layers::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c animation.
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::add_ingame_layers::set_animation_field
( const std::string& name, const bear::visual::animation& value )
{
  bool result(true);

  if ( name == "add_ingame_layers.corrupting_bonus_animation" )
    m_corrupting_animation = value;
  else
    result = super::set_animation_field(name, value);

  return result;
} // add_ingame_layers::set_animation_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c item.
 * \param name The name of the field.
 * \param value The value of the field.
 */
bool ptb::add_ingame_layers::set_item_field
( const std::string& name, bear::engine::base_item* value )
{
  bool result(true);

  if ( name == "add_ingame_layers.status_layer.timer" )
    {
      m_timer = dynamic_cast<bear::timer*>(value);

      if ( m_timer == NULL )
        claw::logger << claw::log_error << "add_ingame_layers::set_item_field:"
                     << " item is not an instance of 'bear::timer'."
                     << std::endl;
    }
  else
    result = super::set_item_field(name, value);

  return result;
} // add_ingame_layers::set_item_field()
