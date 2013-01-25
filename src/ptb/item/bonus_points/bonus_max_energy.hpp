/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An item that adds points if the bonus max_energy has been found.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_BONUS_MAX_ENERGY_HPP__
#define __PTB_BONUS_MAX_ENERGY_HPP__

#include "ptb/item/bonus_points/bonus_points.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that adds points if the bonus max_energy has been found.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class bonus_max_energy:
    public bonus_points
  {
    DECLARE_BASE_ITEM(bonus_max_energy);

  public:
    /** \brief The type of the parent class. */
    typedef bonus_points super;

  public:
    bonus_max_energy();

    void build();

  private:
    bool check() const;

  private:
    /* \brief Indicates if the bonus has already found at the item creation. */
    bool m_already_found;
  }; // class bonus_max_energy
} // namespace ptb

#endif // __PTB_BONUS_MAX_ENERGY_HPP__
