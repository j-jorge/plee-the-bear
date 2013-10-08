/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The base class for the items that can be attacked.
 */
#ifndef __PTB_VULNERABLE_HPP__
#define __PTB_VULNERABLE_HPP__

#include "universe/collision_info.hpp"
#include "engine/base_item.hpp"

namespace ptb
{
  /**
   * \brief The base class for the items that can be attacked.
   */
  class vulnerable
  {
  public:
    /**
     * \brief Processes an attack sent by another item.
     * \param attacker The item who's attacking us.
     * \param side The side on which he is attacking.
     * \return true if this has been effectively attacked.
     */
    virtual bool receive_an_attack
    ( bear::engine::base_item& attacker,
      bear::universe::zone::position side ) = 0;

  }; // class vulnerable
} // namespace ptb

#endif // __PTB_VULNERABLE_HPP__
