/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::counted_enemy class.
 * \author Sébastien Angibaud
 */

#include "ptb/level_variables.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
template<class Base>
void ptb::counted_enemy<Base>::on_enters_layer()
{
  super::on_enters_layer();
  
  level_variables::set_object_count
    ( this->get_level(), "enemy",
      level_variables::get_object_count( this->get_level(), "enemy" ) + 1);
} // counted_enemy::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * Tell that the item must be counted.
 * \param index of the player that finds the item.
 */
template<class Base>
void ptb::counted_enemy<Base>::count_me(unsigned int index)
{
  super::count_me(index);

  this->get_level().set_level_variable
    ( bear::engine::variable<unsigned int>
      ( "counter/carnage/found", get_found_enemy_count()+1 ));

  if ( get_found_enemy_count() == get_total_enemy_count() ) 
    {
      std::ostringstream oss;
      oss << gettext("Carnage") << " " 
	  << get_found_enemy_count() << "/" << get_total_enemy_count();
      
      status_layer_notification_message msg;
      bear::visual::sprite sp = this->get_level_globals().auto_sprite
	( "gfx/ui/bonus-icons/bonus-icons.png", "carnage" );
      
      msg.set_notification( index, sp, oss.str());
      
      this->get_level_globals().send_message
	( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
    }
} // counted_enemy::count_me()

/*----------------------------------------------------------------------------*/
/**
 * \brief The enemy dies.
 * \param attacker The attacker monster.
 */
template<class Base>
void ptb::counted_enemy<Base>::die(const monster& attacker)
{
  super::die(attacker);

  level_variables::set_killed_object_count
    ( this->get_level(), "enemy",
      level_variables::get_killed_object_count
      ( this->get_level(), "enemy" ) + 1);
} // counted_enemy::die()

/*----------------------------------------------------------------------------*/
/**
 * \brief Function tell when the enemy dies.
 * \param index Index of player that kills the enemy.
 */
template<class Base>
void ptb::counted_enemy<Base>::on_die(unsigned int index)
{
  super::on_die(index);
  
  this->count_me(index);
} // counted_enemy::on_die

/*----------------------------------------------------------------------------*/
/**
 * Return the total enemy count.
 */
template<class Base>
unsigned int ptb::counted_enemy<Base>::get_total_enemy_count() const
{
  return level_variables::get_object_count( this->get_level(), "enemy" );
} // counted_enemy::get_total_enemy_count()

/*----------------------------------------------------------------------------*/
/**
 * Return the found count.
 */
template<class Base>
unsigned int ptb::counted_enemy<Base>::get_found_enemy_count() const
{
   bear::engine::variable<unsigned int> var("counter/carnage/found");
   
   if ( this->get_level().level_variable_exists(var) )
   {
      this->get_level().get_level_variable(var);
      return var.get_value();
   }
   else
      return 0;
} // counted_enemy::get_found_enemy_count()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the number of points of carnage.
 */
template<class Base>
unsigned int ptb::counted_enemy<Base>::get_points() const
{
  return 5000;
} // counted_enemy::get_points()
