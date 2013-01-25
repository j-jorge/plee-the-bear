/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::air_fire_water_stone class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/stone/air_fire_water_stone.hpp"

#include "ptb/item/stone/air_stone.hpp"
#include "ptb/item/stone/fire_stone.hpp"
#include "ptb/item/stone/water_stone.hpp"

#include "ptb/reference_point/attack_point_reference_point.hpp"

#include "engine/layer/layer.hpp"
#include "engine/world.hpp"

#include "universe/forced_movement/forced_aiming.hpp"

/*----------------------------------------------------------------------------*/
const double ptb::air_fire_water_stone::s_view_distance = 300;

BASE_ITEM_IMPLEMENT( air_fire_water_stone, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::air_fire_water_stone::air_fire_water_stone()
  : m_enemy_found(false)
{
  m_offensive_coefficients[air_attack] = 1;
  m_offensive_coefficients[fire_attack] = 1;
  m_offensive_coefficients[water_attack] = 1;
} // air_fire_water_stone::air_fire_water_stone()

/*---------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::air_fire_water_stone::on_enters_layer()
{
  super::on_enters_layer();
  set_width(32);
  set_height(32);
  set_model_actor
    ( get_level_globals().get_model("model/stones/air_fire_water_stone.cm") );
  start_model_action("attack");
  m_last_position = get_center_of_mass();
  m_idle_iterations = 0;
} // air_fire_water_stone::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::air_fire_water_stone::progress
( bear::universe::time_type elapsed_time )
{
  if ( has_contact() )
    kill();
  else
    {
      if ( !m_enemy_found )
        {
          rotate();
          search_enemy();
        }

      default_progress( elapsed_time );

      if ( has_forced_movement() &&
           ( m_last_position == get_center_of_mass() ) )
        {
          ++m_idle_iterations;
          if (m_idle_iterations > 1)
            {
              clear_forced_movement();
              m_enemy_found = false;
              m_idle_iterations = 0;
            }
        }
      else
        m_idle_iterations = 0;

      m_last_position = get_center_of_mass();
    }
} // air_fire_water_stone::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Kill the item.
 */
void ptb::air_fire_water_stone::kill()
{
  blast();

  super::kill();
} // air_fire_water_stone::kill()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the stone has the air power.
 */
bool ptb::air_fire_water_stone::has_air_power() const
{
  return true;
} // air_fire_water_stone::has_air_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the stone has the fire power.
 */
bool ptb::air_fire_water_stone::has_fire_power() const
{
  return true;
} // air_fire_water_stone::has_fire_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the stone has the water power.
 */
bool ptb::air_fire_water_stone::has_water_power() const
{
  return true;
} // air_fire_water_stone::has_water_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief The stone blast and create three different stones.
 */
void ptb::air_fire_water_stone::blast()
{
  bear::universe::speed_type speed1(-300, 1000);
  bear::universe::speed_type speed2(0, 1200);
  bear::universe::speed_type speed3(300, 1000);

  if ( has_top_contact() )
    {
      speed1 = bear::universe::speed_type(-500, 0);
      speed2 = bear::universe::speed_type(0, 0);
      speed3 = bear::universe::speed_type(500, 0);
    }
  else if ( has_right_contact() )
    {
      speed1 = bear::universe::speed_type(-300, 1300);
      speed2 = bear::universe::speed_type(-400, 600);
      speed3 = bear::universe::speed_type(-300, -200);
    }
  else if ( has_left_contact() )
    {
      speed1 = bear::universe::speed_type(300, 1300);
      speed2 = bear::universe::speed_type(400, 600);
      speed3 = bear::universe::speed_type(300, -200);
    }

  unsigned int a = (unsigned int)(3.0 * (double)rand() / RAND_MAX);
  if ( a == 0 )
    {
      create_stone(monster::water_attack, speed1 );
      create_stone(monster::fire_attack, speed2);
      create_stone(monster::air_attack, speed3);
    }
  else if ( a == 1 )
    {
      create_stone(monster::water_attack, speed2 );
      create_stone(monster::fire_attack, speed3);
      create_stone(monster::air_attack, speed1);
    }
  else
    {
      create_stone(monster::water_attack, speed3 );
      create_stone(monster::fire_attack, speed1);
      create_stone(monster::air_attack, speed2);
    }
} // air_fire_water_stone::blast()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a stone.
 * \param power The power of the stone.
 * \param speed The speed of the stone.
 */
void ptb::air_fire_water_stone::create_stone
( monster::attack_type power, bear::universe::speed_type& speed )
{
  stone* new_stone;
  if ( power == monster::water_attack )
    new_stone = new water_stone();
  else if ( power == monster::fire_attack )
    new_stone = new fire_stone();
  else if ( power == monster::air_attack )
    new_stone = new air_stone(false);
  else
    new_stone = new stone();
  new_stone->set_z_position(get_z_position());
  new_stone->set_top_left( get_top_left() );
  new_stone->set_monster_type(get_monster_type());
  new_stone->set_monster_index(get_monster_index());
  new_stone->set_speed(speed);
  
  new_item( *new_stone );

  new_stone->set_counted_state(false);
} // create_stone()

/*---------------------------------------------------------------------------*/
/**
 * \brief Search an enemy around the item.
 */
void ptb::air_fire_water_stone::search_enemy()
{
  bear::universe::world::item_list items;
  if ( get_layer().has_world() )
    get_layer().get_world().pick_items_in_circle
      (items, get_center_of_mass(), s_view_distance);
  bool found = false;

  bear::universe::world::item_list::const_iterator it;
  for ( it=items.begin(); (it!=items.end()) && !found; ++it)
    {
      with_attack_point* m = dynamic_cast<with_attack_point*>(*it);

      if ( m != NULL )
        if ( m->has_attack_point() )
          {
            bool ok(true);

            monster* mo = dynamic_cast<monster*>(*it);
            if ( mo != NULL )
              ok = mo->is_vulnerable(*this);

            if ( ok )
            {
              found = true;
              m_enemy_found = true;
              bear::universe::forced_aiming movement;

              movement.set_max_angle( 0.05 );
              movement.set_max_speed( 400 );

              movement.set_reference_point
                ( attack_point_reference_point(**it) );

              set_forced_movement( movement );
            }
          }
    }
} // air_fire_water_stone::search_enemy()
