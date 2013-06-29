/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::monster class.
 * \author Sebastien Angibaud
 */
#include "ptb/item_brick/monster.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/level_variables.hpp"
#include "engine/base_item.hpp"
#include "engine/variable/variable.hpp"

#include <iostream>
#include <sstream>
#include <string>

/*----------------------------------------------------------------------------*/
const unsigned int ptb::monster::s_attack_count = 4;
const double ptb::monster::s_injured_duration = 2;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::monster::monster()
  : m_offensive_force(0), m_energy(0), m_max_energy(0),
    m_offensive_phase(true),
    m_defensive_powers(s_attack_count+1, false),
    m_offensive_coefficients(s_attack_count+1, 0), m_invincible(false),
    m_is_stone_vulnerable(true),
    m_monster_index(0), m_is_injured(false)
{
  m_offensive_coefficients[normal_attack] = 1;
} // base_monster::base_monster()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
ptb::monster::~monster()
{

} // base_monster::~base_monster()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the invincible status.
 * \param invincible The new invincible status.
 */
void ptb::monster::set_invincible(const bool invincible)
{
  m_invincible = invincible;
} // monster::set_invincible()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the monster is invincible.
 */
bool ptb::monster::is_invincible() const
{
  return m_invincible;
} // monster::is_invincible()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the offensive phase status.
 * \param offensive_phase The new offensive phase status.
 */
void ptb::monster::set_offensive_phase(const bool offensive_phase)
{
  m_offensive_phase = offensive_phase;
} // monster::set_offensive_phase()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the offensive phase status.
 */
bool ptb::monster::get_offensive_phase() const
{
  return m_offensive_phase;
} // monster::get_offensive_phase()

/*----------------------------------------------------------------------------*/
/**
 * \brief The item receive an attack.
 *
 * \param attacker The monster attacking me.
 * \param side The size of the collision on the attacker.
 */
bool ptb::monster::receive_an_attack
( monster& attacker, bear::universe::zone::position side )
{
  bool result = false;

  if( !m_invincible && !m_is_injured && is_vulnerable(attacker)
      && (get_energy() != 0) )
    {
      double energy = m_energy;

      if ( !attacker.is_invincible()
           || (attacker.get_monster_type() == stone_monster) )
        {
          energy = 0;

          for( unsigned int i=0; i!=m_defensive_powers.size(); ++i )
            if ( !get_defensive_power_by_side
                (i, attacker, bear::universe::zone::opposite_of(side)) )
              energy += attacker.get_offensive_coefficient(i, *this, side);

          energy *= attacker.m_offensive_force;
        }

      if ( energy > 0 )
        {
          result = true;
          injure( attacker, bear::universe::zone::opposite_of(side),
                  s_injured_duration );
          remove_energy(attacker, energy);
          attacker.has_attacked(*this);
        }
    }

  return result;
} // monster::receive_an_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the defensive power status.
 * \param index Type of the considered attack.
 * \param status The new defensive status.
 */
void ptb::monster::set_defensive_power(attack_type index, bool status)
{
  m_defensive_powers[index] = status;
} // monster::set_defensive_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get a given defensive power status.
 * \param index Type of the considered attack.
 */
bool ptb::monster::get_defensive_power(attack_type index) const
{
  return m_defensive_powers[index];
} // monster::get_defensive_power()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set an offensive coefficient.
 * \param index Type of the considered attack.
 * \param coef The new offensive coefficient.
 */
void
ptb::monster::set_offensive_coefficient(attack_type index, unsigned int coef)
{
  m_offensive_coefficients[index] = coef;
} // monster::set_offensive_coefficient()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the type of monster.
 */
ptb::monster::monster_type ptb::monster::get_monster_type() const
{
  return m_monster_type;
} // monster::get_monster_type()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the type of monster.
 */
void ptb::monster::set_monster_type(ptb::monster::monster_type m)
{
  m_monster_type = m;
} // monster::set_monster_type()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the index of monster.
 */
unsigned int ptb::monster::get_monster_index() const
{
  return m_monster_index;
} // monster::get_monser_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the index of monster.
 */
