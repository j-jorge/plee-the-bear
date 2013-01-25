/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::water_fire_stone class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/stone/water_fire_stone.hpp"

BASE_ITEM_IMPLEMENT( water_fire_stone, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::water_fire_stone::water_fire_stone()
{
  set_elasticity(1);
  m_offensive_coefficients[water_attack] = 1;
  m_iteration_without_move = 0;
} // water_fire_stone::fire_stone()

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::water_fire_stone::on_enters_layer()
{
  super::on_enters_layer();
  m_last_position = get_bottom_left();
  set_model_actor
    (get_level_globals().get_model("model/stones/water_fire_stone.cm"));
  start_model_action("attack");
} // water_fire_stone::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::water_fire_stone::progress( bear::universe::time_type elapsed_time )
{
  if ( ( has_contact() && ( m_iteration_without_move >= 8 ) ) ||
       has_middle_contact() )
    kill();
  else
    {
      if ( ( std::abs(m_last_position.x - get_left()) <= 1 ) &&
           ( std::abs(m_last_position.y - get_bottom()) <= 1 ) )
        ++m_iteration_without_move;
      else
        m_iteration_without_move = 0;

      m_last_position = get_bottom_left();
      progress_fire_stone( elapsed_time );
    }
} // water_fire__stone::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the stone has the water power.
 */
bool ptb::water_fire_stone::has_water_power() const
{
  return true;
} // water_fire_stone::has_water_power()
