/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::status_layer_boss_message class.
 * \author Sebastien Angibaud
 */
#include "ptb/message/status_layer_boss_message.hpp"

#include "ptb/layer/status_layer.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::status_layer_boss_message::status_layer_boss_message()
  : m_boss(NULL)
{

} // status_layer_boss_message::status_layer_boss_message()

/*----------------------------------------------------------------------------*/
/*
 * \brief Set the boss.
 * \param b The boss.
 */
void ptb::status_layer_boss_message::set_boss( monster* b )
{
  m_boss = b;
} // status_layer_boss_message::set_boss()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the message to the status layer.
 * \param that The status layer to apply the message to.
 */
bool ptb::status_layer_boss_message::apply_to( status_layer& that )
{
  that.set_boss(m_boss);
  return true;
} // status_layer_boss_message::apply_to()
