/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::little_plee class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/little_plee.hpp"

#include "ptb/item/floating_score.hpp"
#include "ptb/util/player_util.hpp"

#include "engine/layer/layer.hpp"
#include "engine/level.hpp"
#include "engine/level_globals.hpp"
#include "engine/world.hpp"
#include "universe/derived_item_handle.hpp"

#include "engine/export.hpp"

BASE_ITEM_EXPORT( little_plee, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::little_plee::little_plee()
  : m_current_state(run_state), m_life_given(false), m_nb_idle(0)
{
  set_mass( 100 );
  set_density(2);
  set_z_fixed(false);
} // little_plee::little_plee()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::little_plee::pre_cache()
{
  super::pre_cache();

  get_level_globals().load_model("model/little_plee.cm");
} // little_plee::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::little_plee::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor( get_level_globals().get_model("model/little_plee.cm") );
  start_model_action("run");
} // little_plee::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::little_plee::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  if ( is_in_environment(bear::universe::water_environment)  )
    {
      // little_plee walks on water
      if ( get_speed().y <= 0 )
        set_speed(bear::universe::speed_type(get_speed().x, 0));

      set_contact_friction(0.95);
      set_bottom_contact(true);

      if ( get_layer().has_world() )
        {
          bear::universe::force_type force
            (- get_mass() * get_layer().get_world().get_gravity());

          if ( (get_density() != 0) &&
               ( get_mass() != std::numeric_limits<double>::infinity() )  )
            force += get_layer().get_world().get_gravity() * get_mass() *
              get_layer().get_world().get_average_density
              (get_bounding_box()) / get_density();

          add_external_force(force);
        }
    }

  if ( m_current_state == run_state )
    progress_run();
  else
    progress_jump();
} // little_plee::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::little_plee::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  if ( m_life_given )
    return;

  player_proxy p(&that);

  if ( p != NULL )
    {
      floating_score* s = new floating_score;

      new_item(*s);

      s->set_z_position( get_z_position() + 10 );
      s->set_center_of_mass( get_center_of_mass() );

      s->one_up( p.get_index() );

      m_life_given = true;
      kill();
    }
} // little_plee::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the orientation of the item.
 * \param orientation The new orientation on x axis.
 */
void ptb::little_plee::set_positive_orientation(bool orientation)
{
  get_rendering_attributes().mirror(orientation);
} // little_plee::set_positive_orientation()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start the action.
 */
void ptb::little_plee::start()
{
  do_jump();
} // little_plee::start()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a progress when the item run.
 */
void ptb::little_plee::progress_run()
{
  if ( has_bottom_contact() )
    {
      if ( has_right_contact() || has_left_contact() )
        {
          ++m_nb_idle;
          if ( m_nb_idle >= 2 )
            progress_idle();
        }
      else
        {
          if ( !can_go_toward(get_rendering_attributes().is_mirrored()) )
            get_rendering_attributes().mirror
              ( !get_rendering_attributes().is_mirrored() );

          if ( get_rendering_attributes().is_mirrored() )
            add_internal_force( bear::universe::force_type(-250000, 0) );
          else
            add_internal_force( bear::universe::force_type(250000, 0) );
        }
    }
  else
    {
      m_current_state = jump_state;
      start_model_action("jump");
    }
} // little_plee::progress_run()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a progress when the item jump.
 */
void ptb::little_plee::progress_jump()
{
  if ( has_bottom_contact() )
    {
      m_current_state = run_state;
      start_model_action("run");
    }
  else
    {
      if ( get_rendering_attributes().is_mirrored() )
        add_internal_force( bear::universe::force_type(-100000, 0) );
      else
        add_internal_force( bear::universe::force_type(100000, 0) );

      if ( get_speed().y < 0 )
        start_model_action("fall");
    }
} // little_plee::progress_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do a jump.
 */
void ptb::little_plee::do_jump()
{
  if ( get_rendering_attributes().is_mirrored() )
    add_internal_force( bear::universe::force_type(-4000000, 7500000) );
  else
    add_internal_force( bear::universe::force_type(4000000, 7500000) );
} // little_plee::do_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress when the item is stopped.
 */
void ptb::little_plee::progress_idle()
{
  bool direction_change = false;
  m_nb_idle = 0;
  unsigned int a = (unsigned int)(2.0 * rand() / RAND_MAX);

  if ( a == 0 )
    {
      if ( has_right_contact() && can_go_toward(true) )
        {
          direction_change = true;
          get_rendering_attributes().mirror(true);
          add_internal_force( bear::universe::force_type(-250000, 0) );
        }

      if ( has_left_contact() && can_go_toward(false) )
        {
          direction_change = true;
          get_rendering_attributes().mirror(false);
          add_internal_force( bear::universe::force_type(250000, 0) );
        }
    }

  if ( !direction_change )
    do_jump();
} // little_plee::progress_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Compute if the item can go toward a given orientation.
 */
bool ptb::little_plee::can_go_toward( bool left_orientation )
{
  bool result = true;
  unsigned int closest = 0;
  bear::universe::coordinate_type dist = 1000;

  const player_proxy p1 = util::find_player( get_level_globals(), 1 );
  const player_proxy p2 = util::find_player( get_level_globals(), 2 );

  if ( p1 != NULL )
    {
      closest = 1;
      dist = p1.get_center_of_mass().distance(get_center_of_mass());
    }

  if ( p2 != NULL )
    {
      bear::universe::coordinate_type dist2 =
        p2.get_center_of_mass().distance(get_center_of_mass());
      if ( (closest == 0) || ((closest == 1) && (dist2 < dist)) )
        {
          closest = 2;
          dist = dist2;
        }
    }

  if ( dist <= 250 )
    {
      if ( closest == 1 )
        {
          if ( left_orientation )
            result = ( p1.get_left() > get_right() );
          else
            result = ( p1.get_right() < get_left() );
        }
      else
        {
          if ( closest == 2 )
            {
              if ( left_orientation )
                result = ( p2.get_left() > get_right() );
              else
                result = ( p2.get_right() < get_left() );
             }
        }
    }

  return result;
} // little_plee::can_go_toward()
