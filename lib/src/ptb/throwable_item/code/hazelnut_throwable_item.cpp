/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::hazelnut_throwable_item class.
 * \author Sebastien Angibaud
 */
#include "ptb/throwable_item/hazelnut_throwable_item.hpp"

#include "ptb/level_variables.hpp"
#include "ptb/item/hazelnut.hpp"

const std::string
ptb::hazelnut_throwable_item::s_name = "hazelnut";

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 * \param p The pointer on the player.
 */
ptb::hazelnut_throwable_item::hazelnut_throwable_item(const player_proxy& p)
  : throwable_item("hazelnut"), m_player(p)
{

} // hazelnut_throwable_item::hazelnut_throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the throwable_item.
 */
bear::engine::base_item*
ptb::hazelnut_throwable_item::create_throwable_item() const
{
  return new hazelnut();
} // hazelnut_throwable_item::create_throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Decrease the stock.
 */
void ptb::hazelnut_throwable_item::decrease_stock() const
{
  level_variables::set_current_hazelnut(m_player.get_level(), false);
} // hazelnut::throwable_item::decrease_stock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the stock.
 */
unsigned int ptb::hazelnut_throwable_item::get_stock() const
{
  if (level_variables::get_current_hazelnut(m_player.get_level()) )
    return 1;
  else
    return 0;
} // hazelnut_throwable_item::get_stock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the animation of the throwable_item.
 */
std::string ptb::hazelnut_throwable_item::get_animation() const
{
  return "animation/owl/hazelnut.canim";
} // hazelnut_throwable_item::get_animation()
