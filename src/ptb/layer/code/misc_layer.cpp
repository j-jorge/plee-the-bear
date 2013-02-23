/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::misc_layer class.
 * \author Julien Jorge
 */
#include "ptb/layer/misc_layer.hpp"

#include "engine/game.hpp"
#include "engine/game_network.hpp"
#include "engine/level.hpp"
#include "engine/level_globals.hpp"
#include "engine/network/client_connection.hpp"
#include "engine/network/message/sync.hpp"
#include "engine/system/game_filesystem.hpp"
#include "gui/static_text.hpp"
#include "input/keyboard.hpp"
#include "visual/font/font.hpp"
#include "visual/scene_sprite.hpp"
#include "visual/scene_writing.hpp"

#include "ptb/game_variables.hpp"

#include <sstream>
#include <iomanip>
#include <libintl.h>

#include <claw/bitmap.hpp>
#include <claw/logger.hpp>
#include <claw/png.hpp>

#include <boost/thread.hpp>

#ifdef PTB_TRACE_FPS
typedef std::list<unsigned int> fps_list;
static fps_list g_fps;
#endif

/*----------------------------------------------------------------------------*/
/**
 * \brief Execute the function object to save the image.
 */
template<typename ImageWriter>
void ptb::misc_layer::screenshot_file_save<ImageWriter>::operator()() const
{
  try
    {
      std::ofstream f( file_path.c_str() );
      ImageWriter writer(*image, f);
    }
  catch(std::exception& e)
    {
      claw::logger << claw::log_error << "Screenshot: " << e.what()
                   << std::endl;
    }
} // misc_layer::screenshot_file_save::operator()()




/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::misc_layer::misc_layer()
  : m_fps_text(NULL), m_fps_count(0), m_its_count(0),
#ifdef PTB_TRACE_FPS
    m_show_fps(true),
#else
    m_show_fps(false),
#endif
    m_cursor_position(-1, -1), m_mouse_idle(0), m_first_screenshot(0),
    m_fps_key(bear::input::keyboard::kc_F2),
    m_screenshot_key(bear::input::keyboard::kc_F5),
    m_fullscreen_key(bear::input::keyboard::kc_F12),
    m_screenshot_sequence_key(bear::input::keyboard::kc_F11),
    m_levelshot_key(bear::input::keyboard::kc_F10),
    m_overview_key(bear::input::keyboard::kc_F8)
{

} // misc_layer::misc_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::misc_layer::~misc_layer()
{
  delete m_fps_text;

  if (m_first_screenshot != 0)
    stop_screenshot_sequence();

#ifdef PTB_TRACE_FPS
  std::ofstream f("fps.txt");
  std::size_t i=0;
  for ( fps_list::const_iterator it=g_fps.begin(); it!=g_fps.end(); ++it, ++i )
    f << i << '\t' << *it << '\n';
#endif
} // misc_layer::~misc_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the layer.
 */
void ptb::misc_layer::build()
{
  m_fps_text =
    new bear::gui::static_text
    ( get_level_globals().get_font("font/fixed_white-7x12.fnt", 12) );

  m_fps_text->set_auto_size(true);
  m_fps_text->set_text("0");
  m_fps_text->set_position( m_fps_text->height(), m_fps_text->height() );

  m_last_fps_check = bear::systime::get_date_ms();

  m_cursor =
    get_level_globals().auto_sprite( "gfx/ui/frame.png", "mouse cursor" );

  if ( game_variables::record_game() )
    start_screenshot_sequence();
} // misc_layer::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the layer.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::misc_layer::progress( bear::universe::time_type elapsed_time )
{
  ++m_its_count;
  m_mouse_idle += elapsed_time;

  if ( m_first_screenshot != 0 )
    sequence_screenshot();
} // misc_layer::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the visibles components of the layer on a screen.
 * \param e (out) The scene elements.
 */
void ptb::misc_layer::render( scene_element_list& e ) const
{
  ++m_fps_count;
  render_fps( e );

  if ( m_first_screenshot == 0 )
    render_demo( e );

  //render_network_status( e );

  if ( (m_mouse_idle <= 2) && (m_first_screenshot == 0) )
    e.push_back
      ( bear::visual::scene_sprite
        ( m_cursor_position.x, m_cursor_position.y - m_cursor.height(),
          m_cursor) );
} // misc_layer::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the layer that a key had been pressed.
 * \param key The value of the pressed key.
 */
