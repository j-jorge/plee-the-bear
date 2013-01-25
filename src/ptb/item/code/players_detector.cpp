/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::players_detector class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/players_detector.hpp"

BASE_ITEM_EXPORT( players_detector, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::players_detector::players_detector()
{
  set_weak_collisions(true);
} // players_detector::players_detector()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "std::string".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::players_detector::set_string_field
( const std::string& name, const std::string& value )
{
  bool result(true);

  if ( name == "players_detector.category" )
    m_category = value;
  else
    result = super::set_string_field( name, value );

  return result;
} // players_detector::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the category of the item.
 */
const std::string& ptb::players_detector::get_category() const
{
  return m_category;
} // players_detector::get_category()

/*----------------------------------------------------------------------------*/
/**
 * \brief Activation by one player among the two players.
 * \param p The player.
 */
void ptb::players_detector::on_one_player( const player_proxy& p )
{
  kill();
} // players_detector::on_one_player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Activation by all players.
 * \param p1 The first player.
 * \param p2 The second player. NULL in a single player game.
 */
void ptb::players_detector::on_all_players
( const player_proxy& p1, const player_proxy& p2 )
{
  kill();
} // players_detector::on_all_players()
