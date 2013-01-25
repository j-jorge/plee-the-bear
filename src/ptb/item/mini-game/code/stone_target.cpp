/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::stone_target class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/mini-game/stone_target.hpp"
#include "ptb/item/floating_score.hpp"
#include "ptb/item/stone/stone.hpp"
#include "engine/variable/variable.hpp"
#include "engine/level.hpp"

BASE_ITEM_EXPORT( stone_target, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::stone_target::stone_target()
  : m_hit(false), m_current_animation(&m_hit_animation), m_started(false)
{
  set_phantom(true);
  set_can_move_items(false);
  set_weak_collisions(true);
} // stone_target::stone_target()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::stone_target::pre_cache()
{
  get_level_globals().load_sound("sound/crack.ogg");
} // stone_target::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type visual::animation.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 *
 * Valid values for the \a name and \a value parameters are :
 *  - "animation", visual::animation
 *  - anything supported by the parent class
 */
bool ptb::stone_target::set_animation_field
( const std::string& name, const bear::visual::animation& value )
{
  bool ok = true;

  if (name == "stone_target.starting_animation")
    m_starting_animation = value;
  else  if (name == "stone_target.hit_animation")
    m_hit_animation = value;
  else
    ok = super::set_animation_field(name, value);

  return ok;
} // stone_target::set_animation_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do one step in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::stone_target::progress( bear::universe::time_type elapsed_time )
{
  super::progress(elapsed_time);

  if ( m_current_animation->is_valid() )
    m_current_animation->next(elapsed_time);

  if ( !m_started )
    if ( has_forced_movement() )
      {
        // The target becomes a real enemy so the stones can attack him.
        m_monster_type = monster::enemy_monster;
        m_started = true;
      }

  if ( m_started )
    if ( !has_forced_movement() )
      {
        if ( !m_hit )
          get_level().set_level_variable
              ( bear::engine::variable<unsigned int>
                ( "stone_target", get_stone_target(false)+1 ) );

        m_hit = true;
      }
} // stone_target::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::stone_target::on_enters_layer()
{
  super::on_enters_layer();

  m_monster_type = monster::nature_monster;
  m_energy = 1;
  m_offensive_force = 0;
  m_defensive_powers[normal_attack] = true;

  m_current_animation = &m_starting_animation;
} // stone_target::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the sprite representing the item.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void ptb::stone_target::get_visual
( std::list<bear::engine::scene_visual>& visuals ) const
{
  super::get_visual( visuals );

  add_visual( *m_current_animation, visuals );
} // stone_target::get_visual()

/*----------------------------------------------------------------------------*/
/**
 * \brief Kill the item.
 * \pre m_owner != NULL
 */
void ptb::stone_target::kill()
{
  if ( !m_hit )
    get_level().set_level_variable
      ( bear::engine::variable<unsigned int>
        ( "stone_target", get_stone_target(false)+1 ) );

  m_hit = true;
  super::kill();
} // stone_target::kill()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the collision is with a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::stone_target::collision_check_and_apply
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  stone* s = dynamic_cast<stone*>(&that);

  if ( s != NULL  )
    {
      if ( ( !m_hit ) && has_forced_movement() )
        {
          s->has_attacked(*this);
          clear_forced_movement();
          fix();
          m_current_animation = &m_hit_animation;
          m_current_animation->reset();
          m_hit = true;

          get_level().set_level_variable
            ( bear::engine::variable<unsigned int>
              ( "stone_target", get_stone_target(false)+1 ) );

          get_level().set_level_variable
            ( bear::engine::variable<unsigned int>
              ( "hit_stone_target", get_stone_target(true)+1 ) );

          create_floating_score();
          create_decoration();
          get_level_globals().play_sound
            ( "sound/crack.ogg",
              bear::audio::sound_effect(get_center_of_mass()) );
        }
      else
        default_collision(info);
    }
  else
    default_collision(info);
} // stone_target::collision_check_and_apply()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_apply().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::stone_target::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_and_apply(that, info);
} // stone_target::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a floating score.
 */
void ptb::stone_target::create_floating_score()
{
  floating_score* s = new floating_score;

  s->set_z_position( super::get_z_position() + 10000 );
  s->set_center_of_mass( super::get_center_of_mass() );
  new_item(*s);

  std::ostringstream oss;
  oss << get_stone_target(true) << "/" << get_stone_target(false);

  s->set_score( oss.str() );
  s->get_rendering_attributes().set_intensity(1, 1, 0);
} // stone_target::create_floating_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the number of stone target.
 * \param hit Indicates if we count only hit target.
 */
unsigned int ptb::stone_target::get_stone_target(bool hit) const
{
  if ( hit )
    {
      bear::engine::variable<unsigned int> var("hit_stone_target");

      if ( get_level().level_variable_exists(var) )
        {
          get_level().get_level_variable(var);
          return var.get_value();
        }
      else
        return 0;
    }
  else
    {
      bear::engine::variable<unsigned int> var("stone_target");

      if ( get_level().level_variable_exists(var) )
        {
          get_level().get_level_variable(var);
          return var.get_value();
        }
      else
        return 0;
    }
} // stone_target::get_stone_target()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a decoration.
 */
void ptb::stone_target::create_decoration()
{
  bear::decorative_item* item = new bear::decorative_item;

  bear::engine::level_globals& glob = get_level_globals();

  item->set_sprite(glob.auto_sprite
                   ("gfx/mini-game/stones/target.png", "broken top"));

  item->set_z_position(get_z_position()+10000);
  item->set_mass(1);
  item->set_density(0.5);
  item->get_rendering_attributes().mirror
    (get_rendering_attributes().is_mirrored());
  item->get_rendering_attributes().flip
    (get_rendering_attributes().is_flipped());
  item->set_angular_speed(0.3);
  item->set_system_angle_as_visual_angle(true);

  new_item( *item );
  CLAW_ASSERT( item->is_valid(),
                 "The decoration of stone target isn't correctly initialized" );

  item->set_top_middle(get_top_middle());
  double r1=(double)rand()/(double)RAND_MAX;
  double r2=(double)rand()/(double)RAND_MAX;
  item->add_external_force
    (bear::universe::force_type(200*(r1-0.5), 200*(r2)));
} // stone_target::create_decoration()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell is the item has a defensive power.
 * \param index Index of the power.
 * \param attacker The attacker.
 * \param side The side on which the power is checked.
 */
bool ptb::stone_target::get_defensive_power
( unsigned int index, const monster& attacker,
    bear::universe::zone::position side ) const
{
  return m_hit || !has_forced_movement();
} // stone_target::get_defensive_power()
