/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A bonus that Plee can take by slaping.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_BONUS_BOX_HPP__
#define __PTB_BONUS_BOX_HPP__

#include "ptb/item_brick/base_bonus.hpp"
#include "ptb/item_brick/counted_item.hpp"

namespace ptb
{
  /**
   * \brief A bonus box.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class bonus_box:
    public counted_item<base_bonus>
  {
    DECLARE_BASE_ITEM(bonus_box);

  public:
    /** \brief The type of the parent class. */
    typedef counted_item<base_bonus> super;

  public:
    bonus_box();

    void pre_cache();

  private:
    std::string get_picture_filename() const;
    std::string get_picture_name() const;
    std::string get_notification_text() const;
    unsigned int get_points() const;

    void collision_check_and_apply
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    void create_broken_bonus_box();
    void create_broken_glass(bool left_orientation);

    void do_set_type(base_bonus_type t);
    void create_honeypot_decoration();
    void send_thief_notification(unsigned int index);
  }; // class bonus_box
} // namespace ptb

#endif // __PTB_BONUS_BOX_HPP__
