/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the ptb::wasp class.
 * \author Sébastien Angibaud
 */
#include "ptb/item/forest/wasp.hpp"

#include "ptb/item/headstone.hpp"
#include "ptb/item/forest/sting.hpp"
#include "ptb/util/player_util.hpp"

#include "engine/export.hpp"
#include "engine/game.hpp"
#include "visual/sprite.hpp"
#include "universe/forced_movement/forced_translation.hpp"

#include "engine/world.hpp"

#include <claw/assert.hpp>

BASE_ITEM_EXPORT( wasp, ptb )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
ptb::wasp::wasp()
  : m_progress(NULL), m_is_in_attack(false), m_come_back(false),
    m_oscillation_angle(0), m_fly_time(0), m_have_attacked(false),
    m_contact(false), m_first_target(0, 0), m_second_target(0, 0),
    m_translation(0, 0), m_fly_duration(0)
{
  set_z_fixed(false);

  m_monster_type = monster::enemy_monster;
  m_energy = 10;
  m_offensive_force = s_wasp_offensive_force;
  m_offensive_coefficients[normal_attack] = 1;
  get_rendering_attributes().mirror(false);
  set_category("wasp");
} // wasp::wasp()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void ptb::wasp::pre_cache()
{
  get_level_globals().load_animation("animation/forest/wasp/wasp_soul.canim");
  get_level_globals().load_animation
    ("animation/forest/wasp/sting_explosion.canim");
  get_level_globals().load_model("model/forest/sting.cm");
  get_level_globals().load_model("model/forest/wasp.cm");
  get_level_globals().load_model("model/headstone.cm");
  get_level_globals().load_sound("sound/sting.ogg");
} // wasp::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialise the item.
 */
void ptb::wasp::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor(get_level_globals().get_model("model/forest/wasp.cm"));
  m_first_target = get_center_of_mass();
  m_second_target = m_translation + m_first_target;
  start_fly();
  search_players();
} // wasp::on_enters_layer()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::wasp::progress( bear::universe::time_type elapsed_time )
{
  super::progress( elapsed_time );
  search_players();

  (this->*m_progress)( elapsed_time );
} // wasp::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type "real".
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool ptb::wasp::set_real_field
( const std::string& name, double value )
{
  bool ok = true;

  if (name == "wasp.translation.x")
    m_translation.x = value;
  else if (name == "wasp.translation.y")
    m_translation.y = value;
  else if (name == "wasp.fly_duration")
    {
      m_fly_duration = value;
      if ( m_fly_duration <= 0 )
        m_fly_duration = std::numeric_limits<double>::infinity();
    }
  else
    ok = super::set_real_field(name, value);

  return ok;
} // wasp::set_real_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item that he have no energy now.
 * \param attacker The attacker monster.
 */
void ptb::wasp::inform_no_energy(const monster& attacker)
{
  m_is_injured = false;

  if ( get_current_action_name() != "dead" )
    {
      start_dead();
      die(attacker);
    }
} // wasp::inform_no_energy()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the item tat he left the active region.
 */
void ptb::wasp::leaves_active_region()
{
  super::leaves_active_region();

  if ( get_current_action_name() == "dead" )
    kill();
} // wasp::leaves_active_region()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture filename for counted item class.
 */
std::string ptb::wasp::get_picture_filename() const
{
  return "gfx/forest/bonus-icons/bonus-icons.png";
} // wasp::get_picture_filename()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get picture name for counted item class.
 */
std::string ptb::wasp::get_picture_name() const
{
  return "wasp";
} // wasp::get_picture_name()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get text for notification.
 */
std::string ptb::wasp::get_notification_text() const
{
  return "wasp carnage";
} // wasp::get_notification_text()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state fly.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::wasp::progress_fly
( bear::universe::time_type elapsed_time )
{
  if( !m_have_attacked && scan_players() )
    {
      // we start an offensive
      m_have_attacked = true;
      start_attack();
    }
  else
    {
      m_fly_time += elapsed_time;
      if ( m_fly_time >= m_fly_duration)
        m_fly_time = m_fly_duration;

      if ( m_come_back )
        next_position(m_second_target, m_first_target);
      else
        next_position(m_first_target, m_second_target);

      if( m_fly_time == m_fly_duration)
        {
          m_come_back = !m_come_back;
          m_fly_time = 0;
          m_have_attacked = false;
          oriente();
        }
    }
} // wasp::progress_fly()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state attack.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::wasp::progress_attack
( bear::universe::time_type elapsed_time )
{
  // The model does all.
} // wasp::progress_attack()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state dead.
 * \param elapsed_time Elapsed time since the last call.
 */
