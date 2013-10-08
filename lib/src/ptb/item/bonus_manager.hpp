/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A toggle that updates level bonus objects.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_BONUS_MANAGER_HPP__
#define __PTB_BONUS_MANAGER_HPP__

#include "engine/item_brick/item_with_toggle.hpp"
#include "engine/base_item.hpp"
#include "universe/derived_item_handle.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A toggle that updates level bonus objects.
   *
   * The custom fields of this class are:
   * - any field supported by the parent class.
   *
   * \author Sebastien Angibaud
   */
  class bonus_manager:
    public bear::engine::item_with_toggle
    < bear::engine::base_item >
  {
    DECLARE_BASE_ITEM(bonus_manager);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::item_with_toggle
    < bear::engine::base_item > super;

  public:
    bonus_manager();
    ~bonus_manager();
    void manage(bool update_bonus = true);

  private:
    void on_toggle_on(bear::engine::base_item *activator);
    void save_game_variables() const;
  }; // class bonus_manager
} // namespace ptb

#endif // __PTB_BONUS_MANAGER_HPP__
