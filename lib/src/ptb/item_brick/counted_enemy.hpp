/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing an enemy.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_COUNTED_ENEMY_HPP__
#define __PTB_COUNTED_ENEMY_HPP__

#include "ptb/item_brick/counted_item.hpp"
#include "ptb/item_brick/base_enemy.hpp"

namespace ptb
{
  /**
   * \brief The class describing an enemy that is counted. 
   * This class automatically inherit from
   *        ptb::counted_enemy
   *        ptb::base_enemy
   *
   * \b Template \b arguments : 
   *  - \a score: the score given when the enemy dies. 
   *  - \a Base the base class of the enemy. 
   *
   * \author Sébastien Angibaud 
   */ 
  template<class Base>
  class counted_enemy:
    public counted_item< base_enemy<Base> >
  {
  public:
    /** \brief The type of the parent class. */
    typedef counted_item< base_enemy<Base> > super;
    
  public:
    void on_enters_layer();
    void count_me(unsigned int index);
    void die(const monster& attacker);

  protected:
    void on_die(unsigned int index);
  
  private:
    unsigned int get_total_enemy_count() const;
    unsigned int get_found_enemy_count() const;
    unsigned int get_points() const;
  }; // class counted_enemy
} // namespace ptb

#include "ptb/item_brick/impl/counted_enemy.tpp"

#endif // __PTB_COUNTED_ENEMY_HPP__
