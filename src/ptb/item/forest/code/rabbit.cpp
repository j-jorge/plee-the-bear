/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the ptb::rabbit class.
 * \author Sébastien Angibaud
 * \author Julien Jorge
 */
#include "ptb/item/forest/rabbit.hpp"

#include "ptb/game_variables.hpp"
#include "ptb/item/floating_score.hpp"
#include "ptb/item/stone/stone.hpp"

#include "engine/layer/layer.hpp"
#include "engine/world.hpp"
#include "engine/export.hpp"

#include <claw/assert.hpp>

BASE_ITEM_EXPORT( rabbit, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::rabbit::rabbit()
  : sniffable("rabbit"), 
    m_progress(NULL), m_max_distance(500), m_injured(false),
    m_opacity_effect_duration(0), m_has_carrot(false), 
    m_remaining_action_time(0), m_marionette(false)
{
  set_z_fixed(false);
  set_mass(10);
  set_density(2);
  set_friction(0.9);
  set_can_move_items(false);
} // rabbit::rabbit()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::rabbit::pre_cache()
{
  get_level_globals().load_model("model/forest/rabbit.cm");
} // rabbit::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::rabbit::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor( get_level_globals().get_model("model/forest/rabbit.cm") );
  m_initial_position = get_center_of_mass();
  
  choose_idle_action();
  m_progress = &rabbit::progress_idle;
} // rabbit::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::rabbit::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );

  if ( m_injured && (m_opacity_effect_duration < 1) )
    {
      m_opacity_effect_duration += elapsed_time;
      m_opacity_injured += m_opacity_inc * elapsed_time;

      if ( m_opacity_injured <= 0.3 )
        m_opacity_inc = -m_opacity_inc;
      else if ( m_opacity_injured >= 1 )
        {
          m_opacity_inc = -m_opacity_inc;
          m_opacity_injured = 1;
        }

      get_rendering_attributes().set_opacity(m_opacity_injured);
    }

  if ( m_progress != NULL )
    (this->*m_progress)(elapsed_time);
} // rabbit::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "real".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::rabbit::set_real_field( const std::string& name, double value )
{
  bool ok = true;

  if (name == "rabbit.max_distance")
    m_max_distance = value;
  else
    ok = super::set_real_field(name, value);

  return ok;
} // rabbit::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "bool".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::rabbit::set_bool_field( const std::string& name, bool value )
{
  bool ok = true;

  if (name == "rabbit.is_marionette")
    m_marionette = value;
  else
    ok = super::set_bool_field(name, value);

  return ok;
} // rabbit::set_bool_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item tat he is entering the active region.
 */
void ptb::rabbit::enters_active_region()
{
  if ( get_current_action_name() == "in_burrow" )
    choose_idle_action();
} // rabbit::enters_active_region()

/*----------------------------------------------------------------------------*/
/**
 * \brief Process a collision with an other item.
 * \param that The other item of the collision.
 * \param info Some informations about the collision.
 */
void ptb::rabbit::collision
( bear::engine::base_item& that, bear::universe::collision_info& info )
{
  default_collision(info);

  if ( m_injured || (get_current_action_name() == "in_burrow") )
    return;

  player_proxy p(&that);

  if ( (p != NULL) && (p.get_index() <= 2) )
    {
      if ( is_attacked_by(p) )
        {
          count_me(p.get_index());
          create_floating_score(p.get_index());
	  on_found(p.get_index());
          start_model_action("injured");
        }
      else if ( ( game_variables::get_corrupting_bonus_count() > 0 )
                && ( get_current_action_name() != "eat" ) && !m_has_carrot )
        {
          game_variables::set_corrupting_bonus_count
            (game_variables::get_corrupting_bonus_count() - 1);
          m_has_carrot = true;
        }
    }
  else
    {
      stone* s = dynamic_cast<stone*>(&that);

      if ( s != NULL )
        {
          if ( ( s->get_monster_type() == monster::stone_monster ) &&
               ( ( s->get_monster_index() == 1 ) ||
                 ( s->get_monster_index() == 2 ) ) )
          {
             count_me(s->get_monster_index());
             create_floating_score(s->get_monster_index());
	     s->has_attacked();
	     on_found(s->get_monster_index());
          }

          start_model_action("injured");
        }
    }
} // rabbit::collision()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture filename for counted item class.
 */
std::string ptb::rabbit::get_picture_filename() const
{
  return "gfx/forest/bonus-icons/bonus-icons.png";
} // rabbit::get_picture_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture name for counted item class.
 */
std::string ptb::rabbit::get_picture_name() const
{
  return "rabbit";
} // rabbit::get_picture_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get text for notification.
 */
std::string ptb::rabbit::get_notification_text() const
{
  return "rabbit carnage";
} // rabbit::get_notification_text()

