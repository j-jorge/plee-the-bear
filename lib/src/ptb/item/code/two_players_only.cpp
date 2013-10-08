/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::two_players_only class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/two_players_only.hpp"

#include "ptb/game_variables.hpp"

BASE_ITEM_EXPORT( two_players_only, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::two_players_only::two_players_only()
{
  m_items_two_players.clear();
  m_items_one_player.clear();

  set_global(true);
} // two_players_only::two_players_only()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type list of <*base_item>.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::two_players_only::set_item_list_field
( const std::string& name, const std::vector<base_item*>& value )
{
  bool result = false;

  if ( name == "two_players_only.items_killed_with_two_players" )
    {
      m_items_two_players.clear();
      for ( unsigned int index = 0; index != value.size(); ++index )
        m_items_two_players.push_back(value[index]);
      result = true;
    }
  else if ( name == "two_players_only.items_killed_with_one_player" )
    {
      m_items_one_player.clear();
      for ( unsigned int index = 0; index != value.size(); ++index )
        m_items_one_player.push_back(value[index]);
      result = true;
    }
  else
    result = super::set_item_list_field( name, value );

  return result;
} // two_players_only::set_item_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::two_players_only::build()
{
  std::vector<bear::universe::item_handle>::iterator it;

  if ( game_variables::get_players_count() == 1 )
    {
       for (it = m_items_one_player.begin();
           it != m_items_one_player.end(); ++it)
        if ( *it != NULL )
          {
            base_item*
              item = dynamic_cast<base_item*>(it->get());
            if ( item != NULL )
              item->kill();
          }
    }
  else
    {
      for (it = m_items_two_players.begin();
           it != m_items_two_players.end(); ++it)
        if ( *it != NULL )
          {
            base_item*
              item = dynamic_cast<base_item*>(it->get());
            if ( item != NULL )
              item->kill();
          }
    }

  kill();
} // two_players_only::build()
