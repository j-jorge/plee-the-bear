/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::counted_item class.
 * \author Sébastien Angibaud
 */

#include "ptb/message/status_layer_notification_message.hpp"
#include "ptb/defines.hpp"
#include "ptb/item/bonus_points/bonus_points.hpp"

#include "engine/variable/variable.hpp"
#include "engine/level.hpp"

#include "engine/function/linear_level_variable_getter.hpp"
#include "expr/linear_constant.hpp"

#include <sstream>
#include <libintl.h>

/*----------------------------------------------------------------------------*/
/**
 * Constructor.
 */
template<class Base>
ptb::counted_item<Base>::counted_item()
  : m_bonus_item(true), m_is_counted(false), m_counted_when_dying(false)
{
  
} // counted_item::counted_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
template<class Base>
void ptb::counted_item<Base>::on_enters_layer()
{
  super::on_enters_layer();

  if ( m_bonus_item )
    {
      this->get_level().set_level_variable 
	( bear::engine::variable<unsigned int>
	  ( "counter/total/" + get_notification_text(), get_total_count()+1 ));
      
      if ( ! check_created_bonus_item() )
	create_bonus_item();
    }
} // counted_item::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c bool.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
template<class Base>
bool ptb::counted_item<Base>::set_bool_field
( const std::string& name, bool value )
{
  bool ok = true;

  if (name == "counted_item.bonus_item")
    m_bonus_item = value;
  else if (name == "counted_item.counted_when_dying")
    m_counted_when_dying = value;
  else  
    ok = super::set_bool_field(name, value);

  return ok;
} // counnted_item::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * Count the item.
 * \param index of the player that finds the item.
 */
template<class Base>
void ptb::counted_item<Base>::count_me(unsigned int index)
{
  if ( m_bonus_item )
    {
      m_is_counted = true;
      this->get_level().set_level_variable
	( bear::engine::variable<unsigned int>
	  ( "counter/found/" + get_notification_text(), get_found_count()+1 ));
      
      std::ostringstream oss;
      oss << gettext(get_notification_text().c_str()) << " " 
	  << get_found_count() << "/" << get_total_count();
      
      status_layer_notification_message msg;
      std::string picture_filename(get_picture_filename());
      std::string picture_name(get_picture_name());
      bear::visual::sprite sp;
      if ( ( ! picture_filename.empty() ) && ( ! picture_name.empty() ) ) 
	sp = this->get_level_globals().auto_sprite
	  ( picture_filename, picture_name );
      
      msg.set_notification( index, sp, oss.str());
      
      this->get_level_globals().send_message
	( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
    }
} // counted_item::count_me()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destroy the item. This method is called automatically when the item
 *        is killed.
 * \pre The item has been added in a layer.
 */
template<class Base>
void ptb::counted_item<Base>::destroy()
{
  if ( m_bonus_item && ( ! m_is_counted ) && ( ! m_counted_when_dying ) )
    {
      m_is_counted = true;

      this->get_level().set_level_variable 
	( bear::engine::variable<unsigned int>
	  ( "counter/total/" + get_notification_text(), get_total_count()-1 ));
    }

  super::destroy();
} // counted_item::destroy()

/*----------------------------------------------------------------------------*/
/**
 * Return the total count.
 */
template<class Base>
unsigned int ptb::counted_item<Base>::get_total_count() const
{
   bear::engine::variable<unsigned int> var
     ("counter/total/" + get_notification_text());
   
   if ( this->get_level().level_variable_exists(var) )
   {
      this->get_level().get_level_variable(var);
      return var.get_value();
   }
   else
      return 0;
} // counted_item::get_total_count()

/*----------------------------------------------------------------------------*/
/**
 * Return the found count.
 */
template<class Base>
unsigned int ptb::counted_item<Base>::get_found_count() const
{
   bear::engine::variable<unsigned int> var
     ("counter/found/" + get_notification_text());
   
   if ( this->get_level().level_variable_exists(var) )
   {
      this->get_level().get_level_variable(var);
      return var.get_value();
   }
   else
      return 0;
} // counted_item::get_found_count()

/*----------------------------------------------------------------------------*/
/**
 * Return Check if the associated bonus item has been created.
 */
template<class Base>
bool ptb::counted_item<Base>::check_created_bonus_item() const
{
  bear::engine::variable<bool> var
    ("counter/bonus_item/" + get_notification_text());
  
  if ( this->get_level().level_variable_exists(var) )
    {
      this->get_level().get_level_variable(var);
      return var.get_value();
    }
  else
    return false;
} // counted_item::check_created_bonus_item()

/*----------------------------------------------------------------------------*/
/**
 * Return Create the associated bonus item.
 */
template<class Base>
void ptb::counted_item<Base>::create_bonus_item()
{
  this->get_level().set_level_variable
    ( bear::engine::variable<bool>
      ( "counter/bonus_item/" + get_notification_text(), true ) );

  bonus_points* new_bonus = new bonus_points(get_notification_text(),3000);
  new_bonus->set_center_of_mass(this->get_center_of_mass());
  new_bonus->set_picture_filename(get_picture_filename());
  new_bonus->set_picture_name(get_picture_name());

  new_bonus->set_condition
    ( bear::engine::linear_level_variable_getter<unsigned int>
      ( &(this->get_level()), 
	"counter/found/" + get_notification_text() ) == 
      bear::engine::linear_level_variable_getter<unsigned int>
      ( &(this->get_level()), "counter/total/" + get_notification_text() ));
  
  CLAW_ASSERT(new_bonus->is_valid(),
	      "Bonus created by counted_item isn't correctly initialized" );
  
  this->new_item( *new_bonus );
} // counted_item::create_bonus_item()
