/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a sting.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_STING_HPP__
#define __PTB_STING_HPP__

#include "engine/base_item.hpp"
#include "ptb/item_brick/monster_item.hpp"
#include "engine/model.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a sting.
   * \author Sébastien Angibaud
   */
  class sting:
    public monster_item< bear::engine::model<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(sting);

  public:
    /** \brief The type of the parent class. */
    typedef monster_item< bear::engine::model<bear::engine::base_item> > super;

    /** \brief The energy of a sting.*/
    static const unsigned int s_sting_energy = 1;

    /** \brief The offensive_force of a sting.*/
    static const unsigned int s_sting_offensive_force = 5;

  public:
    sting();

    void on_enters_layer();
    void progress( bear::universe::time_type elapsed_time );
    void leaves_active_region();

  protected:
    virtual void has_attacked(const monster& other);

  private:
    /** \brief Indicates if the sting is dead. */
    bool m_is_dead;

  }; // class sting
} // namespace ptb

#endif // __PTB_STING_HPP__
