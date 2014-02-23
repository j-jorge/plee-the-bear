/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::frame class.
 * \author Julien Jorge
 */
#include "ptb/frame/frame.hpp"

#include "engine/level.hpp"
#include "engine/level_globals.hpp"
#include "ptb/frame/theme_colors.hpp"
#include "ptb/layer/windows_layer.hpp"

#include <limits>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer onwing the window.
 */
ptb::frame::frame( windows_layer* owning_layer )
  : bear::gui::frame(), m_owning_layer(owning_layer)
{
  CLAW_PRECOND(owning_layer != NULL);

  common_init();
} // frame::frame()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param owning_layer The layer onwing the window.
 * \param title The title of the frame.
 */
ptb::frame::frame( windows_layer* owning_layer, const std::string& title )
  : bear::gui::frame(title), m_owning_layer(owning_layer)
{
  CLAW_PRECOND(owning_layer != NULL);

  common_init();
} // frame::frame()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when the frame is displayed.
 */
void ptb::frame::on_focus()
{
  // nothing to do
} // frame::on_focus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the sprite to use for an arrow.
 */
bear::visual::sprite ptb::frame::get_arrow() const
{
  return get_frame_sprite( "arrow" );
} // frame::get_cursor()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the sprite to use for the cursor.
 */
bear::visual::sprite ptb::frame::get_cursor() const
{
  return get_frame_sprite( "cursor" );
} // frame::get_cursor()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the sprite to use for a not checked checkbox.
 */
bear::visual::sprite ptb::frame::get_checkbox_off() const
{
  return get_frame_sprite( "checkbox off" );
} // frame::get_checkbox_off()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the sprite to use for a checked checkbox.
 */
bear::visual::sprite ptb::frame::get_checkbox_on() const
{
  return get_frame_sprite( "checkbox on" );
} // frame::get_checkbox_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the sprite to use for a not checked radio.
 */
bear::visual::sprite ptb::frame::get_radio_off() const
{
  return get_frame_sprite( "radio off" );
} // frame::get_radio_off()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the sprite to use for a checked radio.
 */
bear::visual::sprite ptb::frame::get_radio_on() const
{
  return get_frame_sprite( "radio on" );
} // frame::get_radio_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the sprite of the slider bar.
 */
bear::visual::sprite ptb::frame::get_slider_bar() const
{
  return get_frame_sprite( "slider bar" );
} // frame::get_slider_bar()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the sprite of the slider.
 */
bear::visual::sprite ptb::frame::get_slider() const
{
  return get_frame_sprite( "slider" );
} // frame::get_slider()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the font to use in the frames.
 */
bear::visual::font ptb::frame::get_font() const
{
  return m_owning_layer->get_level().get_globals().get_font
    ("font/AndikaBasic.ttf", 20);
} // frame::get_font()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the default margin between the items.
 */
bear::visual::size_type ptb::frame::get_margin() const
{
  return 20;
} // frame::get_margin()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the windows layer containing this frame.
 */
ptb::windows_layer& ptb::frame::get_layer() const
{
  CLAW_PRECOND( m_owning_layer != NULL );
  return *m_owning_layer;
} // frame::get_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the border of a control such that he looks like he's on the frame.
 * \param c The component for which we set the borders.
 */
void ptb::frame::set_borders_up( bear::gui::visual_component& c )
{
  c.set_top_left_border_color(PTB_THEME_LIGHT);
  c.set_bottom_right_border_color(PTB_THEME_DARK);
} // frame::set_borders_up()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the border of a control such that he looks like he's in the frame.
 * \param c The component for which we set the borders.
 */
void ptb::frame::set_borders_down( bear::gui::visual_component& c )
{
  c.set_top_left_border_color(PTB_THEME_DARK);
  c.set_bottom_right_border_color(PTB_THEME_LIGHT);
} // frame::set_borders_down()

/*----------------------------------------------------------------------------*/
/**
 * \brief Show a window, centered in the scrren, to replace this window.
 * \param wnd The class name of the window to show.
 */
void ptb::frame::show_window( frame* wnd ) const
{
  CLAW_PRECOND(wnd != NULL);
  m_owning_layer->show_centered_window(wnd);
} // frame::show_window()

/*----------------------------------------------------------------------------*/
/**
 * \brief Replace the current window by a new window.
 * \param wnd The class name of the window to show.
 */
void ptb::frame::replace_with( frame* wnd )
{
  CLAW_PRECOND(wnd != NULL);
  m_owning_layer->replace_window(this, wnd);
} // frame::replace_with()

