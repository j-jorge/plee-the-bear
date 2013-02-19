/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the bear::engine::item_that_speaks class.
 * \author Sebastien Angibaud
 */

#include "engine/level_globals.hpp"

#include "ptb/defines.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
template<class Base>
ptb::item_that_speaks<Base>::item_that_speaks()
  : super( PTB_BALLOON_LAYER_DEFAULT_TARGET_NAME )
{

} // item_that_speaks::item_that_speaks()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
template<class Base>
void ptb::item_that_speaks<Base>::pre_cache()
{
  super::pre_cache();

  this->get_level_globals().load_font("font/comic.ttf");
  this->get_level_globals().load_image("gfx/ui/balloon-1.png");
} // item_that_speaks::pre_cache()

/*---------------------------------------------------------------------------*/
/**
 * \brief Initializes the item once that it is in a level.
 */
template<class Base>
void ptb::item_that_speaks<Base>::build()
{
  super::build();

  this->get_balloon().set_spike_sprite
    ( this->get_level_globals().auto_sprite("gfx/ui/balloon-1.png", "spike") );
  this->get_balloon().set_corner_sprite
    ( this->get_level_globals().auto_sprite("gfx/ui/balloon-1.png", "corner") );

  this->get_balloon().set_horizontal_border_sprite
    ( this->get_level_globals().auto_sprite
      ( "gfx/ui/balloon-1.png", "horizontal border" ) );
  this->get_balloon().set_vertical_border_sprite
    ( this->get_level_globals().auto_sprite
      ( "gfx/ui/balloon-1.png", "vertical border" ) );

  this->get_balloon().set_font
    ( this->get_level_globals().get_font("font/comic.ttf", 24) );
} // item_that_speaks::build()
