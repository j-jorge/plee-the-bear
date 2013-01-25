/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::player_action_message class.
 * \author Sebastien Angibaud
 */
#include "ptb/network/message/player_action_message.hpp"

#include <iostream>

MESSAGE_EXPORT( player_action_message, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::player_action_message::player_action_message()
{

} // player_action_message::player_action_message()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param a The pendin action associated with the message.
 */
ptb::player_action_message::player_action_message
( const player_pending_action& a )
  : m_pending_action(a)
{

} // player_action_message::player_action_message()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the pending action.
 */
const ptb::player_pending_action& 
ptb::player_action_message::get_action() const
{
  return m_pending_action;
} // player_action_message::get_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Write a formatted representation of this message in a stream.
 * \param os The stream in which we write.
 */
std::ostream&
ptb::player_action_message::formatted_output( std::ostream& os ) const
{
  return os << m_pending_action.to_string();
} // player_action_message::formatted_output()

/*----------------------------------------------------------------------------*/
/**
 * \brief Read a formatted representation of this message from a stream.
 * \param is The stream from which we read.
 */
std::istream& ptb::player_action_message::formatted_input( std::istream& is )
{
  std::string str;

  is >> str;
  m_pending_action = player_pending_action(str);

  return is;
} // player_action_message::formatted_input()