bool ptb::misc_layer::key_pressed( const bear::input::key_info& key )
{
  bool result = true;

  if ( key.get_code() == m_fps_key )
    m_show_fps = !m_show_fps;
  else if ( key.get_code() == m_screenshot_key )
    screenshot();
  else if ( key.get_code() == m_levelshot_key )
    levelshot();
  else if ( key.get_code() == m_fullscreen_key )
    bear::engine::game::get_instance().toggle_fullscreen();
  else if ( key.get_code() == m_screenshot_sequence_key )
    {
      if (m_first_screenshot != 0)
        stop_screenshot_sequence();
      else
        start_screenshot_sequence();
    }
  else if ( key.get_code() == m_overview_key )
    bear::engine::game::get_instance().toggle_overview_mode();
  else
    result = false;

  return result;
} // misc_layer::key_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the layer that the mouse had been moved.
 * \param pos The new position of the mouse.
 */
bool ptb::misc_layer::mouse_move
( const claw::math::coordinate_2d<unsigned int>& pos )
{
  m_cursor_position = pos;
  m_mouse_idle = 0;

  // let the sub components know the movement
  return false;
} // misc_layer::mouse_move()

/*----------------------------------------------------------------------------*/
/**
 * \brief Take a picture of the whole level.
 */
void ptb::misc_layer::levelshot() const
{
  std::ostringstream name;
  name << "level-" << bear::systime::get_date_ms() << ".bmp";

  screenshot_file_save<claw::graphic::bitmap::writer> writer;
  writer.image = new claw::graphic::image;

  bear::engine::game::get_instance().levelshot(*writer.image);

  const bear::engine::game& g( bear::engine::game::get_instance() );

  writer.file_path =
    g.get_game_filesystem().get_custom_data_file_name( name.str() );

  boost::thread t(writer);
} // misc_layer::levelshot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Take a picture of the screen.
 */
void ptb::misc_layer::screenshot() const
{
  std::ostringstream name;
  name << bear::systime::get_date_ms() << ".png";

  screenshot<claw::graphic::png::writer>(name.str());
} // misc_layer::screenshot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Take a picture of the screen.
 * \param name The name of the file to save the image into.
 */
template<typename ImageWriter>
void ptb::misc_layer::screenshot( const std::string& name ) const
{
  screenshot_file_save<ImageWriter> writer;
  writer.image = new claw::graphic::image;

  bear::engine::game::get_instance().screenshot(*writer.image);

  const bear::engine::game& g( bear::engine::game::get_instance() );

  writer.file_path = 
    g.get_game_filesystem().get_custom_data_file_name( name );

  //boost::thread t(writer);
  writer();
} // misc_layer::screenshot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Take a picture of the screen for the screenshot sequence.
 */
void ptb::misc_layer::sequence_screenshot()
{
  const bear::systime::milliseconds_type d = bear::systime::get_date_ms();

  //if ( d >= m_last_screenshot + 40 ) // 25 fps
    {
      std::ostringstream name;
      name << m_screenshot_prefix << '-' << std::setw(8)
           << std::setfill('0') << m_screenshots_count << ".bmp";
      ++m_screenshots_count;

      screenshot<claw::graphic::bitmap::writer>(name.str());
      m_last_screenshot = d;
    }
} // misc_layer::sequence_screenshot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the images in the sequence.
 */
void ptb::misc_layer::start_screenshot_sequence()
{
  claw::logger << claw::log_verbose << "Starting screenshot sequence."
               << std::endl;

  m_first_screenshot = bear::systime::get_date_ms();
  m_last_screenshot = m_first_screenshot;
  m_screenshots_count = 0;

  std::ostringstream prefix;
  prefix << "s-" << bear::systime::get_date_ms();
  m_screenshot_prefix = prefix.str();
} // misc_layer::start_screenshot_sequence()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the data associated with the screenshots of the sequence.
 */
