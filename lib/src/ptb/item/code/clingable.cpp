/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::clingable class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/clingable.hpp"

#include "ptb/player_proxy.hpp"

#include <algorithm>

BASE_ITEM_EXPORT( clingable, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::clingable::clingable()
{
  set_phantom(true);
  set_weak_collisions(true);
} // clingable::clingable()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do post creation actions.
 */
void ptb::clingable::build()
{
  super::build();

  m_last_position = get_top_left();
} // clingable::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item.
 * \param elapsed_time Elasped time since the last progress.
 */
void ptb::clingable::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  item_list::iterator it;
  std::list<item_list::iterator> dead;

  for (it=m_list_items.begin(); it!=m_list_items.end(); ++it)
    if ( *it == NULL )
      dead.push_front(it);

  for( ; !dead.empty(); dead.pop_front() )
    m_list_items.erase( dead.front() );
} // clingable::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the movement of the item.
 * \param elapsed_time Elasped time since the last call.
 */
void ptb::clingable::move( bear::universe::time_type elapsed_time )
{
  super::move(elapsed_time);

  item_list::iterator it;
  bear::universe::position_type position = get_top_left();

  for(it=m_list_items.begin(); it!=m_list_items.end(); ++it)
    if ( *it != NULL )
      {
        (*it)->set_left((*it)->get_left() + position.x - m_last_position.x);
        (*it)->set_bottom
          ((*it)->get_bottom() + position.y - m_last_position.y);
      }

  for(it=m_old_items.begin(); it!=m_old_items.end(); ++it)
    if ( *it != NULL )
      if ( std::find(m_list_items.begin(), m_list_items.end(), *it)
           == m_list_items.end() ) // item is not on me anymore
        (*it)->set_speed
          ( (*it)->get_speed() + bear::universe::speed_type(get_speed()) );

  m_last_position = position;
  std::swap(m_old_items, m_list_items);
  m_list_items.clear();
} // clingable::move()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the collision is with a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::clingable::collision_check_and_apply
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  player_proxy p(&that);

  if ( p != NULL )
    {
      p.set_can_cling(true);

      if ( p.is_clung() )
        m_list_items.push_front(that);
    }
} // clingable::collision_check_and_apply()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_apply().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::clingable::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_and_apply(that, info);

  super::collision(that, info);
} // clingable::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the items concerned by a progress/move of this one.
 * \param d (out) A list to which are added such items.
 */
void ptb::clingable::get_dependent_items
( bear::universe::physical_item::item_list& d ) const
{
  item_list::const_iterator it;

  for( it=m_list_items.begin(); it!=m_list_items.end(); ++it )
    if ( *it != NULL )
      d.push_back( it->get() );

  for( it=m_old_items.begin(); it!=m_old_items.end(); ++it )
    if ( *it != NULL )
      d.push_back( it->get() );
} // clingable::get_dependent_items()
