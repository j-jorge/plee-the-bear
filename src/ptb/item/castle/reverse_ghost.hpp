/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a ghost that reverse controls.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_REVERSE_GHOST_HPP__
#define __PTB_REVERSE_GHOST_HPP__

#include "ptb/item/castle/ghost.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a ghost that reverses controls.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class reverse_ghost:
    public ghost
  {
    DECLARE_BASE_ITEM(reverse_ghost);

  public:
    /** \brief The type of the parent class. */
    typedef ghost super;

  private:
    typedef void
    (reverse_ghost::*progress_function_type)(bear::universe::time_type);

  public:
    reverse_ghost();
    ~reverse_ghost();

    void pre_cache();
    void on_enters_layer();
    bool set_string_field( const std::string& name, const std::string& value );
    bool is_valid() const;

  protected:
    void control_player();
    void release_player();

  private:
    /** \brief One of both changed action. */
    player_action::value_type m_first_action;

    /** \brief One of both changed action. */
    player_action::value_type m_second_action;
  }; // class reverse_ghost
} // namespace ptb

#endif // __PTB_REVERSE_GHOST_HPP__
