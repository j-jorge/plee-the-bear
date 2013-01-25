/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a stone with the air and fire powers.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_AIR_FIRE_STONE_HPP__
#define __PTB_AIR_FIRE_STONE_HPP__

#include "ptb/player_proxy.hpp"
#include "ptb/item/stone/fire_stone.hpp"
#include "generic_items/reference_item.hpp"

namespace ptb
{
  /**
   * \brief The class describing a stone with the air and fire powers.
   * \author Sébastien Angibaud
   */
  class air_fire_stone:
    public fire_stone
  {
     DECLARE_BASE_ITEM(air_fire_stone);

  public:
    /** \brief The type of the parent class. */
    typedef fire_stone super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  public:
    air_fire_stone();
    ~air_fire_stone();

    virtual void progress( bear::universe::time_type elapsed_time);
    void on_enters_layer();
    virtual void inform_new_stone();
    virtual void kill();
    virtual void inform_no_energy(const monster& attacker);
    virtual bool has_air_power() const;

  private:
    void blast();
    void create_decorations();
    void create_decorative_blast
    (const std::string& action, const bear::universe::speed_type& speed);
    void create_movement();

    static void init_exported_methods();

  private:
    /** \brief Pointer to the player. */
    player_proxy m_player;

    /** \brief Indicates if the stone blast. */
    bool m_blast;

    /** \brief The reference item for the movement. */
    bear::reference_item* m_reference_item;

  }; // class air_fire_stone
} // namespace ptb

#endif // __PTB_AIR_FIRE_STONE_HPP__
