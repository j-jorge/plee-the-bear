/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief This class adds the layers for the graphical user interface in the
 *        current level.
 * \author Julien Jorge
 */
#ifndef __PTB_ADD_INGAME_LAYERS_HPP__
#define __PTB_ADD_INGAME_LAYERS_HPP__

#include "engine/base_item.hpp"
#include "engine/layer/gui_layer.hpp"

#include "generic_items/timer.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief This class adds the layers for the graphical user interface in the
   *        current level.
   *
   * The custom fields of this class are
   * - show_introduction (boolean) tell if we must show the introduction of
   *   the level (with the level name and the act number) (default=true),
   * - status_layer.timer (bear::timer), the timer of the level, shown in the
   *   status layer (default = none).
   *
   * \author Julien Jorge
   */
  class add_ingame_layers:
    public bear::engine::base_item
  {
    DECLARE_BASE_ITEM(add_ingame_layers);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::base_item super;

  public:
    add_ingame_layers();

    void pre_cache();
    void build();

    bool set_bool_field( const std::string& name, bool value );
    bool set_animation_field
    ( const std::string& name, const bear::visual::animation& value );
    bool set_item_field
    ( const std::string& name, bear::engine::base_item* value );

  private:
    /** \brief Tell if we must show the introduction of the level. */
    bool m_add_starting_effect;

    /** \brief The timer of the level, shown in the status layer. */
    bear::timer* m_timer;

    /** \brief The animation for the corrupting bonus, displayed in the status
        layer. */
    bear::visual::animation m_corrupting_animation;

  }; // class add_ingame_layers
} // namespace ptb

#endif // __PTB_ADD_INGAME_LAYERS_HPP__
