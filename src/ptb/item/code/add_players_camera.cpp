/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::add_players_camera class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/add_players_camera.hpp"
#include "universe/derived_item_handle.hpp"

#include "ptb/player.hpp"
#include "ptb/util/player_util.hpp"

BASE_ITEM_EXPORT( add_players_camera, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::add_players_camera::add_players_camera()
  : m_first_player(false), m_second_player(false), m_camera(NULL)
{

} // add_players_camera::add_players_camera()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::add_players_camera::progress
( bear::universe::time_type elapsed_time )
{
  if ( m_camera )
    {
      player_proxy p = util::find_player( get_level_globals(), 1 );

      if ( p!=NULL )
        m_camera->add_item(p.get_player_instance());

      p = util::find_player( get_level_globals(), 2 );

      if ( p!=NULL )
        m_camera->add_item(p.get_player_instance());
    }

  kill();
} // add_players_camera::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type bool.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::add_players_camera::set_bool_field
( const std::string& name, bool value )
{
  bool ok = true;

  if ( name == "add_players_camera.first_item" )
    m_first_player = value;
  else if ( name == "add_players_camera.second_item" )
       m_second_player = value;
  else
    ok = super::set_bool_field(name, value);

  return ok;
} // add_players_camera::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c base_item.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::add_players_camera::set_item_field
( const std::string& name, base_item* value )
{
  bool result = true;

  if ( name == "add_players_camera.camera" )
    m_camera = (bear::camera_on_object*)value;
  else
    result = super::set_item_field(name, value);

  return result;
} // ptb::add_players_camera::set_item_field()
