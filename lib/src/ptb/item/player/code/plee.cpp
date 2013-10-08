/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::plee class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/player/plee.hpp"
#include "generic_items/decorative_item.hpp"

BASE_ITEM_EXPORT( plee, ptb )

/*----------------------------------------------------------------------------*/
const bear::universe::coordinate_type
ptb::plee::s_vertical_jump_force = 8500000;

const double ptb::plee::s_mass = 100;
const double ptb::plee::s_density = 1.5;

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::plee::plee()
  : super( get_physics() )
{
  set_mass(s_mass);
  set_density(s_density);
  set_size( 50, 110 );
} // plee::plee()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::plee::pre_cache()
{
  super::pre_cache();

  // plee
  get_level_globals().load_model("model/player/plee.cm");
  get_level_globals().load_model("model/player/plee-alt.cm");

  // halo for soul
  get_level_globals().load_image("gfx/plee/misc.png");

  // Bath cap
  get_level_globals().load_animation("animation/plee/bath-cap.canim");
} // plee::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do post creation actions.
 */
void ptb::plee::on_enters_layer()
{
  super::on_enters_layer();

  if ( get_index() == 1)
    set_model_actor( get_level_globals().get_model("model/player/plee.cm") );
  else
    set_model_actor
      ( get_level_globals().get_model("model/player/plee-alt.cm") );

  start_action_model("idle");

  m_wait_state_number = 3;
  m_has_main_hat = true;
  m_has_hat = true;
} // plee::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Get the impulse force for vertical jumps.
 */
bear::universe::coordinate_type
ptb::plee::get_vertical_jump_force() const
{
  return s_vertical_jump_force;
} // plee::get_vertical_jump_force()

/*---------------------------------------------------------------------------*/
/**
 * \brief Progress in the water.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::plee::progress_in_water(bear::universe::time_type elapsed_time)
{
  super::progress_in_water(elapsed_time);

  if ( m_has_main_hat )
    take_out_hat();
} // plee::progress_in_water()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration when the player stay in the state idle.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::plee::progress_continue_idle
( bear::universe::time_type elapsed_time )
{
  if ( get_current_action_name() != "take_hat" )
    {
      if ( !m_has_hat )
        start_action_model("take_hat");
      else if ( ( !m_has_main_hat ) &&
                ( !is_in_environment(bear::universe::water_environment) ) )
        start_action_model("take_hat");
    }
} // plee::progress_continue_idle()

/*---------------------------------------------------------------------------*/
/**
 * \brief Get the sprite of the soul.
 */
bear::visual::sprite ptb::plee::get_soul_sprite() const
{
  return bear::visual::sprite
    ( get_level_globals().auto_sprite("gfx/plee/misc.png", "soul effet"));
} // plee::get_soul_sprite()

/*----------------------------------------------------------------------------*/
/**
 * \brief Plee starts to take a new hat.
 */
void ptb::plee::start_take_hat()
{
  if ( !m_has_hat )
    {
      if ( is_in_environment(bear::universe::water_environment) )
        set_global_substitute
          ("new_hat", new bear::visual::animation
           (get_level_globals().get_animation
            ("animation/plee/bath-cap.canim") ) );
      else
        set_global_substitute
            ("new_hat", new bear::visual::animation
             (get_level_globals().get_animation("animation/plee/cap.canim")) );
    }
  else if ( ( !m_has_main_hat ) &&
            ( !is_in_environment(bear::universe::water_environment) ) )
    set_global_substitute
        ("new_hat", new bear::visual::animation
         ( get_level_globals().get_animation("animation/plee/cap.canim") ) );
  else
    set_global_substitute("new_hat", new bear::visual::animation() );
} // plee::start_take_hat()

/*----------------------------------------------------------------------------*/
/**
 * \brief Plee takes a new hat.
 */
void ptb::plee::take_new_hat()
{
  if ( !m_has_hat )
    {
      m_has_hat = true;

      if ( is_in_environment(bear::universe::water_environment) )
        set_global_substitute
          ("hat", new bear::visual::animation
           (get_level_globals().get_animation
            ("animation/plee/bath-cap.canim") ) );
      else
        {
          m_has_main_hat = true;
          set_global_substitute
            ("hat", new bear::visual::animation
             (get_level_globals().get_animation("animation/plee/cap.canim")) );
        }
    }
  else if ( ( !m_has_main_hat ) &&
            ( !is_in_environment(bear::universe::water_environment) ) )
    {
      m_has_main_hat = true;
      m_has_hat = true;
      set_global_substitute
        ("hat", new bear::visual::animation
         ( get_level_globals().get_animation("animation/plee/cap.canim") ) );
    }
} // plee::take_new_hat()

/*----------------------------------------------------------------------------*/
/**
 * \brief Take out the hat.
 */
void ptb::plee::take_out_hat()
{
  bear::engine::model_mark_placement m;

  if ( get_mark_placement("hat", m) )
    {
      m_has_main_hat = false;
      m_has_hat = false;

      bear::universe::position_type pos( m.get_position() );
      bear::decorative_item* item;
      item = new bear::decorative_item();

      bear::visual::sprite spr =
        get_action(get_current_action_name())->get_mark
        (m.get_mark_id()).get_main_animation()->get_sprite();

      spr.combine( get_rendering_attributes() );
      item->set_sprite(spr);

      item->set_z_position(get_z_position() + m.get_depth_position());
      item->set_phantom(false);
      item->set_can_move_items(false);
      item->set_artificial(true);
      item->set_kill_when_leaving(true);
      item->set_density(0.4);
      item->set_mass(2);

      new_item( *item );

      item->set_center_of_mass(pos);

      set_global_substitute
        ("hat", new bear::visual::animation() );
    }
} // plee::take_out_hat()

/*----------------------------------------------------------------------------*/
/**
 * \brief Gets the physics constants defining the behavior of this player.
 */
ptb::player_physics ptb::plee::get_physics() const
{
  player_physics result;

  result.move_force_in_idle = 200000;
  result.move_force_in_jump = 100000;
  result.move_force_in_vertical_jump = 50000;
  result.move_force_in_run = 300000;
  result.move_force_in_swimming = 80000;
  result.min_move_force_in_walk = 70000;
  result.max_move_force_in_walk = 300000;
  result.jump_force = 5200000;
  result.jump_force_in_float = 11500000;
  result.speed_to_run = 580;
  
  return result;
} // plee::get_physics()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::plee::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( plee, take_new_hat, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( plee, start_take_hat, void );
} // plee::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::plee )
