/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a stone with the air power.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_AIR_STONE_HPP__
#define __PTB_AIR_STONE_HPP__

#include "ptb/player_proxy.hpp"
#include "ptb/item/stone/stone.hpp"
#include "generic_items/reference_item.hpp"

namespace ptb
{
  /**
   * \brief The class describing a stone with the air power.
   * \author Sébastien Angibaud
   */
  class air_stone:
    public stone
  {
     DECLARE_BASE_ITEM(air_stone);

  public:
    /** \brief The type of the parent class. */
    typedef stone super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  public:
    air_stone( bool can_explose = true );
    ~air_stone();

    void on_enters_layer();
    virtual void progress( bear::universe::time_type elapsed_time);
    virtual void inform_new_stone();
    virtual void inform_no_energy(const monster& attacker);
    virtual void kill();
    virtual bool has_air_power() const;

  protected:
    void air_progress( bear::universe::time_type elapsed_time);
    virtual void create_decorations();
    virtual void initialize_intensity();
    void blast();
    void create_movement();

  private:
    void create_decorative_blast
    (const std::string& anim_name, const bear::universe::speed_type& speed);
    void create_bubble();

    static void init_exported_methods();

  private:
    /** \brief Pointer to the player. */
    player_proxy m_player;

    /** \brief Indicates if the stone blast. */
    bool m_blast;

    /** \brief The reference item for the movement. */
    bear::reference_item* m_reference_item;

    /** \brief Indicates the time since the stone deflates. */
    bear::universe::time_type m_deflate_time;

    /** \brief Indicates if player can explose the stone. */
    bool m_can_explose;

    /** \brief The time over which the stone falls. */
    static const bear::universe::time_type s_fall_time;
  }; // class air_stone
} // namespace ptb

#endif // __PTB_AIR_STONE_HPP__
