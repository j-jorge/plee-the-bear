/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Base class for the bosses.
 * \author Julien Jorge
 */
#ifndef __PTB_BOSS_HPP__
#define __PTB_BOSS_HPP__

#include "ptb/item_brick/monster_item.hpp"

#include "engine/item_brick/with_toggle.hpp"
#include "engine/model.hpp"
#include "engine/model/model_mark_item.hpp"
#include "engine/base_item.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief Base class for the bosses.
   *
   * The valid fields for this item are
   * - any field supported by the parent classes.
   *
   * \author Julien Jorge
   */
  class boss:
    public monster_item< bear::engine::model< bear::engine::base_item > >
  {
  public:
    /** \brief The type of the parent class. */
    typedef monster_item<
    bear::engine::model < bear::engine::base_item > > super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  private:
    /** \brief The type of the functions used to do the progression of the
        boss. */
    typedef void
    (boss::*progress_function_type)(bear::universe::time_type);

    /** \brief The type of the handle on the toggle activated when the boss is
        dead. */
    typedef
    bear::universe::derived_item_handle<bear::engine::with_toggle>
    toggle_handle;

  public:
    boss();

    void pre_cache();
    void progress( bear::universe::time_type elapsed_time );
    void on_enters_layer();

    bool set_item_field
    ( const std::string& name, bear::engine::base_item* value );

    void corrupt( double amount );

  protected:
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void inform_dead();

    void create_floating_score
    ( const std::string& p1_mark, const std::string& p2_mark ) const;
    void create_floating_score
    ( unsigned int index, const bear::universe::position_type& pos ) const;

    virtual std::string get_bonus_picture_filename() const = 0;
    virtual std::string get_bonus_picture_name() const = 0;

  private:
    void progress_energy( bear::universe::time_type elapsed_time );

    void godify( bear::universe::time_type d, bear::visual::size_type size );

    void show_energy( bear::universe::time_type d );

    static void init_exported_methods();

  private:
    /** \brief Current progress function. */
    progress_function_type m_progress;

    /** \brief The duration of the current action. */
    bear::universe::time_type m_action_duration;

    /** \brief The remaining duration of the god effect. */
    bear::universe::time_type m_godify_duration;

    /** \brief The increment of the energy, in units per seconds, at the
        beginning of the fight. */
    double m_energy_increment;

    /** \brief The item toggled when the boss is dead. */
    toggle_handle m_toggle;

    /** \brief The identifier of the music of the boss. */
    std::size_t m_music_id;

  }; // class boss
} // namespace ptb

#endif // __PTB_BOSS_HPP__