void ptb::wasp::progress_dead
( bear::universe::time_type elapsed_time )
{
  if ( has_bottom_contact() )
    {
      bear::visual::animation soul_anim
        ( get_level_globals().get_animation
          ("animation/forest/wasp/wasp_soul.canim") );
      soul_anim.mirror(get_rendering_attributes().is_mirrored());

      create_headstone
        ( get_bottom_middle(), soul_anim, s_soul_energy,
          get_z_position() - 2 );
      kill();
    }
  else
    get_rendering_attributes().set_angle
      ( get_rendering_attributes().get_angle() - 0.2 );
} // wasp::progress_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of the state fly.
 */
void ptb::wasp::start_fly()
{
  start_model_action("fly");
  m_progress = &wasp::progress_fly;
  oriente();
} // wasp::start_fly()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of the state attack.
 */
void ptb::wasp::start_attack()
{
  start_model_action("attack");
  m_progress = &wasp::progress_attack;
} // wasp::start_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialization of the state dead.
 */
void ptb::wasp::start_dead()
{
  if ( get_current_action_name() != "dead" )
    {
      start_model_action("dead");
      m_progress = &wasp::progress_dead;
    }
} // wasp::start_dead()

/*----------------------------------------------------------------------------*/
/**
 * \brief Oriente the wasp.
 */
void ptb::wasp::oriente()
{
  if ( m_translation.x != 0 )
    {
      if ( m_come_back )
        get_rendering_attributes().mirror
          (m_first_target.x <= m_second_target.x);
      else
        get_rendering_attributes().mirror
          (m_first_target.x > m_second_target.x);
    }
} // wasp::oriente()

/*---------------------------------------------------------------------------*/
/**
 * \brief Go to the next position.
 *  \param origin The origin position.
 *  \param target The target position.
 */
void ptb::wasp::next_position
( bear::universe::position_type& origin,
  bear::universe::position_type& target)
{
  bear::universe::position_type position;

  position.x =
    origin.x + ( ( target.x - origin.x ) * m_fly_time ) /  m_fly_duration;

  position.y =
    origin.y + ( ( target.y - origin.y ) * m_fly_time ) /  m_fly_duration;

  m_oscillation_angle += ( 3.14 / 12 );
  if ( m_oscillation_angle >= 6.28 )
    m_oscillation_angle -= 6.28;

  position.y += ( (sin(m_oscillation_angle)) * 15);

  set_top_left( position  + get_top_left() - get_center_of_mass() );
} // wasp::next_position()

/*---------------------------------------------------------------------------*/
/**
 * \brief Test if the player is in the accesive zone.
 * \param pos Position of the player.
 */
bool ptb::wasp::player_in_zone
( const bear::universe::position_type& pos ) const
{
  bear::universe::speed_type vect(get_center_of_mass(), pos);

  if ( get_rendering_attributes().is_mirrored() )
    if ( ( vect.x > ( 3 * vect.y ) ) && ( vect.x < 0 ) &&
       vect.length() < 400 )
      return true;
    else
      return false;
  else
    if ( ( vect.x > 0 ) && ( vect.x < ( -3 * vect.y ) ) &&
       vect.length() < 400 )
      return true;
    else
      return false;
} // wasp::player_in_zone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Create a sting.
 */
void ptb::wasp::create_sting()
{
  bear::engine::model_mark_placement m;

  if ( get_mark_placement("sting", m) )
    {
      const bear::universe::position_type pos(m.get_position());
      bear::universe::speed_type speed;

      speed.x = 600*std::cos(m.get_angle());
      speed.y = 600*std::sin(m.get_angle());

      sting* new_sting = new sting;

      new_sting->set_forced_movement
        ( bear::universe::forced_translation(speed) );

      CLAW_ASSERT(new_sting->is_valid(),
                  "The sting isn't correctly initialized" );

      new_item( *new_sting );

      new_sting->set_center_of_mass(pos);
      new_sting->set_z_position( m.get_depth_position() );
      new_sting->get_rendering_attributes().set_angle(m.get_angle());
    }
} // wasp::create_sting()

/*---------------------------------------------------------------------------*/
/**
 * \brief Test if there is a player in the accesive zone.
 */
bool ptb::wasp::scan_players() const
{
  bool result = false;

  if(m_first_player != NULL)
    result =
      player_in_zone(m_first_player.get_center_of_mass());

  if( !result && (m_second_player != NULL) )
    result =
      player_in_zone(m_second_player.get_center_of_mass());

  return result;
} // wasp::scan_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Search players.
 */
void ptb::wasp::search_players()
{
  if ( m_first_player == NULL )
    m_first_player = util::find_player( get_level_globals(), 1 );

  if ( m_second_player == NULL )
    m_second_player = util::find_player( get_level_globals(), 2 );
} // wasp::search_players()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void ptb::wasp::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::wasp, create_sting, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( ptb::wasp, start_fly, void );
} // wasp::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( ptb::wasp )
