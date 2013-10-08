/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing God.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_GOD_HPP__
#define __PTB_GOD_HPP__

#include "ptb/item_brick/monster_item.hpp"
#include "ptb/item_brick/item_that_speaks.hpp"
#include "engine/model.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing God.
   * \author Sebastien Angibaud
   */
  class god :
    public item_that_speaks
      < monster_item
        < bear::engine::model
          < bear::engine::base_item> > >
  {
    DECLARE_BASE_ITEM(god);

  public:
    /** \brief The type of the parent class. */
    typedef
    item_that_speaks
      < monster_item
        < bear::engine::model
          < bear::engine::base_item > > > super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  private:
    typedef void (god::*progress_function_type)(bear::universe::time_type);

  public:
    god();

    void progress( bear::universe::time_type elapsed_time );
    void pre_cache();
    void on_enters_layer();

    void launch_ball
    ( bear::universe::time_type d, bear::universe::time_type t );

  private:
    void progress_idle( bear::universe::time_type elapsed_time );
    void progress_talk( bear::universe::time_type elapsed_time );

    void start_idle();
    void start_talk();

    void do_action(const std::string& a);
    void talk(const std::vector<std::string>& speech);

    static void init_exported_methods();

  private:
    /** \brief Current progress function. */
    progress_function_type m_progress;
   }; // class god
} // namespace ptb

#endif // __PTB_GOD_HPP__