/*----------------------------------------------------------------------------*/
/**
 * \brief Close the current window (come back to the previous one).
 */
void ptb::frame::close_window() const
{
  m_owning_layer->close_window();
} // frame::close_window()

/*----------------------------------------------------------------------------*/
/**
 * \brief Insert a control in the list of activable controls.
 * \param c The control to insert in the list.
 */
void ptb::frame::insert_control( bear::gui::visual_component& c )
{
  get_content().insert(&c);

  allow_focus( c );
} // frame::insert_control()

/*----------------------------------------------------------------------------*/
/**
 * \brief Insert a control in the list of activable controls.
 * \param c The control to insert in the list.
 */
void ptb::frame::allow_focus( bear::gui::visual_component& c )
{
  m_controls.push_back(&c);

  if ( m_controls.size() == 1 )
    switch_to_control(0);
} // frame::allow_focus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that a key has been pressed.
 * \param key The code of the key.
 */
bool ptb::frame::process_key_press( const bear::input::key_info& key )
{
  if ( key.is_left() )
    move_cursor_left();
  else if ( key.is_right() )
    move_cursor_right();
  else if ( key.is_up() )
    move_cursor_up();
  else if ( key.is_down() )
    move_cursor_down();

  return false;
} // frame::process_key_press()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that a joystick button has been pressed.
 * \param button The code of the button.
 * \param joy_index The index of the joytick.
 */
bool ptb::frame::process_button_press
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  switch( button )
    {
    case bear::input::joystick::jc_axis_left:  move_cursor_left(); break;
    case bear::input::joystick::jc_axis_right: move_cursor_right(); break;
    case bear::input::joystick::jc_axis_up:    move_cursor_up(); break;
    case bear::input::joystick::jc_axis_down:  move_cursor_down(); break;
    }

  return false;
} // frame::process_button_press()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when a mouse moves over the frame.
 * \param pos The position of the mouse.
 */
bool ptb::frame::process_mouse_move
( const claw::math::coordinate_2d<unsigned int>& pos )
{
  highlight_control_at(pos);

  return false;
} // frame::process_mouse_move()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that a key has been pressed.
 * \param key The code of the key.
 */
bool ptb::frame::on_key_press( const bear::input::key_info& key )
{
  return process_key_press(key);
} // frame::on_key_press()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that a joystick button has been pressed.
 * \param button The code of the button.
 * \param joy_index The index of the joytick.
 */
bool ptb::frame::on_button_press
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  return process_button_press(button, joy_index);
} // frame::on_button_press()

/*----------------------------------------------------------------------------*/
/**
 * \brief Method called when a mouse moves over the frame.
 * \param pos The position of the mouse.
 */
bool ptb::frame::on_mouse_move
( const claw::math::coordinate_2d<unsigned int>& pos )
{
  return process_mouse_move(pos);
} // frame::on_mouse_move()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the sprite of the frame.
 * \param name The name of the sprite to get.
 */
bear::visual::sprite
ptb::frame::get_frame_sprite( const std::string& name ) const
{
  return
    m_owning_layer->get_level().get_globals().auto_sprite
    ( "gfx/ui/frame.png", name );
} // frame::get_frame_sprite()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the frame.
 */
void ptb::frame::common_init()
{
  set_font( get_font() );

  set_size( m_owning_layer->get_size() );

  set_background_color(PTB_THEME_FACE);
  set_borders_up(*this);

  m_current_control = 0;
} // frame::common_init()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the cursor up.
 */
void ptb::frame::move_cursor_up()
{
  switch_to_control
    ( find_nearest_control
      ( std::mem_fun_ref(&bear::gui::visual_component::left),
        std::mem_fun_ref(&bear::gui::visual_component::left),
        std::mem_fun_ref(&bear::gui::visual_component::bottom),
        std::mem_fun_ref(&bear::gui::visual_component::bottom), true
        ) );
} // frame::move_cursor_up()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the cursor down.
 */
void ptb::frame::move_cursor_down()
{
  switch_to_control
    ( find_nearest_control
      ( std::mem_fun_ref(&bear::gui::visual_component::left),
        std::mem_fun_ref(&bear::gui::visual_component::left),
        std::mem_fun_ref(&bear::gui::visual_component::bottom),
        std::mem_fun_ref(&bear::gui::visual_component::bottom)
        ) );
} // frame::move_cursor_down()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the cursor on the left.
 */
void ptb::frame::move_cursor_left()
{
  switch_to_control
    ( find_nearest_control
      ( std::mem_fun_ref(&bear::gui::visual_component::bottom),
        std::mem_fun_ref(&bear::gui::visual_component::bottom),
        std::mem_fun_ref(&bear::gui::visual_component::left),
        std::mem_fun_ref(&bear::gui::visual_component::left)
        ) );
} // frame::move_cursor_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Move the cursor on the left.
 */