/*----------------------------------------------------------------------------*/
/**
 * \brief Return the number of points of carnage.
 */
unsigned int ptb::rabbit::get_points() const
{
  return 5000;
} // rabit::get_points()

/*----------------------------------------------------------------------------*/
/**
 * \brief Test if a given player attack the rabbit.
 * \param p A pointer on the player.
 */
bool ptb::rabbit::is_attacked_by(const player_proxy& p)
{
  bool result(false);

  if ( p.is_invincible() )
    result = true;
  else if ( p.is_in_offensive_phase() )
    {
      if ( p.get_current_action_name() == "start_cling" )
        result = true;
      else
        {
          bear::engine::model_mark_placement m;

          if ( p.get_mark_placement("hand", m) )
            result = get_bounding_box().includes( m.get_position() );
        }
    }

  return result;
} // rabbit::is_attacked_by()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state idle.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::rabbit::progress_idle( bear::universe::time_type elapsed_time )
{
  if ( m_has_carrot )
    start_model_action("eat");
  else if ( m_injured )
    start_model_action("dig");
  else if ( !test_in_sky() )
    {
      if ( get_speed().x != 0 )
        {
          start_model_action("walk");
          m_progress = &rabbit::progress_walk;
        }
    }
} // rabbit::progress_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state jump.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::rabbit::progress_jump( bear::universe::time_type elapsed_time )
{
  if( get_speed().y < 0 )
    start_model_action("fall");
} // rabbit::progress_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state fall.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::rabbit::progress_fall( bear::universe::time_type elapsed_time )
{
  if ( has_bottom_contact() )
    {
      if ( m_injured )
        start_model_action("dig");
      else if ( m_has_carrot )
        start_model_action("eat");
      else
        choose_idle_action();
    }
  else if( get_speed().y > 0 )
    start_model_action("jump");
} // rabbit::progress_fall()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state eat.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::rabbit::progress_eat( bear::universe::time_type elapsed_time )
{
  // do nothing
} // rabbit::progress_explose()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state dig.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::rabbit::progress_dig( bear::universe::time_type elapsed_time )
{
  // do nothing
} // rabbit::progress_dig()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress in the state in_burrow.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::rabbit::progress_in_burrow( bear::universe::time_type elapsed_time )
{
  // do nothing
} // rabbit::progress_in_burrow()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress the injure.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::rabbit::progress_injured( bear::universe::time_type elapsed_time )
{
  if ( has_bottom_contact() )
    start_model_action("dig");
} // rabbit::progress_injured()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress while walking.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::rabbit::progress_walk( bear::universe::time_type elapsed_time )
{
  if ( !has_bottom_contact() )
    {
      if ( get_speed().y > 0 )
        start_model_action("jump");
      else if ( get_speed().y < 0 )
        start_model_action("fall");
    }
  else if ( m_remaining_action_time >= elapsed_time )
    m_remaining_action_time -= elapsed_time;
  else
    {
      m_remaining_action_time = 0;
      if ( get_speed().x == 0 )
        choose_idle_action();
    }
} // rabbit::progress_walk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start idle state.
 */
void ptb::rabbit::start_idle()
{
  m_progress = &rabbit::progress_idle;
} // rabbit::start_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to fall.
 */
void ptb::rabbit::start_fall()
{
  m_progress = &rabbit::progress_fall;

  set_mark_visibility_in_action( "carrot", m_has_carrot );
} // rabbit::start_fall()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to eat.
 */
void ptb::rabbit::start_eat()
{
  m_has_carrot = false;
  m_progress = &rabbit::progress_eat;
} // rabbit::start_eat()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to dig.
 */
void ptb::rabbit::start_dig()
{
  m_progress = &rabbit::progress_dig;
} // rabbit::start_dig()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to stay in burrow.
 */
void ptb::rabbit::start_in_burrow()
{
  kill();
} // rabbit::start_in_burrow()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to be injured.
 */
void ptb::rabbit::start_injured()
{
  m_injured = true;
  m_opacity_injured = 1;
  m_opacity_inc = 2.8;
  m_opacity_effect_duration = 0;

  add_internal_force( bear::universe::force_type( 0, 500000 ) );

  m_progress = &rabbit::progress_injured;
} // rabbit::start_injured()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to walk.
 */
void ptb::rabbit::start_walk()
{
  if ( m_remaining_action_time > 0 )
    {
      double force(300000);

      if ( get_rendering_attributes().is_mirrored() )
        force = -force;

      add_internal_force( bear::universe::force_type(force, 0) );
    }
} // rabbit::start_walk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Prepare the jump.
 */
void ptb::rabbit::pre_jump()
{
  start_model_action("jump");
} // rabbit::pre_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Walk for a given duration.
 * \param duration The duration.
 */
