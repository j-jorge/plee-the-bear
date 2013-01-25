/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A toggle that authorize or refuse an action to both players.
 * \author Julien Jorge
 */
#ifndef __PTB_AUTHORIZE_ACTION_TOGGLE_HPP__
#define __PTB_AUTHORIZE_ACTION_TOGGLE_HPP__

#include "engine/item_brick/item_with_toggle.hpp"
#include "engine/base_item.hpp"
#include "ptb/player_action.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A toggle that authorize or refuse an action to both players.
   *
   * The custom fields of this class are:
   * - action (string, required), the name of the action ,
   * - value (bool), the state of the action (default=true),
   * - any field supported by the parent class.
   *
   * \author Sébastien Angibaud
   */
  class authorize_action_toggle:
    public bear::engine::item_with_toggle
  < bear::engine::base_item >
  {
    DECLARE_BASE_ITEM(authorize_action_toggle);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::item_with_toggle
    < bear::engine::base_item > super;

  public:
    authorize_action_toggle();

    bool set_string_field( const std::string& name, const std::string& value );
    bool set_bool_field( const std::string& name, bool value );

  private:
    void on_toggle_on(bear::engine::base_item *activator);

  private:
    /** \brief Indicates if the action is authorized. */
    bool m_value;

    /** \brief The action to set. */
    player_action::value_type m_action;
  }; // class authorize_action_toggle
} // namespace ptb

#endif // __PTB_AUTHORIZE_ACTION_TOGGLE_HPP__
