/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::windows_layer class.
 * \author Julien Jorge
 */
#include "ptb/layer/windows_layer.hpp"

#include "ptb/frame/frame.hpp"
#include "engine/level_globals.hpp"

#include <claw/tween/single_tweener.hpp>
#include <claw/tween/easing/easing_back.hpp>
#include <claw/tween/easing/easing_quad.hpp>
#include <boost/bind.hpp>

/*----------------------------------------------------------------------------*/
const double ptb::windows_layer::s_effect_duration = 0.5;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::windows_layer::windows_layer()
{

} // windows_layer::windows_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param name The name of the layer in the post_office.
 */
ptb::windows_layer::windows_layer( const std::string& name )
  : bear::communication::messageable(name)
{

} // windows_layer::windows_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::windows_layer::~windows_layer()
{
  clear();
} // windows_layer::~windows_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the layer.
 */
void ptb::windows_layer::build()
{
  get_level_globals().register_item(*this);
} // windows_layer::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the layer.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::windows_layer::progress( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);

  m_tweener.update(elapsed_time);
} // windows_layer::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the layer that a key has been pressed.
 * \param key The value of the pressed key.
 */
bool ptb::windows_layer::key_pressed( const bear::input::key_info& key )
{
  bool result = false;

  if ( !m_windows.empty() )
    {
      result = m_windows.front()->key_pressed(key);

      if ( !result && key.is_escape() )
        result = close_window();
    }

  return result;
} // windows_layer::key_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the layer that a character has been entered.
 * \param key The value of the pressed key.
 */
bool ptb::windows_layer::char_pressed( const bear::input::key_info& key )
{
  bool result = false;

  if ( !m_windows.empty() )
    result = m_windows.front()->char_pressed(key);

  return result;
} // windows_layer::char_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the layer that a joystick button had been pressed.
 * \param button The value of the pressed button.
 * \param joy_index The index of the joystick.
 */
bool ptb::windows_layer::button_pressed
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  if ( !m_windows.empty() )
    return m_windows.front()->button_pressed( button, joy_index );
  else
    return false;
} // windows_layer::button_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the layer that a mouse button has been pressed.
 * \param pos The current position of the cursor.
 * \param key The value of the pressed button.
 */
bool ptb::windows_layer::mouse_pressed
( bear::input::mouse::mouse_code key,
  const claw::math::coordinate_2d<unsigned int>& pos )
{
  bool result = false;

  if ( !m_windows.empty() )
    {
      claw::math::rectangle<unsigned int> bounding_box
        ( m_windows.front()->get_position(), m_windows.front()->get_size() );

      if ( bounding_box.includes( pos ) )
        result = m_windows.front()->mouse_pressed
          ( key, pos - m_windows.front()->get_position() );
    }

  return result;
} // windows_layer::mouse_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the layer that a mouse button has been released.
 * \param pos The current position of the cursor.
 * \param key The value of the pressed button.
 */
bool ptb::windows_layer::mouse_released
( bear::input::mouse::mouse_code key,
  const claw::math::coordinate_2d<unsigned int>& pos )
{
  bool result = false;

  if ( !m_windows.empty() )
    {
      claw::math::rectangle<unsigned int> bounding_box
        ( m_windows.front()->get_position(), m_windows.front()->get_size() );

      if ( bounding_box.includes( pos ) )
        result = m_windows.front()->mouse_released
          ( key, pos - m_windows.front()->get_position() );
    }

  return result;
} // windows_layer::mouse_released()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the layer that a mouse button has been maintained.
 * \param pos The current position of the cursor.
 * \param key The value of the pressed button.
 */
bool ptb::windows_layer::mouse_maintained
( bear::input::mouse::mouse_code key,
  const claw::math::coordinate_2d<unsigned int>& pos )
{
  bool result = false;

  if ( !m_windows.empty() )
    {
      claw::math::rectangle<unsigned int> bounding_box
        ( m_windows.front()->get_position(), m_windows.front()->get_size() );

      if ( bounding_box.includes( pos ) )
        result = m_windows.front()->mouse_maintained
          ( key, pos - m_windows.front()->get_position() );
    }

  return result;
} // windows_layer::mouse_maintained()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the layer that the mouse has been moved.
 * \param pos The new position of the mouse.
 */
bool ptb::windows_layer::mouse_move
( const claw::math::coordinate_2d<unsigned int>& pos )
{
  bool result = false;

  if ( !m_windows.empty() )
    {
      claw::math::rectangle<unsigned int> bounding_box
        ( m_windows.front()->get_position(), m_windows.front()->get_size() );

      if ( bounding_box.includes( pos ) )
        result =
          m_windows.front()->mouse_move
          ( pos - m_windows.front()->get_position() );
    }

  return result;
} // windows_layer::mouse_move()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render the visible components of the layer on a screen.
 * \param e (out) The scene elements.
 */
void ptb::windows_layer::render( scene_element_list& e ) const
{
  for ( std::list<window_item>::const_iterator it=m_windows.begin();
        it!=m_windows.end(); ++it )
    (*it)->render(e);

  for ( std::list<window_item>::const_iterator it=m_dying_windows.begin();
        it!=m_dying_windows.end(); ++it )
    (*it)->render(e);
} // windows_layer::render()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove all windows.
 */
