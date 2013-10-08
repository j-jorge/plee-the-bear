/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::reverse_ghost class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/castle/reverse_ghost.hpp"
#include "ptb/player.hpp"

#include "universe/forced_movement/forced_tracking.hpp"

BASE_ITEM_EXPORT( reverse_ghost, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::reverse_ghost::reverse_ghost()
  : m_first_action(player_action::action_null),
    m_second_action(player_action::action_null)
{
} // reverse_ghost::reverse_ghost()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::reverse_ghost::~reverse_ghost()
{
} // reverse_ghost::~reverse_ghost()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::reverse_ghost::pre_cache()
{
  get_level_globals().load_model("model/castle/reverse_ghost.cm");
} // reverse_ghost::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::reverse_ghost::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor
    ( get_level_globals().get_model("model/castle/reverse_ghost.cm") );
  start_model_action("wait");
  set_origin();
} // reverse_ghost::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "string".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::reverse_ghost::set_string_field
( const std::string& name, const std::string& value )
{
  bool result = true;

  if ( name == "reverse_ghost.first_action" )
    m_first_action = player_action::from_string(value);
  else if ( name == "reverse_ghost.second_action" )
    m_second_action = player_action::from_string(value);
  else
    result = super::set_string_field( name, value );

  return result;
} // reverse::ghost::set_string_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::reverse_ghost::is_valid() const
{
  if ( ( m_first_action == player_action::action_null ) ||
       ( m_second_action == player_action::action_null ) )
    {
      claw::logger << claw::log_error
                   << "ghost: on of action is unknown."
                   << std::endl;
      return false;
    }
  else
    return super::is_valid();
} // reverse_ghost::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Control the current player.
 */
void ptb::reverse_ghost::control_player()
{
  m_player.switch_action(m_first_action, m_second_action);

  bear::universe::forced_tracking mvt;
  mvt.set_reference_point_on_center(*(m_player.get_player_instance()));
  mvt.set_distance(bear::universe::position_type(0, 0));
  set_forced_movement( mvt );
} // reverse_ghost::control_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Release the current player.
 */
void ptb::reverse_ghost::release_player()
{
  m_player.clear_switched_action(m_first_action, m_second_action);
} // reverse_ghost::release_player()
