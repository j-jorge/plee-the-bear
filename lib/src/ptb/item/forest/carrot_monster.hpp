/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a carrot monster.
 * \author S�bastien Angibaud
 */
#ifndef __PTB_CARROT_MONSTER_HPP__
#define __PTB_CARROT_MONSTER_HPP__

#include "engine/base_item.hpp"
#include "ptb/item_brick/monster_item.hpp"
#include "engine/model.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a carrot monster.
   * \author S�bastien Angibaud
   */
  class carrot_monster:
    public monster_item< bear::engine::model<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(carrot_monster);

  public:
    /** \brief The type of the parent class. */
    typedef monster_item< bear::engine::model<bear::engine::base_item> > super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  private:
    /** \brief The type of the functions used to do the progression of the
        item. */
    typedef void
    (carrot_monster::*progress_function_type)(bear::universe::time_type);

  public:
    carrot_monster();

    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );

    void leaves_active_region();
    bool has_attack_point() const;

  private:
    void start_attack();
    void start_crush();
    void progress_attack( bear::universe::time_type elapsed_time );

    static void init_exported_methods();

  private:
    /** \brief Current progress function. */
    progress_function_type m_progress;

  }; // class carrot_monster
} // namespace ptb

#endif // __PTB_CARROT_MONSTER_HPP__
