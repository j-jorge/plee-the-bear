/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::base_enemy class.
 * \author Sébastien Angibaud
 */

#include "ptb/item_brick/base_enemy.hpp"

#include "ptb/item/headstone.hpp"
#include "ptb/item/floating_score.hpp"
#include "ptb/level_variables.hpp"

#include "engine/base_item.hpp"
#include "visual/scene_line.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
template<class Base>
ptb::base_enemy<Base>::base_enemy()
  : sniffable("enemy"), m_score(1000)
{

} // base_enemy::base_enemy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type \c unsigned \c integer.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
template<class Base>
bool ptb::base_enemy<Base>::set_u_integer_field
( const std::string& name, unsigned int value )
{
  bool result = true;

  if ( name == "base_enemy.score" )
    m_score = value;
  else
    result = super::set_u_integer_field(name, value);

  return result;
} // base_enemy::set_u_integer_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the sprite representing the item.
 * \param visuals (out) The sprites of the item, and their positions.
 */
template<class Base>
void
ptb::base_enemy<Base>::get_visual
( std::list<bear::engine::scene_visual>& visuals ) const
{
  super::get_visual(visuals);
  
  if ( monster::is_injured() )
    {
      std::vector<bear::visual::position_type> p;
      p.resize(2);

      p[0].x = this->get_horizontal_middle()-25;
      p[0].y = this->get_top() + 20;
      p[1].x = p[0].x + 50;
      p[1].y = p[0].y;

      bear::engine::scene_visual scene
        ( bear::visual::scene_line(0, 0, claw::graphic::red_pixel, p, 2),
          this->get_z_position()-1 );

      visuals.push_back( scene );

      p[0].x = this->get_horizontal_middle()-25;
      p[0].y = this->get_top() + 20;
      p[1].x = p[0].x +
        50 * monster::get_energy() / monster::get_max_energy();
      p[1].y = p[0].y;

      bear::engine::scene_visual scene2
        ( bear::visual::scene_line(0, 0, claw::graphic::green_pixel, p, 2),
          this->get_z_position() );

      visuals.push_back( scene2 );
    }
} // base_enemy::get_visual()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create an headstone.
 */
template<class Base>
void ptb::base_enemy<Base>::create_headstone
( const bear::universe::position_type& bottom_middle_pos,
  const bear::visual::animation& soul_anim,
  unsigned int soul_energy,
  unsigned int pos_z)
{
  headstone* new_headstone = new headstone;

  new_headstone->set_soul_animation(soul_anim);
  new_headstone->set_bottom_middle
    ( bottom_middle_pos + bear::universe::position_type(0, 2) );
  new_headstone->set_soul_energy(soul_energy);
  new_headstone->set_z_position(pos_z );

  CLAW_ASSERT( new_headstone->is_valid(),
               "The headstone of wasp isn't correctly initialized" );

  super::new_item( *new_headstone );
} // base_enemy::create_headstone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a floating score.
 * \param index The index of the player.
 */
template<class Base>
void ptb::base_enemy<Base>::create_floating_score
( unsigned int index ) const
{
  floating_score* s = new floating_score;

  super::new_item(*s);

  s->set_z_position( super::get_z_position() + 10 );
  s->set_center_of_mass( super::get_center_of_mass() );

  s->add_points( index, m_score, true );
} // base_enemy::create_floating_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if the monster is in a offensive phase.
 */
template<class Base>
bool ptb::base_enemy<Base>::is_in_offensive_phase() const
{
  return super::is_in_offensive_phase() && ( !super::is_injured() );
} // base_enemy::is_in_offensive_phase()

/*----------------------------------------------------------------------------*/
/**
 * \brief The enemy dies.
 * \param attacker The attacker monster.
 */
template<class Base>
void ptb::base_enemy<Base>::die(const monster& attacker)
{
  super::set_mass(0.1);
  super::set_offensive_phase(false);
  
  if ( ( ( attacker.get_monster_type() == monster::player_monster ) ||
         ( attacker.get_monster_type() == monster::stone_monster ) ) &&
       ( ( attacker.get_monster_index() == 1 ) ||
         ( attacker.get_monster_index() == 2 ) ) )
    this->on_die(attacker.get_monster_index());
  else
    {
      this->on_die(1);
      this->on_die(2);
    }
} // base_enemy::die()

/*----------------------------------------------------------------------------*/
/**
 * \brief Function tell when the enemy dies.
 * \param index Index of player that kills the enemy.
 */
template<class Base>
void ptb::base_enemy<Base>::on_die(unsigned int index)
{
  create_floating_score(index);
  on_found(index);
} // base_enemy::on_die
