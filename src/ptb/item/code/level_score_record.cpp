/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::level_score_record class.
 * \author Julien Jorge
 */
#include "ptb/item/level_score_record.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/message/score_message.hpp"

#include "engine/game.hpp"
#include "engine/level.hpp"
#include "engine/level_globals.hpp"
#include "engine/system/game_filesystem.hpp"
#include "engine/item_brick/with_linear_expression_creation.hpp"

BASE_ITEM_EXPORT(level_score_record, ptb)

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::level_score_record::level_score_record()
: m_score_format("%v"), m_maximize_score(true), m_gold(0), m_silver(0),
  m_bronze(0)
{

} // level_score_record::level_score_record()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the item.
 */
void ptb::level_score_record::build()
{
  super::build();

  const bear::engine::game& g( bear::engine::game::get_instance() );

  const std::string filename
    ( g.get_game_filesystem().get_custom_config_file_name
      ( get_level().get_name() ) );

  m_score_table.load( filename );

  m_score_table.set_gold_medal( m_gold );
  m_score_table.set_silver_medal( m_silver );
  m_score_table.set_bronze_medal( m_bronze );
  m_score_table.set_score_ordering( m_maximize_score );
} // level_score_record::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type string.
 * \param name The name of the field to set.
 * \param value The value of the field.
 */
bool ptb::level_score_record::set_string_field
( const std::string& name, const std::string& value )
{
  bool result(true);

  if ( name == "level_score_record.next_level" )
    m_next_level = value;
  else if ( name == "level_score_record.windows_layer" )
    m_window_layer = value;
  else if ( name == "level_score_record.score_format" )
    m_score_format = value;
  else
    result = super::set_string_field(name, value);

  return result;
} // level_score_record::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type boolean.
 * \param name The name of the field to set.
 * \param value The value of the field.
 */
bool
ptb::level_score_record::set_bool_field( const std::string& name, bool value )
{
  bool result(true);

  if ( name == "level_score_record.maximize" )
    m_maximize_score = value;
  else
    result = super::set_bool_field(name, value);

  return result;
} // level_score_record::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the value of a field of type real.
 * \param name The name of the field to set.
 * \param value The value of the field.
 */
bool ptb::level_score_record::set_real_field
( const std::string& name, double value )
{
  bool result(true);

  if ( name == "level_score_record.medal.gold" )
    m_gold = value;
  else if ( name == "level_score_record.medal.silver" )
    m_silver = value;
  else if ( name == "level_score_record.medal.bronze" )
    m_bronze = value;
  else
    result = super::set_real_field(name, value);

  return result;
} // level_score_record::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Function called when the toggle is activated.
 * \param activator The activator of the toggle.
 */
void ptb::level_score_record::on_toggle_on(bear::engine::base_item *activator)
{
  const double value = m_value.evaluate();
  const std::string medal( m_score_table.get_medal_name( value ) );

  score_message msg
    ( m_score_table, value, medal, m_score_format,
      game_variables::get_string_default(m_next_level) );
  get_level_globals().send_message
    ( game_variables::get_string_default(m_window_layer), msg );
} // level_score_record::on_toggle_on()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the expression.
 * \param e The expression to assign to the item.
 */
void ptb::level_score_record::do_set_expression
( const bear::expr::linear_expression& e )
{
  m_value = e;
} // level_score_record::do_set_expression()
