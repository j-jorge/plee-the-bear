/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A item that Plee can throw.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_THROWABLE_ITEM_HPP__
#define __PTB_THROWABLE_ITEM_HPP__

#include "engine/base_item.hpp"

namespace ptb
{
  /**
   * \brief An item that player can throw.
   *
   * \author Sebastien Angibaud
   */
  class throwable_item
  {
  public:
    explicit throwable_item
    ( const std::string& name, bool always_visible = false );
    virtual ~throwable_item();

    virtual bool can_throw() const;
    bool is_empty() const;
    const std::string& get_name() const;

    virtual bear::engine::base_item* create_throwable_item() const = 0;
    virtual void decrease_stock() const = 0;
    virtual unsigned int get_stock() const = 0;
    virtual std::string get_animation() const = 0;

  private:
    /** \brief The name of the throwable_item. */
    std::string m_name;

    /** \brief Indicates if the throwable_item appears with no stock. */
    bool m_always_visible;

  }; // class throwable_item
} // namespace ptb

#endif // __PTB_THROWABLE_ITEM_HPP__
