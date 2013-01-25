/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief An item that adds points if the mini-game has been unlocked.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_BONUS_MINI_GAME_HPP__
#define __PTB_BONUS_MINI_GAME_HPP__

#include "ptb/item/bonus_points/bonus_points.hpp"

#include "engine/export.hpp"

namespace ptb
{
  /**
   * \brief An item that adds points if the mini-game has been unlocked.
   *
   * The valid fields for this item are
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class bonus_mini_game:
    public bonus_points
  {
    DECLARE_BASE_ITEM(bonus_mini_game);

  public:
    /** \brief The type of the parent class. */
    typedef bonus_points super;

  public:
    bonus_mini_game();

    void build();

  private:
    bool check() const;

  private:
    /* \brief Indicates if the mini-game has already been unlocked. */
    bool m_already_unlocked;
  }; // class bonus_mini_game
} // namespace ptb

#endif // __PTB_BONUS_MINI_GAME_HPP__
