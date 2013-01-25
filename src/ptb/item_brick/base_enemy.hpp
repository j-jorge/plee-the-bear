/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing an enemy.
 * \author Sébastien Angibaud
 */
#ifndef __PTB_BASE_ENEMY_HPP__
#define __PTB_BASE_ENEMY_HPP__

#include "ptb/item_brick/sniffable.hpp"
#include "ptb/item_brick/monster_item.hpp"

namespace ptb
{
  /**
   * \brief The class describing an enemy. This class automatically inherit from
   *        ptb::monster_item.
   *
   * \b Template \b arguments :
   *  - \a score: the score given when the enemy dies.
   *  - \a Base the base class of the enemy.
   *
   * \author Sébastien Angibaud
   */
  template<class Base>
  class base_enemy:
    public monster_item< Base >,
    public sniffable
  {
  public:
    /** \brief The type of the parent class. */
    typedef monster_item< Base > super;

  public:
    base_enemy();

    virtual bool set_u_integer_field
    ( const std::string& name, unsigned int value );
    virtual void get_visual
    ( std::list<bear::engine::scene_visual>& visuals ) const;

    void create_headstone
    ( const bear::universe::position_type& bottom_middle_pos,
      const bear::visual::animation& soul_anim,
      unsigned int soul_energy, unsigned int pos_z);

    void create_floating_score( unsigned int index ) const;
    virtual bool is_in_offensive_phase() const;
    virtual void die(const monster& attacker);
    
  protected:
    virtual void on_die(unsigned int index);

  private:
    /** \brief The score to give when this enemy dies. */
    unsigned int m_score;
  }; // class base_enemy
} // namespace ptb

#include "ptb/item_brick/impl/base_enemy.tpp"

#endif // __PTB_BASE_ENEMY_HPP__
