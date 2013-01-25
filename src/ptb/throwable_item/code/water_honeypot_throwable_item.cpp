/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::honeypot_throwable_item class.
 * \author Sebastien Angibaud
 */
#include "ptb/throwable_item/water_honeypot_throwable_item.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/item/small_honeypot.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 * \param p The pointer on the player.
 */
ptb::water_honeypot_throwable_item::water_honeypot_throwable_item
( const player_proxy& p )
  : throwable_item("water_power_honeypot"), m_player(p)
{

} // water_honeypot_throwable_item::water_honeypot_throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the throwable_item.
 */
bear::engine::base_item*
ptb::water_honeypot_throwable_item::create_throwable_item() const
{
  small_honeypot* new_small_honeypot = new small_honeypot();
  new_small_honeypot->set_type(base_bonus::water_power);

  return new_small_honeypot;
} // water_honeypot_throwable_item::create_throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if Plee can throw this throwable_item.
 */
bool ptb::water_honeypot_throwable_item::can_throw() const
{
  return (get_stock() > 0) && m_player.can_throw_power(monster::water_attack);
} // water_honeypot_throwable_item::can_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Decrease the stock.
 */
void ptb::water_honeypot_throwable_item::decrease_stock() const
{
  game_variables::set_water_power(m_player.get_index(), false);
} // water_honeypot_throwable_item::decrease_stock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the stock.
 */
unsigned int ptb::water_honeypot_throwable_item::get_stock() const
{
  if ( game_variables::get_water_power(m_player.get_index()) )
    return 1;
  else
    return 0;
} // water_honeypot_throwable_item::get_stock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the animation of the throwable_item.
 */
std::string ptb::water_honeypot_throwable_item::get_animation() const
{
  return "animation/powerup/small_water.canim";
} // water_honeypot_throwable_item::get_animation()
