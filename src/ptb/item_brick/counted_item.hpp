/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing an item that is counted.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_COUNTED_ITEM_HPP__
#define __PTB_COUNTED_ITEM_HPP__

#include "visual/sprite.hpp"

#include <string>

namespace ptb
{
  /**
   * \brief The class describing an item that is counted.
   *
   * \b Template \b arguments :
   *  - \a Base the base class of the model, should end by
   *    bear::engine::base_item.
   *
   * \author Sébastien Angibaud
   */
  template<class Base>
  class counted_item :
    public Base
  {
  public:
    /** \brief The type of the parent class. */
    typedef Base super;
    
  public:
    counted_item();
    
    void on_enters_layer();
    bool set_bool_field( const std::string& name, bool value );
    void count_me(unsigned int index);
    void destroy();    
    
  private:
    unsigned int get_total_count() const;
    unsigned int get_found_count() const;
    bool check_created_bonus_item() const;
    void create_bonus_item();
    
    virtual std::string get_picture_filename() const = 0;
    virtual std::string get_picture_name() const = 0;
    virtual std::string get_notification_text() const = 0;
    virtual unsigned int get_points() const = 0;

  private:
    /** \brief Indicates if the item must be added in carnage counter. */
    bool m_bonus_item;

    /** \brief Indicates if the item has been counted. */
    bool m_is_counted;

    /** \brief Indicates if the item must be counted when it dies. */
    bool m_counted_when_dying;
  }; // class counted_item
} // namespace ptb

#include "ptb/item_brick/impl/counted_item.tpp"

#endif // __PTB_COUNTED_ITEM_HPP__
