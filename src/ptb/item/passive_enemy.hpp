/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a passive enemy.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_PASSIVE_ENEMY_HPP__
#define __PTB_PASSIVE_ENEMY_HPP__

#include "ptb/item_brick/monster_item.hpp"
#include "generic_items/block.hpp"
#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief The class describing a passive enemy.
   *
   * The valid fields for this item are
   *  - \a type_right_side: \c (string) The type of right side
   * possible values: inactive, solid, attack.
   *  - \a type_left_side: \c (string) The type of left side
   * possible values: inactive, solid, attack.
   *  - \a type_bottom_side: \c (string) The type of bottom side
   * possible values: inactive, solid, attack.
   *  - \a type_top_side: \c (string) The type of top side
   * possible values: inactive, solid, attack.
   *
   * \author Sébastien Angibaud
   */
  class passive_enemy:
    public monster_item< bear::block >
  {
    DECLARE_BASE_ITEM(passive_enemy);

  public:
    /** \brief The type of the parent class. */
    typedef monster_item< bear::block > super;

  public:
     enum side_type
      {
        inactive_type = 0,
        attack_type
      }; // enum side_type

  public:
    passive_enemy();

    void collision( bear::engine::base_item& that,
        bear::universe::collision_info& info );

    bool set_string_field( const std::string& name, const std::string& value );
    bool is_valid() const;

  private:
    bool set_side_type(side_type& side, const std::string& value);

  private:
    /* \brief The type of the right side. */
    side_type m_right_side_type;

    /* \brief The type of the left side. */
    side_type m_left_side_type;

    /* \brief The type of the top side. */
    side_type m_top_side_type;

    /* \brief The type of the bottom side. */
    side_type m_bottom_side_type;
  }; // class passive_enemy
} // namespace ptb

#endif // __PTB_PASSIVE_ENEMY_HPP__
