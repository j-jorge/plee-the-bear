/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::monster_item class.
 * \author Sébastien Angibaud
 */

#include "ptb/item/stone/stone.hpp"
#include "ptb/item_brick/monster.hpp"
#include "ptb/player_proxy.hpp"

#include "generic_items/star.hpp"
#include "generic_items/decorative_effect.hpp"
#include "generic_items/delayed_kill_item.hpp"

#include "universe/zone.hpp"

#include <claw/logger.hpp>
#include <sstream>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
template<class Base>
ptb::monster_item<Base>::monster_item()
  : m_opacity_injured(1), m_opacity_inc(-0.02),
    m_top_unvulnerability(false), m_bottom_unvulnerability(false),
    m_left_unvulnerability(false), m_right_unvulnerability(false)
{
  this->set_can_move_items(false);
} // monster_item::monster_item()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
template<class Base>
void ptb::monster_item<Base>::pre_cache()
{
  super::pre_cache();

  this->get_level_globals().load_sound("sound/hit.ogg");
} // monster_item::pre_cache()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
template<class Base>
void ptb::monster_item<Base>::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  if ( m_is_injured )
    {
      m_injured_time += elapsed_time;
      if ( m_injured_time >= m_injured_duration )
        finish_injure();
      else
        {
          m_opacity_injured += m_opacity_inc;

          if ( m_opacity_injured <= 0.3 )
            m_opacity_inc = 0.02;
          else if ( m_opacity_injured >= 1 )
            {
              m_opacity_inc = -0.02;
              m_opacity_injured = 1;
            }

          this->get_rendering_attributes().set_opacity(m_opacity_injured);
        }
    }
} // monster_item::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do post creation actions.
 */
template<class Base>
void ptb::monster_item<Base>::on_enters_layer()
{
  super::on_enters_layer();

  m_max_energy = m_energy;
} // monster_item::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c unsigned \c integer.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
template<class Base>
bool ptb::monster_item<Base>::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result = true;

  if ( name == "monster_item.offensive_strength" )
    m_offensive_force = value;
  else if ( name == "monster_item.offensive_coefficient.normal" )
    set_offensive_coefficient(normal_attack, value);
  else if ( name == "monster_item.offensive_coefficient.air" )
    set_offensive_coefficient(air_attack, value);
  else if ( name == "monster_item.offensive_coefficient.fire" )
    set_offensive_coefficient(fire_attack, value);
  else if ( name == "monster_item.offensive_coefficient.water" )
    set_offensive_coefficient(water_attack, value);
  else if ( name == "monster_item.offensive_coefficient.indefensible" )
    set_offensive_coefficient(indefensible_attack, value);
  else
    result = super::set_u_integer_field(name, value);

  return result;
} // monster_item::set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c real.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
template<class Base>
bool ptb::monster_item<Base>::set_real_field
( const std::string& name, double value )
{
  bool ok = true;

  if (name == "monster_item.energy")
    set_energy(value);
  else
    ok = super::set_real_field(name, value);

  return ok;
} //  monster_item::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c bool.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
template<class Base>
bool ptb::monster_item<Base>::set_bool_field
( const std::string& name, bool value )
{
  bool ok = true;

  if (name == "monster_item.defensive_power.normal")
    set_defensive_power(normal_attack, value);
  else if (name == "monster_item.defensive_power.air")
    set_defensive_power(air_attack, value);
  else if (name == "monster_item.defensive_power.fire")
    set_defensive_power(fire_attack, value);
  else if (name == "monster_item.defensive_power.water")
    set_defensive_power(water_attack, value);
  else
    ok = super::set_bool_field(name, value);

  return ok;
} // monster_item::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c string.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
template<class Base>
bool ptb::monster_item<Base>::set_string_field
( const std::string& name, const std::string& value )
{
  bool result = true;

  if ( name == "monster_item.monster_type" )
    {
      if ( value == "player" )
        m_monster_type = player_monster;
      else if ( value == "enemy" )
        m_monster_type = enemy_monster;
      else if ( value == "stone" )
        m_monster_type = stone_monster;
      else if ( value == "nature" )
        m_monster_type = nature_monster;
      else
        {
          claw::logger << claw::log_warning
                       << "monster_item::set_string_field(): '" << name
                       << "' does not accept " << value << std::endl;
          result = false;
        }
    }
  else
    result = super::set_string_field(name, value);

  return result;
} // monster_item::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the value returned by get_attack_point() is meaningful.
 */
