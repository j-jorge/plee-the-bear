/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::link_on_players class.
 * \author Julien Jorge
 */
#include "ptb/item/link_on_players.hpp"

#include "ptb/player.hpp"
#include "universe/link/link.hpp"

BASE_ITEM_EXPORT( link_on_players, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::link_on_players::link_on_players()
  : m_strength
  (std::numeric_limits<bear::universe::coordinate_type>::infinity()),
    m_minimal_length(0),
    m_maximal_length
  (std::numeric_limits<bear::universe::coordinate_type>::infinity()),
    m_link_visual(NULL)
{

} // link_on_players::link_on_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Copy constructor.
 * \param that The instance to copy from.
 */
ptb::link_on_players::link_on_players( const link_on_players& that )
  : super(that), m_strength(that.m_strength),
    m_minimal_length(that.m_minimal_length),
    m_maximal_length(that.m_maximal_length),
    m_link_visual(NULL)
{
  if (that.m_link_visual != NULL)
    m_link_visual = that.m_link_visual->clone();
} // link_on_players::link_on_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::link_on_players::~link_on_players()
{
  delete m_link_visual;
} // link_on_players::~link_on_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "real".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::link_on_players::set_real_field
( const std::string& name, double value )
{
  bool result = true;

  if ( name == "link_on_players.strength" )
    m_strength = value;
  else if ( name == "link_on_players.length.minimal" )
    m_minimal_length = value;
  else if ( name == "link_on_players.length.maximal" )
    m_maximal_length = value;
  else
    result = super::set_real_field( name, value );

  return result;
} // link_on_players::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "item".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::link_on_players::set_item_field
( const std::string& name, bear::engine::base_item* value )
{
  bool result = true;

  if ( name == "link_on_players.link_visual" )
    {
      bear::base_link_visual* item
        ( dynamic_cast<bear::base_link_visual*>(value) );

      if ( item == NULL )
        {
          result = false;
          claw::logger << claw::log_warning
                       << "link_on_players.link_visual: item is not of type "
                       << "base_link_visual." << std::endl;
        }
      else
        {
          m_link_visual = item->clone();
          item->kill();
        }
    }
  else
    result = super::set_item_field( name, value );

  return result;
} // link_on_players::set_item_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief All players are colliding with the item.
 * \param p1 The first player.
 * \param p2 The second player.
 */
void ptb::link_on_players::on_all_players
( const player_proxy& p1, const player_proxy& p2 )
{
  player* player_1(p1.get_player_instance());
  player* player_2(p2.get_player_instance());

  // all players does not mean two players in single player game.
  if ( (player_1 != NULL) && (player_2 != NULL) )
    {
      if ( !player_1->is_linked_to(*player_2) )
        {
          bear::universe::link* link
            ( new bear::universe::link
              ( *player_1, *player_2, m_strength, m_minimal_length,
                m_maximal_length ) );

          if (m_link_visual != NULL)
            {
              bear::base_link_visual* vis(m_link_visual->clone());
              vis->set_items(player_1, player_2, link->get_id());
              new_item(*vis);
            }
        }
    }
} // link_on_players::on_all_players()
