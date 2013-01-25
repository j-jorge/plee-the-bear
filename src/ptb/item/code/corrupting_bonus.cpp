/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::corrupting_bonus class.
 * \author Sebastien Angibaud
 */
#include "ptb/item/corrupting_bonus.hpp"

#include "ptb/player_proxy.hpp"
#include "ptb/item/stone/stone.hpp"
#include "ptb/game_variables.hpp"
#include "ptb/item/floating_score.hpp"
#include "ptb/util/player_util.hpp"

#include "universe/forced_movement/base_reference_point.hpp"
#include "universe/forced_movement/forced_aiming.hpp"

#include "generic_items/decorative_item.hpp"

BASE_ITEM_EXPORT( corrupting_bonus, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Contructor.
 */
ptb::corrupting_bonus::corrupting_bonus()
  : m_bonus_given(false)
{
  set_phantom(true);
  set_can_move_items(false);
  set_weak_collisions(true);
} // corrupting_bonus::corrupting_bonus()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::corrupting_bonus::pre_cache()
{
  get_level_globals().load_animation
    ("animation/corrupting-bonus-disapearing.canim");
  get_level_globals().load_sound("sound/corrupting-bonus.ogg");
} // corrupting_bonus::pre_cache()

/*---------------------------------------------------------------------------*/
/**
 * \brief Inform the corrupting bonus that is attracted.
 * \param attractor The attractor.
 */
void ptb::corrupting_bonus::attract(bear::universe::physical_item& attractor)
{
  if ( !has_forced_movement() )
    {
      set_mass(1);
      set_global(true);

      bear::universe::forced_aiming movement;

      movement.set_max_angle( 0.05 );
      movement.set_acceleration( 1000 );
      movement.set_max_speed( 1000 );
      movement.set_reference_point_on_center( attractor );
      movement.set_item( *this );
      movement.set_auto_remove(true);

      set_forced_movement( movement );
    }
} // corrupting_bonus::attract()

/*----------------------------------------------------------------------------*/
/**
 * \brief Check if the collision is with a player.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::corrupting_bonus::collision_check_and_apply
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  if ( m_bonus_given )
    default_collision(info);
  else
    {
      bool ok(false);
      stone* s = dynamic_cast<stone*>(&that);

      if ( s != NULL )
        {
          ok = true;
          create_floating_score(s->get_monster_index());
        }
      else
        {
          player_proxy p(&that);
          if ( p != NULL )
            {
              ok = true;
              create_floating_score(p.get_index());
            }
        }

      if ( ok )
	give_corrupting_bonus();
      else
        default_collision(info);
    }
} // corrupting_bonus::collision_check_and_apply()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call collision_check_and_apply().
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::corrupting_bonus::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  collision_check_and_apply(that, info);
} // corrupting_bonus::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a decoration.
 */
void ptb::corrupting_bonus::create_decoration()
{
  bear::decorative_item* item = new bear::decorative_item;

  item->set_animation
    (get_level_globals().get_animation
     ("animation/corrupting-bonus-disapearing.canim"));
  item->get_rendering_attributes().set_angle(get_visual_angle());
  item->set_kill_when_finished(true);
  item->set_z_position(get_z_position()-1);

  new_item( *item );

  item->set_center_of_mass(get_center_of_mass());

  CLAW_ASSERT(item->is_valid(),
              "The decoration of corrupting_bonus isn't correctly initialized");
} // corrupting_bonus::create_decoration()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a floating score.
 * \param index The index of the player.
 */
void ptb::corrupting_bonus::create_floating_score
( unsigned int index )
{
  floating_score* s = new floating_score;

  s->set_z_position( super::get_z_position() + 10 );
  s->set_center_of_mass( super::get_center_of_mass() );
  new_item(*s);

  s->add_points( index, 10 );
  s->get_rendering_attributes().set_intensity(1, 1, 0);
} // corrupting_bonus::create_floating_score()
 
/*----------------------------------------------------------------------------*/
/**
 * \brief Give corrupting_bonus
 */
void ptb::corrupting_bonus::give_corrupting_bonus()
{
  create_decoration();
  m_bonus_given = true;
  
  game_variables::set_corrupting_bonus_rate_x
    ( ( get_left() - get_level().get_camera_center().x) /
      get_level().get_camera()->get_width() );
  game_variables::set_corrupting_bonus_rate_y
    ( ( get_bottom() - get_level().get_camera_center().y) /
      get_level().get_camera()->get_height() );

  game_variables::set_corrupting_bonus_count
    (game_variables::get_corrupting_bonus_count() + 1);

  create_decoration();
  get_level_globals().play_sound("sound/corrupting-bonus.ogg");
  kill();
} // corrupting_bonus::give_corrupting_bonus()
