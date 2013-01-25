/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The player_action message is used to inform all clients 
 * that a player do an action.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_PLAYER_ACTION_MESSAGE_HPP__
#define __PTB_PLAYER_ACTION_MESSAGE_HPP__

#include "ptb/player_pending_action.hpp"
#include "net/message/message.hpp"

#include "engine/network/message/message_export.hpp"

#include "engine/class_export.hpp"

namespace ptb
{
  /**
   * \brief The player_action message is used to inform all clients
   * that a player do an action.
   * 
   * \author Sebastien Angibaud
   */
  class player_action_message:
    public bear::net::message
  {
    DECLARE_MESSAGE(player_action_message);

  public:
    player_action_message();
    explicit player_action_message( const player_pending_action& a );
    
    const player_pending_action& get_action() const;

  private:
    virtual std::ostream& formatted_output( std::ostream& os ) const;
    virtual std::istream& formatted_input( std::istream& is );
    
  private:
    /** \brief The pending action associated at the message. */
    player_pending_action m_pending_action;
  }; // class player_action_message
} // namespace ptb

#endif // __PTB_PLAYER_ACTION_MESSAGE_HPP__
