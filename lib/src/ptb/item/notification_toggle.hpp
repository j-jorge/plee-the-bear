/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A toggle that sends notification when it is activated.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_NOTIFICATION_TOGGLE_HPP__
#define __PTB_NOTIFICATION_TOGGLE_HPP__

#include "engine/item_brick/item_with_toggle.hpp"
#include "engine/base_item.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A toggle that sends a notification when it is activated.
   *
   * The custom fields of this class are:
   * - text (string), the text of the notification(default=none),
   * - picture filename (string), the picture filename (default=none),
   * - picture name (string), the picture name (default=none)
   * - any field supported by the parent class.
   *
   * \author Sebastien Angibaud
   */
  class notification_toggle:
    public bear::engine::item_with_toggle
    < bear::engine::base_item >
  {
    DECLARE_BASE_ITEM(notification_toggle);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::item_with_toggle
    < bear::engine::base_item > super;

  public:
    notification_toggle();

    bool set_string_field
    ( const std::string& name, const std::string& value );

  protected:
    void on_toggle_on(bear::engine::base_item *activator);

  private:
    /** \brief The text of the notification. */
    std::string m_text;

    /** \brief The picture filename; */
    std::string m_picture_filename;

    /** \brief The picture name; */
    std::string m_picture_name;
  }; // class notification_toggle
} // namespace ptb

#endif // __PTB_NOTIFICATION_TOGGLE_HPP__