void ptb::monster::set_monster_index(unsigned int index)
{
  m_monster_index = index;
} // monster::set_monster_index()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the energy of the monster.
 */
double ptb::monster::get_energy() const
{
  return m_energy;
} // monster::get_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the energy of the monster.
 * \param energy The new energy.
 */
void ptb::monster::set_energy( double energy )
{
  m_energy = std::min(energy, m_max_energy);
} // monster::set_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the initial energy of the monster.
 */
double ptb::monster::get_max_energy() const
{
  return m_max_energy;
} // monster::get_max_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the maximum energy of the monster.
 * \param energy The new energy.
 */
void ptb::monster::set_max_energy( double energy )
{
  m_max_energy = energy;
  set_energy(m_energy);
} // monster::set_max_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return if te monster is injured.
 */
bool ptb::monster::is_injured() const
{
  return m_is_injured;
} // monster::is_injured()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if the monster is in a offensive phase.
 */
bool ptb::monster::is_in_offensive_phase() const
{
  return m_offensive_phase;
} // monster::is_in_offensive_phase()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the current item is vulnerable to an other item.
 *
 * \param attacker Type of the attacker.
 */
bool ptb::monster::is_vulnerable( monster& attacker) const
{
  bool result = false;

  switch( m_monster_type )
    {
    case nature_monster:
      result = false;
      break;

    case player_monster:
      result = player_is_vulnerable(attacker);
      break;

    case stone_monster:
      result = stone_is_vulnerable(attacker);
      break;

    case enemy_monster:
      if ( attacker.get_monster_type() == stone_monster )
        result = is_stone_vulnerable();
      else
        result = ( attacker.get_monster_type() != enemy_monster );
      break;

    default:
      break;
    }

  return result;
} // monster::is_vulnerable()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if the monster is vulnerable for stones.
 */
bool ptb::monster::is_stone_vulnerable() const
{
  return m_is_stone_vulnerable;
} // monster::is_stone_vulnerable()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give a string representation of the item.
 * \param str (out) The result of the convertion.
 */
void ptb::monster::to_string( std::string& str ) const
{
  std::ostringstream oss;

  oss << "\ntype: ";
  if ( m_monster_type == player_monster )
    oss << "player";
  else if ( m_monster_type == enemy_monster )
    oss << "enemy";
  else if ( m_monster_type == stone_monster )
    oss << "stone";
  else if ( m_monster_type == nature_monster )
    oss << "nature";

  oss << "\nmonster_index:" << m_monster_index;
  oss << "\noffensive_force: " << m_offensive_force;
  oss << "\nenergy: " << m_energy;
  oss << "\noffensive_phase: ";
  if ( m_offensive_phase )
    oss << "true";
  else
    oss << "false";

  oss << "\ndefensive: ";
  std::vector<bool>::const_iterator it;
  for(it = m_defensive_powers.begin(); it != m_defensive_powers.end(); ++it )
    oss << *it << " ";

  oss << "\noffensive_coef: ";
  std::vector<unsigned int>::const_iterator it2;
  for(it2 = m_offensive_coefficients.begin();
      it2 != m_offensive_coefficients.end(); ++it2 )
    oss << *it2 << " ";

  oss << "\ninvincible: ";
  if ( m_invincible )
    oss << "true";
  else
    oss << "false";

  oss << "\ninjured: ";
  if ( m_is_injured )
    oss << "true";
  else
    oss << "false";

  oss << "\n";

  str += oss.str();
} // monster::to_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief The monster is injure.
 * \param attacker The monster attacking me.
 * \param side The side on which I am attacked.
 * \param duration The duration of injured state.
 */
void ptb::monster::injure
( const monster& attacker, bear::universe::zone::position side,
  double duration )
{
  m_is_injured = true;
  m_injured_time = 0;
} // monster::injure()

/*----------------------------------------------------------------------------*/
/**
 * \brief The monster isn't injure any more.
 */
void ptb::monster::finish_injure()
{
  m_is_injured = false;
} // monster::finish_injure()

