/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An hazelnut. Bring it to the owl to enter the secret level.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_AZELNUT_HPP__
#define __PTB_AZELNUT_HPP__

#include "ptb/item_brick/sniffable.hpp"

#include "engine/base_item.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/item_brick/item_with_decoration.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An hazelnut. Bring it to the owl to enter the secret level.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class hazelnut:
    public bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item<bear::engine::base_item> >,
    public sniffable
  {
    DECLARE_BASE_ITEM(hazelnut);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item<bear::engine::base_item> > super;

  public:
    hazelnut();

    void pre_cache();
    void build();
    void progress( bear::universe::time_type elapsed_time );

  private:
     void collision_check_and_apply
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    virtual void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );
    void create_level_bonus();
    void send_notification(unsigned int index);
  }; // class hazelnut
} // namespace ptb

#endif // __PTB_AZELNUT_HPP__
