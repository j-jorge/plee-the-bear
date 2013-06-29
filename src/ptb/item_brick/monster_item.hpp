/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a monster (an item with energy).
 * \author Sébastien Angibaud
 */
#ifndef __PTB_MONSTER_ITEM_HPP__
#define __PTB_MONSTER_ITEM_HPP__

#include "ptb/item_brick/monster.hpp"
#include "ptb/item_brick/item_with_attack_point.hpp"
#include "engine/base_item.hpp"
#include "universe/collision_info.hpp"

namespace ptb
{
  /**
   * \brief The class describing a monster (an item with energy).
   *
   * \b Template \b arguments :
   *  - \a Base the base class of the model, should end by
   *    bear::engine::base_item and contain bear::engine::basic_renderable_item.
   *
   * \author Sébastien Angibaud
   */
  template<class Base>
  class monster_item :
    public item_with_attack_point<Base>,
    public monster
  {
  public:
    /** \brief The type of the parent class. */
    typedef item_with_attack_point<Base> super;

  public:
    monster_item();
    monster_item( const std::string& model_file );

    virtual void pre_cache();
    virtual void progress( bear::universe::time_type elapsed_time );
    virtual void on_enters_layer();

    bool set_u_integer_field( const std::string& name, unsigned int value );
    bool set_real_field( const std::string& name, double value );
    bool set_bool_field( const std::string& name, bool value );
    bool set_string_field( const std::string& name, const std::string& value );

    virtual bool has_attack_point() const;

    bool attack( bear::engine::base_item& that );
    bool attack
    ( bear::engine::base_item& that, bear::universe::zone::position side );

    virtual void create_hit_star( const bear::engine::base_item& that ) const;
    void set_top_unvulnerability(bool b);
    void set_bottom_unvulnerability(bool b);
    void set_left_unvulnerability(bool b);
    void set_right_unvulnerability(bool b);

  protected:
    void to_string( std::string& str ) const;

    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );
    bool collision_and_attack
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

    virtual void remove_energy( const monster& attacker, double energy );
    virtual void inform_no_energy(const monster& attacker);

    virtual void injure
    ( const monster& attacker, bear::universe::zone::position side,
      double duration );
    virtual void finish_injure();
    bear::universe::position_type get_stone_vulnerability_position() const;
    virtual bool get_defensive_power_by_side
    ( unsigned int index, const monster& attacker,
      bear::universe::zone::position side ) const;

    void create_hit_star
    ( const bear::universe::position_type& pos, double angle ) const;

    void create_hit_star
    ( const bear::engine::base_item& ref,
      const bear::engine::base_item& that ) const;

    void play_hit_sound( const bear::universe::position_type& pos ) const;

  private:
    /** \brief Transparency of injured frame. */
    double m_opacity_injured;

    /** \brief Increment for the transparency when injured. */
    double m_opacity_inc;

    /** \brief Duration of injured state. */
    double m_injured_duration;

    /** \brief Indicates if the monster is unvulnerable on the top side. */
    bool m_top_unvulnerability;

    /** \brief Indicates if the monster is unvulnerable on the top side. */
    bool m_bottom_unvulnerability;

    /** \brief Indicates if the monster is unvulnerable on the top side. */
    bool m_left_unvulnerability;

    /** \brief Indicates if the monster is unvulnerable on the top side. */
    bool m_right_unvulnerability;
  }; // class monster_item
} // namespace ptb

#include "ptb/item_brick/impl/monster_item.tpp"

#endif // __PTB_MONSTER_ITEM_HPP__