void ptb::misc_layer::stop_screenshot_sequence()
{
  const bear::engine::game& g( bear::engine::game::get_instance() );

  std::string file_name
    ( g.get_game_filesystem().get_custom_data_file_name
      ( m_screenshot_prefix + ".seq" ) );

  std::ofstream f( file_name.c_str() );

  const bear::systime::milliseconds_type d = bear::systime::get_date_ms();
  const unsigned int fps =
    (unsigned int)
    ( (double)m_screenshots_count
      / ((double)(d - m_first_screenshot) / 1000.0)
      + 0.5 );

  f << fps << " # fps" << std::endl;

  claw::logger << claw::log_verbose << "Screenshot sequence stopped. " << fps
               << " fps during " << ((double)(d - m_first_screenshot) / 1000.0)
               << " seconds." << std::endl;

  m_first_screenshot = 0;
} // misc_layer::stop_screenshot_sequence()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the fps text component.
 * \param e (out) The scene elements.
 */
void ptb::misc_layer::render_fps( scene_element_list& e ) const
{
  if ( m_show_fps )
    {
      const bear::systime::milliseconds_type dt =
        bear::systime::get_date_ms() - m_last_fps_check;
      
      if ( dt >= 1000 )
        {
          std::ostringstream oss;
          oss << (m_fps_count * 1000 / dt) << " fps - "
              << (m_its_count * 1000 / dt) << " its";

#ifdef PTB_TRACE_FPS
          g_fps.push_back(m_fps_count);
#endif

          m_fps_text->set_text( oss.str() );
          m_fps_count = 0;
          m_its_count = 0;
          m_last_fps_check = bear::systime::get_date_ms();
        }

      m_fps_text->render( e );
    }
} // misc_layer::render_fps()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the text component displaying the message for the demo version.
 * \param e (out) The scene elements.
 */
void ptb::misc_layer::render_demo( scene_element_list& e ) const
{
  const bear::visual::font font =
    get_level_globals().get_font("font/fixed_white-7x12.fnt", 12);

  const bear::visual::writing w
    ( font,
      gettext
      ( "You are playing a demo version. "
        "The final version may provide a different experience." ) );

  const bear::visual::scene_writing result
    ( (get_size().x - w.get_width()) / 2, 0, w );

  e.push_back( result );
} // misc_layer::render_fps()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the status of the network.
 * \param e (out) The scene elements.
 */
void ptb::misc_layer::render_network_status( scene_element_list& e ) const
{
  const bear::visual::size_type margin(10);
  bear::visual::position_type pos( get_size().x - margin, margin );

  const bear::engine::game_network& network =
    bear::engine::game::get_instance().get_network();
  
  const std::size_t min_horizon = network.get_min_horizon();
  const bear::visual::font font =
    get_level_globals().get_font("font/fixed_white-7x12.fnt", 12);

  for ( std::size_t i=0; i!=network.get_client_count(); ++i )
    {
      const bear::engine::client_future& future = network.get_future(i);
      const std::size_t horizon = future.get_horizon();

      std::ostringstream oss;
      oss << network.get_connection(i).get_host() << ": " << horizon << '/'
          << min_horizon;

      if ( future.get_horizon() > 1 )
        oss << ' ' << format_sync( future.get_sync_message(0) )
            << ' ' << format_sync( future.get_sync_message(horizon - 1) );

      const bear::visual::writing w( font, oss.str() );
      bear::visual::scene_writing result( pos.x - w.get_width(), pos.y, w );

      const double quality = (double)horizon / min_horizon;
      result.get_rendering_attributes().set_intensity
        ( 1 - quality, quality, 0 );

      if ( get_level().is_paused() )
        result.get_rendering_attributes().set_opacity(0.25);

      e.push_back( result );
      pos.y += w.get_height();
    }
} // misc_layer::render_network_status()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the string representing a sync message.
 * \param sync The message represented by the returned string.
 */
std::string ptb::misc_layer::format_sync( const bear::engine::sync& sync ) const
{
  std::ostringstream oss;
  oss << sync.get_id();

  if ( sync.is_active_sync() )
    oss << ' ';
  else
    oss << '*';

  return oss.str();
} // misc_layer::format_sync()
