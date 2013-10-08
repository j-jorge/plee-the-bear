/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::headstone class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/headstone.hpp"

#include "ptb/item/soul.hpp"
#include "engine/game.hpp"
#include "engine/world.hpp"
#include "universe/forced_movement/forced_tracking.hpp"

#include "engine/export.hpp"

BASE_ITEM_EXPORT( headstone, ptb )

const bear::universe::time_type ptb::headstone::s_time_to_appear = 0.5;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::headstone::headstone()
  : m_soul_has_appeared(false), m_soul_energy(0), m_time_start(0)
{
  set_size( 22, 45 );
  set_mass( 0.1 );
  set_can_move_items(false);
  set_system_angle_as_visual_angle(true);
} // headstone::headstone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::headstone::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor(get_level_globals().get_model("model/headstone.cm"));
  start_model_action("appear");
} // headstone::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::headstone::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  bear::universe::speed_type speed = get_speed();
  speed.x = 0;
  set_speed(speed);

  if ( !m_soul_has_appeared )
    {
      m_time_start += elapsed_time;

      if ( m_time_start >= s_time_to_appear )
        {
          m_soul_has_appeared = true;
          create_soul();
        }
    }
} // headstone::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool ptb::headstone::is_valid() const
{
  return m_soul_animation.is_valid() && super::is_valid();
} // headstone::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the soul energy.
 * \param energy The new soul energy.
 */
void ptb::headstone::set_soul_energy( double energy )
{
  m_soul_energy = energy;
} // headstone::set_soul_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the animation of the soul.
 * \param anim the animation of the soul.
 */
void ptb::headstone::set_soul_animation( const bear::visual::animation& anim )
{
  m_soul_animation = anim;
} // headstone::set_soul_animation()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of this state.
 */
void ptb::headstone::create_soul() const
{
  soul* new_soul = new soul;

  new_soul->set_animation(m_soul_animation);
  new_soul->set_size( m_soul_animation.get_max_size() );
  new_soul->set_bottom_middle(get_bottom_middle());
  new_soul->set_energy(m_soul_energy);
  new_soul->set_z_position(get_z_position()+1 );

  new_item( *new_soul );

  CLAW_ASSERT( new_soul->is_valid(),
               "The soul of wasp isn't correctly initialized" );
} // headstone::create_soul()
