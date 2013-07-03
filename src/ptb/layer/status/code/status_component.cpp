/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::status_component class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/status/status_component.hpp"

/*----------------------------------------------------------------------------*/
const double ptb::status_component::s_bar_length = 100;
const unsigned int ptb::status_component::s_margin = 10;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param glob Level globals in which we take the resources.
 * \param p The player from which we take the data.
 * \param active_position the position in active state.
 * \param side Indicates the side on which the component appears.
 * \param x_p The placement on x-coordinate.
 * \param y_p The placement on y-coordinate.
 * \param layer_size The size of the layer.
 */
ptb::status_component::status_component
( bear::engine::level_globals& glob, const player_proxy& p,
  const bear::visual::position_type& active_position,
  bear::universe::zone::position side,
  x_placement x_p, y_placement y_p,
  const bear::universe::size_box_type& layer_size)
  : m_level_globals(glob), m_player(p), m_side(side),
    m_x_placement(x_p), m_y_placement(y_p),
    m_layer_size(layer_size), m_active_position(active_position)
{
  
} // status_component::status_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::status_component::~status_component()
{
  for ( ; !m_signals.empty(); m_signals.pop_front() )
    m_signals.front().disconnect();
} // status_component::~status_component()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the component.
 */
void ptb::status_component::build()
{
  init_signals();
  update_inactive_position();
  on_x_position_update(m_inactive_position.x);
  on_y_position_update(m_inactive_position.y);
} // status_component::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the players status and update local values.
 */
void ptb::status_component::progress( bear::universe::time_type elapsed_time )
{
  update_inactive_position();
  m_tweeners.update(elapsed_time);  
} // status_component::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the players status.
 * \param e (out) The scene elements.
 */
void ptb::status_component::render( scene_element_list& e ) const
{
  // do nothing
} // status_component::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add a new signal.
 * \param s The signal to add.
 */
void ptb::status_component::add_signal(const boost::signals::connection& s)
{
  m_signals.push_back(s);
} // status_component::add_signal()

/*----------------------------------------------------------------------------*/
/**
 * \brief Add a new tweener.
 * \param t The tweener to add.
 */
void ptb::status_component::add_tweener(const claw::tween::tweener& t)
{
  m_tweeners.insert(t);
} // status_component::add_tweener()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the current position of the component.
 */
const bear::visual::position_type& ptb::status_component::get_position() const
{
  return m_position;
} // status_component::get_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the position of the component for rendering.
 */
const bear::visual::position_type& 
ptb::status_component::get_render_position() const
{
  return m_render_position;
} // status_component::get_render_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the position of the component in active status.
 */
const bear::visual::position_type& 
ptb::status_component::get_active_position() const
{
  return m_active_position;
} // status_component::get_active_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the position of the component in inactive status.
 */
const bear::visual::position_type& 
ptb::status_component::get_inactive_position() const
{
  return m_inactive_position;
} // status_component::get_inactive_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the player.
 */
const ptb::player_proxy& ptb::status_component::get_player() const
{
  return m_player;
} // status_component::get_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the player.
 */
ptb::player_proxy& ptb::status_component::get_player()
{
  return m_player;
} // status_component::get_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return level globals.
 */
bear::engine::level_globals& 
ptb::status_component::get_level_globals() const
{
  return m_level_globals;
} // status_component::get_level_globals()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the size of the layer.
 */
const bear::universe::size_box_type& 
ptb::status_component::get_layer_size() const
{
  return m_layer_size;
} // status_component::get_layer_size()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the inactive_position.
 */
void ptb::status_component::update_inactive_position()
{
  m_inactive_position = m_active_position;
  
  if ( m_side == bear::universe::zone::middle_left_zone ) 
    {
      m_inactive_position.x = 0;
      m_inactive_position.x -= width();
    }
  else if ( m_side == bear::universe::zone::middle_right_zone )
    m_inactive_position.x = get_layer_size().x + width();
  else if ( m_side == bear::universe::zone::bottom_zone )
    {
      m_inactive_position.y = 0;
      m_inactive_position.y -= height();
    }
  else if ( m_side == bear::universe::zone::top_zone )
    m_inactive_position.y = get_layer_size().y + height();
} // status_component::update_inactive_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the x-position of the component.
 * \param x The x-position of the component.
 */
void ptb::status_component::on_x_position_update(double x)
{
  m_position.x = x;

  m_render_position.x = x;
  if ( m_x_placement == right_placement )
    m_render_position.x -= width();
  else if ( m_x_placement == middle_x_placement )
    m_render_position.x -= (width() / 2);
} // status_component::on_x_position_update()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the y-position of the component.
 * \param y The y-position of the component.
 */
void ptb::status_component::on_y_position_update(double y)
{
  m_position.y = y;

  m_render_position.y = y;
  if ( m_y_placement == top_placement )
    m_render_position.y -= height();
  else if ( m_y_placement == middle_y_placement )
    m_render_position.y -= (height() / 2);
} // status_component::on_y_position_update()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set all signals to listen.
 */
void ptb::status_component::init_signals()
{
  // do nothing
} // status_component::init_signals()
