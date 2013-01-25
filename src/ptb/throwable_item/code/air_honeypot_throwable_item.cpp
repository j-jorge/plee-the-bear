/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::honeypot_throwable_item class.
 * \author Sebastien Angibaud
 */
#include "ptb/throwable_item/air_honeypot_throwable_item.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/item/small_honeypot.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 * \param p The pointer on the player.
 */
ptb::air_honeypot_throwable_item::air_honeypot_throwable_item
( const player_proxy& p )
  : throwable_item("air_power_honeypot"), m_player(p)
{

} // air_honeypot_throwable_item::air_honeypot_throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the throwable_item.
 */
bear::engine::base_item*
ptb::air_honeypot_throwable_item::create_throwable_item() const
{
  small_honeypot* new_small_honeypot = new small_honeypot();
  new_small_honeypot->set_type(base_bonus::air_power);

  return new_small_honeypot;
} // air_honeypot_throwable_item::create_throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if Plee can throw this throwable_item.
 */
bool ptb::air_honeypot_throwable_item::can_throw() const
{
  return (get_stock() > 0) && m_player.can_throw_power(monster::air_attack);
} // air_honeypot_throwable_item::can_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Decrease the stock.
 */
void ptb::air_honeypot_throwable_item::decrease_stock() const
{
  game_variables::set_air_power(m_player.get_index(), false);
} // air_honeypot_throwable_item::decrease_stock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the stock.
 */
unsigned int ptb::air_honeypot_throwable_item::get_stock() const
{
  if ( game_variables::get_air_power(m_player.get_index()) )
    return 1;
  else
    return 0;
} // air_honeypot_throwable_item::get_stock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the animation of the throwable_item.
 */
std::string ptb::air_honeypot_throwable_item::get_animation() const
{
  return "animation/powerup/small_air.canim";
} // air_honeypot_throwable_item::get_animation()
