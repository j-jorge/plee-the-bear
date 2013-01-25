/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::main_menu_layer class.
 * \author Julien Jorge
 */
#include "ptb/layer/main_menu_layer.hpp"

#include "engine/level_globals.hpp"
#include "ptb/frame/frame_main_menu.hpp"

#include "engine/version.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param pos The position of the main window.
 */
ptb::main_menu_layer::main_menu_layer
( const claw::math::coordinate_2d<unsigned int>& pos )
  : m_engine_version(NULL), m_position(pos)
{

} // main_menu_layer::main_menu_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::main_menu_layer::~main_menu_layer()
{
  delete m_engine_version;
} // main_menu_layer::~main_menu_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the layer.
 */
void ptb::main_menu_layer::build()
{
  super::build();

  m_engine_version =
    new bear::gui::static_text
    ( get_level_globals().get_font("font/fixed_white-7x12.fnt", 12) );

  m_engine_version->set_auto_size(true);
  m_engine_version->set_text(BEAR_VERSION_STRING);
  m_engine_version->set_position
    ( get_size().x - m_engine_version->width() - m_engine_version->height(),
      m_engine_version->height() );

  frame_main_menu* wnd = new frame_main_menu(this);

  wnd->set_position(m_position - wnd->get_size() / 2);
  show_window( wnd );
} // main_menu_layer::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the layer on a screen.
 * \param e (out) The scene elements.
 */
void ptb::main_menu_layer::render( scene_element_list& e ) const
{
  m_engine_version->render(e);
  super::render(e);
} // main_menu_layer::render()