void ptb::frame::move_cursor_right()
{
  switch_to_control
    ( find_nearest_control
      ( std::mem_fun_ref(&bear::gui::visual_component::bottom),
        std::mem_fun_ref(&bear::gui::visual_component::bottom),
        std::mem_fun_ref(&bear::gui::visual_component::left),
        std::mem_fun_ref(&bear::gui::visual_component::left), true
        ) );
} // frame::move_cursor_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Search the nearest control to the current one according to a lexical
 *        comparison of two distances.
 *
 * \param current_value_1 How to get the first value on the current control.
 * \param other_value_1 How to get the first value on the other control.
 * \param current_value_2 How to get the second value on the current control.
 * \param other_value_2 How to get the second value on the other control.
 * \param reversed Indicates if the second value is reversed.
 *
 * The control whose index is returned by this function minimizes the distance
 * between current_value_1(c) - other_value_1(o), then between
 * current_value_2(c) - other_value_2(o), where c is the control whose index is
 * m_current_control and o is an other control.
 */
template< typename CurrentValue1, typename OtherValue1, typename CurrentValue2,
          typename OtherValue2 >
std::size_t ptb::frame::find_nearest_control
( const CurrentValue1& current_value_1, const OtherValue1& other_value_1,
  const CurrentValue2& current_value_2, const OtherValue2& other_value_2,
  bool reversed ) const
{
  if ( m_current_control == m_controls.size() )
    return 0;

  double min_1( std::numeric_limits<double>::max() );
  double min_2( std::numeric_limits<double>::max() );
  double opposite_1( std::numeric_limits<double>::max() );
  double opposite_2( std::numeric_limits<double>::max() );
  std::size_t result(m_current_control);
  std::size_t opposite(m_current_control);
  const bear::gui::visual_component* current = m_controls[m_current_control];

  for ( std::size_t i=0; i!=m_controls.size(); ++i )
    if ( i != m_current_control )
      {
        const double d1
          (std::abs(current_value_1(*current)-other_value_1(*m_controls[i])));
        double d2(current_value_2(*current) - other_value_2(*m_controls[i]));
        if ( reversed )
          d2 = -d2;

        if ( (d2 > 0) && ( (d1 < min_1)||( (d1 == min_1) && (d2 < min_2) ) ) )
            {
              min_1 = d1;
              min_2 = d2;
              result = i;
            }

        if ( (d2 < 0) &&
             ( (d2 < opposite_2)||((d2 == opposite_2) && (d1 < opposite_1)) ) )
          {
            opposite_1 = d1;
            opposite_2 = d2;
            opposite = i;
          }
      }

  if ( (m_current_control == result) && (m_current_control != opposite) )
    result = opposite;

  return result;
} // frame::find_nearest_control()

/*----------------------------------------------------------------------------*/
/**
 * \brief Highlight a control at a given position.
 * \param pos A position where the control is.
 */
bool ptb::frame::highlight_control_at
( const claw::math::coordinate_2d<unsigned int>& pos )
{
  bool stop(false);

  for ( std::size_t i=0; !stop && (i!=m_controls.size()); ++i )
    if ( m_controls[i]->get_rectangle().includes(pos) )
      {
        stop = true;
        switch_to_control(i);
      }

  return stop;
} // frame::highlight_control_at()

/*----------------------------------------------------------------------------*/
/**
 * \brief Switch to an other control.
 * \param i The index of the control to switch to.
 */
void ptb::frame::switch_to_control( std::size_t i )
{
  if ( m_current_control != m_controls.size() )
    m_controls[m_current_control]->set_background_color(PTB_THEME_TRANSPARENT);

  m_current_control = i;

  if ( m_current_control != m_controls.size() )
    {
      m_controls[m_current_control]->set_background_color(PTB_THEME_SELECTION);
      m_controls[m_current_control]->set_focus();
    }
} // frame::switch_to_control()

/*----------------------------------------------------------------------------*/
/**
 * \brief The focus has been set on the frame or one of its children.
 */
void ptb::frame::on_focused()
{
  const bear::gui::visual_component* c(get_content().get_focus());
  std::size_t i(0);
  bool stop(false);

  while ( !stop && (i!=m_controls.size()) )
    if ( m_controls[i] == c )
      stop = true;
    else
      ++i;

  if ( i!=m_current_control )
    switch_to_control(i);
} // frame::on_focus_on()
