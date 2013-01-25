/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::add_main_menu_layer class.
 * \author Julien Jorge
 */
#include "ptb/item/add_main_menu_layer.hpp"

#include "engine/level.hpp"
#include "engine/level_globals.hpp"
#include "ptb/layer/main_menu_layer.hpp"
#include "ptb/layer/misc_layer.hpp"

BASE_ITEM_EXPORT( add_main_menu_layer, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::add_main_menu_layer::add_main_menu_layer()
{

} // add_main_menu_layer::add_main_menu_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::add_main_menu_layer::pre_cache()
{
  get_level_globals().load_font("font/fixed_white-7x12.fnt");
  get_level_globals().load_font("font/fixed_yellow-10x20.fnt");
  get_level_globals().load_image("gfx/ui/frame.png");
} // add_main_menu_layer::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Show the menu.
 */
void ptb::add_main_menu_layer::build()
{
  get_level().push_layer( new main_menu_layer( get_center_of_mass() ) );
  get_level().push_layer( new misc_layer() );
} // add_main_menu_layer::build()
