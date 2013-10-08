/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The base of a monster.
 * \author Sebastien Angibaud
 */
#ifndef __PTB_MONSTER_HPP__
#define __PTB_MONSTER_HPP__

#include "ptb/item_brick/vulnerable.hpp"

#include "universe/types.hpp"
#include "universe/collision_info.hpp"
#include "engine/base_item.hpp"

#include <vector>
#include <string>

namespace ptb
{
  /**
   * \brief The different type of monster.
   */
  class monster:
    public vulnerable
  {
  public:
     /** \brief The different categories of monster. */
    enum monster_type
      {
        player_monster = 0,
        enemy_monster,
        stone_monster,
        nature_monster
      }; // enum monster_type

    enum attack_type
      {
        normal_attack = 0,
        water_attack,
        fire_attack,
        air_attack,
        indefensible_attack
      }; // enum attack_type

    /** \brief The number of attacks. */
    static const unsigned int s_attack_count;

    /** \brief Duration of injured state. */
    static const double s_injured_duration;

  public:
    monster();
    virtual ~monster();

    virtual void set_invincible(const bool invincible);
    bool is_invincible() const;
    void set_offensive_phase(const bool offensive_phase);
    bool get_offensive_phase() const;

    virtual bool attack( bear::engine::base_item& that ) = 0;
    bool receive_an_attack
    ( bear::engine::base_item& attacker, bear::universe::zone::position side );

    // The full namespace is used for the return type to ease the automatic
    // generation of the player_proxy class
    void set_defensive_power(ptb::monster::attack_type index, bool statut);
    bool get_defensive_power(ptb::monster::attack_type index) const;
    void set_offensive_coefficient
    (ptb::monster::attack_type index, unsigned int coef);

    // The full namespace is used for the return type to ease the automatic
    // generation of the player_proxy class
    ptb::monster::monster_type get_monster_type() const;
    void set_monster_type(ptb::monster::monster_type m);

    unsigned int get_monster_index() const;
    void set_monster_index(unsigned int index);
    double get_energy() const;
    void set_energy(double energy);
    double get_max_energy() const;
    void set_max_energy(double energy);
    bool is_injured() const;
    virtual bool is_in_offensive_phase() const;
    bool is_vulnerable( monster& attacker ) const;
    bool is_stone_vulnerable() const;

  protected:
    void to_string( std::string& str ) const;
    virtual void injure
    (const monster& attacker, bear::universe::zone::position side,
     double duration);
    virtual void finish_injure();
    virtual void has_attacked(const monster& other);
    virtual bool get_defensive_power_by_side
    ( unsigned int index, const monster& attacker,
      bear::universe::zone::position side ) const;
    virtual unsigned int get_offensive_coefficient
    ( unsigned int index, const monster& attacker,
      bear::universe::zone::position side ) const;
    virtual void remove_energy(const monster& attacker, double energy );
    void set_stone_vulnerability(bool vulnerable);

  private:
    bool player_is_vulnerable( monster& attacker) const;
    bool stone_is_vulnerable( monster& attacker) const;

    bool receive_an_attack
    ( monster& attacker, bear::universe::zone::position side );

  protected:
    /** \brief Force of attack. */
    unsigned int m_offensive_force;

    /** \brief Remaining energy of the monster. */
    double m_energy;

    /** \brief The initial energy of the monster. */
    double m_max_energy;

    /** \brief Indicate if the monster is in an offensive phase. */
    bool m_offensive_phase;

    /** \brief The vector of defensive powers. */
    std::vector<bool> m_defensive_powers;

    /** \brief The vector of the offensive coefficients. */
    std::vector<unsigned int> m_offensive_coefficients;

    /** \brief Indicates if the monster is invincible. */
    bool m_invincible;

    /** \brief Indicates if the monster is vulnerable for stones. */
    bool m_is_stone_vulnerable;

    /** \brief Which kind of monster am I ? */
    monster_type m_monster_type;

    /** \brief The monster index : for player and stone */
    unsigned int m_monster_index;

    /** \brief Indicates if the monster is injured. */
    bool m_is_injured;

    /** \brief Indicates the time of the attack. */
    bear::universe::time_type m_injured_time;

  }; // class monster
} // namespace ptb

#endif // __PTB_MONSTER_HPP__
