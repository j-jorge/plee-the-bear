/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::air_water_stone class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/stone/air_water_stone.hpp"

BASE_ITEM_IMPLEMENT( air_water_stone, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
  ptb::air_water_stone::air_water_stone()
{
  set_elasticity(1);
  set_density(0.7);
  m_iteration_without_move = 0;
  m_offensive_coefficients[water_attack] = 1;
  m_offensive_coefficients[air_attack] = 1;
} // air_water_stone::air_water_stone()

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::air_water_stone::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor
    (get_level_globals().get_model("model/stones/air_water_stone.cm"));
  start_model_action("attack");

  m_last_position = get_bottom_left();
} // air_water_stone::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::air_water_stone::progress( bear::universe::time_type elapsed_time )
{
  if ( ( has_contact() && ( m_iteration_without_move >= 8 ) ) ||
       has_middle_contact() ||
       ( is_in_environment(bear::universe::water_environment) &&
         !is_only_in_environment(bear::universe::water_environment) &&
         get_current_action_name() != "blast") )
    start_model_action("blast");
  else
    {
      if ( ( std::abs(m_last_position.x - get_left()) <= 1 ) &&
           ( std::abs(m_last_position.y - get_bottom()) <= 1 ) )
        ++m_iteration_without_move;
      else
        m_iteration_without_move = 0;

      m_last_position = get_bottom_left();
      rotate();

      default_progress( elapsed_time );
    }
} // air_water_stone::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform that a new stone is create.
 */
void ptb::air_water_stone::inform_new_stone()
{
  start_model_action("blast");
} // air_water_stone::inform_new_stone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the stone has the water power.
 */
bool ptb::air_water_stone::has_water_power() const
{
  return true;
} // air_water_stone::has_water_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create decorations when the stone blasts.
 */
void ptb::air_water_stone::create_decorations()
{
  // No decorations for this stone.
} // air_water_stone::create_decorations

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of the intensity.
 */
void ptb::air_water_stone::initialize_intensity()
{
  // no initialization for this stone
} // air_water_stone::initialize_intensity()
