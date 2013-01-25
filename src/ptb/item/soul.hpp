/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The soul appears out of a headstone. The player can take it to get
 *        more energy.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_SOUL_HPP__
#define __PTB_SOUL_HPP__

#include "engine/base_item.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/item_brick/item_with_decoration.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The soul appears out of a headstone. The player can take it to get
   *        more energy.
   * \author Sébastien Angibaud
   */
  class soul:
    public bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(soul);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item<bear::engine::base_item> > super;

  public:
    soul();
    ~soul();

    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void set_energy(double value);

    void leaves_active_region();

  private:
    /** \brief The energy of the soul. */
    double m_energy;

  }; // class soul
} // namespace ptb

#endif // __PTB_SOUL_HPP__