/*----------------------------------------------------------------------------*/
/**
 * \brief The item has attacked.
 * \param other The monster that is attacked.
 */
void ptb::monster::has_attacked(const monster& other)
{

} // monster::has_attacked()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell is the item has a defensive power.
 * \param index Index of the power.
 * \param attacker The attacker.
 * \param side The side on which the power is checked.
 */
bool ptb::monster::get_defensive_power_by_side
( unsigned int index, const monster& attacker,
  bear::universe::zone::position side ) const
{
  return m_defensive_powers[index];
} // monster::get_defensive_power_by_side()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the offensive coefficient for a given attacked item and a given
 *        side.
 * \param index The index of the coefficient.
 * \param other The attacked monster.
 * \param side The side of this through which the attack is done.
 */
unsigned int ptb::monster::get_offensive_coefficient
( unsigned int index, const monster& other,
  bear::universe::zone::position side ) const
{
  return m_offensive_coefficients[index];
} // monster::get_offensive_coefficient()

/*----------------------------------------------------------------------------*/
/**
 * \brief We remove some energy of the item..
 *
 * \param attacker The attacker monster.
 * \param energy The quantity of energy removed.
 */
void ptb::monster::remove_energy(const monster& attacker, double energy )
{
  if ( energy >= m_energy )
    m_energy = 0;
  else
    m_energy -= energy;
} // monster::remove_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if the item is vulnerable for stone.
 *
 * \param vulnerable The new vulnerability state.
 */
void ptb::monster::set_stone_vulnerability(bool vulnerable)
{
  m_is_stone_vulnerable = vulnerable;
} // monster::set_stone_vulnerability()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the current player is vulnerable to an other item.
 *
 * \param attacker Type of the attacker.
 */
bool ptb::monster::player_is_vulnerable( monster& attacker) const
{
  bool result(false);

  bool friendly(game_variables::get_friendly_fire());
  bear::engine::variable<bool> var("friendly_fire");
  bear::engine::level& lvl =
    dynamic_cast<const bear::engine::base_item*>(this)->get_level();

  if ( lvl.level_variable_exists(var) )
    friendly = level_variables::get_friendly_fire(lvl);

  if ( (m_monster_index == 1) || (m_monster_index == 2) )
    {
      if ( ( ( attacker.get_monster_type() == stone_monster ) ||
             ( attacker.get_monster_type() == player_monster ) ) &&
           ( ( attacker.m_monster_index == 1 ) ||
             ( attacker.m_monster_index == 2 ) ) )
        {
          if ( attacker.m_monster_index != m_monster_index )
            result = friendly;
          else
            result = false;
        }
      else
        result = true;
    }
  else
    result = ( attacker.get_monster_type() != stone_monster ) ||
      ( attacker.m_monster_index != m_monster_index );

  return result;
} // monster::player_is_vulnerable()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the current stone is vulnerable to an other item.
 *
 * \param attacker Type of the attacker.
 */
bool ptb::monster::stone_is_vulnerable( monster& attacker) const
{
  bool result(false);

  bool friendly(game_variables::get_friendly_fire());
  bear::engine::variable<bool> var("friendly_fire");
  bear::engine::level& lvl =
    dynamic_cast<const bear::engine::base_item*>(this)->get_level();

  if ( lvl.level_variable_exists(var) )
    friendly = level_variables::get_friendly_fire(lvl);

  if ( (m_monster_index == 1) || (m_monster_index == 2) )
    {
      if ( ( ( attacker.get_monster_type() == stone_monster ) ||
             ( attacker.get_monster_type() == player_monster ) ) &&
           ( ( attacker.m_monster_index == 1 ) ||
             ( attacker.m_monster_index == 2 ) ) )
        {
          if ( attacker.m_monster_index != m_monster_index )
            result = friendly;
          else
            result = false;
        }
      else
        result = true;
    }
  else
    result = ( ( attacker.get_monster_type() != stone_monster ) &&
               ( attacker.get_monster_type() != player_monster ) ) ||
      ( attacker.m_monster_index != m_monster_index );

  return result;
} // monster::stone_is_vulnerable()

