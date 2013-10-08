/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a stone.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_STONE_HPP__
#define __PTB_STONE_HPP__

#include "ptb/item_brick/monster_item.hpp"
#include "engine/model.hpp"
#include "engine/base_item.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a stone.
   * \author Sébastien Angibaud
   */
  class stone:
    public monster_item< bear::engine::model<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(stone);

  public:
    /** \brief The type of the parent class. */
    typedef monster_item< bear::engine::model<bear::engine::base_item> > super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  public:
    stone();

    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );
    virtual void has_attacked(const monster& other);
    void has_attacked();
    void leaves_active_region();
    virtual void inform_no_energy(const monster& attacker);
    virtual void kill();
    virtual void inform_new_stone();

    virtual bool has_air_power() const;
    virtual bool has_fire_power() const;
    virtual bool has_water_power() const;
    void set_counted_state(bool value);

  protected:
    void check_traitor(const monster& other);
    void rotate();
    void default_progress( bear::universe::time_type elapsed_time );
  
  private:
    void create_hit_star( const bear::engine::base_item& that ) const;
    void create_bubble();
    void send_notification(const std::string& text) const;
  
  private:
    static void init_exported_methods();

  protected:
    /** \brief Indicates if stone has lost. */
    bool m_lost;

    /** \brief Indicates if stone must be counted. */
    bool m_counted;

    /** \brief The number of lost stones. */
    static int s_lost_stone_count;
  }; // class stone
} // namespace ptb

#endif // __PTB_STONE_HPP__
