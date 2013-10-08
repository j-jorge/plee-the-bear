/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An honeypot. If Plee finds five honeypots, he wins a life.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_HONEYPOT_HPP__
#define __PTB_HONEYPOT_HPP__

#include "ptb/item_brick/sniffable.hpp"

#include "engine/base_item.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/item_brick/item_with_decoration.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An honeypot. If Plee finds five honeypots, he wins a life.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class honeypot:
    public bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item<bear::engine::base_item> >,
    public sniffable
  {
    DECLARE_BASE_ITEM(honeypot);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item<bear::engine::base_item> > super;

  public:
    honeypot();

    void pre_cache();
    void build();

  private:
     void collision_check_and_apply
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    virtual void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void give_life(unsigned int index) const;
    void create_decoration();
    void create_level_bonus(const std::string& name);
    void send_notification(unsigned int index);

  private:
    /** \brief Indicates if the honeypot is already given. */
    bool m_given;

    /** \brief The identifier of the honeypot. */
    unsigned int m_id;
  }; // class honeypot
} // namespace ptb

#endif // __PTB_HONEYPOT_HPP__
