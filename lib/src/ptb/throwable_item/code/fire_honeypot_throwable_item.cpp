/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::honeypot_throwable_item class.
 * \author Sebastien Angibaud
 */
#include "ptb/throwable_item/fire_honeypot_throwable_item.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/item/small_honeypot.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 * \param p The pointer on the player.
 */
ptb::fire_honeypot_throwable_item::fire_honeypot_throwable_item
( const player_proxy& p )
  : throwable_item("fire_power_honeypot"), m_player(p)
{

} // fire_honeypot_throwable_item::fire_honeypot_throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the throwable_item.
 */
bear::engine::base_item*
ptb::fire_honeypot_throwable_item::create_throwable_item() const
{
  small_honeypot* new_small_honeypot = new small_honeypot();
  new_small_honeypot->set_type(base_bonus::fire_power);

  return new_small_honeypot;
} // fire_honeypot_throwable_item::create_throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if Plee can throw this throwable_item.
 */
bool ptb::fire_honeypot_throwable_item::can_throw() const
{
  return (get_stock() > 0) && m_player.can_throw_power(monster::fire_attack);
} // fire_honeypot_throwable_item::can_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Decrease the stock.
 */
void ptb::fire_honeypot_throwable_item::decrease_stock() const
{
  game_variables::set_fire_power(m_player.get_index(), false);
} // fire_honeypot_throwable_item::decrease_stock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the stock.
 */
unsigned int ptb::fire_honeypot_throwable_item::get_stock() const
{
  if ( game_variables::get_fire_power(m_player.get_index()) )
    return 1;
  else
    return 0;
} // fire_honeypot_throwable_item::get_stock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the animation of the throwable_item.
 */
std::string ptb::fire_honeypot_throwable_item::get_animation() const
{
  return "animation/powerup/small_fire.canim";
} // fire_honeypot_throwable_item::get_animation()
