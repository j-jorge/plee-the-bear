/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::player_arrows_layer class.
 * \author Sebastien Angibaud
 */
#include "ptb/layer/player_arrows_layer.hpp"

#include "engine/level.hpp"
#include "universe/zone.hpp"
#include "visual/font/font.hpp"
#include "visual/scene_sprite.hpp"
#include "visual/scene_writing.hpp"
#include "visual/bitmap_writing.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/util/player_util.hpp"

#include <algorithm>
#include <claw/algorithm.hpp>
#include <claw/functional.hpp>
#include <claw/assert.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param screen_size The size of the screen.
 * \param p A pointer to the player.
 * \param arrow The arrow to display.
 * \param f The font to use to display the distance.
 */
ptb::player_arrows_layer::player_data::player_data
( const claw::math::coordinate_2d<unsigned int> screen_size,
  const player_proxy& p, const bear::visual::sprite& arrow,
  const bear::visual::font& f )
  : m_screen_size(screen_size), m_arrow(arrow), m_player(p), m_visible(false)
{

} // player_arrows_layer::player_data::player_data()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the arrow.
 * \param e (out) The scene elements.
 */
void ptb::player_arrows_layer::player_data::render
( scene_element_list& e ) const
{
  if (m_visible)
    {
      e.push_back
        ( bear::visual::scene_sprite(m_position.x, m_position.y, m_arrow) );

      e.push_back
        ( bear::visual::scene_writing
          (m_distance_text_position.x, m_distance_text_position.y,
           m_distance) );
    }
} // player_arrows_layer::player_data::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the position and the angle of the arrow.
 * \param glob The level globals in which we load the media.
 * \param visible_area The visible part of the level.
 */
void ptb::player_arrows_layer::player_data::adjust_arrow
( bear::engine::level_globals& glob,
  const bear::universe::rectangle_type& visible_area )
{
  m_visible = false;

  if ( (m_player != NULL) && !m_player.is_a_marionette() )
    {
      const bear::universe::position_type center =
        m_player.get_center_of_mass();

      if( ( center.x < visible_area.left() ) ||
          ( center.x > visible_area.left() + visible_area.size().x ) ||
          ( center.y < visible_area.bottom() ) ||
          ( center.y > visible_area.bottom() + visible_area.size().y ) )
        {
          adjust_position( visible_area );
          adjust_angle( visible_area );
          adjust_distance(glob, visible_area );

          m_visible = true;
        }
    }
} // player_arrows_layer::player_data::adjust_arrow()

/*----------------------------------------------------------------------------*/
/**
 * \brief Adjust the position of the arrow.
 * \param visible_area The visible part of the layer.
 */
void ptb::player_arrows_layer::player_data::adjust_position
( const bear::universe::rectangle_type& visible_area )
{
  bear::universe::position_type result;

  const bear::universe::position_type pos_player
    ( m_player.get_center_of_mass() );
  const bear::universe::position_type center
    ( visible_area.bottom_left() + visible_area.size() / 2 );

  claw::math::vector_2d<double> vect(center, pos_player);
  vect.normalize();

  // intersection betwwen line and ellipse
  double a = ( m_screen_size.x / 2 ) - 50;
  double b = ( m_screen_size.y / 2 ) - 50;
  double k = ( a*a*b*b ) / ( b*b*vect.x*vect.x + a*a*vect.y*vect.y);
  k = sqrt(k);

  m_position.x = m_screen_size.x / 2 + k*vect.x - m_arrow.get_size().x / 2;
  m_position.y = m_screen_size.y / 2 + k*vect.y - m_arrow.get_size().y / 2;
} // player_arrows_layer::player_data::adjust_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Adjust the angle of the arrow.
 * \param visible_area The visible part of the layer.
 */
void ptb::player_arrows_layer::player_data::adjust_angle
( const bear::universe::rectangle_type& visible_area )
{
  claw::math::coordinate_2d<double> ratio
    ( visible_area.size().x / m_screen_size.x,
      visible_area.size().y / m_screen_size.y );

  bear::universe::position_type relative_position;
  relative_position.x = visible_area.left() +
    ( m_position.x + m_arrow.width() / 2 ) * ratio.x;

  relative_position.y = visible_area.bottom() +
    ( m_position.y + m_arrow.height() / 2 ) * ratio.y;

  bear::universe::speed_type v =
    m_player.get_center_of_mass() - relative_position;

  v.normalize();

  if ( v.y <= 0 )
    m_arrow.set_angle( -acos(v.x) );
  else
    m_arrow.set_angle( acos(v.x) );
} // player_arrows_layer::player_data::adjust_angle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Adjust the distance between the player and the arrow.
 * \param glob The level globals in which we load the media.
 * \param visible_area The visible part of the layer.
 */
