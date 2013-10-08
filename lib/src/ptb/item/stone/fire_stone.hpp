/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a stone with fire power.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_FIRE_STONE_HPP__
#define __PTB_FIRE_STONE_HPP__

#include "ptb/item/stone/stone.hpp"

namespace ptb
{
  /**
   * \brief The class describing a stone with the fire power.
   * \author Sébastien Angibaud
   */
  class fire_stone:
    public stone
  {
    DECLARE_BASE_ITEM(fire_stone);

  public:
    /** \brief The type of the parent class. */
    typedef stone super;

  public:
    fire_stone();

    virtual void progress( bear::universe::time_type elapsed_time );
    virtual void on_enters_layer();
    void has_attacked(const monster& other);
    void inform_no_energy(const monster& attacker);
    virtual bool has_fire_power() const;

  private:
    void create_smoke(const bear::visual::animation& anim);

  protected:
    void progress_fire_stone( bear::universe::time_type elapsed_time );

  private:
    /* \brief The time since the last smoke. */
    bear::universe::time_type m_last_smoke;

    /* \brief Indicates if the stone is extinct. */
    bool m_is_extinct;
  }; // class fire_stone
} // namespace ptb

#endif // __PTB_FIRE_STONE_HPP__