template<class Base>
bool ptb::monster_item<Base>::has_attack_point() const
{
  return this->get_monster_type() != monster::nature_monster;
} // monster_item::has_attack_point()

/*----------------------------------------------------------------------------*/
/**
 * \brief Attack an other item.
 * \param that The item to attack.
 */
template<class Base>
bool ptb::monster_item<Base>::attack( bear::engine::base_item& that )
{
  return attack
      ( that,
          bear::universe::zone::find
          ( that.get_bounding_box(), this->get_bounding_box() ) );
} // monster_item::attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Attack an other item.
 * \param that The item to attack.
 * \param side The side of this with which the attack is done.
 */
template<class Base>
bool ptb::monster_item<Base>::attack
( bear::engine::base_item& that, bear::universe::zone::position side )
{
  bool result = false;

  if ( is_in_offensive_phase() || m_invincible )
    {
      monster* other = dynamic_cast<monster*>(&that);

      if (other != NULL)
        {
          result = other->receive_an_attack(*this, side);

          if( result )
            create_hit_star( that );
        }
    }

  return result;
} // monster_item::attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a star to show a hit.
 * \param that The item being attacked by this.
 */
template<class Base>
void ptb::monster_item<Base>::create_hit_star
( const bear::engine::base_item& that ) const
{
  create_hit_star( *this, that );
} // monster_item::create_hit_star()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if the monster is unvulnerable on the bottom side.
 * \param b The new unvulnerability status.
 */
template<class Base>
void ptb::monster_item<Base>::set_bottom_unvulnerability(bool b)
{
  m_bottom_unvulnerability = b;
} // monster_item::set_bottom_unvulnerability()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if the monster is unvulnerable on the left side.
 * \param b The new unvulnerability status.
 */
template<class Base>
void ptb::monster_item<Base>::set_left_unvulnerability(bool b)
{
  m_left_unvulnerability = b;
} // monster_item::set_left_unvulnerability()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if the monster is unvulnerable on the right side.
 * \param b The new unvulnerability status.
 */
template<class Base>
void ptb::monster_item<Base>::set_right_unvulnerability(bool b)
{
  m_right_unvulnerability = b;
} // monster_item::set_right_unvulnerability()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give a string representation of the item.
 * \param str (out) The result of the conversion.
 */
template<class Base>
void ptb::monster_item<Base>::to_string( std::string& str ) const
{
  super::to_string(str);
  monster::to_string(str);
} // monster_item::to_string()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
template<class Base>
void ptb::monster_item<Base>::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_and_attack(that, info);
} // monster_item::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision and attack.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
template<class Base>
bool ptb::monster_item<Base>::collision_and_attack
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  if ( attack(that, info.get_collision_side()) )
    return true;
  else
    {
      super::collision(that, info);
      return false;
    }
} // monster_item::collision_and_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief We remove some energy of the item.
 * \param attacker The attacker monster.
 * \param energy The quantity of energy removed.
 */
template<class Base>
void ptb::monster_item<Base>::remove_energy
(const monster& attacker, double energy )
{
  if ( energy >= m_energy )
    m_energy = 0;
  else
    m_energy -= energy;

  if ( m_energy == 0)
    inform_no_energy(attacker);
} // monster_item::remove_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item that he have no energy now.
 * \param attacker The attacker monster.
 */
template<class Base>
void ptb::monster_item<Base>::inform_no_energy(const monster& attacker)
{
  this->kill();
} // monster_item::inform_no_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief The monster is injure.
 * \param attacker The monster attacking me.
 * \param side The side on which I am attacked.
 * \param duration The duration of injured state.
 */
template<class Base>
void ptb::monster_item<Base>::injure
( const monster& attacker, bear::universe::zone::position side,
  double duration )
{
  monster::injure(attacker, side, duration);
  m_injured_duration = duration;
  m_opacity_inc = -0.02;
} // ptb::monster_item::injure()

