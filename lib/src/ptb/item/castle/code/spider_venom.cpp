/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::spider_venom class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/castle/spider_venom.hpp"

#include "engine/game.hpp"
#include "engine/world.hpp"
#include "generic_items/decorative_item.hpp"

BASE_ITEM_IMPLEMENT( spider_venom, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::spider_venom::spider_venom()
  : m_is_dead(false), m_is_main_venom(false)
{
  m_monster_type = monster::enemy_monster;
  m_energy = s_spider_venom_energy;

  m_defensive_powers[normal_attack] = true;
  m_offensive_coefficients[indefensible_attack] = 1;
  set_mass(10);

  set_system_angle_as_visual_angle(true);
} // spider_venom::spider_venom()

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::spider_venom::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor(get_level_globals().get_model("model/castle/venom.cm"));

  if ( m_is_main_venom )
    {
      m_offensive_force = s_spider_venom_offensive_force;
      start_model_action("venom");
    }
  else
    {
      m_offensive_force = s_spider_venom_offensive_force / 2;
      start_model_action("drop");
    }
} // spider_venom::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::spider_venom::progress( bear::universe::time_type elapsed_time )
{
  if ( m_is_dead )
    {
      if ( m_is_main_venom)
        {
          create_venom
            ( bear::universe::force_type
              (rand()%200000 + 300000, rand()%200000 + 300000));
          create_venom
            ( bear::universe::force_type
              (- (rand()%200000 + 300000), rand()%200000 + 300000));
          create_venom
            ( bear::universe::force_type
              (100000 - rand()%200000, rand()%200000 + 400000));
        }
      kill();
    }
  else if ( has_contact() )
    {
      if ( !m_is_dead && has_bottom_contact())
        create_splash();
      m_is_dead = true;
    }
  else
    super::progress( elapsed_time );
} // spider_venom::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell that venom is a main venom (created by spider).
 */
void ptb::spider_venom::is_main_venom()
{
  m_is_main_venom = true;
} // spider_venom::is_main_venom()

/*----------------------------------------------------------------------------*/
/**
 * \brief The item has attacked.
 * \param other The monster that is attacked.
 */
void ptb::spider_venom::has_attacked(const monster& other)
{
  m_is_dead = true;
} // spider_venom::has_attacked()

/*---------------------------------------------------------------------------*/
/**
 * \brief Inform the item tat he left the active region.
 */
void ptb::spider_venom::leaves_active_region()
{
  super::leaves_active_region();

  kill();
} // spider_venom::leaves_active_region()

/*---------------------------------------------------------------------------*/
/**
 * \brief Create splash decoration.
 */
void ptb::spider_venom::create_splash()
{
  bear::decorative_item* item = new bear::decorative_item;

  item->set_animation( get_level_globals().get_animation
                       ("animation/castle/spider/venom-splash.canim") );
  item->set_bottom_left(get_bottom_left());
  item->set_system_angle(get_system_angle());
  item->set_system_angle_as_visual_angle(true);

  item->set_kill_when_finished(true);

  new_item( *item );

  CLAW_ASSERT( item->is_valid(),
               "The splash of venom isn't correctly initialized" );
} // spider_venom::create_splash()

/*---------------------------------------------------------------------------*/
/**
 * \brief Create a new venom.
 * \param f The force to give at the created venom.
 */
void ptb::spider_venom::create_venom(const bear::universe::force_type& f)
{
  spider_venom* new_spider_venom = new spider_venom;

  CLAW_ASSERT
    (new_spider_venom->is_valid(),
     "The spider_venom created by spider_venom isn't correctly initialized" );

  new_item( *new_spider_venom );

  new_spider_venom->add_internal_force(f);
  new_spider_venom->set_center_of_mass(get_center_of_mass());
  new_spider_venom->set_z_position( get_z_position() );
} // spider_venom::create_venom()
