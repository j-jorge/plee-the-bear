/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A corrupting bonus. Get a lot of them to avoid fighting the boss.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_CORRUPTING_BONUS_HPP__
#define __PTB_CORRUPTING_BONUS_HPP__

#include "engine/base_item.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/item_brick/item_with_decoration.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief A corrupting bonus. Get a lot of them to avoid fighting the boss.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class corrupting_bonus:
    public bear::engine::item_with_decoration
      < bear::engine::basic_renderable_item<bear::engine::base_item> >
  {
    DECLARE_BASE_ITEM(corrupting_bonus);

  public:
    /** \brief The type of the parent class. */
    typedef
    bear::engine::item_with_decoration
      < bear::engine::basic_renderable_item<bear::engine::base_item> > super;

  public:
    corrupting_bonus();

    void pre_cache();
    void attract(bear::universe::physical_item& attractor);

  private:
     void collision_check_and_apply
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    virtual void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void create_decoration();
    void create_floating_score(unsigned int index);
    void give_corrupting_bonus();

  private:
    /** \brief Indicates if the bonus is already given. */
    bool m_bonus_given;
  }; // class corrupting_bonus
} // namespace ptb

#endif // __PTB_CORRUPTING_BONUS_HPP__
