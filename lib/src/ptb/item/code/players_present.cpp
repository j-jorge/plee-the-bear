/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::players_present class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/players_present.hpp"

BASE_ITEM_EXPORT( players_present, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::players_present::players_present()
  : m_check_all_players(true)
{
  set_weak_collisions(true);
} // players_present::players_present()

/*----------------------------------------------------------------------------*/
/**
 * \brief Copy constructor.
 * \param that The item copied.
 */
ptb::players_present::players_present( const players_present& that)
  : super(that), m_check_all_players(that.m_check_all_players)
{

} // players_present::players_present()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c boolean.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::players_present::set_bool_field
( const std::string& name, bool value )
{
   bool ok = true;

  if (name == "players_present.check_all_players")
    m_check_all_players = value;
  else
    ok = super::set_bool_field(name, value);

  return ok;
} // players_present::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c list of item.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::players_present::set_item_list_field
( const std::string& name, const std::vector<bear::engine::base_item*>& value)
{
  bool ok = true;

  if (name == "players_present.toggles")
    for( std::size_t i=0; i!=value.size(); ++i )
      m_items.push_back( handle_type(value[i]) );
  else
    ok = super::set_item_list_field(name, value);

  return ok;
} // players_present::set_item_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Activation by one player among the two players.
 * \param p The player.
 */
void ptb::players_present::on_one_player( const player_proxy& p )
{
  if ( ( game_variables::get_players_count() == 1 ) ||
       ( !m_check_all_players ) )
    activate_toggles();
} // players_present::on_one_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Activation by all players.
 * \param p1 The first player.
 * \param p2 The second player. NULL in a single player game.
 */
void ptb::players_present::on_all_players
( const player_proxy& p1, const player_proxy& p2 )
{
  activate_toggles();
} // players_present::on_all_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Activate all toggles.
 */
void ptb::players_present::activate_toggles()
{
  handle_list::iterator it;
  std::list<handle_list::iterator> dead;

  for (it=m_items.begin(); it!=m_items.end(); ++it)
    if ( *it == (bear::engine::with_toggle*)NULL )
      dead.push_back(it);
    else
      (*it)->toggle(true, this);

  for ( ; !dead.empty(); dead.pop_front() )
    m_items.erase(dead.front());
} // players_present::activate_toggles()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the items concerned by a progress/move of this one.
 * \param d (out) A list to which are added such items.
 */
void ptb::players_present::get_dependent_items
( std::list<bear::universe::physical_item*>& d ) const
{
  super::get_dependent_items(d);

  handle_list::const_iterator it;

  for (it=m_items.begin(); it!=m_items.end(); ++it)
    if ( *it != (physical_item*)NULL )
      d.push_back(it->get_item());
} // players_present::get_dependent_items()
