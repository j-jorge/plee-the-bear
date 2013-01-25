/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing an item that has an attack point.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_ITEM_WITH_ATTACK_POINT_HPP__
#define __PTB_ITEM_WITH_ATTACK_POINT_HPP__

#include "ptb/item_brick/with_attack_point.hpp"

namespace ptb
{
  /**
   * \brief The class describing an item that has an attack point.
   *
   * \b Template \b arguments :
   *  - \a Base the base class of the model, should end by
   *    bear::engine::base_item.
   *
   * \author Sébastien Angibaud
   */
  template<class Base>
  class item_with_attack_point :
    public Base,
    public with_attack_point
  {
  public:
    /** \brief The type of the parent class. */
    typedef Base super;

  public:
    virtual bear::universe::position_type get_attack_point() const;
    virtual bool has_attack_point() const;
  }; // class item_with_attack_point
} // namespace ptb

#include "ptb/item_brick/impl/item_with_attack_point.tpp"

#endif // __PTB_ITEM_WITH_ATTACK_POINT_HPP__
