/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::demo_level_loader class.
 * \author Julien Jorge
 */
#include "ptb/item/demo_level_loader.hpp"

#include "ptb/defines.hpp"
#include "ptb/game_variables.hpp"
#include "engine/game.hpp"
#include "engine/variable/variable.hpp"
#include "generic_items/delayed_level_loading.hpp"

#include <claw/logger.hpp>

BASE_ITEM_EXPORT( demo_level_loader, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::demo_level_loader::demo_level_loader()
  : m_delay(30), m_elapsed_time(0)
{
  set_phantom(true);
  set_artificial(true);
  set_can_move_items(false);
} // demo_level_loader::demo_level_loader()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type list of std::string.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::demo_level_loader::set_string_list_field
( const std::string& name, const std::vector<std::string>& value )
{
  bool result;

  if ( name == "demo_level_loader.levels" )
    {
      m_level_name = value;
      result = true;
    }
  else
    result = super::set_string_list_field( name, value );

  return result;
} // demo_level_loader::set_string_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type list of unsigned int.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::demo_level_loader::set_u_integer_list_field
( const std::string& name, const std::vector<unsigned int>& value )
{
  bool result;

  if ( name == "demo_level_loader.players_count" )
    {
      m_players_count = value;
      result = true;
    }
  else
    result = super::set_u_integer_list_field( name, value );

  return result;
} // demo_level_loader::set_u_integer_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c real.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::demo_level_loader::set_real_field
( const std::string& name, const double value )
{
  bool result;

  if ( name == "demo_level_loader.delay" )
    {
      m_delay = value;
      result = true;
    }
  else
    result = super::set_real_field( name, value );

  return result;
} // demo_level_loader::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::demo_level_loader::is_valid() const
{
  if ( m_players_count.size() != m_level_name.size() )
    {
      claw::logger << claw::log_error
                   << "demo_level_loader: the list of levels and the one of "
                   << "players count do not have the same length."
                   << std::endl;
      return false;
    }
  else
    return super::is_valid();
} // demo_level_loader::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::demo_level_loader::build()
{
  super::build();

  bear::engine::variable<unsigned int> index("demo/next_index", 0);

  if ( !bear::engine::game::get_instance().game_variable_exists(index) )
    bear::engine::game::get_instance().set_game_variable(index);

  game_variables::set_demo(false);
} // demo_level_loader::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time elapsed time since the last call.
 */
void ptb::demo_level_loader::progress
( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );
  progress_input_reader(elapsed_time);

  if ( (m_elapsed_time < m_delay)
       && (m_elapsed_time + elapsed_time >= m_delay) )
    {
      bear::engine::variable<unsigned int> index("demo/next_index");
      bear::engine::game::get_instance().get_game_variable(index);

      const unsigned int i( index.get_value() );

      if ( i < m_level_name.size() )
        {
          game_variables::set_demo(true);

          bear::engine::game::get_instance().set_game_variable
            ( bear::engine::variable<unsigned int>
              ( "demo/next_index", (i+1) % m_level_name.size() ) );

          game_variables::set_next_level_name(m_level_name[i]);
          game_variables::set_players_count(m_players_count[i]);

          bear::delayed_level_loading* loader
            ( new bear::delayed_level_loading
              ( PTB_LOADING_LEVEL_NAME, 1, false, 1,
                PTB_TRANSITION_EFFECT_DEFAULT_TARGET_NAME ) );

          CLAW_ASSERT
            ( loader->is_valid(), "The level loader is not well initialised." );

          new_item( *loader );
        }
    }

  m_elapsed_time += elapsed_time;
} // demo_level_loader::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief The user is doing something. Reset the timer.
 * \param key The code of the key.
 */
bool ptb::demo_level_loader::key_pressed( const bear::input::key_info& key )
{
  m_elapsed_time = std::numeric_limits<bear::universe::time_type>::infinity();
  return true;
} // demo_level_loader::key_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief The user is doing something. Reset the timer.
 * \param button The code of the button.
 * \param joy_index The index of the joystick.
 */
bool ptb::demo_level_loader::button_pressed
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  m_elapsed_time = std::numeric_limits<bear::universe::time_type>::infinity();
  return true;
} // demo_level_loader::button_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief The user is doing something. Reset the timer.
 * \param button The code of the button.
 * \param pos The position of the cursor on the screen.
 */
bool ptb::demo_level_loader::mouse_pressed
( bear::input::mouse::mouse_code button,
  const claw::math::coordinate_2d<unsigned int>& pos )
{
  m_elapsed_time = std::numeric_limits<bear::universe::time_type>::infinity();
  return true;
} // demo_level_loader::mouse_pressed()