void ptb::player_arrows_layer::player_data::adjust_distance
( bear::engine::level_globals& glob,
  const bear::universe::rectangle_type& visible_area )
{
  claw::math::coordinate_2d<double> ratio
    ( visible_area.size().x / m_screen_size.x,
      visible_area.size().y / m_screen_size.y );

  bear::universe::position_type relative_position;
  relative_position.x = visible_area.left() +
    ( m_position.x + m_arrow.width() / 2 ) * ratio.x;

  relative_position.y = visible_area.bottom() +
    ( m_screen_size.y - m_position.y - m_arrow.height() / 2 ) * ratio.y;

  bear::universe::speed_type vect
    (m_player.get_center_of_mass(), relative_position);
  unsigned int dist = (unsigned int)vect.length() / 100;

  const bear::universe::rectangle_type box = m_player.get_bounding_box();
  bear::visual::font f = glob.get_font("font/bouncy.fnt", 30);
  if ( box.intersects( visible_area ) )
    m_distance.create(f, "");
  else
    {
      std::ostringstream oss;
      oss << dist+1;
      m_distance.create(f, oss.str());
      m_distance->set_intensity(1, 0.8, 0);
    }

  m_distance_text_position = m_position;

  bear::universe::position_type gap;
  gap.x = cos(m_arrow.get_angle()) * 50;
  gap.y = sin(m_arrow.get_angle()) * 50;

  m_distance_text_position.x +=
    m_arrow.width() / 2 - gap.x - m_distance.get_width() / 2;
  m_distance_text_position.y +=
    m_arrow.height() / 2 - gap.y - m_distance.get_height() / 2;
} // player_arrows_layer::player_data::adjust_distance()




/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::player_arrows_layer::player_arrows_layer()
  : m_data_1(NULL), m_data_2(NULL)
{

} // player_arrows_layer::player_arrows_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::player_arrows_layer::~player_arrows_layer()
{
  delete m_data_1;
  delete m_data_2;
} // player_arrows_layer::~player_arrows_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the layer.
 * \param elapsed_time Elapsed time since the last call.
 */
void
ptb::player_arrows_layer::progress( bear::universe::time_type elapsed_time )
{
  search_players();

  if ( m_data_1 != NULL )
    m_data_1->adjust_arrow
      (get_level_globals(), get_level().get_camera_focus() );

  if ( m_data_2 != NULL )
    m_data_2->adjust_arrow
      (get_level_globals(), get_level().get_camera_focus() );
} // player_arrows_layer::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the layer.
 * \param e (out) The scene elements.
 */
void ptb::player_arrows_layer::render( scene_element_list& e ) const
{
  if ( m_data_1 != NULL )
    m_data_1->render(e);

  if ( m_data_2 != NULL )
    m_data_2->render(e);
} // player_arrows_layer::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Search players.
 */
void ptb::player_arrows_layer::search_players( )
{
  if ( m_data_1 == NULL )
    {
      player_proxy p( util::find_player( get_level_globals(), 1 ) );

      if ( p != NULL )
        m_data_1 = new player_data
          ( get_size(), p,
            get_level_globals().auto_sprite
            ("gfx/ui/status/status.png", "arrow 1"),
            get_level_globals().get_font("font/bouncy.fnt", 30) );
    }

  if ( game_variables::get_players_count() == 2 )
    if ( m_data_2 == NULL )
      {
        player_proxy p( util::find_player( get_level_globals(), 2 ) );

        if ( p != NULL )
          m_data_2 = new player_data
            ( get_size(), p,
              get_level_globals().auto_sprite
              ("gfx/ui/status/status.png", "arrow 2"),
              get_level_globals().get_font("font/bouncy.fnt", 30) );
      }
} // player_arrows_layer::search_players( )
