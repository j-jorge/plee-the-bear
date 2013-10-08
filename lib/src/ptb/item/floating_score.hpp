/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief An item that display a score given to a player.
 * \author Angibaud Sebastien
 */
#ifndef __PTB_FLOATING_SCORE_HPP__
#define __PTB_FLOATING_SCORE_HPP__

#include "generic_items/decorative_item.hpp"

#include "engine/export.hpp"

#include <claw/tween/single_tweener.hpp>

namespace ptb
{
  /**
   * \brief An item that display a score given to a player.
   * \author Julien Jorge
   */
  class floating_score:
    public bear::decorative_item
  {
    DECLARE_BASE_ITEM(floating_score);

  public:
    /** \brief The type of the parent class. */
    typedef bear::decorative_item super;

  public:
    floating_score();

    void pre_cache();

    void build();
    
    void add_points
    ( unsigned int player_index, unsigned int score, 
      bool display_star = false );
    void one_up( unsigned int player_index );
    void set_score( const std::string& text);
    
  private:
    void create_effect(bear::engine::base_item* item);
    void give_one_up_to( unsigned int player_index ) const;
    void create_star();

  }; // class floating_score
} // namespace ptb

#endif // __PTB_FLOATING_SCORE_HPP__
