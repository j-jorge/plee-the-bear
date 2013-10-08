/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::bonus_time_record class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/bonus_points/bonus_time_record.hpp"

#include "ptb/message/status_layer_notification_message.hpp"
#include "ptb/level_variables.hpp"
#include "ptb/defines.hpp"

#include "engine/level_globals.hpp"

#include "expr/linear_function.hpp"

#include <libintl.h>

BASE_ITEM_EXPORT( bonus_time_record, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::bonus_time_record::bonus_time_record()
  : super("Rocket bonus", 10000), m_timer(NULL), m_time_record(0)
{
  set_picture_filename("gfx/ui/bonus-icons/bonus-icons.png");
  set_picture_name("time");
} // bonus_time_record::bonus_time_record()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is valid.
 */
bool ptb::bonus_time_record::is_valid() const
{
  return (m_timer != (bear::timer*)NULL) && super::is_valid();
} // bonus_time_record::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::bonus_time_record::build()
{
  super::build();

  set_condition
    ( ( bear::expr::linear_function_maker
        ( m_timer, std::mem_fun_ref(&bear::timer::get_loops) ) == 0 )
      && ( bear::expr::linear_function_maker
           ( m_timer, std::mem_fun_ref(&bear::timer::get_elapsed_time) )
           <= m_time_record ) );
} // bonus_time_record::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "item".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::bonus_time_record::set_item_field
( const std::string& name, bear::engine::base_item* value )
{
  bool result(true);

  if ( name == "bonus_time_record.level_timer" )
    m_timer = value;
  else
    result = super::set_item_field( name, value );

  return result;
} // bonus_time_record::set_item_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c real.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::bonus_time_record::set_real_field
( const std::string& name, double value )
{
  bool result = true;

  if (name == "bonus_time_record.time_record")
    m_time_record = value;
  else
    result = super::set_real_field(name, value);

  return result;
} // bonus_time_record::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Fonction tell when the bonus give points.
 */
void ptb::bonus_time_record::on_give_points() const
{
  status_layer_notification_message msg;

  bear::visual::sprite sp;
  
  if ( ( ! get_picture_filename().empty() ) && 
       ( ! get_picture_name().empty() ) ) 
    sp = get_level_globals().auto_sprite
      ( get_picture_filename(), get_picture_name());
  msg.set_notification( 0, sp, get_name());

  get_level_globals().send_message
    ( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
} // bonus_time_record::on_give_points()
