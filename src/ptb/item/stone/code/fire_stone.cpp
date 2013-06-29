/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::fire_stone class.
 * \author S�bastien Angibaud
 */
#include "ptb/item/stone/fire_stone.hpp"
#include "engine/world.hpp"
#include "generic_items/decorative_item.hpp"

BASE_ITEM_IMPLEMENT( fire_stone, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::fire_stone::fire_stone()
  : m_is_extinct(false)
{
  m_invincible = true;
  m_offensive_coefficients[fire_attack] = 1;
} // fire_stone::fire_stone()

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::fire_stone::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor(get_level_globals().get_model("model/stones/fire_stone.cm"));
  start_model_action("attack");
} // fire_stone::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::fire_stone::progress( bear::universe::time_type elapsed_time )
{
  if ( has_contact() )
    kill();
  else
    progress_fire_stone(elapsed_time);
} // fire_stone::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the stone has the fire power.
 */
bool ptb::fire_stone::has_fire_power() const
{
  return true;
} // fire_stone::has_fire_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief The item has attacked.
 * \param other The monster that is attacked.
 */
void ptb::fire_stone::has_attacked(const monster& other)
{
  // this stone goes through enemies : don't kill
  check_traitor(other);  

  m_lost = false;
} // fire_stone::has_attacked()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item that he have no energy now.
 * \param attacker The attacker monster.
 */
void ptb::fire_stone::inform_no_energy(const monster& attacker)
{
  // this stone goes through enemies
} // fire_stone::inform_no_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a decoration of smoke.
 * \param anim The animation of the smoke.
 */
void ptb::fire_stone::create_smoke(const bear::visual::animation& anim)
{
   bear::decorative_item* item = new bear::decorative_item;

   item->set_animation(anim);
   item->get_rendering_attributes().set_angle(get_visual_angle());
   item->set_kill_when_finished(true);
   item->set_z_position(get_z_position()-1);
   unsigned int gap_x = (unsigned int)( 16.0 * rand() / RAND_MAX);
   unsigned int gap_y = (unsigned int)( 16.0 * rand() / RAND_MAX);
   item->set_gap(-8+gap_x, -8+gap_y);

   new_item( *item );

   item->set_center_of_mass(get_center_of_mass());

   CLAW_ASSERT( item->is_valid(),
                "The smoke of fire_stone isn't correctly initialized" );
} // fire_stone::create_smoke()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration of the stone .
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::fire_stone::progress_fire_stone
( bear::universe::time_type elapsed_time )
{
  if ( !m_is_extinct )
    {
      if ( is_in_environment(bear::universe::water_environment) )
        {
          m_is_extinct = true;
          start_model_action("extinct");

          bear::visual::animation anim
            ( get_level_globals().get_animation("animation/steam.canim") );
          double a = (1.0 * rand() / RAND_MAX);
          anim.set_intensity(a, a, a);
          anim.set_opacity(0.6);
          create_smoke(anim);
        }
      else
        {
          m_last_smoke += elapsed_time;
          if ( m_last_smoke >= 0.025 )
            {
              bear::visual::animation anim
                ( get_level_globals().get_animation("animation/steam.canim") );
              double a = (1.0 * rand() / RAND_MAX);
              anim.set_intensity(a, a, a);
              anim.set_opacity(0.6);
              create_smoke(anim);
              m_last_smoke = 0;
            }
        }
    }

  rotate();
  default_progress(elapsed_time);
} // fire_stone::progress_fire_stone()
