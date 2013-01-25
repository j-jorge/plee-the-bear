/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::on_players_activator class.
 * \author Julien Jorge
 */
#include "ptb/item/on_players_activator.hpp"
#include "ptb/player.hpp"
#include "ptb/item_brick/activate_on_players.hpp"

BASE_ITEM_EXPORT( on_players_activator, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c list of item.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::on_players_activator::set_item_list_field
( const std::string& name, const std::vector<bear::engine::base_item*>& value)
{
  bool ok = true;

  if (name == "on_players_activator.item")
    for( std::size_t i=0; i!=value.size(); ++i )
      m_item.push_back( handle_type(value[i]) );
  else
    ok = super::set_item_list_field(name, value);

  return ok;
} // on_players_activator::set_item_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Activation by one player among the two players.
 * \param p The player.
 */
void ptb::on_players_activator::on_one_player( const player_proxy& p )
{
  handle_list::iterator it;
  std::list<handle_list::iterator> dead;

  for (it=m_item.begin(); it!=m_item.end(); ++it)
    if ( *it == (activate_on_players*)NULL )
      dead.push_back(it);
    else
      (*it)->on_one_player(p);

  for ( ; !dead.empty(); dead.pop_front() )
    m_item.erase(dead.front());
} // on_players_activator::on_one_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Activation by all players.
 * \param p1 The first player.
 * \param p2 The second player. NULL in a single player game.
 */
void ptb::on_players_activator::on_all_players
( const player_proxy& p1, const player_proxy& p2 )
{
  handle_list::iterator it;
  std::list<handle_list::iterator> dead;

  for (it=m_item.begin(); it!=m_item.end(); ++it)
    if ( *it == (activate_on_players*)NULL )
      dead.push_back(it);
    else
      (*it)->on_all_players(p1, p2);

  for ( ; !dead.empty(); dead.pop_front() )
    m_item.erase(dead.front());
} // on_players_activator::on_all_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the items concerned by a progress/move of this one.
 * \param d (out) A list to which are added such items.
 */
void ptb::on_players_activator::get_dependent_items
( std::list<bear::universe::physical_item*>& d ) const
{
  super::get_dependent_items(d);

  handle_list::const_iterator it;

  for (it=m_item.begin(); it!=m_item.end(); ++it)
    if ( *it != (physical_item*)NULL )
      d.push_back(it->get_item());
} // on_players_activator::get_dependent_items()
