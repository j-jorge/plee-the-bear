/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::vertical_gauge class.
 * \author Julien Jorge
 */
#include "ptb/gui/vertical_gauge.hpp"

#include "visual/scene_sprite.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param glob Level globals in which we take the resources.
 * \param length The length of the bar.
 * \param level_sprite The name of the sprite in
 *        "gfx/ui/status/tube-vertical.png" of the image to use for the main
 *        level.
 * \param icon_sprite The name of the sprite in
 *        "gfx/ui/status/tube-vertical.png" of the image to use for the icon of
 *        the bar.
 */
ptb::vertical_gauge::vertical_gauge
( bear::engine::level_globals& glob, unsigned int length,
  const std::string& level_sprite, const std::string& icon_sprite )
  : visual_component(), m_level_value(length)
{
  m_level = glob.auto_sprite("gfx/ui/status/tube-vertical.png", level_sprite);
  m_icon = glob.auto_sprite("gfx/ui/status/tube-vertical.png", icon_sprite);

  m_tube_clamp = glob.auto_sprite("gfx/ui/status/tube-vertical.png", "clamp");
  m_glass_tube = glob.auto_sprite("gfx/ui/status/tube-vertical.png", "tube");

  m_glass_tube.set_height(length);
  m_level.set_height(length);
} // vertical_gauge::vertical_gauge()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int ptb::vertical_gauge::width() const
{
  return std::max( m_tube_clamp.width() + m_icon.width() / 2,
                   m_glass_tube.width() );
} // vertical_gauge::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int ptb::vertical_gauge::height() const
{
  return 2 * m_tube_clamp.height() + m_glass_tube.height()
    + m_icon.height() / 2;
} // vertical_gauge::height()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the level of the bar.
 * \param lev The new level.
 */
void ptb::vertical_gauge::set_level( double lev )
{
  m_level_value = lev;
} // vertical_gauge::set_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return if the level is critical.
 */
bool ptb::vertical_gauge::is_critical() const
{
  return 3 * m_level_value <= m_level.height();
} // vertical_gauge::is_critical

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the bar.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::vertical_gauge::progress
( bear::universe::time_type elapsed_time )
{
  m_level.set_height( (unsigned int)(m_level_value + 0.5) );
} // vertical_gauge::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Display the bar.
 * \param e (out) The scene elements.
 * \param pos The top-left position of the bar.
 */
void ptb::vertical_gauge::render
( scene_element_list& e, const bear::visual::position_type& pos ) const
{
  bear::visual::position_type p(pos.x, pos.y + m_icon.height() / 2);
  bear::visual::sprite clamp(m_tube_clamp);
  const bear::visual::coordinate_type d =
    ( clamp.width() - m_level.width() ) / 2;

  if (d < 0)
    p.x -= d;

  clamp.flip(true);
  e.push_back( bear::visual::scene_sprite(p.x, p.y, clamp) );

  p.x += d;
  p.y += clamp.height();
  e.push_back( bear::visual::scene_sprite(p.x, p.y, m_level) );
  e.push_back( bear::visual::scene_sprite(p.x, p.y, m_glass_tube) );

  p.x -= d;
  p.y += m_glass_tube.height();
  clamp.flip(false);
  e.push_back( bear::visual::scene_sprite(p.x, p.y, clamp) );

  p += clamp.get_size() - m_icon.get_size() / 2;
  e.push_back( bear::visual::scene_sprite(p.x, p.y, m_icon) );
} // vertical_gauge::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the scene elements of the component.
 * \param e (out) The scene elements.
 */
void ptb::vertical_gauge::display
( std::list<bear::visual::scene_element>& e ) const
{
  render(e, bear::visual::position_type(bottom(), left()));
} // vertical_gauge::display()
