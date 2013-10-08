/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::save_player_position class.
 * \author Julien Jorge
 */
#include "ptb/item/save_player_position.hpp"

#include "ptb/player_proxy.hpp"

#include "engine/export.hpp"

BASE_ITEM_EXPORT( save_player_position, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::save_player_position::save_player_position()
  : m_player_index(1), m_activated(false), m_collision(false), m_ready(true),
    m_can_be_reactivated(false)
{
  set_can_move_items(false);
  set_phantom(true);
} // save_player_position::save_player_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "unsigned integer".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::save_player_position::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result;

  if ( name == "save_player_position.player_index" )
    {
      set_player_index(value);
      result = true;
    }
  else
    result = super::set_u_integer_field( name, value );

  return result;
} // player_start_position::set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void
ptb::save_player_position::progress( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);

  if (m_can_be_reactivated && !m_collision)
    m_ready = true;

  m_collision = false;
} // save_player_position::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the index of the player whose position is saved.
 */
unsigned int ptb::save_player_position::get_player_index() const
{
  return m_player_index;
} // save_player_position::get_player_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the index of the player whose position is saved.
 * \param i The index of the player.
 */
void ptb::save_player_position::set_player_index( unsigned int i )
{
  m_player_index = i;
} // save_player_position::set_player_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that the item can be activated several times.
 * \param b Can or cannot.
 */
void ptb::save_player_position::can_be_reactivated( bool b )
{
  m_can_be_reactivated = b;
} // save_player_position::can_be_reactivated()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item can be reactivated.
 */
bool ptb::save_player_position::is_activated() const
{
  return m_activated;
} // save_player_position::is_activated()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do extra stuff at activation time.
 */
void ptb::save_player_position::activate()
{
  // nothing to do
} // save_player_position::activate()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do extra stuff at reactivation time.
 */
void ptb::save_player_position::reactivate()
{
  // nothing to do
} // save_player_position::reactivate()

/*----------------------------------------------------------------------------*/
/**
 * \brief Collision with an other item.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::save_player_position::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if ( p != NULL )
    if ( p.get_index() == m_player_index )
      {
        m_collision = true;

        if ( m_ready )
          {
            if ( !m_activated )
              {
                p.save_position( get_top_middle() );
                m_activated = true;
                activate();
              }
            else if (m_can_be_reactivated)
              {
                p.save_position( get_top_middle() );
                reactivate();
              }

            m_ready = false;
          }
      }
} // save_player_position::collision()
