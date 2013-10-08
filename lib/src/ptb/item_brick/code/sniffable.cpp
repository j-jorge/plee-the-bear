/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::sniffable class.
 * \author Sebastien Angibaud
 */
#include "ptb/item_brick/sniffable.hpp"
#include "ptb/message/status_layer_notification_message.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/defines.hpp"

#include "engine/level_globals.hpp"

#include <libintl.h>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::sniffable::sniffable( const std::string& category)
  : m_category(category)
{

} // sniffable::sniffable()

/*----------------------------------------------------------------------------*/
/**
 * \brief Event that occurs when the item is found.
 * \param index Index of player that finds item. 
 */
void ptb::sniffable::on_found(unsigned int index)
{
  if ( ! game_variables::get_persistent_sniffable(index, m_category ) )
    {
      game_variables::set_persistent_sniffable(index, m_category);
      send_notification(index);
    }
} // sniffable::on_found()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the category.
 * \param category The category.
 */
void ptb::sniffable::set_category( const std::string& category )
{
  m_category = category;
} // sniffable::set_category()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the category.
 */
std::string ptb::sniffable::get_category() const
{
  return m_category;
} // sniffable::get_category()

/*----------------------------------------------------------------------------*/
/**
 * \brief Send a notification on status layer.
 * \param index Index of player that finds hazelnut. 
 */
void ptb::sniffable::send_notification(unsigned int index)
{
  status_layer_notification_message msg;

  bear::visual::sprite sp;
  msg.set_notification( index, sp, gettext(m_category.c_str()));

  //get_level_globals().send_message
  //  ( PTB_STATUS_LAYER_DEFAULT_TARGET_NAME, msg );
} // sniffable::send_notification()