void ptb::windows_layer::clear()
{
  for ( ; !m_windows.empty(); m_windows.pop_front() )
    delete m_windows.front();

  for ( ; !m_dying_windows.empty(); m_dying_windows.pop_front() )
    delete m_dying_windows.front();

  m_ref_bottom.clear();
  m_tweener.clear();
} // windows_layer::clear()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if there is no window displayed.
 */
bool ptb::windows_layer::empty() const
{
  return m_windows.empty();
} // windows_layer::empty()

/*----------------------------------------------------------------------------*/
/**
 * \brief Show a window, centered in the screen.
 * \param wnd The window to show.
 * \post !m_window.empty() && m_window.front() is centered in the screen.
 */
void ptb::windows_layer::show_centered_window( window_item wnd )
{
  wnd->set_position( (get_size() - wnd->get_size()) / 2 );
  show_window(wnd);
} // windows_layer::show_centered_window()

/*----------------------------------------------------------------------------*/
/**
 * \brief Replace the top window.
 * \param old_wnd The window to replace.
 * \param new_wnd The new window.
 * \post !m_window.empty() && m_window.front() is centered in the screen.
 */
void ptb::windows_layer::replace_window
( window_item old_wnd, window_item new_wnd )
{
  CLAW_PRECOND(old_wnd == m_windows.front());
  CLAW_PRECOND(old_wnd != new_wnd);

  m_windows.front()->close();
  pop_window();

  show_centered_window(new_wnd);
} // windows_layer::replace_window()

/*----------------------------------------------------------------------------*/
/**
 * \brief Show a window.
 * \param wnd The window to show.
 * \post !m_window.empty()
 */
void ptb::windows_layer::show_window( window_item wnd )
{
  if ( !m_windows.empty() )
    apply_hide_effect( m_windows.front(), false );

  m_ref_bottom[wnd] = wnd->bottom();

  m_windows.push_front( wnd );
  apply_show_effect( wnd );

  wnd->on_focus();
} // windows_layer::show_window()

/*----------------------------------------------------------------------------*/
/**
 * \brief Close the current window.
 */
bool ptb::windows_layer::close_window()
{
  bool result = false;

  if ( !m_windows.empty() )
    if ( m_windows.front()->close() )
      {
        pop_window();

        if ( !m_windows.empty() )
          m_windows.front()->on_focus();

        result = true;
      }

  return result;
} // windows_layer::close_window()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do the stuff related to a score message.
 * \param msg The message to process.
 */
bool ptb::windows_layer::process_score_message( const score_message& msg )
{
  // nothing to do
  return false;
} // windows_layer::process_score_message()

/*----------------------------------------------------------------------------*/
/**
 * \brief Pop the current window.
 */
void ptb::windows_layer::pop_window()
{
  apply_hide_effect( m_windows.front(), true );
  m_windows.pop_front();

  if ( !m_windows.empty() )
    apply_show_effect( m_windows.front() );
} // windows_layer::pop_window()

/*----------------------------------------------------------------------------*/
/**
 * \brief Delete the oldest dead window.
 */
void ptb::windows_layer::delete_next_window()
{
  CLAW_PRECOND( !m_dying_windows.empty() );

  const window_item w = m_dying_windows.front();
  m_dying_windows.pop_front();

  m_ref_bottom.erase(w);
  delete w;
} // windows_layer::delete_next_window()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply an effect for a window being shown.
 * \param wnd The window to show.
 */
void ptb::windows_layer::apply_show_effect( window_item wnd )
{
  CLAW_PRECOND( std::find(m_dying_windows.begin(), m_dying_windows.end(), wnd)
                == m_dying_windows.end() );
  CLAW_PRECOND( m_ref_bottom.find(wnd) != m_ref_bottom.end() );

  wnd->enable();

  const claw::tween::single_tweener t
    ( get_size().y, m_ref_bottom[wnd], s_effect_duration,
      boost::bind( &frame::set_bottom, wnd, _1 ),
      &claw::tween::easing_back::ease_out );

  m_tweener.insert(t);
} // windows_layer::apply_show_effect()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply an effect for a window being hidden.
 * \param wnd The window to hide.
 * \param d Tell if the window must be deleted at the end of the effect.
 */
void ptb::windows_layer::apply_hide_effect( window_item wnd, bool d )
{
  CLAW_PRECOND( std::find(m_dying_windows.begin(), m_dying_windows.end(), wnd)
                == m_dying_windows.end() );

  wnd->disable();

  // The effect duration must be greater or equal to the effect applied when
  // showing the window. Otherwise hiding and deleting a window before the end
  // of its show effect will result in a segfault caused by the show effect
  // updating the position of the window once it was deleted by the end of the
  // hide effect.
  claw::tween::single_tweener t
    ( wnd->top(), 0, s_effect_duration, boost::bind( &frame::set_top, wnd, _1 ),
      &claw::tween::easing_quad::ease_out );

  if ( d )
    {
      m_dying_windows.push_back(wnd);
      t.on_finished( boost::bind(&windows_layer::delete_next_window, this) );
    }

  m_tweener.insert(t);
} // windows_layer::apply_hide_effect()
