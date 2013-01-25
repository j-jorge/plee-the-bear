/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::horizontal_gauge class.
 * \author Julien Jorge
 */
#include "ptb/gui/horizontal_gauge.hpp"

#include "visual/scene_sprite.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param glob Level globals in which we take the resources.
 * \param length The length of the bar.
 * \param level_sprite The name of the sprite in "gfx/ui/status/tube.png" of the
 *        image to use for the main level.
 * \param loss_sprite The name of the sprite in "gfx/ui/status/tube.png" of the
 *        image to use for the loss level.
 * \param icon_name The name of the sprite in
 *        "gfx/ui/status/tube-vertical.png" of the image to use for the icon of
 *        the bar.
 * \param clamp_flashing Indicates if the clamp flashes when the level is low.
 */
ptb::horizontal_gauge::horizontal_gauge
( bear::engine::level_globals& glob, unsigned int length,
  const std::string& level_sprite, const std::string& loss_sprite,
  const std::string& icon_name, bool clamp_flashing )
  : visual_component(), m_max_value(1), m_level_value(0),
    m_clamp_green_intensity(1), m_clamp_increment_direction(0)
{
  set_level_sprite( glob, level_sprite );

  if ( !loss_sprite.empty() )
    m_loss = glob.auto_sprite("gfx/ui/status/tube.png", loss_sprite);

  if ( !icon_name.empty() )
    m_icon = glob.auto_sprite("gfx/ui/status/tube-vertical.png", icon_name);

  m_loss.set_opacity(0);

  if ( clamp_flashing )
    m_clamp_increment_direction = 1;

  m_tube_clamp = glob.auto_sprite("gfx/ui/status/tube.png", "clamp");
  m_glass_tube =  glob.auto_sprite("gfx/ui/status/tube.png", "tube");

  m_glass_tube.set_width(length);
  m_level.set_width(0);

} // horizontal_gauge::horizontal_gauge()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the length.
 */
void ptb::horizontal_gauge::set_length(unsigned int length)
{
  m_glass_tube.set_width(length);
  update_bar();
} // horizontal_gauge::set_length()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual length of the bar.
 */
unsigned int ptb::horizontal_gauge::length() const
{
  return m_glass_tube.width();
} // horizontal_gauge::length()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual width of the bar.
 */
unsigned int ptb::horizontal_gauge::width() const
{
  return 2 * m_tube_clamp.width() + m_glass_tube.width() + m_icon.width() / 2;
} // horizontal_gauge::width()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the visual height of the bar.
 */
unsigned int ptb::horizontal_gauge::height() const
{
  return std::max
    ( m_tube_clamp.height() + m_icon.height() / 2, m_glass_tube.height() );
} // horizontal_gauge::height()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the sprite used to display the level in the bar.
 * \param glob Level globals in which we take the resources.
 * \param level_sprite The name of the sprite in "gfx/ui/status/tube.png" of the
 *        image to use for the main level.
 */
void ptb::horizontal_gauge::set_level_sprite
( bear::engine::level_globals& glob, const std::string& level_sprite )
{
  m_level = glob.auto_sprite("gfx/ui/status/tube.png", level_sprite);
} // horizontal_gauge::set_level_sprite()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the level of the bar.
 * \param lev The new level.
 */
void ptb::horizontal_gauge::set_level( double lev )
{
  if ( lev != m_level_value )
    {
      if ( lev < m_level_value )
        m_loss.set_opacity(1);
      else
        m_loss.set_opacity(0);

      m_level_value = std::min(lev, m_max_value);
      update_bar();
    }
} // horizontal_gauge::set_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the level of the bar.
 */
double ptb::horizontal_gauge::get_level() const
{
  return m_level_value;
} // horizontal_gauge::get_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the maximum level of the bar.
 * \param lev The new maximum level.
 */
void ptb::horizontal_gauge::set_max_level( double lev )
{
  m_max_value = lev;
  m_level_value = std::min(m_level_value, m_max_value);
  update_bar();
} // horizontal_gauge::set_max_level()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return if the level is critical.
 */
bool ptb::horizontal_gauge::is_critical() const
{
  return 4 * m_level_value <= m_max_value;
} // horizontal_gauge::is_critical

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one progress iteration.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::horizontal_gauge::progress
( bear::universe::time_type elapsed_time )
{
  update_bar();

  if ( m_loss.get_opacity() >= 0 )
    m_loss.set_opacity
      ( std::max(0.0, m_loss.get_opacity() - elapsed_time/2) );

  if ( (4 * m_level_value <= m_max_value)
       && (m_clamp_increment_direction != 0) )
    {
      m_clamp_green_intensity +=
        2 * m_clamp_increment_direction * elapsed_time;

      if ( m_clamp_green_intensity > 1 )
        {
          m_clamp_green_intensity = 1;
          m_clamp_increment_direction = -1;
        }
      else if ( m_clamp_green_intensity < 0 )
        {
          m_clamp_green_intensity = 0;
          m_clamp_increment_direction = 1;
        }

      m_loss.set_opacity(1);
    }
  else
    m_clamp_green_intensity = 1;
} // horizontal_gauge::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Display the bar.
 * \param e (out) The scene elements.
 * \param pos The position of the bar.
 */
void ptb::horizontal_gauge::render
( scene_element_list& e, const bear::visual::position_type& pos ) const
{
  bear::universe::position_type p(pos);
  bear::visual::sprite clamp(m_tube_clamp);
  const bear::visual::coordinate_type d =
    ( clamp.height() - m_level.height() ) / 2;

  clamp.set_intensity(1, m_clamp_green_intensity, 1);

  if (d < 0)
    p.y -= d;

  e.push_back
    ( bear::visual::scene_sprite(p.x + m_icon.width() / 2, p.y, clamp) );
  e.push_back
    ( bear::visual::scene_sprite
      (p.x, p.y + clamp.height() - m_icon.height() / 2,
       m_icon) );

  p.x += clamp.width() + m_icon.width() / 2;
  p.y += d;

  e.push_back( bear::visual::scene_sprite(p.x, p.y, m_level) );

  if ( m_loss.get_opacity() != 0 )
    e.push_back( bear::visual::scene_sprite(p.x, p.y, m_loss) );

  e.push_back( bear::visual::scene_sprite(p.x, p.y, m_glass_tube) );

  p.x += m_glass_tube.width();
  p.y -= d;
  clamp.mirror(true);
  e.push_back( bear::visual::scene_sprite(p.x, p.y, clamp) );
} // horizontal_gauge::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the bar.
 */
void ptb::horizontal_gauge::update_bar()
{
  m_level.set_width
    ( (unsigned int)
      (m_level_value * m_glass_tube.width() / m_max_value + 0.5) );
  m_loss.set_width( m_level.width() );
} // horizontal_gauge::update_bar()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the scene elements of the component.
 * \param e (out) The scene elements.
 */
void ptb::horizontal_gauge::display
( std::list<bear::visual::scene_element>& e ) const
{
  render(e, bear::visual::position_type(bottom(), left()));
} // horizontal_gauge::display()