/*----------------------------------------------------------------------------*/
/**
 * \brief The monster isn't injure any more.
 */
template<class Base>
void ptb::monster_item<Base>::finish_injure()
{
  monster::finish_injure();

  this->get_rendering_attributes().set_opacity(1);
} // ptb::monster_item::finish_injure()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell is the item has a defensive power.
 * \param index Index of the power.
 * \param attacker The attacker.
 * \param side The side on which the power is checked.
 */
template<class Base>
bool ptb::monster_item<Base>::get_defensive_power_by_side
( unsigned int index, const monster& attacker,
  bear::universe::zone::position side ) const
{
  if ( m_defensive_powers[index] )
    return true;
  else if ( side == bear::universe::zone::top_zone )
    {
      if ( this->get_rendering_attributes().is_flipped() )
        return m_bottom_unvulnerability;
      else
        return m_top_unvulnerability;
    }
  else if ( side == bear::universe::zone::bottom_zone )
    {
      if ( this->get_rendering_attributes().is_flipped() )
        return m_top_unvulnerability;
      else
        return m_bottom_unvulnerability;
    }
  else if ( side == bear::universe::zone::middle_left_zone )
    {
      if ( this->get_rendering_attributes().is_mirrored() )
        return m_right_unvulnerability;
      else
        return m_left_unvulnerability;
    }
  else if ( side == bear::universe::zone::middle_right_zone )
    {
      if ( this->get_rendering_attributes().is_mirrored() )
        return m_left_unvulnerability;
      else
        return m_right_unvulnerability;
    }
  else
    return false;
} // monster_item::get_defensive_power_by_side()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if the monster is unvulnerable on the top side.
 * \param b The new unvulnerability status.
 */
template<class Base>
void ptb::monster_item<Base>::set_top_unvulnerability(bool b)
{
  m_top_unvulnerability = b;
} // monster_item::set_top_unvulnerability()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a star to show a hit.
 * \param pos The center of mass of the star.
 * \param angle The angle of the star.
 */
template<class Base>
void ptb::monster_item<Base>::create_hit_star
( const bear::universe::position_type& pos, double angle ) const
{
  bear::star* s =
    new bear::star
    ( 4, 0.35, bear::visual::color_type("#C0C0C0"), 1,
      bear::visual::color_type("#D93C1F") );

  s->set_size(20, 20);
  s->set_z_position( super::get_z_position() + 10 );
  s->set_center_of_mass( pos );
  s->get_rendering_attributes().set_angle(angle);

  this->new_item(*s);

  bear::decorative_effect* decoration_effect = new bear::decorative_effect;

  decoration_effect->set_duration(0.2);
  decoration_effect->set_size_factor(1, 1.1);
  decoration_effect->set_angle_offset(0, 0.2);
  decoration_effect->set_item(s, false);

  this->new_item( *decoration_effect );

  bear::delayed_kill_item* k = new bear::delayed_kill_item();
  k->add_item(s);
  k->set_duration(0.4);
  k->set_center_of_mass( s->get_center_of_mass() );

  this->new_item( *k );

  play_hit_sound( pos );
} // monster_item::create_hit_star()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a star to show a hit at the intersection of two items.
 * \param ref The item to consider as the attacker.
 * \param that The item being attacked by this.
 */
template<class Base>
void ptb::monster_item<Base>::create_hit_star
( const bear::engine::base_item& ref,
  const bear::engine::base_item& that ) const
{
  if ( ref.get_bounding_box().intersects( that.get_bounding_box() ) )
    {
      const bear::universe::rectangle_type r =
        ref.get_bounding_box().intersection( that.get_bounding_box() );

      create_hit_star( r.bottom_left() + r.size() / 2, 0 );
    }
} // monster_item::create_hit_star()

/*----------------------------------------------------------------------------*/
/**
 * \brief Play the sound of a hit.
 * \param pos The position of the sound in the word.
 */
template<class Base>
void ptb::monster_item<Base>::play_hit_sound
( const bear::universe::position_type& pos ) const
{
  bear::audio::sound_effect e;
  e.set_position(pos);

  this->get_level_globals().play_sound("sound/hit.ogg", e);
} // monster_item::play_hit_sound()
