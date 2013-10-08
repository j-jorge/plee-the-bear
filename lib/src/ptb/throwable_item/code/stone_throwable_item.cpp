/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::stone_throwable_item class.
 * \author Sebastien Angibaud
 */
#include "ptb/throwable_item/stone_throwable_item.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/item/air_bubble.hpp"
#include "ptb/item/stone/air_fire_stone.hpp"
#include "ptb/item/stone/air_fire_water_stone.hpp"
#include "ptb/item/stone/air_water_stone.hpp"
#include "ptb/item/stone/air_stone.hpp"
#include "ptb/item/stone/water_fire_stone.hpp"
#include "ptb/item/stone/water_stone.hpp"
#include "ptb/item/stone/fire_stone.hpp"
#include "engine/world.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 * \param p The pointer on the player.
 */
ptb::stone_throwable_item::stone_throwable_item(const player_proxy& p)
  : throwable_item("stone", true), m_player(p)
{

} // stone_throwable_item::stone_throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create the throwable_item.
 */
bear::engine::base_item*
ptb::stone_throwable_item::create_throwable_item() const
{
  stone* new_stone(NULL);

  if ( game_variables::get_stones_count(m_player.get_index()) > 0 )
    {
      if ( game_variables::get_air_power(m_player.get_index()) )
        if ( game_variables::get_fire_power(m_player.get_index()) )
          if ( game_variables::get_water_power(m_player.get_index()) )
            new_stone= new air_fire_water_stone();
          else
            new_stone= new air_fire_stone();
        else
          if ( game_variables::get_water_power(m_player.get_index()) )
            return create_air_water_stone();
          else
            new_stone= new air_stone();
      else
        if ( game_variables::get_fire_power(m_player.get_index()) )
          if ( game_variables::get_water_power(m_player.get_index()) )
            new_stone= new water_fire_stone();
          else
            new_stone= new fire_stone();
        else
          if ( game_variables::get_water_power(m_player.get_index()) )
            new_stone= new water_stone();
          else
            new_stone= new stone();

      new_stone->set_monster_index(m_player.get_index());
      new_stone->set_monster_type(monster::stone_monster);
    }

  return new_stone;
} // throwable_item::create_throwable_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Decrease the stock.
 */
void ptb::stone_throwable_item::decrease_stock() const
{
  game_variables::set_stones_count
    ( m_player.get_index(),
      game_variables::get_stones_count(m_player.get_index()) -
      get_required_stones());
} // throwable_item::decrease_stock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the stock.
 */
unsigned int ptb::stone_throwable_item::get_stock() const
{
  return game_variables::get_stones_count(m_player.get_index());
} // stone_throwable_item::get_stock()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if Plee can throw this throwable_item.
 */
bool ptb::stone_throwable_item::can_throw() const
{
  return get_stock() >= get_required_stones();
}// stone_throwable_item::can_throw()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the animation of the throwable_item.
 */
std::string ptb::stone_throwable_item::get_animation() const
{
  if ( game_variables::get_air_power(m_player.get_index()) )
    {
      if ( game_variables::get_fire_power(m_player.get_index()) )
        {
          if ( game_variables::get_water_power(m_player.get_index()) )
            return "animation/stones/air_fire_water_stone.canim";
          else
            return "animation/stones/air_fire_stone.canim";
        }
      else if ( game_variables::get_water_power(m_player.get_index()) )
        return "animation/stones/air_water_stone.canim";
      else
        return "animation/stones/air_stone.canim";
    }
  else if ( game_variables::get_fire_power(m_player.get_index()) )
    {
      if ( game_variables::get_water_power(m_player.get_index()) )
        return "animation/stones/water_fire_stone.canim";
      else
        return "animation/stones/fire_stone.canim";
    }
  else if ( game_variables::get_water_power(m_player.get_index()) )
    return "animation/stones/water_stone.canim";
  else
    return "animation/stones/stone.canim";
} // stone_throwable_item::get_animation()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create air_water_stone or air_bubble according to player's position.
 */
bear::engine::base_item*
ptb::stone_throwable_item::create_air_water_stone() const
{
  bool in_water(false);

  if ( m_player.has_owner() )
    {
      bear::engine::model_mark_placement m;

      if ( m_player.get_mark_placement("hand", m) )
        in_water = m_player.get_owner().is_in_environment
          (m.get_position(), bear::universe::water_environment);
    }

  if ( in_water )
    {
      air_bubble* new_air_bubble(NULL);

      new_air_bubble = new air_bubble();
      new_air_bubble->set_oxygen(1500);

      return new_air_bubble;
    }
  else
    {
      stone* new_stone(NULL);
      new_stone = new air_water_stone();

      new_stone->set_monster_index(m_player.get_index());
      new_stone->set_monster_type(monster::stone_monster);

      return new_stone;
    }
} // stone_throwable_item::create_air_water_stone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the number of required stones to throw.
 */
unsigned int ptb::stone_throwable_item::get_required_stones() const
{
  unsigned int n(1);

  if ( game_variables::get_air_power(m_player.get_index()) )
    {
      if ( game_variables::get_fire_power(m_player.get_index()) )
        {
          if ( game_variables::get_water_power(m_player.get_index()) )
            n=3;
          else
            n=2;
        }
      else if ( game_variables::get_water_power(m_player.get_index()) )
        n=2;
    }
  else if ( game_variables::get_fire_power(m_player.get_index())
            && game_variables::get_water_power(m_player.get_index()) )
      n=2;

  return n;
} // stone_throwable_item::get_required_stones()