void ptb::rabbit::walk( bear::universe::time_type duration )
{
  m_remaining_action_time = duration;
  m_progress = &rabbit::progress_walk;
  start_model_action("walk");
} // rabbit::walk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the walk.
 */
void ptb::rabbit::apply_walk()
{
  // action time in (0.5, 1.5)
  walk( 0.5 + ((double)rand() * 1) / RAND_MAX );
} // rabbit::apply_walk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply a jump.
 */
void ptb::rabbit::apply_jump()
{
  bear::universe::force_type force(900000, 750000);

  if ( get_rendering_attributes().is_mirrored() )
    force.x *= -1;

  add_internal_force( force );

  m_progress = &rabbit::progress_jump;
} // rabbit::apply_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Choose an idle action.
 */
void ptb::rabbit::choose_idle_action()
{
  start_model_action("idle_1");
} // rabbit::choose_idle_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Scan if there is a player in a given direction.
 * \param origin The position from which we start watching.
 * \param dir The direction of the scan.
 */
bool ptb::rabbit::scan_no_wall_in_direction
( const bear::universe::position_type& origin,
  const bear::universe::vector_type& dir ) const
{
  if ( get_layer().has_world() )
    {
      bear::universe::item_picking_filter filter;
      filter.set_can_move_items_value(true);
      filter.set_forbidden_position(origin);

      return get_layer().get_world().pick_item_in_direction
        (origin, dir, filter) == NULL;
    }
  else
    return false;
} // rabbit::scan_no_wall_in_direction()

/*---------------------------------------------------------------------------*/
/**
 * \brief Test if the rabbit is in the sky and change state thereof.
 *         Return true if the rabbit is in the sky.
 */
bool ptb::rabbit::test_in_sky()
{
  bool result = false;

  if ( !has_bottom_contact() )
    {
      result = true;

      if( get_speed().y <= 0 )
        start_model_action("fall");
      else
        start_model_action("jump");
    }

  return result;
} // rabbit::test_in_sky()

/*----------------------------------------------------------------------------*/
/**
 * \brief Consider moving or something.
 */
void ptb::rabbit::try_to_move()
{
  if ( !has_bottom_contact() || m_marionette )
    return;

  double p = (double)rand() / RAND_MAX;
  bool idle_fallback(true);

  if ( can_move_forward() )
    {
      if ( p > 0.5 )
        {
          pre_jump();
          idle_fallback = false;
        }
      else if ( p > 0.2 )
        {
          apply_walk();
          idle_fallback = false;
        }
    }

  if ( idle_fallback )
    {
      get_rendering_attributes().mirror
        ( !get_rendering_attributes().is_mirrored() );

      choose_idle_action();
    }
} // rabbit::try_to_move()

/*----------------------------------------------------------------------------*/
/**
 * \brief Test if the rabbit can move forward.
 */
bool ptb::rabbit::can_move_forward() const
{
  // always allow to comme back toward the initial position
  if ( !get_rendering_attributes().is_mirrored()
       && (get_center_of_mass().x < m_initial_position.x) )
    return true;

  if ( get_rendering_attributes().is_mirrored()
       && (get_center_of_mass().x > m_initial_position.x) )
    return true;

  bool result = true;

  const bear::universe::coordinate_type dist =
    m_initial_position.distance(get_center_of_mass());

  if ( dist > m_max_distance )
    {
      if ( get_rendering_attributes().is_mirrored()
           && (get_center_of_mass().x < m_initial_position.x) )
        result = false;

      if ( !get_rendering_attributes().is_mirrored()
           && (get_center_of_mass().x > m_initial_position.x) )
        result = false;
    }

  if ( result )
    {
      bear::universe::vector_type dir(m_max_distance, 0);

      if ( get_rendering_attributes().is_mirrored() )
        dir.x *= -1;

      result = scan_no_wall_in_direction(get_center_of_mass(), dir);
    }

  return result;
} // rabbit::can_move_forward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a floating score.
 * \param index The index of the player.
 */
void ptb::rabbit::create_floating_score( unsigned int index ) const
{
  floating_score* s = new floating_score;

  s->set_z_position( super::get_z_position() + 10 );
  s->set_center_of_mass( super::get_center_of_mass() );
  new_item(*s);

  s->add_points( index, 1 );
} // rabbit::create_floating_score()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::rabbit::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( rabbit, start_idle, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( rabbit, apply_jump, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( rabbit, start_walk, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( rabbit, start_fall, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( rabbit, start_eat, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( rabbit, start_dig, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( rabbit, start_in_burrow, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( rabbit, start_injured, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( rabbit, try_to_move, void );

  TEXT_INTERFACE_CONNECT_METHOD_1( rabbit, walk, void,
                                   bear::universe::time_type );
} // rabbit::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::rabbit )
